#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 ADC Function Disable 1 Register (REG30h, address 0x30)
 *
 * One-byte read/write register that individually disables ADC measurements for
 * four additional analog channels (D+, D-, VAC2, VAC1). Each bit disables (1)
 * or enables (0) a specific channel. All channels are enabled by default
 * (reset value 0x00).
 *
 * Register layout (8 bits):
 *   Bit 7    — DP_ADC_DIS    D+ voltage ADC  (0=enabled, 1=disabled)
 *   Bit 6    — DM_ADC_DIS    D- voltage ADC  (0=enabled, 1=disabled)
 *   Bit 5    — VAC2_ADC_DIS  VAC2 voltage ADC (0=enabled, 1=disabled)
 *   Bit 4    — VAC1_ADC_DIS  VAC1 voltage ADC (0=enabled, 1=disabled)
 *   Bits 3:0 — RESERVED [R]
 *
 * Reset value: 0x00 (all ADC channels enabled)
 *
 * Semantic validity:
 *   - Reserved bits [3:0] must be zero.
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W] (bits 3:0 are read-only RESERVED)
 *
 * @note This class extends TPS25751Register — the same device-agnostic decoder
 *       base used by all TPS25751/BQ25798 register classes.
 */
class AdcFunctionDisable1 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::ADC_FUNCTION_DISABLE_1;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit AdcFunctionDisable1()
        : TPS25751Register(Registers::ADC_FUNCTION_DISABLE_1.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit AdcFunctionDisable1(const uint8_t* data)
        : TPS25751Register(data, Registers::ADC_FUNCTION_DISABLE_1.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    AdcFunctionDisable1(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit AdcFunctionDisable1(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors — each returns true when the channel is DISABLED
    // -----------------------------------------------------------------------

    /**
     * @brief DP_ADC_DIS — D+ voltage ADC disable (bit 7)
     * @return true if the D+ ADC channel is disabled
     */
    bool dpAdcDisabled() const;

    /**
     * @brief DM_ADC_DIS — D- voltage ADC disable (bit 6)
     * @return true if the D- ADC channel is disabled
     */
    bool dmAdcDisabled() const;

    /**
     * @brief VAC2_ADC_DIS — VAC2 voltage ADC disable (bit 5)
     * @return true if the VAC2 ADC channel is disabled
     */
    bool vac2AdcDisabled() const;

    /**
     * @brief VAC1_ADC_DIS — VAC1 voltage ADC disable (bit 4)
     * @return true if the VAC1 ADC channel is disabled
     */
    bool vac1AdcDisabled() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // Each setter DISABLES the channel when @p disabled is true (matches decode).
    // -----------------------------------------------------------------------

    /// @brief Set DP_ADC_DIS — D+ voltage ADC disable (bit 7)
    void setDpAdcDisabled(bool disabled);

    /// @brief Set DM_ADC_DIS — D- voltage ADC disable (bit 6)
    void setDmAdcDisabled(bool disabled);

    /// @brief Set VAC2_ADC_DIS — VAC2 voltage ADC disable (bit 5)
    void setVac2AdcDisabled(bool disabled);

    /// @brief Set VAC1_ADC_DIS — VAC1 voltage ADC disable (bit 4)
    void setVac1AdcDisabled(bool disabled);

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
     *   - Reserved bits [3:0] are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize  = Registers::ADC_FUNCTION_DISABLE_1.size;
    static constexpr uint8_t kReservedMask  = 0x0F;  ///< Bits [3:0]
};

}  // namespace BQ25798
