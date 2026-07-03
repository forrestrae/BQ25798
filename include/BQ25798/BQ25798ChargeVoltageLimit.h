#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charge Voltage Limit Register (REG01h, address 0x01)
 *
 * Two-byte read/write register setting the battery voltage regulation limit.
 * The charger will regulate the battery to this voltage during the constant-
 * voltage phase of charging.
 *
 * Register layout (16 bits, big-endian on the wire):
 *   _raw[0] = MSB (lower register address byte)
 *   _raw[1] = LSB
 *   Bits 15:11 — RESERVED
 *   Bits 10:0  — VREG_10:0   Battery voltage regulation limit
 *
 * Conversion: millivolts = VREG * 10
 *   Range: 0 mV (0x000) to 20460 mV (0x7FF), 10 mV/LSB
 *
 * Semantic validity:
 *   - Reserved bits [15:11] must be zero.
 *
 * Register size: 2 bytes
 * Access: Read/Write [R/W]
 */
class ChargeVoltageLimit : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGE_VOLTAGE_LIMIT;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 2-byte register
    explicit ChargeVoltageLimit()
        : TPS25751Register(Registers::CHARGE_VOLTAGE_LIMIT.size) {}

    /// @brief Construct from raw byte array (fixed 2-byte size)
    explicit ChargeVoltageLimit(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGE_VOLTAGE_LIMIT.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargeVoltageLimit(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargeVoltageLimit(Registers::RegisterInfo regInfo)
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
     * @brief Raw VREG field — VREG_10:0 (bits 10:0 of the 16-bit value)
     * @return 11-bit raw value; 0 if not valid
     */
    uint16_t vregRaw() const;

    /**
     * @brief Battery voltage regulation limit in millivolts
     *
     * Converts the 11-bit VREG field using: mV = VREG * 10
     * @return Voltage in mV; 0 if not valid
     */
    uint16_t millivolts() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /**
     * @brief Set raw VREG field — VREG_10:0 (bits 10:0 of the 16-bit value)
     * @param value 11-bit raw value (masked to 11 bits)
     */
    void setVregRaw(uint16_t value);

    /**
     * @brief Set battery voltage regulation limit from millivolts
     *
     * Inverts mV = VREG * 10: VREG = mV / 10.
     * @param mV Voltage in millivolts
     */
    void setMillivolts(uint16_t mV);

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
     *   - Reserved bits [15:11] are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t  kExpectedSize  = Registers::CHARGE_VOLTAGE_LIMIT.size;
    static constexpr uint16_t kReservedMask  = 0xF800;  ///< Bits [15:11]
    static constexpr uint16_t kVregMask      = 0x07FF;  ///< Bits [10:0]
    static constexpr uint16_t kLsbMv         = 10;      ///< mV per LSB
};

}  // namespace BQ25798
