#include "BQ25798/BQ25798TsAdc.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint16_t TsAdc::raw16() const
{
    if (!isValid() || !isValidSize(kExpectedSize)) return 0;
    // Big-endian: _raw[0] is the MSB (lower register address byte).
    return (uint16_t(_raw[0]) << 8) | uint16_t(_raw[1]);
}

float TsAdc::percent() const
{
    if (!isValid() || !isValidSize(kExpectedSize)) return 0.0f;
    // LSB = 0.0976563 % of REGN (100.0 / 1024.0)
    return static_cast<float>(raw16()) * kLsb;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void TsAdc::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 TS ADC Register (REG3Fh) ==="));

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

    s.print(F("  TS: "));
    s.print(percent());
    s.println(F(" % of REGN"));

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool TsAdc::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
