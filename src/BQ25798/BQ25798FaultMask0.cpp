#include "BQ25798/BQ25798FaultMask0.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool FaultMask0::ibatRegMask()  const { return extractBits(7, 1) != 0; }
bool FaultMask0::vbusOvpMask()  const { return extractBits(6, 1) != 0; }
bool FaultMask0::vbatOvpMask()  const { return extractBits(5, 1) != 0; }
bool FaultMask0::ibusOcpMask()  const { return extractBits(4, 1) != 0; }
bool FaultMask0::ibatOcpMask()  const { return extractBits(3, 1) != 0; }
bool FaultMask0::convOcpMask()  const { return extractBits(2, 1) != 0; }
bool FaultMask0::vac2OvpMask()  const { return extractBits(1, 1) != 0; }
bool FaultMask0::vac1OvpMask()  const { return extractBits(0, 1) != 0; }

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; sibling bits preserved)
// ---------------------------------------------------------------------------

void FaultMask0::setIbatRegMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 7, 1, masked ? 1 : 0); }
void FaultMask0::setVbusOvpMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 6, 1, masked ? 1 : 0); }
void FaultMask0::setVbatOvpMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 5, 1, masked ? 1 : 0); }
void FaultMask0::setIbusOcpMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 4, 1, masked ? 1 : 0); }
void FaultMask0::setIbatOcpMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 3, 1, masked ? 1 : 0); }
void FaultMask0::setConvOcpMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 2, 1, masked ? 1 : 0); }
void FaultMask0::setVac2OvpMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 1, 1, masked ? 1 : 0); }
void FaultMask0::setVac1OvpMask(bool masked) { if (!isValid()) return; BQ25798::setField8(_raw, 0, 1, masked ? 1 : 0); }

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void FaultMask0::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Fault Mask 0 Register (REG2Ch) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  IBAT_REG_MASK (bit 7): "));
    s.println(ibatRegMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  VBUS_OVP_MASK (bit 6): "));
    s.println(vbusOvpMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  VBAT_OVP_MASK (bit 5): "));
    s.println(vbatOvpMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  IBUS_OCP_MASK (bit 4): "));
    s.println(ibusOcpMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  IBAT_OCP_MASK (bit 3): "));
    s.println(ibatOcpMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  CONV_OCP_MASK (bit 2): "));
    s.println(convOcpMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  VAC2_OVP_MASK (bit 1): "));
    s.println(vac2OvpMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));
    s.print(F("  VAC1_OVP_MASK (bit 0): "));
    s.println(vac1OvpMask() ? F("Masked (no INT)") : F("Unmasked (INT enabled)"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool FaultMask0::isSemanticallyValid() const
{
    if (!isValid()) return false;
    if (!isValidSize(kExpectedSize)) return false;
    return true;
}

}  // namespace BQ25798
