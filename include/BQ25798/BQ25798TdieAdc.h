#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 TDIE ADC Result Register (REG41h, address 0x41)
 *
 * Two-byte read-only register containing the ADC result for the die temperature.
 * The value is signed (two's complement) with an LSB of 0.5 °C.
 *
 * Register layout (16 bits, big-endian on the wire):
 *   _raw[0] = MSB (lower register address byte)
 *   _raw[1] = LSB
 *   Full signed 16-bit value (two's complement).
 *
 * Conversion: celsius = (float)(int16_t)raw16() * 0.5f
 *
 * Register size: 2 bytes
 * Access: Read-only [R]
 * Sign: SIGNED (int16_t, two's complement)
 * LSB: 0.5 °C
 */
class TdieAdc : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 2-byte register
    explicit TdieAdc()
        : TPS25751Register(Registers::TDIE_ADC.size) {}

    /// @brief Construct from raw byte array (fixed 2-byte size)
    explicit TdieAdc(const uint8_t* data)
        : TPS25751Register(data, Registers::TDIE_ADC.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    TdieAdc(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit TdieAdc(Registers::RegisterInfo regInfo)
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
     * @brief Die temperature in degrees Celsius (signed, 0.5 °C LSB)
     * @return Signed floating-point temperature; 0.0f if not valid
     */
    float celsius() const;

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
    static constexpr uint8_t kExpectedSize = Registers::TDIE_ADC.size;
    /// LSB in degrees Celsius
    static constexpr float   kLsb          = 0.5f;
};

}  // namespace BQ25798
