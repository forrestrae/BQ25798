#include "BQ25798/BQ25798TerminationControl.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool TerminationControl::regRst() const
{
    // REG_RST — bit 6 of byte 0
    return extractBits(6, 1) != 0;
}

bool TerminationControl::stopWdChg() const
{
    // STOP_WD_CHG — bit 5 of byte 0
    return extractBits(5, 1) != 0;
}

uint8_t TerminationControl::itermRaw() const
{
    // ITERM_4:0 — 5-bit field starting at bit 0 of byte 0
    return extractBits(0, 5);
}

uint16_t TerminationControl::milliamps() const
{
    if (!isValid()) return 0;
    return static_cast<uint16_t>(static_cast<uint16_t>(itermRaw()) * kLsbMa);
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void TerminationControl::setRegRst(bool on)
{
    if (!isValid()) return;
    // REG_RST — bit 6 of byte 0
    BQ25798::setField8(_raw, 6, 1, on ? 1 : 0);
}

void TerminationControl::setStopWdChg(bool on)
{
    if (!isValid()) return;
    // STOP_WD_CHG — bit 5 of byte 0
    BQ25798::setField8(_raw, 5, 1, on ? 1 : 0);
}

void TerminationControl::setItermRaw(uint8_t raw)
{
    if (!isValid()) return;
    // ITERM_4:0 — 5-bit field starting at bit 0 of byte 0
    BQ25798::setField8(_raw, 0, 5, raw);
}

void TerminationControl::setMilliamps(uint16_t ma)
{
    if (!isValid()) return;
    // Invert milliamps() = ITERM * 40 mA  ->  ITERM = ma / 40
    const uint8_t code = static_cast<uint8_t>(ma / kLsbMa);
    BQ25798::setField8(_raw, 0, 5, code);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void TerminationControl::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Termination Control Register (REG09h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  REG_RST     (bit 6): "));
    s.println(regRst() ? F("Reset in progress") : F("Not reset"));

    s.print(F("  STOP_WD_CHG (bit 5): "));
    s.println(stopWdChg() ? F("WD expiry disables charging") : F("WD expiry keeps EN_CHG setting"));

    s.print(F("  ITERM_4:0 (bits 4:0): "));
    s.print(itermRaw());
    s.print(F("  ->  "));
    s.print(milliamps());
    s.println(F(" mA (= ITERM * 40 mA)"));

    s.print(F("  Reserved [bit 7]: "));
    s.println((_raw[0] & kReservedMask) >> 7);

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool TerminationControl::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bit 7 must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
