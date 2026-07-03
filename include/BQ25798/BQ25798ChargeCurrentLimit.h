#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charge Current Limit Register (REG03h, address 0x03)
 *
 * Two-byte read/write register setting the fast-charge current limit.
 *
 * Register layout (16 bits, big-endian on the wire):
 *   _raw[0] = MSB (lower register address byte)
 *   _raw[1] = LSB
 *   Bits 15:9 — RESERVED
 *   Bits 8:0  — ICHG_8:0   Charge current limit
 *
 * Conversion: milliamps = ICHG * 10
 *   Range: 0 mA (0x000) to 5120 mA (0x1FF), 10 mA/LSB
 *
 * Semantic validity:
 *   - Reserved bits [15:9] must be zero.
 *
 * Register size: 2 bytes
 * Access: Read/Write [R/W]
 */
class ChargeCurrentLimit : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGE_CURRENT_LIMIT;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 2-byte register
    explicit ChargeCurrentLimit()
        : TPS25751Register(Registers::CHARGE_CURRENT_LIMIT.size) {}

    /// @brief Construct from raw byte array (fixed 2-byte size)
    explicit ChargeCurrentLimit(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGE_CURRENT_LIMIT.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargeCurrentLimit(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargeCurrentLimit(Registers::RegisterInfo regInfo)
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
     * @brief Raw ICHG field — ICHG_8:0 (bits 8:0 of the 16-bit value)
     * @return 9-bit raw value; 0 if not valid
     */
    uint16_t ichgRaw() const;

    /**
     * @brief Fast-charge current limit in milliamps
     *
     * Converts the 9-bit ICHG field using: mA = ICHG * 10
     * @return Current in mA; 0 if not valid
     */
    uint16_t milliamps() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /**
     * @brief Set raw ICHG field — ICHG_8:0 (bits 8:0 of the 16-bit value)
     * @param value 9-bit raw value (masked to 9 bits)
     */
    void setIchgRaw(uint16_t value);

    /**
     * @brief Set fast-charge current limit from milliamps
     *
     * Inverts mA = ICHG * 10: ICHG = mA / 10.
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
    static constexpr uint8_t  kExpectedSize  = Registers::CHARGE_CURRENT_LIMIT.size;
    static constexpr uint16_t kReservedMask  = 0xFE00;  ///< Bits [15:9]
    static constexpr uint16_t kIchgMask      = 0x01FF;  ///< Bits [8:0]
    static constexpr uint16_t kLsbMa         = 10;      ///< mA per LSB
};

}  // namespace BQ25798
