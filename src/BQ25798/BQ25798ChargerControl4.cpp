#include "BQ25798/BQ25798ChargerControl4.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerControl4::enAcdrv2() const
{
    // EN_ACDRV2 — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool ChargerControl4::enAcdrv1() const
{
    // EN_ACDRV1 — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool ChargerControl4::pwmFreq() const
{
    // PWM_FREQ — bit 5 of byte 0 (1 = 750 kHz, 0 = 1.5 MHz)
    return extractBits(5, 1) != 0;
}

bool ChargerControl4::disStat() const
{
    // DIS_STAT — bit 4 of byte 0 (1 = STAT pin disabled)
    return extractBits(4, 1) != 0;
}

bool ChargerControl4::disVsysShort() const
{
    // DIS_VSYS_SHORT — bit 3 of byte 0 (1 = protection disabled)
    return extractBits(3, 1) != 0;
}

bool ChargerControl4::disVotgUvp() const
{
    // DIS_VOTG_UVP — bit 2 of byte 0 (1 = protection disabled)
    return extractBits(2, 1) != 0;
}

bool ChargerControl4::forceVindpmDet() const
{
    // FORCE_VINDPM_DET — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool ChargerControl4::enIbusOcp() const
{
    // EN_IBUS_OCP — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void ChargerControl4::setEnAcdrv2(bool on)
{
    if (!isValid()) return;
    // EN_ACDRV2 — bit 7 of byte 0
    BQ25798::setField8(_raw, 7, 1, on ? 1 : 0);
}

void ChargerControl4::setEnAcdrv1(bool on)
{
    if (!isValid()) return;
    // EN_ACDRV1 — bit 6 of byte 0
    BQ25798::setField8(_raw, 6, 1, on ? 1 : 0);
}

void ChargerControl4::setPwmFreq(bool on)
{
    if (!isValid()) return;
    // PWM_FREQ — bit 5 of byte 0 (1 = 750 kHz, 0 = 1.5 MHz)
    BQ25798::setField8(_raw, 5, 1, on ? 1 : 0);
}

void ChargerControl4::setDisStat(bool on)
{
    if (!isValid()) return;
    // DIS_STAT — bit 4 of byte 0 (1 = STAT pin disabled)
    BQ25798::setField8(_raw, 4, 1, on ? 1 : 0);
}

void ChargerControl4::setDisVsysShort(bool on)
{
    if (!isValid()) return;
    // DIS_VSYS_SHORT — bit 3 of byte 0 (1 = protection disabled)
    BQ25798::setField8(_raw, 3, 1, on ? 1 : 0);
}

void ChargerControl4::setDisVotgUvp(bool on)
{
    if (!isValid()) return;
    // DIS_VOTG_UVP — bit 2 of byte 0 (1 = protection disabled)
    BQ25798::setField8(_raw, 2, 1, on ? 1 : 0);
}

void ChargerControl4::setForceVindpmDet(bool on)
{
    if (!isValid()) return;
    // FORCE_VINDPM_DET — bit 1 of byte 0 (self-clears when detection completes)
    BQ25798::setField8(_raw, 1, 1, on ? 1 : 0);
}

void ChargerControl4::setEnIbusOcp(bool on)
{
    if (!isValid()) return;
    // EN_IBUS_OCP — bit 0 of byte 0
    BQ25798::setField8(_raw, 0, 1, on ? 1 : 0);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerControl4::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Control 4 Register (REG13h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  EN_ACDRV2        (bit 7): "));
    s.println(enAcdrv2() ? F("ACDRV2 on") : F("ACDRV2 off (default)"));

    s.print(F("  EN_ACDRV1        (bit 6): "));
    s.println(enAcdrv1() ? F("ACDRV1 on") : F("ACDRV1 off (default)"));

    s.print(F("  PWM_FREQ         (bit 5): "));
    s.println(pwmFreq() ? F("750 kHz") : F("1.5 MHz"));

    s.print(F("  DIS_STAT         (bit 4): "));
    s.println(disStat() ? F("STAT pin disabled") : F("STAT pin enabled (default)"));

    s.print(F("  DIS_VSYS_SHORT   (bit 3): "));
    s.println(disVsysShort() ? F("VSYS short protection disabled") : F("VSYS short protection enabled (default)"));

    s.print(F("  DIS_VOTG_UVP     (bit 2): "));
    s.println(disVotgUvp() ? F("VOTG UVP protection disabled") : F("VOTG UVP protection enabled (default)"));

    s.print(F("  FORCE_VINDPM_DET (bit 1): "));
    s.println(forceVindpmDet() ? F("Force VINDPM detection") : F("Normal"));

    s.print(F("  EN_IBUS_OCP      (bit 0): "));
    s.println(enIbusOcp() ? F("IBUS OCP enabled (default)") : F("IBUS OCP disabled"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerControl4::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: all bits defined — no additional semantic constraints
    return true;
}

}  // namespace BQ25798
