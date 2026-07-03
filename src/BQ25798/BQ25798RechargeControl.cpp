#include "BQ25798/BQ25798RechargeControl.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

RechargeControl::Cell RechargeControl::cell() const
{
    // CELL_1:0 — 2-bit field, bits 7:6 (bit position 6, width 2)
    return extractEnum<Cell>(
        6, 2,
        static_cast<uint8_t>(Cell::S4),  // max valid = 3
        Cell::S1                          // default on out-of-range
    );
}

RechargeControl::Trechg RechargeControl::trechg() const
{
    // TRECHG_1:0 — 2-bit field, bits 5:4 (bit position 4, width 2)
    return extractEnum<Trechg>(
        4, 2,
        static_cast<uint8_t>(Trechg::Ms2048),  // max valid = 3
        Trechg::Ms1024                           // default on out-of-range
    );
}

uint8_t RechargeControl::vrechgRaw() const
{
    // VRECHG_3:0 — 4-bit field, bits 3:0 (bit position 0, width 4)
    return extractBits(0, 4);
}

uint16_t RechargeControl::millivoltsBelowVreg() const
{
    // 50 mV/LSB, 50 mV minimum offset
    return static_cast<uint16_t>(vrechgRaw()) * 50u + 50u;
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void RechargeControl::setCell(Cell v)
{
    if (!isValid()) return;
    // CELL_1:0 — 2-bit field, bits 7:6 (bit position 6, width 2)
    BQ25798::setField8(_raw, 6, 2, static_cast<uint8_t>(v));
}

void RechargeControl::setTrechg(Trechg v)
{
    if (!isValid()) return;
    // TRECHG_1:0 — 2-bit field, bits 5:4 (bit position 4, width 2)
    BQ25798::setField8(_raw, 4, 2, static_cast<uint8_t>(v));
}

void RechargeControl::setVrechgRaw(uint8_t raw)
{
    if (!isValid()) return;
    // VRECHG_3:0 — 4-bit field, bits 3:0 (bit position 0, width 4)
    BQ25798::setField8(_raw, 0, 4, raw);
}

void RechargeControl::setMillivoltsBelowVreg(uint16_t mv)
{
    if (!isValid()) return;
    // Invert millivoltsBelowVreg() = VRECHG * 50 + 50  ->  VRECHG = (mv - 50) / 50
    // Guard unsigned underflow for offsets at or below the 50 mV minimum.
    const uint8_t code = (mv <= 50u) ? 0u : static_cast<uint8_t>((mv - 50u) / 50u);
    BQ25798::setField8(_raw, 0, 4, code);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void RechargeControl::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Re-Charge Control Register (REG0Ah) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  CELL       (bits 7:6): "));
    switch (cell()) {
        case Cell::S1: s.println(F("1s (1-cell)"));  break;
        case Cell::S2: s.println(F("2s (2-cell)"));  break;
        case Cell::S3: s.println(F("3s (3-cell)"));  break;
        case Cell::S4: s.println(F("4s (4-cell)"));  break;
        default:       s.println(F("Unknown"));       break;
    }

    s.print(F("  TRECHG     (bits 5:4): "));
    switch (trechg()) {
        case Trechg::Ms64:   s.println(F("64 ms"));           break;
        case Trechg::Ms256:  s.println(F("256 ms"));          break;
        case Trechg::Ms1024: s.println(F("1024 ms (default)")); break;
        case Trechg::Ms2048: s.println(F("2048 ms"));         break;
        default:             s.println(F("Unknown"));          break;
    }

    s.print(F("  VRECHG     (bits 3:0): "));
    s.print(vrechgRaw());
    s.print(F(" -> "));
    s.print(millivoltsBelowVreg());
    s.println(F(" mV below VREG"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool RechargeControl::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
