#include "BQ25798/BQ25798ChargeVoltageLimit.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint16_t ChargeVoltageLimit::raw16() const
{
    if (!isValid() || _len < 2) return 0;
    return static_cast<uint16_t>(static_cast<uint16_t>(_raw[0]) << 8) |
           static_cast<uint16_t>(_raw[1]);
}

uint16_t ChargeVoltageLimit::vregRaw() const
{
    // VREG_10:0 — bits 10:0 of the 16-bit big-endian value
    return raw16() & kVregMask;
}

uint16_t ChargeVoltageLimit::millivolts() const
{
    if (!isValid()) return 0;
    return static_cast<uint16_t>(vregRaw() * kLsbMv);
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; reserved bits preserved)
// ---------------------------------------------------------------------------

void ChargeVoltageLimit::setVregRaw(uint16_t value)
{
    if (!isValid()) return;
    // VREG_10:0 — bits 10:0 of the 16-bit big-endian value
    BQ25798::setField16BE(_raw, 0, 11, value);
}

void ChargeVoltageLimit::setMillivolts(uint16_t mV)
{
    if (!isValid()) return;
    // Invert mV = VREG * 10
    BQ25798::setField16BE(_raw, 0, 11, static_cast<uint16_t>(mV / kLsbMv));
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargeVoltageLimit::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charge Voltage Limit Register (REG01h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    const uint16_t r = raw16();

    s.print(F("  VREG_10:0 (bits 10:0): "));
    s.print(vregRaw());
    s.print(F("  ->  "));
    s.print(millivolts());
    s.println(F(" mV (= VREG * 10 mV)"));

    s.print(F("  Reserved [15:11]: 0x"));
    s.println((r & kReservedMask) >> 11, HEX);

    s.print(F("  Raw 16-bit: 0x"));
    if (r < 0x1000) s.print(F("0"));
    if (r < 0x0100) s.print(F("0"));
    if (r < 0x0010) s.print(F("0"));
    s.println(r, HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargeVoltageLimit::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bits [15:11] must be zero
    if (raw16() & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
