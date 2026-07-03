#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Control 1 Register (REG10h, address 0x10)
 *
 * One-byte read/write register controlling backup mode VBUS threshold,
 * VAC overvoltage protection threshold, watchdog reset, and watchdog timer.
 *
 * Register layout (8 bits):
 *   Bits 7:6 — VBUS_BACKUP_1:0  Backup mode VBUS threshold as ratio of VINDPM (enum)
 *   Bits 5:4 — VAC_OVP_1:0      VAC overvoltage protection threshold (enum)
 *   Bit  3   — WD_RST            I2C watchdog timer reset
 *   Bits 2:0 — WATCHDOG_2:0     Watchdog timer setting (enum)
 *
 * Reset value: 0x85 (VBUS_BACKUP=80%VINDPM, VAC_OVP=26V, WD_RST=0, WATCHDOG=40s)
 * Access: Read/Write [R/W]
 */
class ChargerControl1 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGER_CONTROL_1;

    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief VBUS_BACKUP_1:0 — backup mode trigger threshold as a ratio of VINDPM (bits 7:6)
     */
    enum class VbusBackup : uint8_t {
        Pct40 = 0,  ///< 40% * VINDPM
        Pct60 = 1,  ///< 60% * VINDPM
        Pct80 = 2,  ///< 80% * VINDPM (default)
        Pct100 = 3, ///< 100% * VINDPM
    };

    /**
     * @brief VAC_OVP_1:0 — VAC overvoltage protection threshold (bits 5:4)
     */
    enum class VacOvp : uint8_t {
        V26 = 0,  ///< 26 V (default)
        V18 = 1,  ///< 18 V
        V12 = 2,  ///< 12 V
        V7  = 3,  ///< 7 V
    };

    /**
     * @brief WATCHDOG_2:0 — watchdog timer setting (bits 2:0)
     */
    enum class Watchdog : uint8_t {
        Disable = 0,  ///< Watchdog disabled
        S0p5    = 1,  ///< 0.5 s
        S1      = 2,  ///< 1 s
        S2      = 3,  ///< 2 s
        S20     = 4,  ///< 20 s
        S40     = 5,  ///< 40 s (default)
        S80     = 6,  ///< 80 s
        S160    = 7,  ///< 160 s
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerControl1()
        : TPS25751Register(Registers::CHARGER_CONTROL_1.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerControl1(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_CONTROL_1.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerControl1(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerControl1(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Backup mode VBUS threshold — VBUS_BACKUP_1:0 (bits 7:6)
     * @return VbusBackup enum value
     */
    VbusBackup vbusBackup() const;

    /**
     * @brief VAC overvoltage protection threshold — VAC_OVP_1:0 (bits 5:4)
     * @return VacOvp enum value
     */
    VacOvp vacOvp() const;

    /**
     * @brief Watchdog timer reset — WD_RST (bit 3)
     * @return true if reset is requested (bit self-clears after timer resets)
     */
    bool wdRst() const;

    /**
     * @brief Watchdog timer setting — WATCHDOG_2:0 (bits 2:0)
     * @return Watchdog enum value
     */
    Watchdog watchdog() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Set backup mode VBUS threshold — VBUS_BACKUP_1:0 (bits 7:6)
    void setVbusBackup(VbusBackup v);

    /// @brief Set VAC overvoltage protection threshold — VAC_OVP_1:0 (bits 5:4)
    void setVacOvp(VacOvp v);

    /// @brief Request I2C watchdog timer reset — WD_RST (bit 3).
    /// The bit self-clears in hardware after the watchdog timer resets.
    void setWdRst(bool on);

    /// @brief Set watchdog timer setting — WATCHDOG_2:0 (bits 2:0)
    void setWatchdog(Watchdog v);

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
     * Returns true when basic validity and correct register size pass.
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_CONTROL_1.size;
};

}  // namespace BQ25798
