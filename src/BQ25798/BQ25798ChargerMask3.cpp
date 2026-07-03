#include "BQ25798/BQ25798ChargerMask3.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerMask3::vbatotgLowMask() const { return extractBits(4, 1) != 0; }
bool ChargerMask3::tsColdMask()     const { return extractBits(3, 1) != 0; }
bool ChargerMask3::tsCoolMask()     const { return extractBits(2, 1) != 0; }
bool ChargerMask3::tsWarmMask()     const { return extractBits(1, 1) != 0; }
bool ChargerMask3::tsHotMask()      const { return extractBits(0, 1) != 0; }

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; sibling/reserved bits preserved)
// ---------------------------------------------------------------------------

void ChargerMask3::setVbatotgLowMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 4, 1, masked ? 1 : 0); }
void ChargerMask3::setTsColdMask(bool masked)     { if (!isValid()) return; BQ25798::setField8(_raw, 3, 1, masked ? 1 : 0); }
void ChargerMask3::setTsCoolMask(bool masked)     { if (!isValid()) return; BQ25798::setField8(_raw, 2, 1, masked ? 1 : 0); }
void ChargerMask3::setTsWarmMask(bool masked)     { if (!isValid()) return; BQ25798::setField8(_raw, 1, 1, masked ? 1 : 0); }
void ChargerMask3::setTsHotMask(bool masked)      { if (!isValid()) return; BQ25798::setField8(_raw, 0, 1, masked ? 1 : 0); }

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerMask3::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Mask 3 Register (REG2Bh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.println(F("  (bits 7:5): RESERVED"));
    s.print(F("  VBATOTG_LOW_MASK (bit 4): "));
    s.println(vbatotgLowMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  TS_COLD_MASK     (bit 3): "));
    s.println(tsColdMask()     ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  TS_COOL_MASK     (bit 2): "));
    s.println(tsCoolMask()     ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  TS_WARM_MASK     (bit 1): "));
    s.println(tsWarmMask()     ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  TS_HOT_MASK      (bit 0): "));
    s.println(tsHotMask()      ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerMask3::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    // Reserved bits 7:5 must be zero
    if (_raw[0] & kReservedMask) return false;
    return true;
}

}  // namespace BQ25798
