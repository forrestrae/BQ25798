#include "BQ25798/BQ25798ChargerFlag3.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Accessors
// ---------------------------------------------------------------------------

bool ChargerFlag3::vbatotgLowFlag() const
{
    // VBATOTG_LOW_FLAG — bit 4 of byte 0
    return extractBits(4, 1) != 0;
}

bool ChargerFlag3::tsColdFlag() const
{
    // TS_COLD_FLAG — bit 3 of byte 0
    return extractBits(3, 1) != 0;
}

bool ChargerFlag3::tsCoolFlag() const
{
    // TS_COOL_FLAG — bit 2 of byte 0
    return extractBits(2, 1) != 0;
}

bool ChargerFlag3::tsWarmFlag() const
{
    // TS_WARM_FLAG — bit 1 of byte 0
    return extractBits(1, 1) != 0;
}

bool ChargerFlag3::tsHotFlag() const
{
    // TS_HOT_FLAG — bit 0 of byte 0
    return extractBits(0, 1) != 0;
}

// ---------------------------------------------------------------------------
// debugPrint
// ---------------------------------------------------------------------------

void ChargerFlag3::debugPrint(Stream& s) const
{
    s.println(F("=== BQ25798 Charger Flag 3 Register (REG25h) ==="));

    if (!isValid()) {
        s.println(F("  [invalid — no data]"));
        return;
    }

    s.print(F("  RESERVED          (bits 7:5): 0x"));
    s.println((_raw[0] >> 5) & 0x07, HEX);

    s.print(F("  VBATOTG_LOW_FLAG  (bit 4): "));
    s.println(vbatotgLowFlag() ? F("1 — VBAT fell below OTG enable threshold") : F("0 — Normal"));

    s.print(F("  TS_COLD_FLAG      (bit 3): "));
    s.println(tsColdFlag() ? F("1 — TS crossed cold threshold (T1)") : F("0 — Normal"));

    s.print(F("  TS_COOL_FLAG      (bit 2): "));
    s.println(tsCoolFlag() ? F("1 — TS crossed cool threshold (T2)") : F("0 — Normal"));

    s.print(F("  TS_WARM_FLAG      (bit 1): "));
    s.println(tsWarmFlag() ? F("1 — TS crossed warm threshold (T3)") : F("0 — Normal"));

    s.print(F("  TS_HOT_FLAG       (bit 0): "));
    s.println(tsHotFlag() ? F("1 — TS crossed hot threshold (T5)") : F("0 — Normal"));

    s.print(F("  Raw byte: 0x"));
    if (_raw[0] < 0x10) s.print(F("0"));
    s.println(_raw[0], HEX);

    s.println();
}

// ---------------------------------------------------------------------------
// isSemanticallyValid
// ---------------------------------------------------------------------------

bool ChargerFlag3::isSemanticallyValid() const
{
    // Tier 1: basic validity (non-null pointer, non-zero length)
    if (!isValid()) return false;

    // Tier 2: data validity — correct register size
    if (!isValidSize(kExpectedSize)) return false;

    // Tier 3: reserved bits [7:5] must be zero
    if (_raw[0] & kReservedMask) return false;

    return true;
}

}  // namespace BQ25798
