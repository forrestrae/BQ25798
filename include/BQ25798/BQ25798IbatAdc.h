#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 IBAT ADC Result Register (REG33h, address 0x33)
 *
 * Two-byte read-only register containing the ADC result for battery current.
 * The value is signed (two's complement) with an LSB of 1 mA. Positive values
 * indicate charging current; negative values indicate discharge current.
 *
 * Register layout (16 bits, big-endian on the wire):
 *   _raw[0] = MSB (lower register address byte)
 *   _raw[1] = LSB
 *   Full signed 16-bit value interpreted as two's complement milliamps.
 *
 * Conversion: milliamps = (int16_t)((uint16_t(_raw[0]) << 8) | uint16_t(_raw[1]))
 *
 * Register size: 2 bytes
 * Access: Read-only [R]
 * Sign: SIGNED (int16_t, two's complement)
 * LSB: 1 mA
 */
class IbatAdc : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 2-byte register
    explicit IbatAdc()
        : TPS25751Register(Registers::IBAT_ADC.size) {}

    /// @brief Construct from raw byte array (fixed 2-byte size)
    explicit IbatAdc(const uint8_t* data)
        : TPS25751Register(data, Registers::IBAT_ADC.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    IbatAdc(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit IbatAdc(Registers::RegisterInfo regInfo)
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
     * @brief Battery current in milliamps (signed, two's complement)
     * @return Signed milliamp value; positive = charging, negative = discharging; 0 if not valid
     */
    int16_t milliamps() const;

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
    static constexpr uint8_t kExpectedSize = Registers::IBAT_ADC.size;
};

}  // namespace BQ25798
