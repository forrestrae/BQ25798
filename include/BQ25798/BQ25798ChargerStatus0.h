#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Status 0 Register (REG1Bh, address 0x1B)
 *
 * One-byte read-only register containing power-path, power-good, and VBUS
 * presence status flags.
 *
 * Register layout (8 bits):
 *   Bit 7 — IINDPM_STAT    IINDPM/IOTG regulation status
 *   Bit 6 — VINDPM_STAT    VINDPM/VOTG regulation status
 *   Bit 5 — WD_STAT        I2C watchdog timer status
 *   Bit 4 — RESERVED
 *   Bit 3 — PG_STAT        Power Good status
 *   Bit 2 — AC2_PRESENT_STAT  VAC2 insert status
 *   Bit 1 — AC1_PRESENT_STAT  VAC1 insert status
 *   Bit 0 — VBUS_PRESENT_STAT VBUS present status
 *
 * Semantic validity:
 *   - Reserved bit 4 must be zero.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class ChargerStatus0 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerStatus0()
        : TPS25751Register(Registers::CHARGER_STATUS_0.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerStatus0(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_STATUS_0.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerStatus0(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerStatus0(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief IINDPM/IOTG regulation status — bit 7
     * @return true if in IINDPM regulation (forward mode) or IOTG regulation (OTG mode)
     */
    bool iindpmStat() const;

    /**
     * @brief VINDPM/VOTG regulation status — bit 6
     * @return true if in VINDPM regulation (forward mode) or VOTG regulation (OTG mode)
     */
    bool vindpmStat() const;

    /**
     * @brief I2C watchdog timer status — bit 5
     * @return true if watchdog timer has expired
     */
    bool wdStat() const;

    /**
     * @brief Power Good status — bit 3
     * @return true if power good
     */
    bool pgStat() const;

    /**
     * @brief VAC2 insert status — bit 2
     * @return true if VAC2 is present (above present threshold)
     */
    bool ac2PresentStat() const;

    /**
     * @brief VAC1 insert status — bit 1
     * @return true if VAC1 is present (above present threshold)
     */
    bool ac1PresentStat() const;

    /**
     * @brief VBUS present status — bit 0
     * @return true if VBUS is present (above present threshold)
     */
    bool vbusPresentStat() const;

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
     *   - Reserved bit 4 is zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_STATUS_0.size;
    static constexpr uint8_t kReservedMask = 0x10;  ///< Bit 4
};

}  // namespace BQ25798
