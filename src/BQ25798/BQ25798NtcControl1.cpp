#include "BQ25798/BQ25798NtcControl1.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

NtcControl1::TsCool NtcControl1::tsCool() const
{
    // TS_COOL_1:0 — 2-bit field at bits 7:6 (bit position 6, width 2)
    return extractEnum<TsCool>(
        6, 2,
        static_cast<uint8_t>(TsCool::Pct62p4_20C),  // max valid = 3
        TsCool::Pct68p4_10C                          // default on out-of-range
    );
}

NtcControl1::TsWarm NtcControl1::tsWarm() const
{
    // TS_WARM_1:0 — 2-bit field at bits 5:4 (bit position 4, width 2)
    return extractEnum<TsWarm>(
        4, 2,
        static_cast<uint8_t>(TsWarm::Pct37p7_55C),  // max valid = 3
        TsWarm::Pct44p8_45C                          // default on out-of-range
    );
}

NtcControl1::Bhot NtcControl1::bhot() const
{
    // BHOT_1:0 — 2-bit field at bits 3:2 (bit position 2, width 2)
    return extractEnum<Bhot>(
        2, 2,
        static_cast<uint8_t>(Bhot::Disabled),  // max valid = 3
        Bhot::Deg60                             // default on out-of-range
    );
}

bool NtcControl1::bcold() const
{
    // BCOLD — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool NtcControl1::tsIgnore() const
{
    // TS_IGNORE — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void NtcControl1::setTsCool(TsCool v)
{
    if (!isValid()) return;
    // TS_COOL_1:0 — 2-bit field at bits 7:6 (bit position 6, width 2)
    BQ25798::setField8(_raw, 6, 2, static_cast<uint8_t>(v));
}

void NtcControl1::setTsWarm(TsWarm v)
{
    if (!isValid()) return;
    // TS_WARM_1:0 — 2-bit field at bits 5:4 (bit position 4, width 2)
    BQ25798::setField8(_raw, 4, 2, static_cast<uint8_t>(v));
}

void NtcControl1::setBhot(Bhot v)
{
    if (!isValid()) return;
    // BHOT_1:0 — 2-bit field at bits 3:2 (bit position 2, width 2)
    BQ25798::setField8(_raw, 2, 2, static_cast<uint8_t>(v));
}

void NtcControl1::setBcold(bool on)
{
    if (!isValid()) return;
    // BCOLD — bit 1 of byte 0
    BQ25798::setField8(_raw, 1, 1, on ? 1 : 0);
}

void NtcControl1::setTsIgnore(bool on)
{
    if (!isValid()) return;
    // TS_IGNORE — bit 0 of byte 0
    BQ25798::setField8(_raw, 0, 1, on ? 1 : 0);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void NtcControl1::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 NTC Control 1 Register (REG18h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  TS_COOL_1:0 (bits 7:6) [VT2 cool threshold]: "));
    switch (tsCool()) {
        case TsCool::Pct71p1_5C:
            s.println(F("0 -> 71.1% of REGN (~5°C)"));
            break;
        case TsCool::Pct68p4_10C:
            s.println(F("1 -> 68.4% of REGN (~10°C) (default)"));
            break;
        case TsCool::Pct65p5_15C:
            s.println(F("2 -> 65.5% of REGN (~15°C)"));
            break;
        case TsCool::Pct62p4_20C:
            s.println(F("3 -> 62.4% of REGN (~20°C)"));
            break;
        default:
            s.println(F("Unknown"));
            break;
    }

    s.print(F("  TS_WARM_1:0 (bits 5:4) [VT3 warm threshold]: "));
    switch (tsWarm()) {
        case TsWarm::Pct48p4_40C:
            s.println(F("0 -> 48.4% of REGN (~40°C)"));
            break;
        case TsWarm::Pct44p8_45C:
            s.println(F("1 -> 44.8% of REGN (~45°C) (default)"));
            break;
        case TsWarm::Pct41p2_50C:
            s.println(F("2 -> 41.2% of REGN (~50°C)"));
            break;
        case TsWarm::Pct37p7_55C:
            s.println(F("3 -> 37.7% of REGN (~55°C)"));
            break;
        default:
            s.println(F("Unknown"));
            break;
    }

    s.print(F("  BHOT_1:0 (bits 3:2) [OTG TS HOT threshold]: "));
    switch (bhot()) {
        case Bhot::Deg55:
            s.println(F("0 -> 55°C"));
            break;
        case Bhot::Deg60:
            s.println(F("1 -> 60°C (default)"));
            break;
        case Bhot::Deg65:
            s.println(F("2 -> 65°C"));
            break;
        case Bhot::Disabled:
            s.println(F("3 -> Disabled"));
            break;
        default:
            s.println(F("Unknown"));
            break;
    }

    s.print(F("  BCOLD (bit 1) [OTG TS COLD threshold]: "));
    s.println(bcold() ? F("-20°C") : F("-10°C (default)"));

    s.print(F("  TS_IGNORE (bit 0): "));
    s.println(tsIgnore() ? F("Ignore (TS always good)") : F("NOT ignore (default)"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool NtcControl1::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: all bits defined — no reserved bits to check
    return true;
}

}  // namespace BQ25798
