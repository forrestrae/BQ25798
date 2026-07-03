#include "BQ25798/BQ25798ChargerFlag2.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerFlag2::dpdmDoneFlag() const
{
    // DPDM_DONE_FLAG — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool ChargerFlag2::adcDoneFlag() const
{
    // ADC_DONE_FLAG — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool ChargerFlag2::vsysFlag() const
{
    // VSYS_FLAG — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool ChargerFlag2::chgTmrFlag() const
{
    // CHG_TMR_FLAG — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

bool ChargerFlag2::trichgTmrFlag() const
{
    // TRICHG_TMR_FLAG — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool ChargerFlag2::prechgTmrFlag() const
{
    // PRECHG_TMR_FLAG — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool ChargerFlag2::topoffTmrFlag() const
{
    // TOPOFF_TMR_FLAG — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerFlag2::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Flag 2 Register (REG24h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  RESERVED          (bit 7): "));
    s.println((_raw[0] >> 7) & 1);

    s.print(F("  DPDM_DONE_FLAG    (bit 6): "));
    s.println(dpdmDoneFlag() ? F("1 — D+/D- detection completed") : F("0 — Not started or ongoing"));

    s.print(F("  ADC_DONE_FLAG     (bit 5): "));
    s.println(adcDoneFlag() ? F("1 — ADC one-shot conversion completed") : F("0 — Not completed"));

    s.print(F("  VSYS_FLAG         (bit 4): "));
    s.println(vsysFlag() ? F("1 — Entered or exited VSYSMIN regulation") : F("0 — Normal"));

    s.print(F("  CHG_TMR_FLAG      (bit 3): "));
    s.println(chgTmrFlag() ? F("1 — Fast charge timer expired") : F("0 — Normal"));

    s.print(F("  TRICHG_TMR_FLAG   (bit 2): "));
    s.println(trichgTmrFlag() ? F("1 — Trickle charge timer expired") : F("0 — Normal"));

    s.print(F("  PRECHG_TMR_FLAG   (bit 1): "));
    s.println(prechgTmrFlag() ? F("1 — Pre-charge timer expired") : F("0 — Normal"));

    s.print(F("  TOPOFF_TMR_FLAG   (bit 0): "));
    s.println(topoffTmrFlag() ? F("1 — Top-off timer expired") : F("0 — Normal"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerFlag2::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: reserved bit 7 must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
