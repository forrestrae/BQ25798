#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Control 0 Register (REG0Fh, address 0x0F)
 *
 * One-byte read/write register controlling automatic and forced battery
 * discharging, charger enable, ICO, HIZ mode, termination, and backup mode.
 *
 * Register layout (8 bits):
 *   Bit 7 — EN_AUTO_IBATDIS  Auto battery discharging during OVP fault
 *   Bit 6 — FORCE_IBATDIS    Force battery discharging current
 *   Bit 5 — EN_CHG           Charger enable
 *   Bit 4 — EN_ICO            Input Current Optimizer enable
 *   Bit 3 — FORCE_ICO        Force ICO start
 *   Bit 2 — EN_HIZ            Enable HIZ mode
 *   Bit 1 — EN_TERM           Enable termination
 *   Bit 0 — EN_BACKUP         Enable backup mode
 *
 * Reset value: 0xA2 (EN_AUTO_IBATDIS=1, EN_CHG=1, EN_TERM=1)
 * Access: Read/Write [R/W]
 */
class ChargerControl0 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGER_CONTROL_0;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerControl0()
        : TPS25751Register(Registers::CHARGER_CONTROL_0.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerControl0(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_CONTROL_0.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerControl0(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerControl0(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Auto battery discharging during battery OVP fault — EN_AUTO_IBATDIS (bit 7)
     * @return true if the charger will apply a discharging current on BAT during OVP
     */
    bool enAutoIbatDis() const;

    /**
     * @brief Force battery discharging current — FORCE_IBATDIS (bit 6)
     * @return true if the charger is forced to apply a discharging current regardless of OVP status
     */
    bool forceIbatDis() const;

    /**
     * @brief Charger enable — EN_CHG (bit 5)
     * @return true if charging is enabled
     */
    bool enChg() const;

    /**
     * @brief Input Current Optimizer enable — EN_ICO (bit 4)
     * @return true if ICO is enabled
     */
    bool enIco() const;

    /**
     * @brief Force ICO start — FORCE_ICO (bit 3)
     * @return true if ICO start is forced (returns 0 after ICO starts; only valid when EN_ICO=1)
     */
    bool forceIco() const;

    /**
     * @brief HIZ mode enable — EN_HIZ (bit 2)
     * @return true if HIZ mode is enabled
     */
    bool enHiz() const;

    /**
     * @brief Termination enable — EN_TERM (bit 1)
     * @return true if termination is enabled
     */
    bool enTerm() const;

    /**
     * @brief Backup mode enable — EN_BACKUP (bit 0)
     * @return true if backup mode is enabled (OTG engages when VBUS droops below REG10 threshold)
     */
    bool enBackup() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own bit)
    // -----------------------------------------------------------------------

    /// @brief Set auto battery discharging during OVP — EN_AUTO_IBATDIS (bit 7)
    void setEnAutoIbatDis(bool on);

    /// @brief Set force battery discharging current — FORCE_IBATDIS (bit 6)
    void setForceIbatDis(bool on);

    /// @brief Set charger enable — EN_CHG (bit 5)
    void setEnChg(bool on);

    /// @brief Set Input Current Optimizer enable — EN_ICO (bit 4)
    void setEnIco(bool on);

    /// @brief Set force ICO start — FORCE_ICO (bit 3)
    void setForceIco(bool on);

    /// @brief Set HIZ mode enable — EN_HIZ (bit 2)
    void setEnHiz(bool on);

    /// @brief Set termination enable — EN_TERM (bit 1)
    void setEnTerm(bool on);

    /// @brief Set backup mode enable — EN_BACKUP (bit 0)
    void setEnBackup(bool on);

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
     * All bits are defined (no reserved bits in this register).
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_CONTROL_0.size;
};

}  // namespace BQ25798
