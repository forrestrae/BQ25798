#include "BQ25798/BQ25798FaultStatus0.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool FaultStatus0::ibatRegStat() const
{
    // IBAT_REG_STAT — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool FaultStatus0::vbusOvpStat() const
{
    // VBUS_OVP_STAT — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool FaultStatus0::vbatOvpStat() const
{
    // VBAT_OVP_STAT — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool FaultStatus0::ibusOcpStat() const
{
    // IBUS_OCP_STAT — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool FaultStatus0::ibatOcpStat() const
{
    // IBAT_OCP_STAT — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

bool FaultStatus0::convOcpStat() const
{
    // CONV_OCP_STAT — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool FaultStatus0::vac2OvpStat() const
{
    // VAC2_OVP_STAT — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool FaultStatus0::vac1OvpStat() const
{
    // VAC1_OVP_STAT — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void FaultStatus0::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Fault Status 0 Register (REG20h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  IBAT Discharge Regulation (7)  : "));
    s.println(ibatRegStat() ? F("In IBAT discharge regulation") : F("Normal"));

    s.print(F("  VBUS Over-Voltage (bit 6)      : "));
    s.println(vbusOvpStat() ? F("In OVP") : F("Normal"));

    s.print(F("  VBAT Over-Voltage (bit 5)      : "));
    s.println(vbatOvpStat() ? F("In OVP") : F("Normal"));

    s.print(F("  IBUS Over-Current (bit 4)      : "));
    s.println(ibusOcpStat() ? F("In OCP") : F("Normal"));

    s.print(F("  IBAT Over-Current (bit 3)      : "));
    s.println(ibatOcpStat() ? F("In OCP") : F("Normal"));

    s.print(F("  Converter Over-Current (bit 2) : "));
    s.println(convOcpStat() ? F("In OCP") : F("Normal"));

    s.print(F("  VAC2 Over-Voltage (bit 1)      : "));
    s.println(vac2OvpStat() ? F("In OVP") : F("Normal"));

    s.print(F("  VAC1 Over-Voltage (bit 0)      : "));
    s.println(vac1OvpStat() ? F("In OVP") : F("Normal"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool FaultStatus0::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: no reserved-bit checks — all 8 bits are defined fault flags
    return true;
}

}  // namespace BQ25798
