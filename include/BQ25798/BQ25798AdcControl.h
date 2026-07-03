#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 ADC Control Register (REG2Eh, address 0x2E)
 *
 * One-byte read/write register that controls the ADC subsystem: enable/disable,
 * conversion rate (continuous vs. one-shot), sample resolution, and averaging.
 *
 * Register layout (8 bits):
 *   Bit  7     — ADC_EN          ADC enable (0=disable, 1=enable)
 *   Bit  6     — ADC_RATE        Conversion rate (0=continuous, 1=one-shot)
 *   Bits 5:4   — ADC_SAMPLE_1:0  Sample resolution (enum, 2 bits)
 *   Bit  3     — ADC_AVG         Averaging mode (0=single, 1=running average)
 *   Bit  2     — ADC_AVG_INIT    Average initial value (0=existing reg, 1=new conversion)
 *   Bits 1:0   — RESERVED
 *
 * Reset value: 0x30 (ADC_EN=0, ADC_RATE=0, ADC_SAMPLE=0b11 [12-bit], AVG=0, AVG_INIT=0)
 *
 * Semantic validity:
 *   - Reserved bits [1:0] must be zero.
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W]
 *
 * @note This class extends TPS25751Register — the same device-agnostic decoder
 *       base used by all TPS25751/BQ25798 register classes.
 */
class AdcControl : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::ADC_CONTROL;

    // -----------------------------------------------------------------------
    // ADC_SAMPLE_1:0 resolution enum (bits 5:4)
    // -----------------------------------------------------------------------

    /**
     * @brief ADC effective sample resolution
     *
     * Encodes the ADC_SAMPLE_1:0 two-bit field (bits 5:4).
     * Lower value = higher resolution but slower conversion.
     */
    enum class SampleResolution : uint8_t {
        Bits15 = 0,  ///< 15-bit effective resolution (default / highest quality)
        Bits14 = 1,  ///< 14-bit effective resolution
        Bits13 = 2,  ///< 13-bit effective resolution
        Bits12 = 3,  ///< 12-bit effective resolution (not recommended)
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit AdcControl()
        : TPS25751Register(Registers::ADC_CONTROL.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit AdcControl(const uint8_t* data)
        : TPS25751Register(data, Registers::ADC_CONTROL.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    AdcControl(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit AdcControl(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief ADC enable — ADC_EN (bit 7)
     * @return true if the ADC is enabled
     */
    bool adcEnabled() const;

    /**
     * @brief ADC conversion rate — ADC_RATE (bit 6)
     * @return true = one-shot, false = continuous
     */
    bool adcOneShot() const;

    /**
     * @brief ADC sample resolution — ADC_SAMPLE_1:0 (bits 5:4)
     * @return SampleResolution enum value
     */
    SampleResolution adcSampleResolution() const;

    /**
     * @brief ADC averaging mode — ADC_AVG (bit 3)
     * @return true = running average, false = single value
     */
    bool adcAveraging() const;

    /**
     * @brief ADC average initial value control — ADC_AVG_INIT (bit 2)
     * @return true = start average from a new conversion,
     *         false = start from existing register value
     */
    bool adcAvgInit() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Set ADC enable — ADC_EN (bit 7)
    void setAdcEnabled(bool on);

    /// @brief Set ADC conversion rate — ADC_RATE (bit 6); true = one-shot, false = continuous
    void setAdcOneShot(bool on);

    /// @brief Set ADC sample resolution — ADC_SAMPLE_1:0 (bits 5:4)
    void setAdcSampleResolution(SampleResolution v);

    /// @brief Set ADC averaging mode — ADC_AVG (bit 3); true = running average
    void setAdcAveraging(bool on);

    /// @brief Set ADC average initial value control — ADC_AVG_INIT (bit 2)
    void setAdcAvgInit(bool on);

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
     *   - Reserved bits [1:0] are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize  = Registers::ADC_CONTROL.size;
    static constexpr uint8_t kReservedMask  = 0x03;  ///< Bits [1:0]
};

}  // namespace BQ25798
