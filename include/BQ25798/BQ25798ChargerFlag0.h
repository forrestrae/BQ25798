#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Flag 0 Register (REG22h, address 0x22)
 *
 * One-byte read-only register containing interrupt flags for input regulation,
 * watchdog, power-good, and VBUS/VAC present events. Each flag bit latches on
 * the rising edge (or any change, for PG_FLAG/AC*_PRESENT_FLAG/VBUS_PRESENT_FLAG)
 * of the corresponding status signal and is cleared by reading this register.
 *
 * Register layout (8 bits):
 *   Bit 7 — IINDPM_FLAG       IINDPM / IOTG rising edge
 *   Bit 6 — VINDPM_FLAG       VINDPM / VOTG regulation rising edge
 *   Bit 5 — WD_FLAG           I2C watchdog timer rising edge
 *   Bit 4 — POORSRC_FLAG      Poor source status rising edge
 *   Bit 3 — PG_FLAG           Any change in PG_STAT
 *   Bit 2 — AC2_PRESENT_FLAG  VAC2 present status changed
 *   Bit 1 — AC1_PRESENT_FLAG  VAC1 present status changed
 *   Bit 0 — VBUS_PRESENT_FLAG VBUS present status changed
 *
 * No reserved bits — all 8 bits are defined flags.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 *
 * @note Extends TPS25751Register — the device-agnostic decoder base shared by
 *       all TPS25751 and BQ25798 register classes.
 */
class ChargerFlag0 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerFlag0()
        : TPS25751Register(Registers::CHARGER_FLAG_0.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerFlag0(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_FLAG_0.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerFlag0(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerFlag0(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors — one per flag bit, bit positions per TRM Table 9-22
    // -----------------------------------------------------------------------

    /// @brief IINDPM_FLAG — bit 7: IINDPM / IOTG rising edge detected
    bool iindpmFlag() const;

    /// @brief VINDPM_FLAG — bit 6: VINDPM / VOTG regulation rising edge detected
    bool vindpmFlag() const;

    /// @brief WD_FLAG — bit 5: I2C watchdog timer rising edge detected
    bool wdFlag() const;

    /// @brief POORSRC_FLAG — bit 4: Poor source status rising edge detected
    bool poorsrcFlag() const;

    /// @brief PG_FLAG — bit 3: Any change in PG_STAT (adapter qualified or lost)
    bool pgFlag() const;

    /// @brief AC2_PRESENT_FLAG — bit 2: VAC2 present status changed
    bool ac2PresentFlag() const;

    /// @brief AC1_PRESENT_FLAG — bit 1: VAC1 present status changed
    bool ac1PresentFlag() const;

    /// @brief VBUS_PRESENT_FLAG — bit 0: VBUS present status changed
    bool vbusPresentFlag() const;

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
     *
     * All 8 bits are defined flags (no reserved bits), so no reserved-bit
     * check is needed.
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_FLAG_0.size;
};

}  // namespace BQ25798
