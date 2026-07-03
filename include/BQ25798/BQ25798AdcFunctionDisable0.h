#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 ADC Function Disable 0 Register (REG2Fh, address 0x2F)
 *
 * One-byte read/write register that individually disables ADC measurements for
 * seven analog channels. Each bit disables (1) or enables (0) a specific channel.
 * All channels are enabled by default (reset value 0x00).
 *
 * Register layout (8 bits):
 *   Bit 7  — IBUS_ADC_DIS  Bus current ADC    (0=enabled, 1=disabled)
 *   Bit 6  — IBAT_ADC_DIS  Battery current ADC (0=enabled, 1=disabled)
 *   Bit 5  — VBUS_ADC_DIS  Bus voltage ADC     (0=enabled, 1=disabled)
 *   Bit 4  — VBAT_ADC_DIS  Battery voltage ADC (0=enabled, 1=disabled)
 *   Bit 3  — VSYS_ADC_DIS  System voltage ADC  (0=enabled, 1=disabled)
 *   Bit 2  — TS_ADC_DIS    Temperature sensor ADC (0=enabled, 1=disabled)
 *   Bit 1  — TDIE_ADC_DIS  Die temperature ADC (0=enabled, 1=disabled)
 *   Bit 0  — RESERVED [R]
 *
 * Reset value: 0x00 (all ADC channels enabled)
 *
 * Semantic validity:
 *   - Reserved bit [0] must be zero.
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W] (bit 0 is read-only RESERVED)
 *
 * @note This class extends TPS25751Register — the same device-agnostic decoder
 *       base used by all TPS25751/BQ25798 register classes.
 */
class AdcFunctionDisable0 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::ADC_FUNCTION_DISABLE_0;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit AdcFunctionDisable0()
        : TPS25751Register(Registers::ADC_FUNCTION_DISABLE_0.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit AdcFunctionDisable0(const uint8_t* data)
        : TPS25751Register(data, Registers::ADC_FUNCTION_DISABLE_0.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    AdcFunctionDisable0(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit AdcFunctionDisable0(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors — each returns true when the channel is DISABLED
    // -----------------------------------------------------------------------

    /**
     * @brief IBUS_ADC_DIS — bus current ADC disable (bit 7)
     * @return true if the IBUS ADC channel is disabled
     */
    bool ibusAdcDisabled() const;

    /**
     * @brief IBAT_ADC_DIS — battery current ADC disable (bit 6)
     * @return true if the IBAT ADC channel is disabled
     */
    bool ibatAdcDisabled() const;

    /**
     * @brief VBUS_ADC_DIS — bus voltage ADC disable (bit 5)
     * @return true if the VBUS ADC channel is disabled
     */
    bool vbusAdcDisabled() const;

    /**
     * @brief VBAT_ADC_DIS — battery voltage ADC disable (bit 4)
     * @return true if the VBAT ADC channel is disabled
     */
    bool vbatAdcDisabled() const;

    /**
     * @brief VSYS_ADC_DIS — system voltage ADC disable (bit 3)
     * @return true if the VSYS ADC channel is disabled
     */
    bool vsysAdcDisabled() const;

    /**
     * @brief TS_ADC_DIS — temperature sensor ADC disable (bit 2)
     * @return true if the TS ADC channel is disabled
     */
    bool tsAdcDisabled() const;

    /**
     * @brief TDIE_ADC_DIS — die temperature ADC disable (bit 1)
     * @return true if the TDIE ADC channel is disabled
     */
    bool tdieAdcDisabled() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // Each setter DISABLES the channel when @p disabled is true (matches decode).
    // -----------------------------------------------------------------------

    /// @brief Set IBUS_ADC_DIS — bus current ADC disable (bit 7)
    void setIbusAdcDisabled(bool disabled);

    /// @brief Set IBAT_ADC_DIS — battery current ADC disable (bit 6)
    void setIbatAdcDisabled(bool disabled);

    /// @brief Set VBUS_ADC_DIS — bus voltage ADC disable (bit 5)
    void setVbusAdcDisabled(bool disabled);

    /// @brief Set VBAT_ADC_DIS — battery voltage ADC disable (bit 4)
    void setVbatAdcDisabled(bool disabled);

    /// @brief Set VSYS_ADC_DIS — system voltage ADC disable (bit 3)
    void setVsysAdcDisabled(bool disabled);

    /// @brief Set TS_ADC_DIS — temperature sensor ADC disable (bit 2)
    void setTsAdcDisabled(bool disabled);

    /// @brief Set TDIE_ADC_DIS — die temperature ADC disable (bit 1)
    void setTdieAdcDisabled(bool disabled);

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
     *   - Reserved bit [0] is zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize  = Registers::ADC_FUNCTION_DISABLE_0.size;
    static constexpr uint8_t kReservedMask  = 0x01;  ///< Bit [0]
};

}  // namespace BQ25798
