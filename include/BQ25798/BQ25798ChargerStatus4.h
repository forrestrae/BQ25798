#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Status 4 Register (REG1Fh, address 0x1F)
 *
 * One-byte read-only register containing OTG voltage and TS temperature
 * range status flags.
 *
 * Register layout (8 bits):
 *   Bits [7:5] — RESERVED
 *   Bit  4     — VBATOTG_LOW_STAT  Battery voltage too low for OTG
 *   Bit  3     — TS_COLD_STAT      TS temperature in cold range (< T1)
 *   Bit  2     — TS_COOL_STAT      TS temperature in cool range (T1–T2)
 *   Bit  1     — TS_WARM_STAT      TS temperature in warm range (T3–T5)
 *   Bit  0     — TS_HOT_STAT       TS temperature in hot range (> T5)
 *
 * Semantic validity:
 *   - Reserved bits [7:5] must be zero.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class ChargerStatus4 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerStatus4()
        : TPS25751Register(Registers::CHARGER_STATUS_4.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerStatus4(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_STATUS_4.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerStatus4(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerStatus4(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Battery voltage too low for OTG — bit 4
     * @return true if battery voltage is too low to enable OTG operation
     */
    bool vbatOtgLowStat() const;

    /**
     * @brief TS temperature cold range — bit 3
     * @return true if TS temperature is in cold range (below T1)
     */
    bool tsColdStat() const;

    /**
     * @brief TS temperature cool range — bit 2
     * @return true if TS temperature is in cool range (between T1 and T2)
     */
    bool tsCoolStat() const;

    /**
     * @brief TS temperature warm range — bit 1
     * @return true if TS temperature is in warm range (between T3 and T5)
     */
    bool tsWarmStat() const;

    /**
     * @brief TS temperature hot range — bit 0
     * @return true if TS temperature is in hot range (above T5)
     */
    bool tsHotStat() const;

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    /**
     * @brief Print register fields to @p s in a human-readable format
     *
     * Uses F() for every string literal (flash storage on AVR/Teensy).
     */
    void debugPrint(Stream& s = Serial) const override;

    /**
     * @brief Semantic validation
     *
     * Returns true when:
     *   - Basic validity passes (non-null, correct size)
     *   - Reserved bits [7:5] are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_STATUS_4.size;
    static constexpr uint8_t kReservedMask = 0xE0;  ///< Bits [7:5]
};

}  // namespace BQ25798
