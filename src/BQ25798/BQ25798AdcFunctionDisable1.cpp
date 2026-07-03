#include "BQ25798/BQ25798AdcFunctionDisable1.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool AdcFunctionDisable1::dpAdcDisabled() const
{
    // DP_ADC_DIS — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool AdcFunctionDisable1::dmAdcDisabled() const
{
    // DM_ADC_DIS — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool AdcFunctionDisable1::vac2AdcDisabled() const
{
    // VAC2_ADC_DIS — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool AdcFunctionDisable1::vac1AdcDisabled() const
{
    // VAC1_ADC_DIS — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void AdcFunctionDisable1::setDpAdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // DP_ADC_DIS — bit 7 of byte 0
    BQ25798::setField8(_raw, 7, 1, disabled ? 1 : 0);
}

void AdcFunctionDisable1::setDmAdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // DM_ADC_DIS — bit 6 of byte 0
    BQ25798::setField8(_raw, 6, 1, disabled ? 1 : 0);
}

void AdcFunctionDisable1::setVac2AdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // VAC2_ADC_DIS — bit 5 of byte 0
    BQ25798::setField8(_raw, 5, 1, disabled ? 1 : 0);
}

void AdcFunctionDisable1::setVac1AdcDisabled(bool disabled)
{
    if (!isValid()) return;
    // VAC1_ADC_DIS — bit 4 of byte 0
    BQ25798::setField8(_raw, 4, 1, disabled ? 1 : 0);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void AdcFunctionDisable1::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 ADC Function Disable 1 Register (REG30h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  DP_ADC_DIS   (bit 7): "));
    s.println(dpAdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  DM_ADC_DIS   (bit 6): "));
    s.println(dmAdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  VAC2_ADC_DIS (bit 5): "));
    s.println(vac2AdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  VAC1_ADC_DIS (bit 4): "));
    s.println(vac1AdcDisabled() ? F("Disabled") : F("Enabled"));

    s.print(F("  RESERVED  (bits 3:0): 0x"));
    const uint8_t reserved = extractBits(0, 4);
    if (reserved < 0x10) s.print(F("0"));
    s.println(reserved, HEX);

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool AdcFunctionDisable1::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bits [3:0] must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
