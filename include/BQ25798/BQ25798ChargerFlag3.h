#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Flag 3 Register (REG25h, address 0x25)
 *
 * One-byte read-only register containing interrupt flags for OTG low-battery
 * and temperature-sensor (TS) threshold crossing events. Each flag latches on
 * the relevant edge and is cleared by reading this register.
 *
 * Register layout (8 bits):
 *   Bits 7:5 — RESERVED
 *   Bit  4   — VBATOTG_LOW_FLAG  VBAT fell below OTG enable threshold
 *   Bit  3   — TS_COLD_FLAG      TS crossed cold threshold (T1)
 *   Bit  2   — TS_COOL_FLAG      TS crossed cool threshold (T2)
 *   Bit  1   — TS_WARM_FLAG      TS crossed warm threshold (T3)
 *   Bit  0   — TS_HOT_FLAG       TS crossed hot threshold (T5)
 *
 * Reserved bits: 7:5 — must be zero in a valid register read.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class ChargerFlag3 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerFlag3()
        : TPS25751Register(Registers::CHARGER_FLAG_3.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerFlag3(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_FLAG_3.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerFlag3(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerFlag3(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors — one per flag bit, bit positions per TRM Table 9-25
    // -----------------------------------------------------------------------

    /// @brief VBATOTG_LOW_FLAG — bit 4: VBAT fell below OTG enable threshold
    bool vbatotgLowFlag() const;

    /// @brief TS_COLD_FLAG — bit 3: TS crossed cold temperature threshold (T1)
    bool tsColdFlag() const;

    /// @brief TS_COOL_FLAG — bit 2: TS crossed cool temperature threshold (T2)
    bool tsCoolFlag() const;

    /// @brief TS_WARM_FLAG — bit 1: TS crossed warm temperature threshold (T3)
    bool tsWarmFlag() const;

    /// @brief TS_HOT_FLAG — bit 0: TS crossed hot temperature threshold (T5)
    bool tsHotFlag() const;

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    /**
     * @brief Print register fields to @p s in a human-readable format.
     *
     * Uses F() for every string literal (flash storage on AVR/Teensy).
     */
    void debugPrint(Stream& s = Serial) const override;

    /**
     * @brief Semantic validation.
     *
     * Returns true when:
     *   - Basic validity passes (non-null, correct size)
     *   - Size matches the expected 1-byte width
     *   - Reserved bits [7:5] are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize  = Registers::CHARGER_FLAG_3.size;
    static constexpr uint8_t kReservedMask  = 0xE0u;  ///< Bits [7:5]
};

}  // namespace BQ25798
