#include "BQ25798/BQ25798DpdmDriver.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

DpdmDriver::DplusDac DpdmDriver::dplusDac() const
{
    // DPLUS_DAC_2:0 — 3-bit field, bits 7:5 (bit position 5, width 3)
    return extractEnum<DplusDac>(
        5, 3,
        static_cast<uint8_t>(DplusDac::Short),  // max valid = 7
        DplusDac::HIZ                             // default on out-of-range
    );
}

DpdmDriver::DminusDac DpdmDriver::dminusDac() const
{
    // DMINUS_DAC_2:0 — 3-bit field, bits 4:2 (bit position 2, width 3)
    return extractEnum<DminusDac>(
        2, 3,
        static_cast<uint8_t>(DminusDac::Reserved),  // max valid = 7
        DminusDac::HIZ                                // default on out-of-range
    );
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; sibling/reserved bits preserved)
// ---------------------------------------------------------------------------

void DpdmDriver::setDplusDac(DplusDac v)
{
    if (!isValid()) return;
    // DPLUS_DAC_2:0 — 3-bit field, bits 7:5 (bit position 5, width 3)
    BQ25798::setField8(_raw, 5, 3, static_cast<uint8_t>(v));
}

void DpdmDriver::setDminusDac(DminusDac v)
{
    if (!isValid()) return;
    // DMINUS_DAC_2:0 — 3-bit field, bits 4:2 (bit position 2, width 3)
    BQ25798::setField8(_raw, 2, 3, static_cast<uint8_t>(v));
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void DpdmDriver::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 DPDM Driver Register (REG47h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  DPLUS_DAC  (bits 7:5): "));
    switch (dplusDac()) {
        case DplusDac::HIZ:   s.println(F("Hi-Z (default)")); break;
        case DplusDac::V0:    s.println(F("0 V"));            break;
        case DplusDac::V0p6:  s.println(F("0.6 V"));          break;
        case DplusDac::V1p2:  s.println(F("1.2 V"));          break;
        case DplusDac::V2p0:  s.println(F("2.0 V"));          break;
        case DplusDac::V2p7:  s.println(F("2.7 V"));          break;
        case DplusDac::V3p3:  s.println(F("3.3 V"));          break;
        case DplusDac::Short: s.println(F("D+/D- Short"));    break;
        default:              s.println(F("Unknown"));          break;
    }

    s.print(F("  DMINUS_DAC (bits 4:2): "));
    switch (dminusDac()) {
        case DminusDac::HIZ:      s.println(F("Hi-Z (default)")); break;
        case DminusDac::V0:       s.println(F("0 V"));            break;
        case DminusDac::V0p6:     s.println(F("0.6 V"));          break;
        case DminusDac::V1p2:     s.println(F("1.2 V"));          break;
        case DminusDac::V2p0:     s.println(F("2.0 V"));          break;
        case DminusDac::V2p7:     s.println(F("2.7 V"));          break;
        case DminusDac::V3p3:     s.println(F("3.3 V"));          break;
        case DminusDac::Reserved: s.println(F("Reserved (invalid)")); break;
        default:                  s.println(F("Unknown"));         break;
    }

    s.println(F("  (bits 1:0): RESERVED"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool DpdmDriver::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    // Reserved bits 1:0 must be zero
    if (_raw[0] & kReservedMask) return false;
    // DMINUS_DAC value 7h is reserved
    if (dminusDac() == DminusDac::Reserved) return false;
    return true;
}

}  // namespace BQ25798
