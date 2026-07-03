#include "BQ25798/BQ25798AdcControl.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool AdcControl::adcEnabled() const
{
    // ADC_EN — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool AdcControl::adcOneShot() const
{
    // ADC_RATE — bit 6 of byte 0 (1 = one-shot, 0 = continuous)
    return extractBits(6, 1) != 0;
}

AdcControl::SampleResolution AdcControl::adcSampleResolution() const
{
    // ADC_SAMPLE_1:0 — 2-bit field, bits 5:4 (bit position 4, width 2)
    return extractEnum<SampleResolution>(
        4, 2,
        static_cast<uint8_t>(SampleResolution::Bits12),  // max valid = 3
        SampleResolution::Bits15                          // default on out-of-range
    );
}

bool AdcControl::adcAveraging() const
{
    // ADC_AVG — bit 3 of byte 0 (1 = running average)
    return extractBits(3, 1) != 0;
}

bool AdcControl::adcAvgInit() const
{
    // ADC_AVG_INIT — bit 2 of byte 0 (1 = start from new conversion)
    return extractBits(2, 1) != 0;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void AdcControl::setAdcEnabled(bool on)
{
    if (!isValid()) return;
    // ADC_EN — bit 7 of byte 0
    BQ25798::setField8(_raw, 7, 1, on ? 1 : 0);
}

void AdcControl::setAdcOneShot(bool on)
{
    if (!isValid()) return;
    // ADC_RATE — bit 6 of byte 0 (1 = one-shot, 0 = continuous)
    BQ25798::setField8(_raw, 6, 1, on ? 1 : 0);
}

void AdcControl::setAdcSampleResolution(SampleResolution v)
{
    if (!isValid()) return;
    // ADC_SAMPLE_1:0 — 2-bit field, bits 5:4 (bit position 4, width 2)
    BQ25798::setField8(_raw, 4, 2, static_cast<uint8_t>(v));
}

void AdcControl::setAdcAveraging(bool on)
{
    if (!isValid()) return;
    // ADC_AVG — bit 3 of byte 0 (1 = running average)
    BQ25798::setField8(_raw, 3, 1, on ? 1 : 0);
}

void AdcControl::setAdcAvgInit(bool on)
{
    if (!isValid()) return;
    // ADC_AVG_INIT — bit 2 of byte 0 (1 = start from new conversion)
    BQ25798::setField8(_raw, 2, 1, on ? 1 : 0);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void AdcControl::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 ADC Control Register (REG2Eh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  ADC_EN    (bit 7): "));
    s.println(adcEnabled() ? F("Enabled") : F("Disabled"));

    s.print(F("  ADC_RATE  (bit 6): "));
    s.println(adcOneShot() ? F("One-shot") : F("Continuous"));

    s.print(F("  ADC_SAMPLE (bits 5:4): "));
    switch (adcSampleResolution()) {
        case SampleResolution::Bits15:
            s.println(F("15-bit effective resolution"));
            break;
        case SampleResolution::Bits14:
            s.println(F("14-bit effective resolution"));
            break;
        case SampleResolution::Bits13:
            s.println(F("13-bit effective resolution"));
            break;
        case SampleResolution::Bits12:
            s.println(F("12-bit effective resolution (not recommended)"));
            break;
        default:
            s.println(F("Unknown"));
            break;
    }

    s.print(F("  ADC_AVG      (bit 3): "));
    s.println(adcAveraging() ? F("Running average") : F("Single value"));

    s.print(F("  ADC_AVG_INIT (bit 2): "));
    s.println(adcAvgInit() ? F("Start from new conversion") : F("Start from existing register value"));

    s.print(F("  RESERVED  (bits 1:0): 0x"));
    const uint8_t reserved = extractBits(0, 2);
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

bool AdcControl::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bits [1:0] must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
