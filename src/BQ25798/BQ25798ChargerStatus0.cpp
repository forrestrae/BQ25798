#include "BQ25798/BQ25798ChargerStatus0.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerStatus0::iindpmStat() const
{
    // IINDPM_STAT — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool ChargerStatus0::vindpmStat() const
{
    // VINDPM_STAT — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool ChargerStatus0::wdStat() const
{
    // WD_STAT — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool ChargerStatus0::pgStat() const
{
    // PG_STAT — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

bool ChargerStatus0::ac2PresentStat() const
{
    // AC2_PRESENT_STAT — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool ChargerStatus0::ac1PresentStat() const
{
    // AC1_PRESENT_STAT — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool ChargerStatus0::vbusPresentStat() const
{
    // VBUS_PRESENT_STAT — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerStatus0::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Status 0 Register (REG1Bh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  IINDPM/IOTG Regulation (bit 7) : "));
    s.println(iindpmStat() ? F("In regulation") : F("Normal"));

    s.print(F("  VINDPM/VOTG Regulation (bit 6) : "));
    s.println(vindpmStat() ? F("In regulation") : F("Normal"));

    s.print(F("  Watchdog Timer (bit 5)         : "));
    s.println(wdStat() ? F("Expired") : F("Normal"));

    s.print(F("  Power Good (bit 3)             : "));
    s.println(pgStat() ? F("Power good") : F("NOT power good"));

    s.print(F("  VAC2 Present (bit 2)           : "));
    s.println(ac2PresentStat() ? F("Present") : F("NOT present"));

    s.print(F("  VAC1 Present (bit 1)           : "));
    s.println(ac1PresentStat() ? F("Present") : F("NOT present"));

    s.print(F("  VBUS Present (bit 0)           : "));
    s.println(vbusPresentStat() ? F("Present") : F("NOT present"));

    s.print(F("  Reserved [bit 4]               : "));
    s.println((_raw[0] & kReservedMask) >> 4);

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerStatus0::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bit 4 must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
