#include "BQ25798/BQ25798ChargerFlag0.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerFlag0::iindpmFlag() const
{
    // IINDPM_FLAG — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool ChargerFlag0::vindpmFlag() const
{
    // VINDPM_FLAG — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool ChargerFlag0::wdFlag() const
{
    // WD_FLAG — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool ChargerFlag0::poorsrcFlag() const
{
    // POORSRC_FLAG — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool ChargerFlag0::pgFlag() const
{
    // PG_FLAG — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

bool ChargerFlag0::ac2PresentFlag() const
{
    // AC2_PRESENT_FLAG — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool ChargerFlag0::ac1PresentFlag() const
{
    // AC1_PRESENT_FLAG — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool ChargerFlag0::vbusPresentFlag() const
{
    // VBUS_PRESENT_FLAG — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerFlag0::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Flag 0 Register (REG22h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  IINDPM_FLAG       (bit 7): "));
    s.println(iindpmFlag() ? F("1 — IINDPM/IOTG rising edge detected") : F("0 — Normal"));

    s.print(F("  VINDPM_FLAG       (bit 6): "));
    s.println(vindpmFlag() ? F("1 — VINDPM/VOTG rising edge detected") : F("0 — Normal"));

    s.print(F("  WD_FLAG           (bit 5): "));
    s.println(wdFlag() ? F("1 — Watchdog timer rising edge detected") : F("0 — Normal"));

    s.print(F("  POORSRC_FLAG      (bit 4): "));
    s.println(poorsrcFlag() ? F("1 — Poor source status rising edge detected") : F("0 — Normal"));

    s.print(F("  PG_FLAG           (bit 3): "));
    s.println(pgFlag() ? F("1 — PG_STAT changed") : F("0 — Normal"));

    s.print(F("  AC2_PRESENT_FLAG  (bit 2): "));
    s.println(ac2PresentFlag() ? F("1 — VAC2 present status changed") : F("0 — Normal"));

    s.print(F("  AC1_PRESENT_FLAG  (bit 1): "));
    s.println(ac1PresentFlag() ? F("1 — VAC1 present status changed") : F("0 — Normal"));

    s.print(F("  VBUS_PRESENT_FLAG (bit 0): "));
    s.println(vbusPresentFlag() ? F("1 — VBUS present status changed") : F("0 — Normal"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerFlag0::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: no reserved bits in this register — all bits are defined flags
    return true;
}

}  // namespace BQ25798
