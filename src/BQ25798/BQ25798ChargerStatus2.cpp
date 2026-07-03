#include "BQ25798/BQ25798ChargerStatus2.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

ChargerStatus2::IcoStat ChargerStatus2::icoStat() const
{
    // ICO_STAT[1:0] — bits [7:6] of byte 0 (2-bit field starting at bit 6)
    return extractEnum<IcoStat>(6, 2,
        static_cast<uint8_t>(IcoStat::Reserved),
        IcoStat::Disabled);
}

bool ChargerStatus2::tregStat() const
{
    // TREG_STAT — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool ChargerStatus2::dpdmStat() const
{
    // DPDM_STAT — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool ChargerStatus2::vbatPresentStat() const
{
    // VBAT_PRESENT_STAT — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerStatus2::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Status 2 Register (REG1Dh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    // ICO_STAT
    s.print(F("  ICO Status (bits [7:6])        : "));
    switch (icoStat()) {
        case IcoStat::Disabled:        s.println(F("ICO Disabled"));                      break;
        case IcoStat::InProgress:      s.println(F("ICO Optimization In Progress"));      break;
        case IcoStat::MaxCurrentFound: s.println(F("Maximum Input Current Detected"));    break;
        case IcoStat::Reserved:        s.println(F("Reserved"));                          break;
        default:                       s.println(F("Unknown"));                           break;
    }

    s.print(F("  Reserved [5:3]                 : 0x"));
    s.println((_raw[0] & kReservedMask) >> 3, HEX);

    s.print(F("  Thermal Regulation (bit 2)     : "));
    s.println(tregStat() ? F("In thermal regulation") : F("Normal"));

    s.print(F("  D+/D- Detection (bit 1)        : "));
    s.println(dpdmStat() ? F("Detection ongoing") : F("Not started / done"));

    s.print(F("  VBAT Present (bit 0)           : "));
    s.println(vbatPresentStat() ? F("Present") : F("NOT present"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerStatus2::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bits [5:3] must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
