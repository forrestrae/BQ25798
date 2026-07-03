#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 ICO Current Limit Register (REG19h, address 0x19)
 *
 * Two-byte read-only register reporting the input current limit as determined
 * by the Input Current Optimiser (ICO) algorithm or the ILIM_HIZ pin setting.
 *
 * Register layout (16 bits, big-endian on the wire):
 *   _raw[0] = MSB (lower register address byte)
 *   _raw[1] = LSB
 *   Bits 15:9 — RESERVED
 *   Bits 8:0  — ICO_ILIM_8:0   ICO-determined input current limit
 *
 * Conversion: milliamps = ICO_ILIM * 10
 *   Range: 0 mA (0x000) to 5120 mA (0x1FF), 10 mA/LSB
 *
 * Semantic validity:
 *   - Reserved bits [15:9] must be zero.
 *
 * Register size: 2 bytes
 * Access: Read-only [R]
 * Reset: 0x0000
 */
class IcoCurrentLimit : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 2-byte register
    explicit IcoCurrentLimit()
        : TPS25751Register(Registers::ICO_CURRENT_LIMIT.size) {}

    /// @brief Construct from raw byte array (fixed 2-byte size)
    explicit IcoCurrentLimit(const uint8_t* data)
        : TPS25751Register(data, Registers::ICO_CURRENT_LIMIT.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    IcoCurrentLimit(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit IcoCurrentLimit(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Assembled raw 16-bit register value (big-endian: _raw[0]=MSB, _raw[1]=LSB)
     * @return Raw unsigned 16-bit value; 0 if not valid
     */
    uint16_t raw16() const;

    /**
     * @brief Raw ICO_ILIM field — ICO_ILIM_8:0 (bits 8:0 of the 16-bit value)
     * @return 9-bit raw value; 0 if not valid
     */
    uint16_t icoIlimRaw() const;

    /**
     * @brief ICO-determined input current limit in milliamps
     *
     * Converts the 9-bit ICO_ILIM field using: mA = ICO_ILIM * 10
     * @return Current in mA; 0 if not valid
     */
    uint16_t milliamps() const;

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
     * @brief Semantic validation
     *
     * Returns true when:
     *   - Basic validity passes (non-null, correct size)
     *   - Reserved bits [15:9] are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t  kExpectedSize  = Registers::ICO_CURRENT_LIMIT.size;
    static constexpr uint16_t kReservedMask  = 0xFE00;  ///< Bits [15:9]
    static constexpr uint16_t kIcoIlimMask   = 0x01FF;  ///< Bits [8:0]
    static constexpr uint16_t kLsbMa         = 10;      ///< mA per LSB
};

}  // namespace BQ25798
