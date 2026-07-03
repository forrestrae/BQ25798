#include "BQ25798/BQ25798ChargerStatus3.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerStatus3::acrb2Stat() const
{
    // ACRB2_STAT — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool ChargerStatus3::acrb1Stat() const
{
    // ACRB1_STAT — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool ChargerStatus3::adcDoneStat() const
{
    // ADC_DONE_STAT — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool ChargerStatus3::vsysStat() const
{
    // VSYS_STAT — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool ChargerStatus3::chgTmrStat() const
{
    // CHG_TMR_STAT — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

bool ChargerStatus3::trichgTmrStat() const
{
    // TRICHG_TMR_STAT — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool ChargerStatus3::prechgTmrStat() const
{
    // PRECHG_TMR_STAT — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerStatus3::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Status 3 Register (REG1Eh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  ACFET2-RBFET2 Placed (bit 7)   : "));
    s.println(acrb2Stat() ? F("Placed") : F("NOT placed"));

    s.print(F("  ACFET1-RBFET1 Placed (bit 6)   : "));
    s.println(acrb1Stat() ? F("Placed") : F("NOT placed"));

    s.print(F("  ADC Conversion Done (bit 5)    : "));
    s.println(adcDoneStat() ? F("Complete") : F("NOT complete"));

    s.print(F("  VSYS Regulation (bit 4)        : "));
    s.println(vsysStat() ? F("In VSYSMIN regulation (VBAT < VSYSMIN)") : F("Normal (VBAT > VSYSMIN)"));

    s.print(F("  Fast Charge Timer (bit 3)      : "));
    s.println(chgTmrStat() ? F("Safety timer expired") : F("Normal"));

    s.print(F("  Trickle Charge Timer (bit 2)   : "));
    s.println(trichgTmrStat() ? F("Safety timer expired") : F("Normal"));

    s.print(F("  Pre-charge Timer (bit 1)       : "));
    s.println(prechgTmrStat() ? F("Safety timer expired") : F("Normal"));

    s.print(F("  Reserved [bit 0]               : "));
    s.println(_raw[0] & kReservedMask);

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerStatus3::isSemanticallyValid() const
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
