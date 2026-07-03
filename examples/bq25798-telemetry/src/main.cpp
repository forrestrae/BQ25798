#include <Arduino.h>
#include <TPS25751.h>
#include <BQ25798/BQ25798.h>

// ---------------------------------------------------------------------------
// BQ25798 ADC telemetry sketch
//
// Reads all nine Phase-1 ADC result registers once per loop and prints their
// converted values. Each read issues one I2Cr transaction over the TPS25751
// I2Cc bus; the TRM requires >=5 s between consecutive I2Cr commands of the
// same type, so the loop paces itself with a 6 s inter-read delay.
//
// ADC channels read:
//   VBUS (REG35h)  — input bus voltage,   mV, unsigned, 0–30000 mV nominal
//   VBAT (REG3Bh)  — battery voltage,     mV, unsigned, 0–20000 mV nominal
//   VSYS (REG3Dh)  — system voltage,      mV, unsigned, 0–20000 mV nominal
//   VAC1 (REG37h)  — adapter 1 voltage,   mV, unsigned, 0–30000 mV nominal
//   VAC2 (REG39h)  — adapter 2 voltage,   mV, unsigned, 0–30000 mV nominal
//   IBUS (REG31h)  — input bus current,   mA, signed
//   IBAT (REG33h)  — battery current,     mA, signed
//   TS   (REG3Fh)  — thermistor %REGN,    %,  unsigned
//   TDIE (REG41h)  — die temperature,     °C, signed 0.5 °C LSB, -40..150 °C
//
// NOTE: ADC must be enabled in hardware (ADC_CONTROL register, bit ENADC=1)
// for these registers to return live data. The ADC_CONTROL register is
// read-write. This sketch is intentionally read-only — to enable the ADC,
// write 0x80 to REG2Eh via bq.writeRegister() or a future writeAdcControl()
// method. Uncommenting the block in setup() below shows the write sequence.
//
// Wiring: BQ25798 on TPS25751 I2Cc bus (7-bit address 0x6B). Probe I2Cc_SDA/
// SCL to observe transactions.
// ---------------------------------------------------------------------------

const TPS25751  pd;       // host on the primary I2Ct bus
BQ25798::Device bq(pd);  // typed BQ25798 driver over I2Cr/I2Cw 4CC tasks

// Print a labelled millivolt reading with an in-range check.
static void printMv(const __FlashStringHelper* label,
                    uint16_t mv,
                    uint16_t maxMv)
{
    Serial.print(label);
    Serial.print(mv);
    Serial.print(F(" mV"));
    if (mv > maxMv) {
        Serial.print(F("  [OUT OF RANGE: max "));
        Serial.print(maxMv);
        Serial.print(F(" mV]"));
    }
    Serial.println();
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

    // To enable the ADC before reading (write-only path, out of scope for this
    // read-only sketch — uncomment if a writeRegister helper is available):
    //
    //   const uint8_t adcEnable = 0x80;  // ENADC=1, one-shot=0, all channels
    //   bq.writeRegister(
    //       static_cast<uint8_t>(BQ25798::Registers::Address::ADC_CONTROL),
    //       &adcEnable, 1);
    //   delay(150);  // allow first conversion to complete (~100 ms typical)

    Serial.println(F("BQ25798 ADC telemetry sketch ready."));
    Serial.println(F("Reading 9 ADC channels once per loop (6 s inter-read delay)."));
    Serial.println(F("ADC must be enabled (ENADC=1) in hardware for live data."));
}

void loop()
{
    Serial.println();
    Serial.println(F("===== BQ25798 ADC Telemetry ====="));

    // --- Voltage rails ---
    {
        auto vbus = bq.readVbusAdc(/*validate=*/false);
        if (vbus) {
            printMv(F("  VBUS : "), vbus->millivolts(), 30000);
        } else {
            Serial.println(F("  VBUS : read failed"));
        }
        delay(5100);
    }
    {
        auto vbat = bq.readVbatAdc(/*validate=*/false);
        if (vbat) {
            printMv(F("  VBAT : "), vbat->millivolts(), 20000);
        } else {
            Serial.println(F("  VBAT : read failed"));
        }
        delay(5100);
    }
    {
        auto vsys = bq.readVsysAdc(/*validate=*/false);
        if (vsys) {
            printMv(F("  VSYS : "), vsys->millivolts(), 20000);
        } else {
            Serial.println(F("  VSYS : read failed"));
        }
        delay(5100);
    }
    {
        auto vac1 = bq.readVac1Adc(/*validate=*/false);
        if (vac1) {
            printMv(F("  VAC1 : "), vac1->millivolts(), 30000);
        } else {
            Serial.println(F("  VAC1 : read failed"));
        }
        delay(5100);
    }
    {
        auto vac2 = bq.readVac2Adc(/*validate=*/false);
        if (vac2) {
            printMv(F("  VAC2 : "), vac2->millivolts(), 30000);
        } else {
            Serial.println(F("  VAC2 : read failed"));
        }
        delay(5100);
    }

    // --- Current rails ---
    {
        auto ibus = bq.readIbusAdc(/*validate=*/false);
        if (ibus) {
            Serial.print(F("  IBUS : "));
            Serial.print(ibus->milliamps());
            Serial.println(F(" mA"));
        } else {
            Serial.println(F("  IBUS : read failed"));
        }
        delay(5100);
    }
    {
        auto ibat = bq.readIbatAdc(/*validate=*/false);
        if (ibat) {
            Serial.print(F("  IBAT : "));
            Serial.print(ibat->milliamps());
            Serial.println(F(" mA"));
        } else {
            Serial.println(F("  IBAT : read failed"));
        }
        delay(5100);
    }

    // --- Thermistor ---
    {
        auto ts = bq.readTsAdc(/*validate=*/false);
        if (ts) {
            Serial.print(F("  TS   : "));
            Serial.print(ts->percent(), 2);
            Serial.println(F(" % REGN"));
        } else {
            Serial.println(F("  TS   : read failed"));
        }
        delay(5100);
    }

    // --- Die temperature ---
    {
        auto tdie = bq.readTdieAdc(/*validate=*/false);
        if (tdie) {
            const float degC = tdie->celsius();
            Serial.print(F("  TDIE : "));
            Serial.print(degC, 1);
            Serial.print(F(" degC"));
            if (degC < -40.0f || degC > 150.0f) {
                Serial.print(F("  [OUT OF RANGE: -40..150 degC]"));
            }
            Serial.println();
        } else {
            Serial.println(F("  TDIE : read failed"));
        }
        delay(5100);
    }

    Serial.println(F("===== end of telemetry sweep ====="));
    // Overall loop pacing is provided by the per-read 6 s delays above.
    // No additional delay needed here.
}
