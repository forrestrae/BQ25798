#include <Arduino.h>
#include <TPS25751.h>
#include <BQ25798/BQ25798.h>

// ---------------------------------------------------------------------------
// Minimal BQ25798 read sketch — validates the I2Cc downstream-device path
// (BQ25798::Device / I2Cr) against a logic-analyzer capture.
//
// It reads the BQ25798 Part Information register (REG48h) once per loop, well
// over the TRM's 5 s minimum spacing apart, so each I2Cc transaction is cleanly
// isolated on the analyzer. Read-only / non-destructive — no I2Cw is issued.
//
// Wiring: BQ25798 sits on the TPS25751's secondary I2Cc bus (not the Teensy's
// primary I2Ct bus). Probe I2Cc_SDA/SCL with the analyzer.
// ---------------------------------------------------------------------------

const TPS25751      pd;                   // host on the primary I2Ct bus
BQ25798::Device     bq(pd);              // typed BQ25798 driver over I2Cr/I2Cw 4CC tasks

void setup()
{
    Serial.begin(115200);
    while (!Serial && millis() < 3000)
    {
        delay(10);
    }

    // Surface every I2Ct transaction and 4CC task step so the serial log lines
    // up 1:1 with what you see on the analyzer.
    TPS25751::setDebugLevel(DEBUG_LEVEL_WARN);
    TPS25751::setDebugCategories(DEBUG_CAT_I2C | DEBUG_CAT_TASK);

    Serial.println(F("Initializing TPS25751 host..."));
    pd.begin();

    Serial.println(F("BQ25798 downstream-read sketch ready."));
    Serial.println(F("One I2Cr per loop, >=6s apart, for clean logic-analyzer captures."));
}

void loop()
{
    Serial.println();
    Serial.println(F("---- I2Cr: BQ25798 REG48 (Part Information), 1 byte ----"));
    Serial.println(F("Expected I2Cc txn: [S] 0x6B+W, 0x48, [Sr] 0x6B+R, <1 byte>, [P]"));

    // Use the typed driver — validates PN field internally.
    auto info = bq.readPartInfo(/*validate=*/true);

    if (info)
    {
        Serial.print(F("  PN[5:3]      = 0b")); Serial.println(info->partNumber(), BIN);
        Serial.print(F("  DEV_REV[2:0] = "));    Serial.println(info->deviceRevision());
        info->debugPrint(Serial);
        Serial.println(F("  OK: PN=011b -> BQ25798 (data decoded from DATA offset 1 correctly)"));
    }
    else
    {
        Serial.println(F("  FAILED: I2Cr did not complete, or PN check failed."));
        Serial.println(F("  Check: device present @0x6B on I2Cc, bus pull-ups, and the offset-1 decode."));
    }

    // TRM requires >=5 s between consecutive I2Cr commands. The library only
    // warns (DEBUG_CAT_TASK), it does not block — so we pace it here.
    delay(5100);
}
