#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 TS ADC Result Register (REG3Fh, address 0x3F)
 *
 * Two-byte read-only register containing the ADC result for the TS (thermistor)
 * pin as a percentage of REGN. The value is unsigned with an LSB of 0.0976563 %
 * (i.e. 100/1024 %).
 *
 * Register layout (16 bits, big-endian on the wire):
 *   _raw[0] = MSB (lower register address byte)
 *   _raw[1] = LSB
 *   Full unsigned 16-bit value.
 *
 * Conversion: percent = (float)raw16() * 0.0976563f
 *
 * Register size: 2 bytes
 * Access: Read-only [R]
 * Sign: Unsigned
 * LSB: 0.0976563 % of REGN
 */
class TsAdc : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 2-byte register
    explicit TsAdc()
        : TPS25751Register(Registers::TS_ADC.size) {}

    /// @brief Construct from raw byte array (fixed 2-byte size)
    explicit TsAdc(const uint8_t* data)
        : TPS25751Register(data, Registers::TS_ADC.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    TsAdc(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit TsAdc(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Assembled raw 16-bit register value (big-endian: _raw[0]=MSB, _raw[1]=LSB)
     * @return Raw unsigned 16-bit value, or 0 if not valid
     */
    uint16_t raw16() const;

    /**
     * @brief TS pin voltage as a percentage of REGN
     * @return Percentage (0.0 – ~100.0 %); 0.0f if not valid
     */
    float percent() const;

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
     * @brief Semantic validation — isValid() + correct size (2 bytes)
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t  kExpectedSize = Registers::TS_ADC.size;
    /// LSB in percent-of-REGN (100.0 / 1024.0)
    static constexpr float    kLsb          = 0.0976563f;
};

}  // namespace BQ25798
