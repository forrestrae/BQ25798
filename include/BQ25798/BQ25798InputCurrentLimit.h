#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Input Current Limit Register (REG06h, address 0x06)
 *
 * Two-byte read/write register setting the input current limit (IINDPM).
 * The limit is automatically set by D+/D- detection at plug-in but can be
 * overridden by writing this register.
 *
 * Register layout (16 bits, big-endian on the wire):
 *   _raw[0] = MSB (lower register address byte)
 *   _raw[1] = LSB
 *   Bits 15:9 — RESERVED
 *   Bits 8:0  — IINDPM_8:0   Input current limit
 *
 * Conversion: milliamps = IINDPM * 10
 *   Range: 0 mA (0x000) to 5120 mA (0x1FF), 10 mA/LSB
 *
 * Semantic validity:
 *   - Reserved bits [15:9] must be zero.
 *
 * Register size: 2 bytes
 * Access: Read/Write [R/W]
 */
class InputCurrentLimit : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::INPUT_CURRENT_LIMIT;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 2-byte register
    explicit InputCurrentLimit()
        : TPS25751Register(Registers::INPUT_CURRENT_LIMIT.size) {}

    /// @brief Construct from raw byte array (fixed 2-byte size)
    explicit InputCurrentLimit(const uint8_t* data)
        : TPS25751Register(data, Registers::INPUT_CURRENT_LIMIT.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    InputCurrentLimit(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit InputCurrentLimit(Registers::RegisterInfo regInfo)
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
     * @brief Raw IINDPM field — IINDPM_8:0 (bits 8:0 of the 16-bit value)
     * @return 9-bit raw value; 0 if not valid
     */
    uint16_t iindpmRaw() const;

    /**
     * @brief Input current limit in milliamps
     *
     * Converts the 9-bit IINDPM field using: mA = IINDPM * 10
     * @return Current in mA; 0 if not valid
     */
    uint16_t milliamps() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /**
     * @brief Set raw IINDPM field — IINDPM_8:0 (bits 8:0 of the 16-bit value)
     * @param value 9-bit raw value (masked to 9 bits)
     */
    void setIindpmRaw(uint16_t value);

    /**
     * @brief Set input current limit from milliamps
     *
     * Inverts mA = IINDPM * 10: IINDPM = mA / 10.
     * @param mA Current in milliamps
     */
    void setMilliamps(uint16_t mA);

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
    static constexpr uint8_t  kExpectedSize  = Registers::INPUT_CURRENT_LIMIT.size;
    static constexpr uint16_t kReservedMask  = 0xFE00;  ///< Bits [15:9]
    static constexpr uint16_t kIindpmMask    = 0x01FF;  ///< Bits [8:0]
    static constexpr uint16_t kLsbMa         = 10;      ///< mA per LSB
};

}  // namespace BQ25798
