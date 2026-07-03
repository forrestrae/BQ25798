#include "BQ25798/BQ25798ChargerControl1.h"
#include "BQ25798/BQ25798Encode.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

ChargerControl1::VbusBackup ChargerControl1::vbusBackup() const
{
    // VBUS_BACKUP_1:0 — 2-bit field, bits 7:6 (bit position 6, width 2)
    return extractEnum<VbusBackup>(
        6, 2,
        static_cast<uint8_t>(VbusBackup::Pct100),  // max valid = 3
        VbusBackup::Pct80                           // default on out-of-range
    );
}

ChargerControl1::VacOvp ChargerControl1::vacOvp() const
{
    // VAC_OVP_1:0 — 2-bit field, bits 5:4 (bit position 4, width 2)
    return extractEnum<VacOvp>(
        4, 2,
        static_cast<uint8_t>(VacOvp::V7),  // max valid = 3
        VacOvp::V26                         // default on out-of-range
    );
}

bool ChargerControl1::wdRst() const
{
    // WD_RST — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

ChargerControl1::Watchdog ChargerControl1::watchdog() const
{
    // WATCHDOG_2:0 — 3-bit field, bits 2:0 (bit position 0, width 3)
    return extractEnum<Watchdog>(
        0, 3,
        static_cast<uint8_t>(Watchdog::S160),  // max valid = 7
        Watchdog::S40                           // default on out-of-range
    );
}

// ---------------------------------------------------------------------------
// Field setters (read-modify-write; siblings/reserved bits preserved)
// ---------------------------------------------------------------------------

void ChargerControl1::setVbusBackup(VbusBackup v)
{
    if (!isValid()) return;
    // VBUS_BACKUP_1:0 — bits 7:6 (bit position 6, width 2)
    BQ25798::setField8(_raw, 6, 2, static_cast<uint8_t>(v));
}

void ChargerControl1::setVacOvp(VacOvp v)
{
    if (!isValid()) return;
    // VAC_OVP_1:0 — bits 5:4 (bit position 4, width 2)
    BQ25798::setField8(_raw, 4, 2, static_cast<uint8_t>(v));
}

void ChargerControl1::setWdRst(bool on)
{
    if (!isValid()) return;
    // WD_RST — bit 3 of byte 0 (self-clears after the watchdog timer resets)
    BQ25798::setField8(_raw, 3, 1, on ? 1 : 0);
}

void ChargerControl1::setWatchdog(Watchdog v)
{
    if (!isValid()) return;
    // WATCHDOG_2:0 — bits 2:0 (bit position 0, width 3)
    BQ25798::setField8(_raw, 0, 3, static_cast<uint8_t>(v));
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerControl1::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Control 1 Register (REG10h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  VBUS_BACKUP (bits 7:6): "));
    switch (vbusBackup()) {
        case VbusBackup::Pct40:  s.println(F("40% * VINDPM"));  break;
        case VbusBackup::Pct60:  s.println(F("60% * VINDPM"));  break;
        case VbusBackup::Pct80:  s.println(F("80% * VINDPM (default)"));  break;
        case VbusBackup::Pct100: s.println(F("100% * VINDPM")); break;
        default:                 s.println(F("Unknown"));        break;
    }

    s.print(F("  VAC_OVP     (bits 5:4): "));
    switch (vacOvp()) {
        case VacOvp::V26: s.println(F("26 V (default)")); break;
        case VacOvp::V18: s.println(F("18 V"));           break;
        case VacOvp::V12: s.println(F("12 V"));           break;
        case VacOvp::V7:  s.println(F("7 V"));            break;
        default:          s.println(F("Unknown"));         break;
    }

    s.print(F("  WD_RST      (bit  3): "));
    s.println(wdRst() ? F("Reset requested") : F("Normal"));

    s.print(F("  WATCHDOG    (bits 2:0): "));
    switch (watchdog()) {
        case Watchdog::Disable: s.println(F("Disabled"));        break;
        case Watchdog::S0p5:    s.println(F("0.5 s"));           break;
        case Watchdog::S1:      s.println(F("1 s"));             break;
        case Watchdog::S2:      s.println(F("2 s"));             break;
        case Watchdog::S20:     s.println(F("20 s"));            break;
        case Watchdog::S40:     s.println(F("40 s (default)")); break;
        case Watchdog::S80:     s.println(F("80 s"));            break;
        case Watchdog::S160:    s.println(F("160 s"));           break;
        default:                s.println(F("Unknown"));          break;
    }

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerControl1::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: all bits defined — no additional semantic constraints
    return true;
}

}  // namespace BQ25798
