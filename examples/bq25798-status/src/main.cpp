#include <Arduino.h>
#include <TPS25751.h>
#include <BQ25798/BQ25798.h>

// ---------------------------------------------------------------------------
// BQ25798 status and flags sketch
//
// Reads and debug-prints all charger status, charger flag, fault status, and
// fault flag registers once per loop. Each register is a separate I2Cr
// transaction; the TRM mandates >=5 s between consecutive I2Cr commands of
// the same type, so a 6 s delay is inserted between every read.
//
// Registers read (all 1-byte, read-only):
//   ChargerStatus0–4 (REG1Bh–REG1Fh) — power-path, PG, VBUS, VSYS, fault flags
//   ChargerFlag0–3   (REG22h–REG25h) — latched change flags matching status bits
//   FaultStatus0–1   (REG20h–REG21h) — OVP, OCP, short-circuit fault status
//   FaultFlag0–1     (REG26h–REG27h) — latched fault change flags
//
// Read-only / non-destructive. Validate=false so nullptr only means I2C
// failure (not a reserved-bit mismatch), giving the most forgiving output.
//
// Wiring: BQ25798 on TPS25751 I2Cc bus (7-bit address 0x6B).
// ---------------------------------------------------------------------------

const TPS25751  pd;       // host on the primary I2Ct bus
BQ25798::Device bq(pd);  // typed BQ25798 driver over I2Cr/I2Cw 4CC tasks

// Helper: read, print, or report failure. validate=false to show raw data.
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

    Serial.println(F("BQ25798 status/flags sketch ready."));
    Serial.println(F("Reading 14 status/flag registers once per loop (6 s inter-read delay)."));
}

void loop()
{
    Serial.println();
    Serial.println(F("========== BQ25798 Status & Flags =========="));

    // --- Charger Status ---
    readAndPrint(F("ChargerStatus0 (REG1Bh)"), bq.readChargerStatus0(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerStatus1 (REG1Ch)"), bq.readChargerStatus1(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerStatus2 (REG1Dh)"), bq.readChargerStatus2(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerStatus3 (REG1Eh)"), bq.readChargerStatus3(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerStatus4 (REG1Fh)"), bq.readChargerStatus4(/*validate=*/false));
    delay(5100);

    // --- Charger Flags ---
    readAndPrint(F("ChargerFlag0   (REG22h)"), bq.readChargerFlag0(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerFlag1   (REG23h)"), bq.readChargerFlag1(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerFlag2   (REG24h)"), bq.readChargerFlag2(/*validate=*/false));
    delay(5100);
    readAndPrint(F("ChargerFlag3   (REG25h)"), bq.readChargerFlag3(/*validate=*/false));
    delay(5100);

    // --- Fault Status ---
    readAndPrint(F("FaultStatus0   (REG20h)"), bq.readFaultStatus0(/*validate=*/false));
    delay(5100);
    readAndPrint(F("FaultStatus1   (REG21h)"), bq.readFaultStatus1(/*validate=*/false));
    delay(5100);

    // --- Fault Flags ---
    readAndPrint(F("FaultFlag0     (REG26h)"), bq.readFaultFlag0(/*validate=*/false));
    delay(5100);
    readAndPrint(F("FaultFlag1     (REG27h)"), bq.readFaultFlag1(/*validate=*/false));

    Serial.println(F("========== end of status sweep =========="));
    delay(5100);

}
