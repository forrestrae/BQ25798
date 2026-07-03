#include "BQ25798/BQ25798TdieAdc.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint16_t TdieAdc::raw16() const
{
    if (!isValid() || !isValidSize(kExpectedSize)) return 0;
    // Big-endian: _raw[0] is the MSB (lower register address byte).
    return (uint16_t(_raw[0]) << 8) | uint16_t(_raw[1]);
}

float TdieAdc::celsius() const
{
    if (!isValid() || !isValidSize(kExpectedSize)) return 0.0f;
    // Reinterpret raw16() as two's complement signed, then scale by 0.5 °C/LSB.
    return static_cast<float>(static_cast<int16_t>(raw16())) * kLsb;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void TdieAdc::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 TDIE ADC Register (REG41h) ==="));

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

    s.print(F("  TDIE: "));
    s.print(celsius());
    s.println(F(" deg C"));

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool TdieAdc::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
