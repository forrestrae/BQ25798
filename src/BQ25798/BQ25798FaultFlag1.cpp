#include "BQ25798/BQ25798FaultFlag1.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool FaultFlag1::vsysShortFlag() const
{
    // VSYS_SHORT_FLAG — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool FaultFlag1::vsysOvpFlag() const
{
    // VSYS_OVP_FLAG — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool FaultFlag1::otgOvpFlag() const
{
    // OTG_OVP_FLAG — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool FaultFlag1::otgUvpFlag() const
{
    // OTG_UVP_FLAG — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool FaultFlag1::tshutFlag() const
{
    // TSHUT_FLAG — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void FaultFlag1::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Fault Flag 1 Register (REG27h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  VSYS_SHORT_FLAG  (bit 7): "));
    s.println(vsysShortFlag() ? F("1 — Stop switching due to system short") : F("0 — Normal"));

    s.print(F("  VSYS_OVP_FLAG    (bit 6): "));
    s.println(vsysOvpFlag() ? F("1 — Stop switching due to system over-voltage") : F("0 — Normal"));

    s.print(F("  OTG_OVP_FLAG     (bit 5): "));
    s.println(otgOvpFlag() ? F("1 — Stop OTG due to VBUS over-voltage") : F("0 — Normal"));

    s.print(F("  OTG_UVP_FLAG     (bit 4): "));
    s.println(otgUvpFlag() ? F("1 — Stop OTG due to VBUS under-voltage") : F("0 — Normal"));

    s.print(F("  RESERVED         (bit 3): "));
    s.println((_raw[0] >> 3) & 1);

    s.print(F("  TSHUT_FLAG       (bit 2): "));
    s.println(tshutFlag() ? F("1 — Thermal shutdown rising threshold detected") : F("0 — Normal"));

    s.print(F("  RESERVED         (bits 1:0): "));
    s.println(_raw[0] & 0x03);

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool FaultFlag1::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: reserved bits (3, 1:0) must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
