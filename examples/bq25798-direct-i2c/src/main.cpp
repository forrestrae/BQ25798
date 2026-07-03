#include <Arduino.h>
#include <Wire.h>
#include <TPS25751.h>
#include <BQ25798/BQ25798.h>

// ---------------------------------------------------------------------------
// Direct-bus BQ25798 read sketch — the non-proxied variant of
// read-downstream-bq25798-reg.
//
// Here the BQ25798 is wired straight to the Teensy's own I2C bus (Wire), NOT
// behind the TPS25751 on its secondary I2Cc bus. The driver is constructed with
// the direct (TwoWire&) constructor, so every read/write is a plain Arduino-Wire
// register transaction — no 4CC I2Cr/I2Cw relay, and therefore none of the proxy
// constraints (no TRM 5 s spacing, no 63/11-byte payload caps).
//
// It reads Part Information (REG48h) plus a few ADC channels each loop and prints
// decoded engineering units. Read-only / non-destructive — no register is written.
//
// Wiring: BQ25798 SDA/SCL on the Teensy's primary I2C (pins 18/19 on Teensy 4.x),
// with bus pull-ups. No TPS25751 is involved. Probe the primary I2C bus with a
// logic analyzer: you should see a plain [S] 0x6B+W, 0x48, [Sr] 0x6B+R, <byte>, [P]
// transaction and NO COMMAND/DATA (4CC) traffic.
// ---------------------------------------------------------------------------

// No TPS25751 host — the charger is on the MCU's own Wire bus.
BQ25798::Device bq(Wire2, 0x6B);   // direct (TwoWire&) constructor

void setup()
{
    Serial.begin(115200);
    while (!Serial && millis() < 3000)
    {
        delay(10);
    }
    Wire2.begin();              // caller owns the bus in direct mode
    Wire2.setClock(400000);

    // Surface direct-mode I2C warnings (direct transport uses DEBUG_CAT_I2C).
    TPS25751::setDebugLevel(DEBUG_LEVEL_TRACE);
    TPS25751::setDebugCategories(DEBUG_CAT_I2C);

    Serial.println(F("BQ25798 DIRECT-bus read sketch ready (no TPS25751 proxy)."));
    Serial.println(F("Reading over the Teensy's own Wire bus — standard I2C, no 5 s pacing."));
}

void loop()
{
    Serial.println();
    Serial.println(F("---- Direct I2C: BQ25798 REG48 (Part Information), 1 byte ----"));
    Serial.println(F("Expected bus txn: [S] 0x6B+W, 0x48, [Sr] 0x6B+R, <1 byte>, [P]"));

    auto info = bq.readPartInfo(/*validate=*/true);
    if (info)
    {
        Serial.print(F("  PN[5:3]      = 0b")); Serial.println(info->partNumber(), BIN);
        Serial.print(F("  DEV_REV[2:0] = "));    Serial.println(info->deviceRevision());
        Serial.println(F("  OK: PN=011b -> BQ25798 read directly (no 4CC relay)."));
    }
    else
    {
        Serial.println(F("  FAILED: direct I2C read did not complete, or PN check failed."));
        Serial.println(F("  Check: device present @0x6B on Wire, bus pull-ups, Wire.begin()."));
    }

    // A few ADC channels (need the ADC enabled to read non-zero; this build does
    // not write, so values reflect whatever the charger's ADC state already is).
    auto vbus = bq.readVbusAdc();
    auto vsys = bq.readVsysAdc();
    auto ibus = bq.readIbusAdc();
    if (vbus) { Serial.print(F("  VBUS = ")); Serial.print(vbus->millivolts()); Serial.println(F(" mV")); }
    if (vsys) { Serial.print(F("  VSYS = ")); Serial.print(vsys->millivolts()); Serial.println(F(" mV")); }
    if (ibus) { Serial.print(F("  IBUS = ")); Serial.print(ibus->milliamps());  Serial.println(F(" mA")); }

    // No TRM spacing in direct mode — pace only for a readable serial log.
    delay(1000);
}
