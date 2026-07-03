#include "BQ25798/BQ25798IotgRegulation.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

IotgRegulation::PrechgTmr IotgRegulation::prechgTmr() const
{
    // PRECHG_TMR — bit 7 (bit position 7, width 1)
    return extractEnum<PrechgTmr>(
        7, 1,
        static_cast<uint8_t>(PrechgTmr::Hours0p5),  // max valid = 1
        PrechgTmr::Hours2                             // default on out-of-range
    );
}

uint8_t IotgRegulation::iotgRaw() const
{
    // IOTG_6:0 — 7-bit field, bits 6:0 (bit position 0, width 7)
    return extractBits(0, 7);
}

uint16_t IotgRegulation::milliamps() const
{
    // 40 mA/LSB, no offset
    return static_cast<uint16_t>(iotgRaw()) * 40u;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; other fields preserved)
// ---------------------------------------------------------------------------

void IotgRegulation::setPrechgTmr(PrechgTmr value)
{
    if (!isValid()) return;
    // PRECHG_TMR — bit 7 (bit position 7, width 1)
    BQ25798::setField8(_raw, 7, 1, static_cast<uint8_t>(value));
}

void IotgRegulation::setIotgRaw(uint8_t value)
{
    if (!isValid()) return;
    // IOTG_6:0 — 7-bit field, bits 6:0 (bit position 0, width 7)
    BQ25798::setField8(_raw, 0, 7, value);
}

void IotgRegulation::setMilliamps(uint16_t mA)
{
    if (!isValid()) return;
    // Invert mA = IOTG * 40
    BQ25798::setField8(_raw, 0, 7, static_cast<uint8_t>(mA / 40u));
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void IotgRegulation::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 IOTG Regulation Register (REG0Dh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  PRECHG_TMR (bit  7): "));
    switch (prechgTmr()) {
        case PrechgTmr::Hours2:   s.println(F("2 hrs (default)")); break;
        case PrechgTmr::Hours0p5: s.println(F("0.5 hrs"));         break;
        default:                  s.println(F("Unknown"));          break;
    }

    s.print(F("  IOTG_6:0   (bits 6:0): "));
    s.print(iotgRaw());
    s.print(F(" -> "));
    s.print(milliamps());
    s.println(F(" mA"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool IotgRegulation::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
