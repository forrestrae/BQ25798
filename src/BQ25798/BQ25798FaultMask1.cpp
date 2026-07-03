#include "BQ25798/BQ25798FaultMask1.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool FaultMask1::vsysShortMask() const { return extractBits(7, 1) != 0; }
bool FaultMask1::vsysOvpMask()   const { return extractBits(6, 1) != 0; }
bool FaultMask1::otgOvpMask()    const { return extractBits(5, 1) != 0; }
bool FaultMask1::otgUvpMask()    const { return extractBits(4, 1) != 0; }
bool FaultMask1::tshutMask()     const { return extractBits(2, 1) != 0; }

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; sibling/reserved bits preserved)
// ---------------------------------------------------------------------------

void FaultMask1::setVsysShortMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 7, 1, masked ? 1 : 0); }
void FaultMask1::setVsysOvpMask(bool masked)   { if (!isValid()) return; BQ25798::setField8(_raw, 6, 1, masked ? 1 : 0); }
void FaultMask1::setOtgOvpMask(bool masked)    { if (!isValid()) return; BQ25798::setField8(_raw, 5, 1, masked ? 1 : 0); }
void FaultMask1::setOtgUvpMask(bool masked)    { if (!isValid()) return; BQ25798::setField8(_raw, 4, 1, masked ? 1 : 0); }
void FaultMask1::setTshutMask(bool masked)     { if (!isValid()) return; BQ25798::setField8(_raw, 2, 1, masked ? 1 : 0); }

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void FaultMask1::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Fault Mask 1 Register (REG2Dh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  VSYS_SHORT_MASK (bit 7): "));
    s.println(vsysShortMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  VSYS_OVP_MASK   (bit 6): "));
    s.println(vsysOvpMask()   ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  OTG_OVP_MASK    (bit 5): "));
    s.println(otgOvpMask()    ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  OTG_UVP_MASK    (bit 4): "));
    s.println(otgUvpMask()    ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.println(F("  (bit 3): RESERVED"));
    s.print(F("  TSHUT_MASK      (bit 2): "));
    s.println(tshutMask()     ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.println(F("  (bits 1:0): RESERVED"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool FaultMask1::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    // Reserved bits 3, 1, 0 must be zero
    if (_raw[0] & kReservedMask) return false;
    return true;
}

}  // namespace BQ25798
