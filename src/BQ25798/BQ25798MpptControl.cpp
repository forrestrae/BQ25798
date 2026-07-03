#include "BQ25798/BQ25798MpptControl.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

MpptControl::VocPct MpptControl::vocPct() const
{
    // VOC_PCT_2:0 — 3-bit field, bits 7:5 (bit position 5, width 3)
    return extractEnum<VocPct>(
        5, 3,
        static_cast<uint8_t>(VocPct::Pct100),  // max valid = 7
        VocPct::Pct87p5                          // default on out-of-range
    );
}

MpptControl::VocDly MpptControl::vocDly() const
{
    // VOC_DLY_1:0 — 2-bit field, bits 4:3 (bit position 3, width 2)
    return extractEnum<VocDly>(
        3, 2,
        static_cast<uint8_t>(VocDly::S5),  // max valid = 3
        VocDly::Ms300                        // default on out-of-range
    );
}

MpptControl::VocRate MpptControl::vocRate() const
{
    // VOC_RATE_1:0 — 2-bit field, bits 2:1 (bit position 1, width 2)
    return extractEnum<VocRate>(
        1, 2,
        static_cast<uint8_t>(VocRate::Min30),  // max valid = 3
        VocRate::Min2                            // default on out-of-range
    );
}

bool MpptControl::enMppt() const
{
    // EN_MPPT — bit 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void MpptControl::setVocPct(VocPct v)
{
    if (!isValid()) return;
    // VOC_PCT_2:0 — 3-bit field, bits 7:5 (bit position 5, width 3)
    BQ25798::setField8(_raw, 5, 3, static_cast<uint8_t>(v));
}

void MpptControl::setVocDly(VocDly v)
{
    if (!isValid()) return;
    // VOC_DLY_1:0 — 2-bit field, bits 4:3 (bit position 3, width 2)
    BQ25798::setField8(_raw, 3, 2, static_cast<uint8_t>(v));
}

void MpptControl::setVocRate(VocRate v)
{
    if (!isValid()) return;
    // VOC_RATE_1:0 — 2-bit field, bits 2:1 (bit position 1, width 2)
    BQ25798::setField8(_raw, 1, 2, static_cast<uint8_t>(v));
}

void MpptControl::setEnMppt(bool on)
{
    if (!isValid()) return;
    // EN_MPPT — bit 0
    BQ25798::setField8(_raw, 0, 1, on ? 1 : 0);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void MpptControl::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 MPPT Control Register (REG15h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  VOC_PCT  (bits 7:5): "));
    switch (vocPct()) {
        case VocPct::Pct56p25: s.println(F("56.25%"));          break;
        case VocPct::Pct62p5:  s.println(F("62.5%"));           break;
        case VocPct::Pct68p75: s.println(F("68.75%"));          break;
        case VocPct::Pct75:    s.println(F("75%"));              break;
        case VocPct::Pct81p25: s.println(F("81.25%"));          break;
        case VocPct::Pct87p5:  s.println(F("87.5% (default)")); break;
        case VocPct::Pct93p75: s.println(F("93.75%"));          break;
        case VocPct::Pct100:   s.println(F("100%"));             break;
        default:               s.println(F("Unknown"));           break;
    }

    s.print(F("  VOC_DLY  (bits 4:3): "));
    switch (vocDly()) {
        case VocDly::Ms50:  s.println(F("50 ms"));              break;
        case VocDly::Ms300: s.println(F("300 ms (default)"));   break;
        case VocDly::S2:    s.println(F("2 s"));                break;
        case VocDly::S5:    s.println(F("5 s"));                break;
        default:            s.println(F("Unknown"));             break;
    }

    s.print(F("  VOC_RATE (bits 2:1): "));
    switch (vocRate()) {
        case VocRate::S30:   s.println(F("30 s"));              break;
        case VocRate::Min2:  s.println(F("2 mins (default)"));  break;
        case VocRate::Min10: s.println(F("10 mins"));           break;
        case VocRate::Min30: s.println(F("30 mins"));           break;
        default:             s.println(F("Unknown"));            break;
    }

    s.print(F("  EN_MPPT  (bit  0): "));
    s.println(enMppt() ? F("Enabled") : F("Disabled (default)"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool MpptControl::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
