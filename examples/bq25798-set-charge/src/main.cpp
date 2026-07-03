#include <Arduino.h>
#include <TPS25751.h>
#include <BQ25798/BQ25798.h>

// ---------------------------------------------------------------------------
// BQ25798 guarded charge-enable write demo
//
// Proves the downstream-device WRITE path end-to-end against a real BQ25798 on
// the TPS25751 I2Cc bus, NON-DESTRUCTIVELY and REVERSIBLY:
//
//   1. Read ChargerControl0 (REG0Fh) and capture the original EN_CHG (bit 5)
//      and the full raw byte.
//   2. Toggle EN_CHG via bq.enableCharging(!original) — a one-call
//      read-modify-write that preserves all other bits.
//   3. Read back, assert EN_CHG flipped AND every other bit is unchanged.
//   4. RESTORE the original EN_CHG via bq.enableCharging(original) and read
//      back to confirm the register matches the captured original byte.
//
// Each step is a separate I2Cr/I2Cw 4CC transaction. The TRM mandates >=5 s
// between consecutive same-type commands, so a 5.1 s delay separates every
// transaction.
//
// SAFE: this sketch only toggles and then RESTORES the charger-enable bit. It
// never issues REG_RST and never cuts power. EN_CHG is briefly toggled and
// returned to its original value.
//
// Wiring: BQ25798 on TPS25751 I2Cc bus (7-bit address 0x6B).
// ---------------------------------------------------------------------------

const TPS25751  pd;       // host on the primary I2Ct bus
BQ25798::Device bq(pd);  // typed BQ25798 driver over I2Cr/I2Cw 4CC tasks

// Helper: read ChargerControl0, print it, return the raw byte (or -1 on failure).
static int readControl0Byte(const __FlashStringHelper* label)
{
    Serial.print(F("-- "));
    Serial.print(label);
    Serial.println(F(" --"));
    auto reg = bq.readChargerControl0(/*validate=*/false);
    if (!reg) {
        Serial.println(F("  [I2C read failed]"));
        return -1;
    }
    reg->debugPrint(Serial);
    return reg->raw()[0];
}

void setup()
{
    Serial.begin(115200);
    while (!Serial && millis() < 3000)
    {
        delay(10);
    }

    TPS25751::setDebugLevel(DEBUG_LEVEL_WARN);
    TPS25751::setDebugCategories(DEBUG_CAT_I2C | DEBUG_CAT_TASK);

    Serial.println(F("Initializing TPS25751 host..."));
    pd.begin();

    Serial.println(F("BQ25798 set-charge (guarded write) sketch ready."));
    Serial.println(F("Toggles EN_CHG then restores it (5.1 s between transactions)."));
}

void loop()
{
    Serial.println();
    Serial.println(F("========== BQ25798 EN_CHG write round-trip =========="));

    // --- 1. Read original ---
    int original = readControl0Byte(F("Original ChargerControl0 (REG0Fh)"));
    if (original < 0) {
        Serial.println(F("FAIL: could not read original — aborting round-trip"));
        delay(5100);
        return;
    }
    const bool origEnChg = (original & (1 << 5)) != 0;
    Serial.print(F("  Captured EN_CHG = "));
    Serial.println(origEnChg ? F("1 (charging enabled)") : F("0 (charging disabled)"));
    delay(5100);

    // --- 2. Toggle EN_CHG ---
    Serial.println(F("-- Writing toggled EN_CHG --"));
    if (!bq.enableCharging(!origEnChg)) {
        Serial.println(F("FAIL: enableCharging(toggle) write failed"));
        delay(5100);
        return;
    }
    delay(5100);

    // --- 3. Read back and verify only EN_CHG changed ---
    int toggled = readControl0Byte(F("Toggled ChargerControl0 (REG0Fh)"));
    if (toggled < 0) {
        Serial.println(F("FAIL: could not read back toggled value"));
        delay(5100);
        return;
    }
    const bool toggledEnChg = (toggled & (1 << 5)) != 0;
    const int  otherBitsMask = ~(1 << 5) & 0xFF;
    const bool enChgFlipped  = (toggledEnChg != origEnChg);
    const bool othersIntact  = ((toggled & otherBitsMask) == (original & otherBitsMask));

    Serial.print(F("  EN_CHG flipped:        "));
    Serial.println(enChgFlipped ? F("PASS") : F("FAIL"));
    Serial.print(F("  Other bits unchanged:  "));
    Serial.println(othersIntact ? F("PASS") : F("FAIL"));
    delay(5100);

    // --- 4. Restore original EN_CHG ---
    Serial.println(F("-- Restoring original EN_CHG --"));
    if (!bq.enableCharging(origEnChg)) {
        Serial.println(F("FAIL: enableCharging(restore) write failed"));
        delay(5100);
        return;
    }
    delay(5100);

    int restored = readControl0Byte(F("Restored ChargerControl0 (REG0Fh)"));
    if (restored < 0) {
        Serial.println(F("FAIL: could not read back restored value"));
        delay(5100);
        return;
    }
    const bool fullyRestored = (restored == original);
    Serial.print(F("  Register restored:     "));
    Serial.println(fullyRestored ? F("PASS") : F("FAIL"));

    const bool allPass = enChgFlipped && othersIntact && fullyRestored;
    Serial.print(F("========== round-trip result: "));
    Serial.print(allPass ? F("PASS") : F("FAIL"));
    Serial.println(F(" =========="));
    delay(5100);

    // --- 5. Convenience-setter identity round-trip (non-destructive) ---
    // Re-write the charge-current limit with its OWN current value and confirm
    // the engineering-unit encode path reproduces it (rounded to the 10 mA LSB).
    // This exercises setChargeCurrentLimit()/setMilliamps() without changing the
    // charger's behavior.
    Serial.println(F("-- ICHG convenience-setter identity round-trip --"));
    auto cc = bq.readChargeCurrentLimit(/*validate=*/false);
    if (!cc) {
        Serial.println(F("  [I2C read failed] — skipping ICHG round-trip"));
        delay(5100);
        return;
    }
    const uint16_t origMa = cc->milliamps();
    Serial.print(F("  Original ICHG = "));
    Serial.print(origMa);
    Serial.println(F(" mA"));
    delay(5100);

    if (!bq.setChargeCurrentLimit(origMa)) {
        Serial.println(F("FAIL: setChargeCurrentLimit write failed"));
        delay(5100);
        return;
    }
    delay(5100);

    auto cc2 = bq.readChargeCurrentLimit(/*validate=*/false);
    if (!cc2) {
        Serial.println(F("  [I2C read-back failed]"));
        delay(5100);
        return;
    }
    const uint16_t roundedMa = static_cast<uint16_t>((origMa / 10) * 10);
    const bool ichgMatch = (cc2->milliamps() == roundedMa);
    Serial.print(F("  Read-back ICHG = "));
    Serial.print(cc2->milliamps());
    Serial.print(F(" mA -> "));
    Serial.println(ichgMatch ? F("PASS") : F("FAIL"));
    delay(5100);
}
