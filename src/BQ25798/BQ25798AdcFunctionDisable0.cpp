#include "BQ25798/BQ25798AdcFunctionDisable0.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool AdcFunctionDisable0::ibusAdcDisabled() const
{
    // IBUS_ADC_DIS — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool AdcFunctionDisable0::ibatAdcDisabled() const
{
    // IBAT_ADC_DIS — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool AdcFunctionDisable0::vbusAdcDisabled() const
{
    // VBUS_ADC_DIS — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool AdcFunctionDisable0::vbatAdcDisabled() const
{
    // VBAT_ADC_DIS — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool AdcFunctionDisable0::vsysAdcDisabled() const
{
    // VSYS_ADC_DIS — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

bool AdcFunctionDisable0::tsAdcDisabled() const
{
    // TS_ADC_DIS — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool AdcFunctionDisable0::tdieAdcDisabled() const
{
    // TDIE_ADC_DIS — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void AdcFunctionDisable0::setIbusAdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // IBUS_ADC_DIS — bit 7 of byte 0
    BQ25798::setField8(_raw, 7, 1, disabled ? 1 : 0);
}

void AdcFunctionDisable0::setIbatAdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // IBAT_ADC_DIS — bit 6 of byte 0
    BQ25798::setField8(_raw, 6, 1, disabled ? 1 : 0);
}

void AdcFunctionDisable0::setVbusAdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // VBUS_ADC_DIS — bit 5 of byte 0
    BQ25798::setField8(_raw, 5, 1, disabled ? 1 : 0);
}

void AdcFunctionDisable0::setVbatAdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // VBAT_ADC_DIS — bit 4 of byte 0
    BQ25798::setField8(_raw, 4, 1, disabled ? 1 : 0);
}

void AdcFunctionDisable0::setVsysAdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // VSYS_ADC_DIS — bit 3 of byte 0
    BQ25798::setField8(_raw, 3, 1, disabled ? 1 : 0);
}

void AdcFunctionDisable0::setTsAdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // TS_ADC_DIS — bit 2 of byte 0
    BQ25798::setField8(_raw, 2, 1, disabled ? 1 : 0);
}

void AdcFunctionDisable0::setTdieAdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // TDIE_ADC_DIS — bit 1 of byte 0
    BQ25798::setField8(_raw, 1, 1, disabled ? 1 : 0);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void AdcFunctionDisable0::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 ADC Function Disable 0 Register (REG2Fh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  IBUS_ADC_DIS (bit 7): "));
    s.println(ibusAdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  IBAT_ADC_DIS (bit 6): "));
    s.println(ibatAdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  VBUS_ADC_DIS (bit 5): "));
    s.println(vbusAdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  VBAT_ADC_DIS (bit 4): "));
    s.println(vbatAdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  VSYS_ADC_DIS (bit 3): "));
    s.println(vsysAdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  TS_ADC_DIS   (bit 2): "));
    s.println(tsAdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  TDIE_ADC_DIS (bit 1): "));
    s.println(tdieAdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  RESERVED     (bit 0): "));
    s.println(extractBits(0, 1));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool AdcFunctionDisable0::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bit [0] must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
