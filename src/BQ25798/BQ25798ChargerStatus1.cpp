#include "BQ25798/BQ25798ChargerStatus1.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

ChargerStatus1::ChgStat ChargerStatus1::chgStat() const
{
    // CHG_STAT[2:0] — bits [7:5] of byte 0 (3-bit field starting at bit 5)
    return extractEnum<ChgStat>(5, 3,
        static_cast<uint8_t>(ChgStat::TerminationDone),
        ChgStat::NotCharging);
}

ChargerStatus1::VbusStat ChargerStatus1::vbusStat() const
{
    // VBUS_STAT[3:0] — bits [4:1] of byte 0 (4-bit field starting at bit 1)
    return extractEnum<VbusStat>(1, 4,
        static_cast<uint8_t>(VbusStat::ReservedF),
        VbusStat::NoInputOrOtg);
}

bool ChargerStatus1::bc12DoneStat() const
{
    // BC1.2_DONE_STAT — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerStatus1::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Status 1 Register (REG1Ch) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    // CHG_STAT
    s.print(F("  Charge Status (bits [7:5])     : "));
    switch (chgStat()) {
        case ChgStat::NotCharging:     s.println(F("Not Charging"));                     break;
        case ChgStat::TrickleCharge:   s.println(F("Trickle Charge"));                   break;
        case ChgStat::Precharge:       s.println(F("Pre-charge"));                       break;
        case ChgStat::FastCharge:      s.println(F("Fast Charge (CC mode)"));            break;
        case ChgStat::TaperCharge:     s.println(F("Taper Charge (CV mode)"));           break;
        case ChgStat::Reserved:        s.println(F("Reserved"));                         break;
        case ChgStat::TopOff:          s.println(F("Top-off Timer Active Charging"));    break;
        case ChgStat::TerminationDone: s.println(F("Charge Termination Done"));          break;
        default:                       s.println(F("Unknown"));                          break;
    }

    // VBUS_STAT
    s.print(F("  VBUS Status (bits [4:1])       : "));
    switch (vbusStat()) {
        case VbusStat::NoInputOrOtg:       s.println(F("No Input / BHOT / BCOLD (OTG)"));        break;
        case VbusStat::UsbSdp:             s.println(F("USB SDP (500 mA)"));                     break;
        case VbusStat::UsbCdp:             s.println(F("USB CDP (1.5 A)"));                      break;
        case VbusStat::UsbDcp:             s.println(F("USB DCP (3.25 A)"));                     break;
        case VbusStat::Hvdcp:              s.println(F("Adjustable HVDCP (1.5 A)"));             break;
        case VbusStat::UnknownAdapter:     s.println(F("Unknown Adapter (3 A)"));                break;
        case VbusStat::NonStandardAdapter: s.println(F("Non-Standard Adapter (1/2/2.1/2.4 A)")); break;
        case VbusStat::OtgMode:            s.println(F("OTG Mode"));                             break;
        case VbusStat::NotQualified:       s.println(F("Not Qualified Adapter"));                break;
        case VbusStat::Reserved9:          s.println(F("Reserved (9h)"));                        break;
        case VbusStat::ReservedA:          s.println(F("Reserved (Ah)"));                        break;
        case VbusStat::DirectVbus:         s.println(F("Device Powered Directly from VBUS"));    break;
        case VbusStat::BackupMode:         s.println(F("Backup Mode"));                          break;
        case VbusStat::ReservedD:          s.println(F("Reserved (Dh)"));                        break;
        case VbusStat::ReservedE:          s.println(F("Reserved (Eh)"));                        break;
        case VbusStat::ReservedF:          s.println(F("Reserved (Fh)"));                        break;
        default:                           s.println(F("Unknown"));                              break;
    }

    s.print(F("  BC1.2 / Non-Std Detection Done : "));
    s.println(bc12DoneStat() ? F("Complete") : F("NOT complete"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerStatus1::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: no reserved-bit checks — all 8 bits are defined fields
    return true;
}

}  // namespace BQ25798
