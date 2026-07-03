#include "BQ25798/BQ25798DminusAdc.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint16_t DminusAdc::raw16() const
{
    if (!isValid() || !isValidSize(kExpectedSize)) return 0;
    // Big-endian: _raw[0] is the MSB (lower register address byte).
    return (uint16_t(_raw[0]) << 8) | uint16_t(_raw[1]);
}

uint16_t DminusAdc::millivolts() const
{
    // LSB = 1 mV, unsigned — raw16() is already the millivolt count.
    return raw16();
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void DminusAdc::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 D- ADC Register (REG45h) ==="));

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

    s.print(F("  D-: "));
    s.print(millivolts());
    s.println(F(" mV"));

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool DminusAdc::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
