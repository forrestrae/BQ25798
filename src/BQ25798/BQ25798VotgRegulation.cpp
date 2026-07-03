#include "BQ25798/BQ25798VotgRegulation.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint16_t VotgRegulation::raw16() const
{
    if (!isValid() || !isValidSize(kExpectedSize)) return 0;
    // Big-endian: _raw[0] is the MSB (lower register address byte).
    return (uint16_t(_raw[0]) << 8) | uint16_t(_raw[1]);
}

uint16_t VotgRegulation::votgRaw() const
{
    return raw16() & kVotgMask;
}

uint16_t VotgRegulation::millivolts() const
{
    // 10 mV/LSB, 2800 mV offset
    return static_cast<uint16_t>(votgRaw() * 10u + 2800u);
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; reserved bits preserved)
// ---------------------------------------------------------------------------

void VotgRegulation::setVotgRaw(uint16_t value)
{
    if (!isValid()) return;
    // VOTG_10:0 — bits 10:0 of the 16-bit big-endian value
    BQ25798::setField16BE(_raw, 0, 11, value);
}

void VotgRegulation::setMillivolts(uint16_t mV)
{
    if (!isValid()) return;
    // Invert mV = (VOTG * 10) + 2800; guard against unsigned underflow.
    const uint16_t code = (mV <= 2800u) ? 0
                          : static_cast<uint16_t>((mV - 2800u) / 10u);
    BQ25798::setField16BE(_raw, 0, 11, code);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void VotgRegulation::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 VOTG Regulation Register (REG0Bh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    const uint16_t r = raw16();
    s.print(F("  Raw (hex): 0x"));
    if (r < 0x1000) s.print(F("0"));
    if (r < 0x0100) s.print(F("0"));
    if (r < 0x0010) s.print(F("0"));
    s.println(r, HEX);

    s.print(F("  Reserved (bits 15:11): 0x"));
    s.println((r & kReservedMask) >> 11, HEX);

    s.print(F("  VOTG_10:0  (bits 10:0): "));
    s.println(votgRaw());

    s.print(F("  OTG Voltage: "));
    s.print(millivolts());
    s.println(F(" mV"));

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool VotgRegulation::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    // Reserved bits 15:11 must be zero
    if (raw16() & kReservedMask) return false;
    return true;
}

}  // namespace BQ25798
