#include "BQ25798/BQ25798TimerControl.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

TimerControl::TopoffTmr TimerControl::topoffTmr() const
{
    // TOPOFF_TMR_1:0 — 2-bit field, bits 7:6 (bit position 6, width 2)
    return extractEnum<TopoffTmr>(
        6, 2,
        static_cast<uint8_t>(TopoffTmr::Min45),  // max valid = 3
        TopoffTmr::Disabled                        // default on out-of-range
    );
}

bool TimerControl::enTrichgTmr() const
{
    // EN_TRICHG_TMR — bit 5
    return extractBits(5, 1) != 0;
}

bool TimerControl::enPrechgTmr() const
{
    // EN_PRECHG_TMR — bit 4
    return extractBits(4, 1) != 0;
}

bool TimerControl::enChgTmr() const
{
    // EN_CHG_TMR — bit 3
    return extractBits(3, 1) != 0;
}

TimerControl::ChgTmr TimerControl::chgTmr() const
{
    // CHG_TMR_1:0 — 2-bit field, bits 2:1 (bit position 1, width 2)
    return extractEnum<ChgTmr>(
        1, 2,
        static_cast<uint8_t>(ChgTmr::Hours24),  // max valid = 3
        ChgTmr::Hours12                           // default on out-of-range
    );
}

bool TimerControl::tmr2xEn() const
{
    // TMR2X_EN — bit 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void TimerControl::setTopoffTmr(TopoffTmr v)
{
    if (!isValid()) return;
    // TOPOFF_TMR_1:0 — 2-bit field, bits 7:6 (bit position 6, width 2)
    BQ25798::setField8(_raw, 6, 2, static_cast<uint8_t>(v));
}

void TimerControl::setEnTrichgTmr(bool on)
{
    if (!isValid()) return;
    // EN_TRICHG_TMR — bit 5
    BQ25798::setField8(_raw, 5, 1, on ? 1 : 0);
}

void TimerControl::setEnPrechgTmr(bool on)
{
    if (!isValid()) return;
    // EN_PRECHG_TMR — bit 4
    BQ25798::setField8(_raw, 4, 1, on ? 1 : 0);
}

void TimerControl::setEnChgTmr(bool on)
{
    if (!isValid()) return;
    // EN_CHG_TMR — bit 3
    BQ25798::setField8(_raw, 3, 1, on ? 1 : 0);
}

void TimerControl::setChgTmr(ChgTmr v)
{
    if (!isValid()) return;
    // CHG_TMR_1:0 — 2-bit field, bits 2:1 (bit position 1, width 2)
    BQ25798::setField8(_raw, 1, 2, static_cast<uint8_t>(v));
}

void TimerControl::setTmr2xEn(bool on)
{
    if (!isValid()) return;
    // TMR2X_EN — bit 0
    BQ25798::setField8(_raw, 0, 1, on ? 1 : 0);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void TimerControl::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Timer Control Register (REG0Eh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  TOPOFF_TMR   (bits 7:6): "));
    switch (topoffTmr()) {
        case TopoffTmr::Disabled: s.println(F("Disabled (default)")); break;
        case TopoffTmr::Min15:    s.println(F("15 mins"));            break;
        case TopoffTmr::Min30:    s.println(F("30 mins"));            break;
        case TopoffTmr::Min45:    s.println(F("45 mins"));            break;
        default:                  s.println(F("Unknown"));             break;
    }

    s.print(F("  EN_TRICHG_TMR (bit  5): "));
    s.println(enTrichgTmr() ? F("Enabled (default)") : F("Disabled"));

    s.print(F("  EN_PRECHG_TMR (bit  4): "));
    s.println(enPrechgTmr() ? F("Enabled (default)") : F("Disabled"));

    s.print(F("  EN_CHG_TMR    (bit  3): "));
    s.println(enChgTmr() ? F("Enabled (default)") : F("Disabled"));

    s.print(F("  CHG_TMR      (bits 2:1): "));
    switch (chgTmr()) {
        case ChgTmr::Hours5:  s.println(F("5 hrs"));              break;
        case ChgTmr::Hours8:  s.println(F("8 hrs"));              break;
        case ChgTmr::Hours12: s.println(F("12 hrs (default)"));   break;
        case ChgTmr::Hours24: s.println(F("24 hrs"));             break;
        default:              s.println(F("Unknown"));             break;
    }

    s.print(F("  TMR2X_EN     (bit  0): "));
    s.println(tmr2xEn() ? F("2x slowdown enabled (default)") : F("Normal"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool TimerControl::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
