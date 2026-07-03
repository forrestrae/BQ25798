#include "BQ25798/BQ25798IcoCurrentLimit.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint16_t IcoCurrentLimit::raw16() const
{
    if (!isValid() || _len < 2) return 0;
    return static_cast<uint16_t>(static_cast<uint16_t>(_raw[0]) << 8) |
           static_cast<uint16_t>(_raw[1]);
}

uint16_t IcoCurrentLimit::icoIlimRaw() const
{
    // ICO_ILIM_8:0 — bits 8:0 of the 16-bit big-endian value
    return raw16() & kIcoIlimMask;
}

uint16_t IcoCurrentLimit::milliamps() const
{
    if (!isValid()) return 0;
    return static_cast<uint16_t>(icoIlimRaw() * kLsbMa);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void IcoCurrentLimit::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 ICO Current Limit Register (REG19h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    const uint16_t r = raw16();

    s.print(F("  ICO_ILIM_8:0 (bits 8:0): "));
    s.print(icoIlimRaw());
    s.print(F("  ->  "));
    s.print(milliamps());
    s.println(F(" mA (= ICO_ILIM * 10 mA)"));

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

bool IcoCurrentLimit::isSemanticallyValid() const
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
