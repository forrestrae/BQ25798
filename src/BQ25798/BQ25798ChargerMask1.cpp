#include "BQ25798/BQ25798ChargerMask1.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerMask1::chgMask()         const { return extractBits(7, 1) != 0; }
bool ChargerMask1::icoMask()         const { return extractBits(6, 1) != 0; }
bool ChargerMask1::vbusMask()        const { return extractBits(4, 1) != 0; }
bool ChargerMask1::tregMask()        const { return extractBits(2, 1) != 0; }
bool ChargerMask1::vbatPresentMask() const { return extractBits(1, 1) != 0; }
bool ChargerMask1::bc12DoneMask()    const { return extractBits(0, 1) != 0; }

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; sibling/reserved bits preserved)
// ---------------------------------------------------------------------------

void ChargerMask1::setChgMask(bool masked)         { if (!isValid()) return; BQ25798::setField8(_raw, 7, 1, masked ? 1 : 0); }
void ChargerMask1::setIcoMask(bool masked)         { if (!isValid()) return; BQ25798::setField8(_raw, 6, 1, masked ? 1 : 0); }
void ChargerMask1::setVbusMask(bool masked)        { if (!isValid()) return; BQ25798::setField8(_raw, 4, 1, masked ? 1 : 0); }
void ChargerMask1::setTregMask(bool masked)        { if (!isValid()) return; BQ25798::setField8(_raw, 2, 1, masked ? 1 : 0); }
void ChargerMask1::setVbatPresentMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 1, 1, masked ? 1 : 0); }
void ChargerMask1::setBc12DoneMask(bool masked)    { if (!isValid()) return; BQ25798::setField8(_raw, 0, 1, masked ? 1 : 0); }

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerMask1::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Mask 1 Register (REG29h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  CHG_MASK          (bit 7): "));
    s.println(chgMask()         ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  ICO_MASK          (bit 6): "));
    s.println(icoMask()         ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.println(F("  (bit 5): RESERVED"));
    s.print(F("  VBUS_MASK         (bit 4): "));
    s.println(vbusMask()        ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.println(F("  (bit 3): RESERVED"));
    s.print(F("  TREG_MASK         (bit 2): "));
    s.println(tregMask()        ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  VBAT_PRESENT_MASK (bit 1): "));
    s.println(vbatPresentMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  BC12_DONE_MASK    (bit 0): "));
    s.println(bc12DoneMask()    ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerMask1::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    // Reserved bits 5 and 3 should be zero
    if (_raw[0] & kReservedMask) return false;
    return true;
}

}  // namespace BQ25798
