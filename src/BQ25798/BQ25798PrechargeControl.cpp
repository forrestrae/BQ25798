#include "BQ25798/BQ25798PrechargeControl.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

PrechargeControl::VbatLowv PrechargeControl::vbatLowv() const
{
    // VBAT_LOWV_1:0 — 2-bit field at bits 7:6 (bit position 6, width 2)
    return extractEnum<VbatLowv>(
        6, 2,
        static_cast<uint8_t>(VbatLowv::Pct71p4),  // max valid = 3
        VbatLowv::Pct71p4                           // default on out-of-range
    );
}

uint8_t PrechargeControl::iprechgRaw() const
{
    // IPRECHG_5:0 — 6-bit field starting at bit 0 of byte 0
    return extractBits(0, 6);
}

uint16_t PrechargeControl::milliamps() const
{
    if (!isValid()) return 0;
    return static_cast<uint16_t>(static_cast<uint16_t>(iprechgRaw()) * kLsbMa);
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void PrechargeControl::setVbatLowv(VbatLowv v)
{
    if (!isValid()) return;
    // VBAT_LOWV_1:0 — 2-bit field at bits 7:6
    BQ25798::setField8(_raw, 6, 2, static_cast<uint8_t>(v));
}

void PrechargeControl::setIprechgRaw(uint8_t raw)
{
    if (!isValid()) return;
    // IPRECHG_5:0 — 6-bit field starting at bit 0 of byte 0
    BQ25798::setField8(_raw, 0, 6, raw);
}

void PrechargeControl::setMilliamps(uint16_t ma)
{
    if (!isValid()) return;
    // Invert milliamps() = IPRECHG * 40 mA  ->  IPRECHG = ma / 40
    const uint8_t code = static_cast<uint8_t>(ma / kLsbMa);
    BQ25798::setField8(_raw, 0, 6, code);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void PrechargeControl::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Precharge Control Register (REG08h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  VBAT_LOWV_1:0 (bits 7:6): "));
    switch (vbatLowv()) {
        case VbatLowv::Pct15:
            s.println(F("0 -> 15% of VREG"));
            break;
        case VbatLowv::Pct62p2:
            s.println(F("1 -> 62.2% of VREG"));
            break;
        case VbatLowv::Pct66p7:
            s.println(F("2 -> 66.7% of VREG"));
            break;
        case VbatLowv::Pct71p4:
            s.println(F("3 -> 71.4% of VREG (default)"));
            break;
        default:
            s.println(F("Unknown"));
            break;
    }

    s.print(F("  IPRECHG_5:0 (bits 5:0): "));
    s.print(iprechgRaw());
    s.print(F("  ->  "));
    s.print(milliamps());
    s.println(F(" mA (= IPRECHG * 40 mA)"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool PrechargeControl::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: all bits defined — no reserved bits to check
    return true;
}

}  // namespace BQ25798
