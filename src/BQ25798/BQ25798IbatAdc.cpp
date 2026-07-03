#include "BQ25798/BQ25798IbatAdc.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint16_t IbatAdc::raw16() const
{
    if (!isValid() || !isValidSize(kExpectedSize)) return 0;
    // Big-endian: _raw[0] is the MSB (lower register address byte).
    return (uint16_t(_raw[0]) << 8) | uint16_t(_raw[1]);
}

int16_t IbatAdc::milliamps() const
{
    if (!isValid() || !isValidSize(kExpectedSize)) return 0;
    // Reinterpret the unsigned assembly as two's complement signed.
    return static_cast<int16_t>(raw16());
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void IbatAdc::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 IBAT ADC Register (REG33h) ==="));

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

    s.print(F("  IBAT: "));
    s.print(milliamps());
    s.println(F(" mA"));

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool IbatAdc::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
