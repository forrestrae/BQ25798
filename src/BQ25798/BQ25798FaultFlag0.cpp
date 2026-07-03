#include "BQ25798/BQ25798FaultFlag0.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool FaultFlag0::ibatRegFlag() const
{
    // IBAT_REG_FLAG — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool FaultFlag0::vbusOvpFlag() const
{
    // VBUS_OVP_FLAG — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool FaultFlag0::vbatOvpFlag() const
{
    // VBAT_OVP_FLAG — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool FaultFlag0::ibusOcpFlag() const
{
    // IBUS_OCP_FLAG — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool FaultFlag0::ibatOcpFlag() const
{
    // IBAT_OCP_FLAG — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

bool FaultFlag0::convOcpFlag() const
{
    // CONV_OCP_FLAG — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool FaultFlag0::vac2OvpFlag() const
{
    // VAC2_OVP_FLAG — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool FaultFlag0::vac1OvpFlag() const
{
    // VAC1_OVP_FLAG — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void FaultFlag0::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Fault Flag 0 Register (REG26h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  IBAT_REG_FLAG  (bit 7): "));
    s.println(ibatRegFlag() ? F("1 — Enter or exit IBAT regulation") : F("0 — Normal"));

    s.print(F("  VBUS_OVP_FLAG  (bit 6): "));
    s.println(vbusOvpFlag() ? F("1 — Entered VBUS OVP") : F("0 — Normal"));

    s.print(F("  VBAT_OVP_FLAG  (bit 5): "));
    s.println(vbatOvpFlag() ? F("1 — Entered VBAT OVP") : F("0 — Normal"));

    s.print(F("  IBUS_OCP_FLAG  (bit 4): "));
    s.println(ibusOcpFlag() ? F("1 — Entered IBUS OCP") : F("0 — Normal"));

    s.print(F("  IBAT_OCP_FLAG  (bit 3): "));
    s.println(ibatOcpFlag() ? F("1 — Entered discharged OCP") : F("0 — Normal"));

    s.print(F("  CONV_OCP_FLAG  (bit 2): "));
    s.println(convOcpFlag() ? F("1 — Entered converter cycle-by-cycle OCP") : F("0 — Normal"));

    s.print(F("  VAC2_OVP_FLAG  (bit 1): "));
    s.println(vac2OvpFlag() ? F("1 — Entered VAC2 OVP") : F("0 — Normal"));

    s.print(F("  VAC1_OVP_FLAG  (bit 0): "));
    s.println(vac1OvpFlag() ? F("1 — Entered VAC1 OVP") : F("0 — Normal"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool FaultFlag0::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: no reserved bits in this register — all bits are defined flags
    return true;
}

}  // namespace BQ25798
