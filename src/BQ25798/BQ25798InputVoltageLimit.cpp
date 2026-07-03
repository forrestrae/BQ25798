#include "BQ25798/BQ25798InputVoltageLimit.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint8_t InputVoltageLimit::vindpmRaw() const
{
    // VINDPM_7:0 — full byte 0
    return extractBits(0, 8);
}

uint16_t InputVoltageLimit::millivolts() const
{
    if (!isValid()) return 0;
    return static_cast<uint16_t>(static_cast<uint16_t>(vindpmRaw()) * kLsbMv);
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; reserved bits preserved)
// ---------------------------------------------------------------------------

void InputVoltageLimit::setVindpmRaw(uint8_t value)
{
    if (!isValid()) return;
    // VINDPM_7:0 — full byte 0
    BQ25798::setField8(_raw, 0, 8, value);
}

void InputVoltageLimit::setMillivolts(uint16_t mV)
{
    if (!isValid()) return;
    // Invert mV = VINDPM * 100
    BQ25798::setField8(_raw, 0, 8, static_cast<uint8_t>(mV / kLsbMv));
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void InputVoltageLimit::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Input Voltage Limit Register (REG05h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  VINDPM_7:0 (bits 7:0): "));
    s.print(vindpmRaw());
    s.print(F("  ->  "));
    s.print(millivolts());
    s.println(F(" mV (= VINDPM * 100 mV)"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool InputVoltageLimit::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: no reserved bits to check — all 8 bits are defined
    return true;
}

}  // namespace BQ25798
