#include "BQ25798/BQ25798FaultStatus1.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool FaultStatus1::vsysShortStat() const
{
    // VSYS_SHORT_STAT — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool FaultStatus1::vsysOvpStat() const
{
    // VSYS_OVP_STAT — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool FaultStatus1::otgOvpStat() const
{
    // OTG_OVP_STAT — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool FaultStatus1::otgUvpStat() const
{
    // OTG_UVP_STAT — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool FaultStatus1::tshutStat() const
{
    // TSHUT_STAT — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void FaultStatus1::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Fault Status 1 Register (REG21h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  VSYS Short Circuit (bit 7)     : "));
    s.println(vsysShortStat() ? F("In SYS short circuit protection") : F("Normal"));

    s.print(F("  VSYS Over-Voltage (bit 6)      : "));
    s.println(vsysOvpStat() ? F("In SYS over-voltage protection") : F("Normal"));

    s.print(F("  OTG Over-Voltage (bit 5)       : "));
    s.println(otgOvpStat() ? F("In OTG over-voltage") : F("Normal"));

    s.print(F("  OTG Under-Voltage (bit 4)      : "));
    s.println(otgUvpStat() ? F("In OTG under-voltage") : F("Normal"));

    s.print(F("  Reserved [bit 3]               : "));
    s.println((_raw[0] >> 3) & 1);

    s.print(F("  Thermal Shutdown (bit 2)       : "));
    s.println(tshutStat() ? F("In thermal shutdown protection") : F("Normal"));

    s.print(F("  Reserved [1:0]                 : 0x"));
    s.println(_raw[0] & 0x03, HEX);

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool FaultStatus1::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bits (bit 3, bits [1:0]) must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
