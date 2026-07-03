#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 D- ADC Result Register (REG45h, address 0x45)
 *
 * Two-byte read-only register containing the ADC result for D- voltage.
 * The value is unsigned with an LSB of 1 mV.
 *
 * Register layout (16 bits, big-endian on the wire):
 *   _raw[0] = MSB (lower register address byte)
 *   _raw[1] = LSB
 *   Full unsigned 16-bit value: D-_ADC_15:0 (bits 15:0) in millivolts.
 *
 * Conversion: millivolts = (uint16_t(_raw[0]) << 8) | uint16_t(_raw[1])
 *
 * Register size: 2 bytes
 * Access: Read-only [R]
 * LSB: 1 mV
 */
class DminusAdc : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 2-byte register
    explicit DminusAdc()
        : TPS25751Register(Registers::DMINUS_ADC.size) {}

    /// @brief Construct from raw byte array (fixed 2-byte size)
    explicit DminusAdc(const uint8_t* data)
        : TPS25751Register(data, Registers::DMINUS_ADC.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    DminusAdc(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit DminusAdc(Registers::RegisterInfo regInfo)
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
     * @brief D- voltage in millivolts (unsigned, 1 mV/LSB)
     * @return Unsigned millivolt value; 0 if not valid
     */
    uint16_t millivolts() const;

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    void debugPrint(Stream& s = Serial) const override;
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::DMINUS_ADC.size;
};

}  // namespace BQ25798
