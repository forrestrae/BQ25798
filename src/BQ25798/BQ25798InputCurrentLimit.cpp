#include "BQ25798/BQ25798InputCurrentLimit.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint16_t InputCurrentLimit::raw16() const
{
    if (!isValid() || _len < 2) return 0;
    return static_cast<uint16_t>(static_cast<uint16_t>(_raw[0]) << 8) |
           static_cast<uint16_t>(_raw[1]);
}

uint16_t InputCurrentLimit::iindpmRaw() const
{
    // IINDPM_8:0 — bits 8:0 of the 16-bit big-endian value
    return raw16() & kIindpmMask;
}

uint16_t InputCurrentLimit::milliamps() const
{
    if (!isValid()) return 0;
    return static_cast<uint16_t>(iindpmRaw() * kLsbMa);
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; reserved bits preserved)
// ---------------------------------------------------------------------------

void InputCurrentLimit::setIindpmRaw(uint16_t value)
{
    if (!isValid()) return;
    // IINDPM_8:0 — bits 8:0 of the 16-bit big-endian value
    BQ25798::setField16BE(_raw, 0, 9, value);
}

void InputCurrentLimit::setMilliamps(uint16_t mA)
{
    if (!isValid()) return;
    // Invert mA = IINDPM * 10
    BQ25798::setField16BE(_raw, 0, 9, static_cast<uint16_t>(mA / kLsbMa));
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void InputCurrentLimit::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Input Current Limit Register (REG06h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    const uint16_t r = raw16();

    s.print(F("  IINDPM_8:0 (bits 8:0): "));
    s.print(iindpmRaw());
    s.print(F("  ->  "));
    s.print(milliamps());
    s.println(F(" mA (= IINDPM * 10 mA)"));

    s.print(F("  Reserved [15:9]: 0x"));
    s.println((r & kReservedMask) >> 9, HEX);

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

bool InputCurrentLimit::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bits [15:9] must be zero
    if (raw16() & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
