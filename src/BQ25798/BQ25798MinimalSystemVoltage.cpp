#include "BQ25798/BQ25798MinimalSystemVoltage.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint8_t MinimalSystemVoltage::vsysminRaw() const
{
    // VSYSMIN_5:0 — 6-bit field starting at bit 0 of byte 0
    return extractBits(0, 6);
}

uint16_t MinimalSystemVoltage::millivolts() const
{
    if (!isValid()) return 0;
    return static_cast<uint16_t>(kOffsetMv + static_cast<uint16_t>(vsysminRaw()) * kLsbMv);
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; reserved bits preserved)
// ---------------------------------------------------------------------------

void MinimalSystemVoltage::setVsysminRaw(uint8_t value)
{
    if (!isValid()) return;
    // VSYSMIN_5:0 — 6-bit field starting at bit 0 of byte 0
    BQ25798::setField8(_raw, 0, 6, value);
}

void MinimalSystemVoltage::setMillivolts(uint16_t mV)
{
    if (!isValid()) return;
    // Invert mV = 2500 + (VSYSMIN * 250); guard against unsigned underflow.
    const uint16_t code = (mV <= kOffsetMv) ? 0
                          : static_cast<uint16_t>((mV - kOffsetMv) / kLsbMv);
    BQ25798::setField8(_raw, 0, 6, static_cast<uint8_t>(code));
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void MinimalSystemVoltage::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Minimal System Voltage Register (REG00h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    const uint8_t raw = vsysminRaw();

    s.print(F("  VSYSMIN_5:0 (bits 5:0): "));
    s.print(raw);
    s.print(F("  ->  "));
    s.print(millivolts());
    s.println(F(" mV (= 2500 + VSYSMIN * 250 mV)"));

    s.print(F("  Reserved [7:6]: 0x"));
    s.println((_raw[0] & kReservedMask) >> 6, HEX);

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool MinimalSystemVoltage::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bits [7:6] must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
