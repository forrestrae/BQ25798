#include "BQ25798/BQ25798PartInfo.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

uint8_t PartInfo::partNumber() const
{
    // PN[5:3] — 3-bit field starting at bit 3 of byte 0
    return extractBits(3, 3);
}

uint8_t PartInfo::deviceRevision() const
{
    // DEV_REV[2:0] — 3-bit field starting at bit 0 of byte 0
    return extractBits(0, 3);
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void PartInfo::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Part Information Register (REG48h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    const uint8_t pn  = partNumber();
    const uint8_t rev = deviceRevision();

    s.print(F("  Part Number (PN[5:3])  : 0b"));
    // Print as 3-bit binary, MSB first
    s.print((pn >> 2) & 1);
    s.print((pn >> 1) & 1);
    s.print(pn & 1);
    s.print(F(" ("));
    s.print(pn);
    s.println(F(")"));

    if (pn == kExpectedPN) {
        s.println(F("    -> BQ25798"));
    } else {
        s.println(F("    -> Unknown (expected 011b for BQ25798)"));
    }

    s.print(F("  Device Revision (DEV_REV[2:0]): "));
    s.println(rev);

    s.print(F("  Reserved [7:6]: 0x"));
    if (isValid()) {
        s.println((_raw[0] & kReservedMask) >> 6, HEX);
    }

    s.print(F("  Raw byte: 0x"));
    if (isValid()) {
        if (_raw[0] < 0x10) s.print(F("0"));
        s.println(_raw[0], HEX);
    }

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool PartInfo::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bits [7:6] must be zero
    if (_raw[0] & kReservedMask) return false;

    // Part number must identify a BQ25798
    if (partNumber() != kExpectedPN) return false;

    return true;
}

}  // namespace BQ25798
