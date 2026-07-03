#include "BQ25798/BQ25798ChargerStatus4.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerStatus4::vbatOtgLowStat() const
{
    // VBATOTG_LOW_STAT — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool ChargerStatus4::tsColdStat() const
{
    // TS_COLD_STAT — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

bool ChargerStatus4::tsCoolStat() const
{
    // TS_COOL_STAT — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool ChargerStatus4::tsWarmStat() const
{
    // TS_WARM_STAT — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool ChargerStatus4::tsHotStat() const
{
    // TS_HOT_STAT — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerStatus4::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Status 4 Register (REG1Fh) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  Reserved [7:5]                 : 0x"));
    s.println((_raw[0] & kReservedMask) >> 5, HEX);

    s.print(F("  VBAT Too Low for OTG (bit 4)   : "));
    s.println(vbatOtgLowStat() ? F("Too low for OTG") : F("High enough for OTG"));

    s.print(F("  TS Cold (bit 3, < T1)          : "));
    s.println(tsColdStat() ? F("In cold range") : F("NOT in cold range"));

    s.print(F("  TS Cool (bit 2, T1-T2)         : "));
    s.println(tsCoolStat() ? F("In cool range") : F("NOT in cool range"));

    s.print(F("  TS Warm (bit 1, T3-T5)         : "));
    s.println(tsWarmStat() ? F("In warm range") : F("NOT in warm range"));

    s.print(F("  TS Hot (bit 0, > T5)           : "));
    s.println(tsHotStat() ? F("In hot range") : F("NOT in hot range"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerStatus4::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: semantic checks
    // Reserved bits [7:5] must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
