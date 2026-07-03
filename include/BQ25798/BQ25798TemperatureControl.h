#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Temperature Control Register (REG16h, address 0x16)
 *
 * One-byte read/write register controlling thermal regulation and shutdown
 * thresholds, pull-down resistor enables, and backup ACFET1 control.
 *
 * Register layout (8 bits):
 *   Bits 7:6 — TREG_1:0       Thermal regulation thresholds (enum)
 *   Bits 5:4 — TSHUT_1:0     Thermal shutdown thresholds (enum)
 *   Bit  3   — VBUS_PD_EN    Enable VBUS pull-down resistor (6 kΩ)
 *   Bit  2   — VAC1_PD_EN    Enable VAC1 pull-down resistor
 *   Bit  1   — VAC2_PD_EN    Enable VAC2 pull-down resistor
 *   Bit  0   — BKUP_ACFET1_ON  Turn on ACFET1 in backup mode
 *
 * Reset value: 0xC0
 * Access: Read/Write [R/W]
 */
class TemperatureControl : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::TEMPERATURE_CONTROL;

    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief TREG_1:0 — thermal regulation threshold (bits 7:6)
     */
    enum class Treg : uint8_t {
        C60  = 0,  ///< 60°C
        C80  = 1,  ///< 80°C
        C100 = 2,  ///< 100°C
        C120 = 3,  ///< 120°C (default)
    };

    /**
     * @brief TSHUT_1:0 — thermal shutdown threshold (bits 5:4)
     */
    enum class Tshut : uint8_t {
        C150 = 0,  ///< 150°C (default)
        C130 = 1,  ///< 130°C
        C120 = 2,  ///< 120°C
        C85  = 3,  ///< 85°C
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit TemperatureControl()
        : TPS25751Register(Registers::TEMPERATURE_CONTROL.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit TemperatureControl(const uint8_t* data)
        : TPS25751Register(data, Registers::TEMPERATURE_CONTROL.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    TemperatureControl(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit TemperatureControl(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Thermal regulation threshold — TREG_1:0 (bits 7:6)
     * @return Treg enum value
     */
    Treg treg() const;

    /**
     * @brief Thermal shutdown threshold — TSHUT_1:0 (bits 5:4)
     * @return Tshut enum value
     */
    Tshut tshut() const;

    /**
     * @brief Enable VBUS pull-down resistor — VBUS_PD_EN (bit 3)
     * @return true if enabled
     */
    bool vbusPdEn() const;

    /**
     * @brief Enable VAC1 pull-down resistor — VAC1_PD_EN (bit 2)
     * @return true if enabled
     */
    bool vac1PdEn() const;

    /**
     * @brief Enable VAC2 pull-down resistor — VAC2_PD_EN (bit 1)
     * @return true if enabled
     */
    bool vac2PdEn() const;

    /**
     * @brief Turn on ACFET1 in backup mode — BKUP_ACFET1_ON (bit 0)
     * @return true if ACFET1 turn-on is requested
     */
    bool bkupAcfet1On() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Set thermal regulation threshold — TREG_1:0 (bits 7:6)
    void setTreg(Treg v);

    /// @brief Set thermal shutdown threshold — TSHUT_1:0 (bits 5:4)
    void setTshut(Tshut v);

    /// @brief Set enable VBUS pull-down resistor — VBUS_PD_EN (bit 3)
    void setVbusPdEn(bool on);

    /// @brief Set enable VAC1 pull-down resistor — VAC1_PD_EN (bit 2)
    void setVac1PdEn(bool on);

    /// @brief Set enable VAC2 pull-down resistor — VAC2_PD_EN (bit 1)
    void setVac2PdEn(bool on);

    /// @brief Set turn-on ACFET1 in backup mode — BKUP_ACFET1_ON (bit 0)
    void setBkupAcfet1On(bool on);

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
    static constexpr uint8_t kExpectedSize = Registers::TEMPERATURE_CONTROL.size;
};

}  // namespace BQ25798
