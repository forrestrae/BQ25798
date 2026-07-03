#include "BQ25798/BQ25798TemperatureControl.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

TemperatureControl::Treg TemperatureControl::treg() const
{
    // TREG_1:0 — 2-bit field, bits 7:6 (bit position 6, width 2)
    return extractEnum<Treg>(
        6, 2,
        static_cast<uint8_t>(Treg::C120),  // max valid = 3
        Treg::C120                           // default on out-of-range
    );
}

TemperatureControl::Tshut TemperatureControl::tshut() const
{
    // TSHUT_1:0 — 2-bit field, bits 5:4 (bit position 4, width 2)
    return extractEnum<Tshut>(
        4, 2,
        static_cast<uint8_t>(Tshut::C85),  // max valid = 3
        Tshut::C150                          // default on out-of-range
    );
}

bool TemperatureControl::vbusPdEn() const
{
    // VBUS_PD_EN — bit 3
    return extractBits(3, 1) != 0;
}

bool TemperatureControl::vac1PdEn() const
{
    // VAC1_PD_EN — bit 2
    return extractBits(2, 1) != 0;
}

bool TemperatureControl::vac2PdEn() const
{
    // VAC2_PD_EN — bit 1
    return extractBits(1, 1) != 0;
}

bool TemperatureControl::bkupAcfet1On() const
{
    // BKUP_ACFET1_ON — bit 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void TemperatureControl::setTreg(Treg v)
{
    if (!isValid()) return;
    // TREG_1:0 — 2-bit field, bits 7:6 (bit position 6, width 2)
    BQ25798::setField8(_raw, 6, 2, static_cast<uint8_t>(v));
}

void TemperatureControl::setTshut(Tshut v)
{
    if (!isValid()) return;
    // TSHUT_1:0 — 2-bit field, bits 5:4 (bit position 4, width 2)
    BQ25798::setField8(_raw, 4, 2, static_cast<uint8_t>(v));
}

void TemperatureControl::setVbusPdEn(bool on)
{
    if (!isValid()) return;
    // VBUS_PD_EN — bit 3
    BQ25798::setField8(_raw, 3, 1, on ? 1 : 0);
}

void TemperatureControl::setVac1PdEn(bool on)
{
    if (!isValid()) return;
    // VAC1_PD_EN — bit 2
    BQ25798::setField8(_raw, 2, 1, on ? 1 : 0);
}

void TemperatureControl::setVac2PdEn(bool on)
{
    if (!isValid()) return;
    // VAC2_PD_EN — bit 1
    BQ25798::setField8(_raw, 1, 1, on ? 1 : 0);
}

void TemperatureControl::setBkupAcfet1On(bool on)
{
    if (!isValid()) return;
    // BKUP_ACFET1_ON — bit 0
    BQ25798::setField8(_raw, 0, 1, on ? 1 : 0);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void TemperatureControl::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Temperature Control Register (REG16h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  TREG         (bits 7:6): "));
    switch (treg()) {
        case Treg::C60:  s.println(F("60 C"));              break;
        case Treg::C80:  s.println(F("80 C"));              break;
        case Treg::C100: s.println(F("100 C"));             break;
        case Treg::C120: s.println(F("120 C (default)"));   break;
        default:         s.println(F("Unknown"));            break;
    }

    s.print(F("  TSHUT        (bits 5:4): "));
    switch (tshut()) {
        case Tshut::C150: s.println(F("150 C (default)")); break;
        case Tshut::C130: s.println(F("130 C"));           break;
        case Tshut::C120: s.println(F("120 C"));           break;
        case Tshut::C85:  s.println(F("85 C"));            break;
        default:          s.println(F("Unknown"));          break;
    }

    s.print(F("  VBUS_PD_EN   (bit  3): "));
    s.println(vbusPdEn() ? F("Enabled") : F("Disabled (default)"));

    s.print(F("  VAC1_PD_EN   (bit  2): "));
    s.println(vac1PdEn() ? F("Enabled") : F("Disabled (default)"));

    s.print(F("  VAC2_PD_EN   (bit  1): "));
    s.println(vac2PdEn() ? F("Enabled") : F("Disabled (default)"));

    s.print(F("  BKUP_ACFET1_ON (bit 0): "));
    s.println(bkupAcfet1On() ? F("Turn on ACFET1") : F("IDLE (default)"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool TemperatureControl::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
