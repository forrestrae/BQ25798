#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Control 3 Register (REG12h, address 0x12)
 *
 * One-byte read/write register controlling ACDRV gating, OTG mode, PFM
 * settings, wake-up delay, LDO mode, and OOA settings.
 *
 * Register layout (8 bits):
 *   Bit 7 — DIS_ACDRV     Disable both ACDRV gate drivers
 *   Bit 6 — EN_OTG        OTG mode enable
 *   Bit 5 — PFM_OTG_DIS   Disable PFM in OTG mode
 *   Bit 4 — PFM_FWD_DIS   Disable PFM in forward mode
 *   Bit 3 — WKUP_DLY      Wake-up-from-ship-mode QON pull-low duration
 *   Bit 2 — DIS_LDO       Disable BATFET LDO mode in pre-charge
 *   Bit 1 — DIS_OTG_OOA   Disable OOA in OTG mode
 *   Bit 0 — DIS_FWD_OOA   Disable OOA in forward mode
 *
 * Reset value: 0x00
 * Access: Read/Write [R/W]
 */
class ChargerControl3 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGER_CONTROL_3;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerControl3()
        : TPS25751Register(Registers::CHARGER_CONTROL_3.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerControl3(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_CONTROL_3.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerControl3(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerControl3(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Disable both ACDRV gate drivers — DIS_ACDRV (bit 7)
     * @return true if both EN_ACDRV1 and EN_ACDRV2 are forced off
     */
    bool disAcdrv() const;

    /**
     * @brief OTG mode enable — EN_OTG (bit 6)
     * @return true if OTG mode is enabled
     */
    bool enOtg() const;

    /**
     * @brief Disable PFM in OTG mode — PFM_OTG_DIS (bit 5)
     * @return true if PFM is disabled in OTG mode
     */
    bool pfmOtgDis() const;

    /**
     * @brief Disable PFM in forward mode — PFM_FWD_DIS (bit 4)
     * @return true if PFM is disabled in forward mode
     */
    bool pfmFwdDis() const;

    /**
     * @brief Wake-up from ship mode QON pull-low duration — WKUP_DLY (bit 3)
     * @return true = 15 ms required; false = 1 s required (default)
     */
    bool wkupDly() const;

    /**
     * @brief Disable BATFET LDO mode in pre-charge — DIS_LDO (bit 2)
     * @return true if LDO mode is disabled
     */
    bool disLdo() const;

    /**
     * @brief Disable OOA in OTG mode — DIS_OTG_OOA (bit 1)
     * @return true if OOA is disabled in OTG mode
     */
    bool disOtgOoa() const;

    /**
     * @brief Disable OOA in forward mode — DIS_FWD_OOA (bit 0)
     * @return true if OOA is disabled in forward mode
     */
    bool disFwdOoa() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Disable both ACDRV gate drivers — DIS_ACDRV (bit 7)
    void setDisAcdrv(bool on);

    /// @brief Enable OTG mode — EN_OTG (bit 6)
    void setEnOtg(bool on);

    /// @brief Disable PFM in OTG mode — PFM_OTG_DIS (bit 5)
    void setPfmOtgDis(bool on);

    /// @brief Disable PFM in forward mode — PFM_FWD_DIS (bit 4)
    void setPfmFwdDis(bool on);

    /// @brief Set wake-up-from-ship-mode QON pull-low duration — WKUP_DLY (bit 3).
    /// true = 15 ms; false = 1 s (default).
    void setWkupDly(bool on);

    /// @brief Disable BATFET LDO mode in pre-charge — DIS_LDO (bit 2)
    void setDisLdo(bool on);

    /// @brief Disable OOA in OTG mode — DIS_OTG_OOA (bit 1)
    void setDisOtgOoa(bool on);

    /// @brief Disable OOA in forward mode — DIS_FWD_OOA (bit 0)
    void setDisFwdOoa(bool on);

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
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_CONTROL_3.size;
};

}  // namespace BQ25798
