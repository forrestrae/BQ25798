#include <Arduino.h>
#include <TPS25751.h>
#include <BQ25798/BQ25798.h>

// ---------------------------------------------------------------------------
// BQ25798 charge configuration read sketch
//
// Reads and debug-prints all Phase-1 charge configuration registers once per
// loop. Each register is a separate I2Cr transaction; the TRM mandates >=5 s
// between consecutive I2Cr commands of the same type, so a 6 s delay is
// inserted between every read.
//
// Registers read:
//   MinimalSystemVoltage (REG00h) — VSYS_MIN limit, 1-byte
//   ChargeVoltageLimit   (REG01h) — CV limit (VREG), 2-byte
//   ChargeCurrentLimit   (REG03h) — CC limit (ICHG), 2-byte
//   InputVoltageLimit    (REG05h) — VINDPM threshold, 1-byte
//   InputCurrentLimit    (REG06h) — IINDPM limit, 2-byte
//   PrechargeControl     (REG08h) — VBAT_LOWV threshold, IPRECHG, 1-byte
//   TerminationControl   (REG09h) — ITERM, REG_RST, 1-byte
//   ChargerControl0–5    (REG0Fh–REG14h) — main charger enable/mode/timer settings
//   NtcControl0–1        (REG17h–REG18h) — NTC thresholds and hysteresis
//   IcoCurrentLimit      (REG19h) — ICO result, 2-byte, read-only
//
// Read-only / non-destructive. validate=false to show raw data even when
// reserved bits are non-zero.
//
// Wiring: BQ25798 on TPS25751 I2Cc bus (7-bit address 0x6B).
// ---------------------------------------------------------------------------

const TPS25751  pd;       // host on the primary I2Ct bus
BQ25798::Device bq(pd);  // typed BQ25798 driver over I2Cr/I2Cw 4CC tasks

// Helper: read, print, or report failure.
template <typename T>
static void readAndPrint(const __FlashStringHelper* label,
                         std::unique_ptr<T> reg)
{
    Serial.print(F("-- "));
    Serial.print(label);
    Serial.println(F(" --"));
    if (reg) {
        reg->debugPrint(Serial);
    } else {
        Serial.println(F("  [I2C read failed]"));
    }
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

    Serial.println(F("BQ25798 charge-config sketch ready."));
    Serial.println(F("Reading 15 config registers once per loop (6 s inter-read delay)."));
}

void loop()
{
    Serial.println();
    Serial.println(F("========== BQ25798 Charge Configuration =========="));

    // --- Charge limits & thresholds ---
    readAndPrint(F("MinimalSystemVoltage (REG00h)"), bq.readMinimalSystemVoltage(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargeVoltageLimit   (REG01h)"), bq.readChargeVoltageLimit(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargeCurrentLimit   (REG03h)"), bq.readChargeCurrentLimit(/*validate=*/false));
    delay(5100);
    readAndPrint(F("InputVoltageLimit    (REG05h)"), bq.readInputVoltageLimit(/*validate=*/false));
    delay(5100);
    readAndPrint(F("InputCurrentLimit    (REG06h)"), bq.readInputCurrentLimit(/*validate=*/false));
    delay(5100);
    readAndPrint(F("PrechargeControl     (REG08h)"), bq.readPrechargeControl(/*validate=*/false));
    delay(5100);
    readAndPrint(F("TerminationControl   (REG09h)"), bq.readTerminationControl(/*validate=*/false));
    delay(5100);

    // --- Charger control ---
    readAndPrint(F("ChargerControl0      (REG0Fh)"), bq.readChargerControl0(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerControl1      (REG10h)"), bq.readChargerControl1(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerControl2      (REG11h)"), bq.readChargerControl2(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerControl3      (REG12h)"), bq.readChargerControl3(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerControl4      (REG13h)"), bq.readChargerControl4(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerControl5      (REG14h)"), bq.readChargerControl5(/*validate=*/false));
    delay(5100);

    // --- NTC configuration ---
    readAndPrint(F("NtcControl0          (REG17h)"), bq.readNtcControl0(/*validate=*/false));
    delay(5100);
    readAndPrint(F("NtcControl1          (REG18h)"), bq.readNtcControl1(/*validate=*/false));
    delay(5100);

    // --- ICO result (read-only) ---
    readAndPrint(F("IcoCurrentLimit      (REG19h)"), bq.readIcoCurrentLimit(/*validate=*/false));
    delay(5100);

    Serial.println(F("========== end of charge-config sweep =========="));
}
