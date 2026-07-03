#include "BQ25798/BQ25798VsysAdc.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint16_t VsysAdc::raw16() const
{
    if (!isValid() || !isValidSize(kExpectedSize)) return 0;
    // Big-endian: _raw[0] is the MSB (lower register address byte).
    return (uint16_t(_raw[0]) << 8) | uint16_t(_raw[1]);
}

uint16_t VsysAdc::millivolts() const
{
    // LSB = 1 mV, unsigned — raw16() is already the millivolt count.
    return raw16();
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void VsysAdc::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 VSYS ADC Register (REG3Dh) ==="));

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

    s.print(F("  VSYS: "));
    s.print(millivolts());
    s.println(F(" mV"));

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool VsysAdc::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
