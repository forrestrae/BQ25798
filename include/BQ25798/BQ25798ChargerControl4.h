#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Control 4 Register (REG13h, address 0x13)
 *
 * One-byte read/write register controlling the ACDRV gate drivers, switching
 * frequency, STAT pin, VSYS short protection, VOTG UVP protection, VINDPM
 * detection, and IBUS OCP.
 *
 * Register layout (8 bits):
 *   Bit 7 — EN_ACDRV2          Enable ACFET2-RBFET2 gate driver
 *   Bit 6 — EN_ACDRV1          Enable ACFET1-RBFET1 gate driver
 *   Bit 5 — PWM_FREQ            Switching frequency selection
 *   Bit 4 — DIS_STAT            Disable STAT pin output
 *   Bit 3 — DIS_VSYS_SHORT      Disable forward mode VSYS short protection
 *   Bit 2 — DIS_VOTG_UVP        Disable OTG VOTG UVP protection
 *   Bit 1 — FORCE_VINDPM_DET    Force VINDPM detection
 *   Bit 0 — EN_IBUS_OCP         Enable IBUS OCP in forward mode
 *
 * Reset value: POR-default depends on PROG pin strapping (PWM_FREQ bit)
 * Access: Read/Write [R/W]
 */
class ChargerControl4 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGER_CONTROL_4;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerControl4()
        : TPS25751Register(Registers::CHARGER_CONTROL_4.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerControl4(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_CONTROL_4.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerControl4(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerControl4(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Enable ACFET2-RBFET2 gate driver — EN_ACDRV2 (bit 7)
     * @return true if ACDRV2 is enabled (locked at 0 if no FET populated at POR)
     */
    bool enAcdrv2() const;

    /**
     * @brief Enable ACFET1-RBFET1 gate driver — EN_ACDRV1 (bit 6)
     * @return true if ACDRV1 is enabled (locked at 0 if no FET populated at POR)
     */
    bool enAcdrv1() const;

    /**
     * @brief Switching frequency selection — PWM_FREQ (bit 5)
     * @return true = 750 kHz; false = 1.5 MHz
     */
    bool pwmFreq() const;

    /**
     * @brief Disable STAT pin output — DIS_STAT (bit 4)
     * @return true if STAT pin is disabled
     */
    bool disStat() const;

    /**
     * @brief Disable forward mode VSYS short hiccup protection — DIS_VSYS_SHORT (bit 3)
     * @return true if VSYS short protection is disabled
     */
    bool disVsysShort() const;

    /**
     * @brief Disable OTG mode VOTG UVP hiccup protection — DIS_VOTG_UVP (bit 2)
     * @return true if VOTG UVP protection is disabled
     */
    bool disVotgUvp() const;

    /**
     * @brief Force VINDPM detection — FORCE_VINDPM_DET (bit 1)
     * @return true if VINDPM detection is forced (self-clears when done; requires VBAT>VSYSMIN)
     */
    bool forceVindpmDet() const;

    /**
     * @brief Enable IBUS OCP in forward mode — EN_IBUS_OCP (bit 0)
     * @return true if IBUS OCP is enabled
     */
    bool enIbusOcp() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Enable ACFET2-RBFET2 gate driver — EN_ACDRV2 (bit 7)
    void setEnAcdrv2(bool on);

    /// @brief Enable ACFET1-RBFET1 gate driver — EN_ACDRV1 (bit 6)
    void setEnAcdrv1(bool on);

    /// @brief Set switching frequency — PWM_FREQ (bit 5). true = 750 kHz; false = 1.5 MHz.
    void setPwmFreq(bool on);

    /// @brief Disable STAT pin output — DIS_STAT (bit 4)
    void setDisStat(bool on);

    /// @brief Disable forward mode VSYS short protection — DIS_VSYS_SHORT (bit 3)
    void setDisVsysShort(bool on);

    /// @brief Disable OTG VOTG UVP protection — DIS_VOTG_UVP (bit 2)
    void setDisVotgUvp(bool on);

    /// @brief Force VINDPM detection — FORCE_VINDPM_DET (bit 1).
    /// The bit self-clears in hardware once detection completes.
    void setForceVindpmDet(bool on);

    /// @brief Enable IBUS OCP in forward mode — EN_IBUS_OCP (bit 0)
    void setEnIbusOcp(bool on);

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
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_CONTROL_4.size;
};

}  // namespace BQ25798
