#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 NTC Control 1 Register (REG18h, address 0x18)
 *
 * One-byte read/write register configuring NTC thermistor temperature thresholds
 * for JEITA charging and OTG protection, and the TS-ignore option.
 *
 * Register layout (8 bits):
 *   Bits 7:6 — TS_COOL_1:0   JEITA VT2 rising threshold (cool threshold, enum)
 *   Bits 5:4 — TS_WARM_1:0   JEITA VT3 falling threshold (warm threshold, enum)
 *   Bits 3:2 — BHOT_1:0      OTG mode TS HOT threshold (enum)
 *   Bit  1   — BCOLD          OTG mode TS COLD threshold
 *   Bit  0   — TS_IGNORE      Ignore TS feedback (bypass NTC monitoring)
 *
 * Semantic validity:
 *   - No reserved bits; any 8-bit value is structurally valid.
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W]
 * Reset: 0x54 (TS_COOL=0b01, TS_WARM=0b01, BHOT=0b01, BCOLD=0, TS_IGNORE=0)
 */
class NtcControl1 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::NTC_CONTROL_1;

    // -----------------------------------------------------------------------
    // TS_COOL enum — JEITA VT2 rising threshold (bits 7:6)
    // -----------------------------------------------------------------------

    /**
     * @brief JEITA VT2 comparator voltage rising threshold (cool temperature boundary)
     *
     * Expressed as a percentage of REGN. Approximate temperature in brackets
     * assumes 103AT NTC thermistor with RT1=5.24 kΩ and RT2=30.31 kΩ.
     */
    enum class TsCool : uint8_t {
        Pct71p1_5C  = 0,  ///< 71.1% of REGN (~5°C)
        Pct68p4_10C = 1,  ///< 68.4% of REGN (~10°C) (default)
        Pct65p5_15C = 2,  ///< 65.5% of REGN (~15°C)
        Pct62p4_20C = 3,  ///< 62.4% of REGN (~20°C)
    };

    // -----------------------------------------------------------------------
    // TS_WARM enum — JEITA VT3 falling threshold (bits 5:4)
    // -----------------------------------------------------------------------

    /**
     * @brief JEITA VT3 comparator voltage falling threshold (warm temperature boundary)
     *
     * Expressed as a percentage of REGN. Approximate temperature in brackets
     * assumes 103AT NTC thermistor with RT1=5.24 kΩ and RT2=30.31 kΩ.
     */
    enum class TsWarm : uint8_t {
        Pct48p4_40C = 0,  ///< 48.4% of REGN (~40°C)
        Pct44p8_45C = 1,  ///< 44.8% of REGN (~45°C) (default)
        Pct41p2_50C = 2,  ///< 41.2% of REGN (~50°C)
        Pct37p7_55C = 3,  ///< 37.7% of REGN (~55°C)
    };

    // -----------------------------------------------------------------------
    // BHOT enum — OTG mode TS HOT threshold (bits 3:2)
    // -----------------------------------------------------------------------

    /**
     * @brief OTG mode TS HOT temperature threshold
     */
    enum class Bhot : uint8_t {
        Deg55    = 0,  ///< 55°C
        Deg60    = 1,  ///< 60°C (default)
        Deg65    = 2,  ///< 65°C
        Disabled = 3,  ///< Disabled
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit NtcControl1()
        : TPS25751Register(Registers::NTC_CONTROL_1.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit NtcControl1(const uint8_t* data)
        : TPS25751Register(data, Registers::NTC_CONTROL_1.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    NtcControl1(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit NtcControl1(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief JEITA VT2 (cool) threshold — TS_COOL_1:0 (bits 7:6)
     * @return TsCool enum value
     */
    TsCool tsCool() const;

    /**
     * @brief JEITA VT3 (warm) threshold — TS_WARM_1:0 (bits 5:4)
     * @return TsWarm enum value
     */
    TsWarm tsWarm() const;

    /**
     * @brief OTG mode TS HOT threshold — BHOT_1:0 (bits 3:2)
     * @return Bhot enum value
     */
    Bhot bhot() const;

    /**
     * @brief OTG mode TS COLD threshold — BCOLD (bit 1)
     * @return false = -10°C (default), true = -20°C
     */
    bool bcold() const;

    /**
     * @brief TS ignore flag — TS_IGNORE (bit 0)
     * @return true if NTC monitoring is bypassed (charger treats TS as always good)
     */
    bool tsIgnore() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Set JEITA VT2 (cool) threshold — TS_COOL_1:0 (bits 7:6)
    void setTsCool(TsCool v);

    /// @brief Set JEITA VT3 (warm) threshold — TS_WARM_1:0 (bits 5:4)
    void setTsWarm(TsWarm v);

    /// @brief Set OTG mode TS HOT threshold — BHOT_1:0 (bits 3:2)
    void setBhot(Bhot v);

    /// @brief Set OTG mode TS COLD threshold — BCOLD (bit 1); true = -20°C, false = -10°C
    void setBcold(bool on);

    /// @brief Set TS ignore flag — TS_IGNORE (bit 0); true bypasses NTC monitoring
    void setTsIgnore(bool on);

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    /**
     * @brief Print register fields to @p s in a human-readable format
     *
     * Uses F() for every string literal (flash storage on AVR/Teensy).
     * Decodes all enum fields to their descriptive text.
     */
    void debugPrint(Stream& s = Serial) const override;

    /**
     * @brief Semantic validation
     *
     * Returns true when basic validity passes (non-null, correct size).
     * All bits are defined; no reserved bits to check.
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::NTC_CONTROL_1.size;
};

}  // namespace BQ25798
