#include "BQ25798/BQ25798ChargerMask2.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerMask2::dpdmDoneMask()  const { return extractBits(6, 1) != 0; }
bool ChargerMask2::adcDoneMask()   const { return extractBits(5, 1) != 0; }
bool ChargerMask2::vsysMask()      const { return extractBits(4, 1) != 0; }
bool ChargerMask2::chgTmrMask()    const { return extractBits(3, 1) != 0; }
bool ChargerMask2::trichgTmrMask() const { return extractBits(2, 1) != 0; }
bool ChargerMask2::prechgTmrMask() const { return extractBits(1, 1) != 0; }
bool ChargerMask2::topoffTmrMask() const { return extractBits(0, 1) != 0; }

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; sibling/reserved bits preserved)
// ---------------------------------------------------------------------------

void ChargerMask2::setDpdmDoneMask(bool masked)  { if (!isValid()) return; BQ25798::setField8(_raw, 6, 1, masked ? 1 : 0); }
void ChargerMask2::setAdcDoneMask(bool masked)   { if (!isValid()) return; BQ25798::setField8(_raw, 5, 1, masked ? 1 : 0); }
void ChargerMask2::setVsysMask(bool masked)      { if (!isValid()) return; BQ25798::setField8(_raw, 4, 1, masked ? 1 : 0); }
void ChargerMask2::setChgTmrMask(bool masked)    { if (!isValid()) return; BQ25798::setField8(_raw, 3, 1, masked ? 1 : 0); }
void ChargerMask2::setTrichgTmrMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 2, 1, masked ? 1 : 0); }
void ChargerMask2::setPrechgTmrMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 1, 1, masked ? 1 : 0); }
void ChargerMask2::setTopoffTmrMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 0, 1, masked ? 1 : 0); }

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerMask2::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Mask 2 Register (REG2Ah) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.println(F("  (bit 7): RESERVED"));
    s.print(F("  DPDM_DONE_MASK  (bit 6): "));
    s.println(dpdmDoneMask()  ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  ADC_DONE_MASK   (bit 5): "));
    s.println(adcDoneMask()   ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  VSYS_MASK       (bit 4): "));
    s.println(vsysMask()      ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  CHG_TMR_MASK    (bit 3): "));
    s.println(chgTmrMask()    ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  TRICHG_TMR_MASK (bit 2): "));
    s.println(trichgTmrMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  PRECHG_TMR_MASK (bit 1): "));
    s.println(prechgTmrMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  TOPOFF_TMR_MASK (bit 0): "));
    s.println(topoffTmrMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerMask2::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    // Reserved bit 7 should be zero
    if (_raw[0] & kReservedMask) return false;
    return true;
}

}  // namespace BQ25798
