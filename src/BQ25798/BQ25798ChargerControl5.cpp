#include "BQ25798/BQ25798ChargerControl5.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerControl5::sfetPresent() const
{
    // SFET_PRESENT — bit 7 of byte 0
    return extractBits(7, 1) != 0;
}

bool ChargerControl5::enIbat() const
{
    // EN_IBAT — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

ChargerControl5::IbatReg ChargerControl5::ibatReg() const
{
    // IBAT_REG_1:0 — 2-bit field, bits 4:3 (bit position 3, width 2)
    return extractEnum<IbatReg>(
        3, 2,
        static_cast<uint8_t>(IbatReg::Disable),  // max valid = 3
        IbatReg::Disable                          // default on out-of-range
    );
}

bool ChargerControl5::enIindpm() const
{
    // EN_IINDPM — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool ChargerControl5::enExtilim() const
{
    // EN_EXTILIM — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool ChargerControl5::enBatoc() const
{
    // EN_BATOC — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void ChargerControl5::setSfetPresent(bool on)
{
    if (!isValid()) return;
    // SFET_PRESENT — bit 7 of byte 0
    BQ25798::setField8(_raw, 7, 1, on ? 1 : 0);
}

void ChargerControl5::setEnIbat(bool on)
{
    if (!isValid()) return;
    // EN_IBAT — bit 5 of byte 0
    BQ25798::setField8(_raw, 5, 1, on ? 1 : 0);
}

void ChargerControl5::setIbatReg(IbatReg v)
{
    if (!isValid()) return;
    // IBAT_REG_1:0 — bits 4:3 (bit position 3, width 2)
    BQ25798::setField8(_raw, 3, 2, static_cast<uint8_t>(v));
}

void ChargerControl5::setEnIindpm(bool on)
{
    if (!isValid()) return;
    // EN_IINDPM — bit 2 of byte 0
    BQ25798::setField8(_raw, 2, 1, on ? 1 : 0);
}

void ChargerControl5::setEnExtilim(bool on)
{
    if (!isValid()) return;
    // EN_EXTILIM — bit 1 of byte 0
    BQ25798::setField8(_raw, 1, 1, on ? 1 : 0);
}

void ChargerControl5::setEnBatoc(bool on)
{
    if (!isValid()) return;
    // EN_BATOC — bit 0 of byte 0
    BQ25798::setField8(_raw, 0, 1, on ? 1 : 0);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerControl5::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Control 5 Register (REG14h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  SFET_PRESENT (bit 7): "));
    s.println(sfetPresent() ? F("Ship FET populated") : F("No ship FET (default)"));

    s.print(F("  RESERVED     (bit 6): 0x"));
    s.println(extractBits(6, 1), HEX);

    s.print(F("  EN_IBAT      (bit 5): "));
    s.println(enIbat() ? F("IBAT discharge sensing enabled") : F("IBAT discharge sensing disabled (default)"));

    s.print(F("  IBAT_REG     (bits 4:3): "));
    switch (ibatReg()) {
        case IbatReg::A3:      s.println(F("3 A"));             break;
        case IbatReg::A4:      s.println(F("4 A"));             break;
        case IbatReg::A5:      s.println(F("5 A"));             break;
        case IbatReg::Disable: s.println(F("Disabled (default)")); break;
        default:               s.println(F("Unknown"));          break;
    }

    s.print(F("  EN_IINDPM    (bit 2): "));
    s.println(enIindpm() ? F("IINDPM/IOTG enabled (default)") : F("IINDPM/IOTG disabled"));

    s.print(F("  EN_EXTILIM   (bit 1): "));
    s.println(enExtilim() ? F("External ILIM enabled (default)") : F("External ILIM disabled"));

    s.print(F("  EN_BATOC     (bit 0): "));
    s.println(enBatoc() ? F("Battery OCP enabled") : F("Battery OCP disabled (default)"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerControl5::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: reserved bit 6 must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
