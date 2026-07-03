#include "BQ25798/BQ25798NtcControl0.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

NtcControl0::JeitaVset NtcControl0::jeitaVset() const
{
    // JEITA_VSET_2:0 — 3-bit field at bits 7:5 (bit position 5, width 3)
    return extractEnum<JeitaVset>(
        5, 3,
        static_cast<uint8_t>(JeitaVset::VregUnchanged),  // max valid = 7
        JeitaVset::VregUnchanged                          // default on out-of-range
    );
}

NtcControl0::JeitaIseth NtcControl0::jeitaIseth() const
{
    // JEITA_ISETH_1:0 — 2-bit field at bits 4:3 (bit position 3, width 2)
    return extractEnum<JeitaIseth>(
        3, 2,
        static_cast<uint8_t>(JeitaIseth::IchgUnchanged),  // max valid = 3
        JeitaIseth::IchgUnchanged                          // default on out-of-range
    );
}

NtcControl0::JeitaIsetc NtcControl0::jeitaIsetc() const
{
    // JEITA_ISETC_1:0 — 2-bit field at bits 2:1 (bit position 1, width 2)
    return extractEnum<JeitaIsetc>(
        1, 2,
        static_cast<uint8_t>(JeitaIsetc::IchgUnchanged),  // max valid = 3
        JeitaIsetc::Ichg20Pct                              // default on out-of-range
    );
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void NtcControl0::setJeitaVset(JeitaVset v)
{
    if (!isValid()) return;
    // JEITA_VSET_2:0 — 3-bit field at bits 7:5 (bit position 5, width 3)
    BQ25798::setField8(_raw, 5, 3, static_cast<uint8_t>(v));
}

void NtcControl0::setJeitaIseth(JeitaIseth v)
{
    if (!isValid()) return;
    // JEITA_ISETH_1:0 — 2-bit field at bits 4:3 (bit position 3, width 2)
    BQ25798::setField8(_raw, 3, 2, static_cast<uint8_t>(v));
}

void NtcControl0::setJeitaIsetc(JeitaIsetc v)
{
    if (!isValid()) return;
    // JEITA_ISETC_1:0 — 2-bit field at bits 2:1 (bit position 1, width 2)
    BQ25798::setField8(_raw, 1, 2, static_cast<uint8_t>(v));
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void NtcControl0::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 NTC Control 0 Register (REG17h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  JEITA_VSET_2:0 (bits 7:5) [hot-range voltage]: "));
    switch (jeitaVset()) {
        case JeitaVset::Suspend:
            s.println(F("0 -> Charge Suspend"));
            break;
        case JeitaVset::VregMinus800:
            s.println(F("1 -> VREG - 800 mV"));
            break;
        case JeitaVset::VregMinus600:
            s.println(F("2 -> VREG - 600 mV"));
            break;
        case JeitaVset::VregMinus400:
            s.println(F("3 -> VREG - 400 mV (default)"));
            break;
        case JeitaVset::VregMinus300:
            s.println(F("4 -> VREG - 300 mV"));
            break;
        case JeitaVset::VregMinus200:
            s.println(F("5 -> VREG - 200 mV"));
            break;
        case JeitaVset::VregMinus100:
            s.println(F("6 -> VREG - 100 mV"));
            break;
        case JeitaVset::VregUnchanged:
            s.println(F("7 -> VREG unchanged"));
            break;
        default:
            s.println(F("Unknown"));
            break;
    }

    s.print(F("  JEITA_ISETH_1:0 (bits 4:3) [hot-range current]: "));
    switch (jeitaIseth()) {
        case JeitaIseth::Suspend:
            s.println(F("0 -> Charge Suspend"));
            break;
        case JeitaIseth::Ichg20Pct:
            s.println(F("1 -> 20% of ICHG"));
            break;
        case JeitaIseth::Ichg40Pct:
            s.println(F("2 -> 40% of ICHG"));
            break;
        case JeitaIseth::IchgUnchanged:
            s.println(F("3 -> ICHG unchanged (default)"));
            break;
        default:
            s.println(F("Unknown"));
            break;
    }

    s.print(F("  JEITA_ISETC_1:0 (bits 2:1) [cool-range current]: "));
    switch (jeitaIsetc()) {
        case JeitaIsetc::Suspend:
            s.println(F("0 -> Charge Suspend"));
            break;
        case JeitaIsetc::Ichg20Pct:
            s.println(F("1 -> 20% of ICHG (default)"));
            break;
        case JeitaIsetc::Ichg40Pct:
            s.println(F("2 -> 40% of ICHG"));
            break;
        case JeitaIsetc::IchgUnchanged:
            s.println(F("3 -> ICHG unchanged"));
            break;
        default:
            s.println(F("Unknown"));
            break;
    }

    s.print(F("  Reserved [bit 0]: "));
    s.println(_raw[0] & kReservedMask);

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool NtcControl0::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bit 0 must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
