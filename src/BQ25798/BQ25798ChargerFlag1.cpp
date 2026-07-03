#include "BQ25798/BQ25798ChargerFlag1.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerFlag1::chgFlag() const
{
    // CHG_FLAG — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool ChargerFlag1::icoFlag() const
{
    // ICO_FLAG — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool ChargerFlag1::vbusFlag() const
{
    // VBUS_FLAG — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool ChargerFlag1::tregFlag() const
{
    // TREG_FLAG — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool ChargerFlag1::vbatPresentFlag() const
{
    // VBAT_PRESENT_FLAG — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool ChargerFlag1::bc12DoneFlag() const
{
    // BC1.2_DONE_FLAG — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerFlag1::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Flag 1 Register (REG23h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  CHG_FLAG          (bit 7): "));
    s.println(chgFlag() ? F("1 — Charge status changed") : F("0 — Normal"));

    s.print(F("  ICO_FLAG          (bit 6): "));
    s.println(icoFlag() ? F("1 — ICO status changed") : F("0 — Normal"));

    s.print(F("  RESERVED          (bit 5): "));
    s.println((_raw[0] >> 5) & 1);

    s.print(F("  VBUS_FLAG         (bit 4): "));
    s.println(vbusFlag() ? F("1 — VBUS status changed") : F("0 — Normal"));

    s.print(F("  RESERVED          (bit 3): "));
    s.println((_raw[0] >> 3) & 1);

    s.print(F("  TREG_FLAG         (bit 2): "));
    s.println(tregFlag() ? F("1 — Thermal regulation rising threshold detected") : F("0 — Normal"));

    s.print(F("  VBAT_PRESENT_FLAG (bit 1): "));
    s.println(vbatPresentFlag() ? F("1 — VBAT present status changed") : F("0 — Normal"));

    s.print(F("  BC1.2_DONE_FLAG   (bit 0): "));
    s.println(bc12DoneFlag() ? F("1 — BC1.2 detection status changed") : F("0 — Normal"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerFlag1::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: reserved bits (5, 3) must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
