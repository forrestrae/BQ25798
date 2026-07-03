#include "BQ25798/BQ25798ChargerControl0.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerControl0::enAutoIbatDis() const
{
    // EN_AUTO_IBATDIS — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool ChargerControl0::forceIbatDis() const
{
    // FORCE_IBATDIS — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool ChargerControl0::enChg() const
{
    // EN_CHG — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

bool ChargerControl0::enIco() const
{
    // EN_ICO — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool ChargerControl0::forceIco() const
{
    // FORCE_ICO — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

bool ChargerControl0::enHiz() const
{
    // EN_HIZ — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool ChargerControl0::enTerm() const
{
    // EN_TERM — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool ChargerControl0::enBackup() const
{
    // EN_BACKUP — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// Field setters (single-bit read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void ChargerControl0::setEnAutoIbatDis(bool on)
{
    if (!isValid()) return;
    // EN_AUTO_IBATDIS — bit 7 of byte 0
    BQ25798::setField8(_raw, 7, 1, on ? 1 : 0);
}

void ChargerControl0::setForceIbatDis(bool on)
{
    if (!isValid()) return;
    // FORCE_IBATDIS — bit 6 of byte 0
    BQ25798::setField8(_raw, 6, 1, on ? 1 : 0);
}

void ChargerControl0::setEnChg(bool on)
{
    if (!isValid()) return;
    // EN_CHG — bit 5 of byte 0
    BQ25798::setField8(_raw, 5, 1, on ? 1 : 0);
}

void ChargerControl0::setEnIco(bool on)
{
    if (!isValid()) return;
    // EN_ICO — bit 4 of byte 0
    BQ25798::setField8(_raw, 4, 1, on ? 1 : 0);
}

void ChargerControl0::setForceIco(bool on)
{
    if (!isValid()) return;
    // FORCE_ICO — bit 3 of byte 0
    BQ25798::setField8(_raw, 3, 1, on ? 1 : 0);
}

void ChargerControl0::setEnHiz(bool on)
{
    if (!isValid()) return;
    // EN_HIZ — bit 2 of byte 0
    BQ25798::setField8(_raw, 2, 1, on ? 1 : 0);
}

void ChargerControl0::setEnTerm(bool on)
{
    if (!isValid()) return;
    // EN_TERM — bit 1 of byte 0
    BQ25798::setField8(_raw, 1, 1, on ? 1 : 0);
}

void ChargerControl0::setEnBackup(bool on)
{
    if (!isValid()) return;
    // EN_BACKUP — bit 0 of byte 0
    BQ25798::setField8(_raw, 0, 1, on ? 1 : 0);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerControl0::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Control 0 Register (REG0Fh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  EN_AUTO_IBATDIS (bit 7): "));
    s.println(enAutoIbatDis() ? F("Enabled — discharge on OVP") : F("Disabled"));

    s.print(F("  FORCE_IBATDIS   (bit 6): "));
    s.println(forceIbatDis() ? F("Forced discharging") : F("IDLE"));

    s.print(F("  EN_CHG          (bit 5): "));
    s.println(enChg() ? F("Charge Enabled") : F("Charge Disabled"));

    s.print(F("  EN_ICO          (bit 4): "));
    s.println(enIco() ? F("ICO Enabled") : F("ICO Disabled"));

    s.print(F("  FORCE_ICO       (bit 3): "));
    s.println(forceIco() ? F("Force ICO start") : F("Do NOT force ICO"));

    s.print(F("  EN_HIZ          (bit 2): "));
    s.println(enHiz() ? F("HIZ Enabled") : F("HIZ Disabled"));

    s.print(F("  EN_TERM         (bit 1): "));
    s.println(enTerm() ? F("Termination Enabled") : F("Termination Disabled"));

    s.print(F("  EN_BACKUP       (bit 0): "));
    s.println(enBackup() ? F("Backup Mode Enabled") : F("Backup Mode Disabled"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerControl0::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: all bits defined — no additional semantic constraints
    return true;
}

}  // namespace BQ25798
