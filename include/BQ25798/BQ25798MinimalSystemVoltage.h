#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Minimal System Voltage Register (REG00h, address 0x00)
 *
 * One-byte read/write register setting the minimum system voltage. The system
 * voltage will not fall below this threshold even when the battery voltage is
 * lower (e.g. deeply discharged battery).
 *
 * Register layout (8 bits):
 *   Bits 7:6 — RESERVED
 *   Bits 5:0 — VSYSMIN_5:0   Minimal system voltage setting
 *
 * Conversion: millivolts = 2500 + (VSYSMIN * 250)
 *   Range: 2500 mV (0x00) to 16250 mV (0x3F), 250 mV/LSB
 *
 * Semantic validity:
 *   - Reserved bits [7:6] must be zero.
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W]
 */
class MinimalSystemVoltage : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::MINIMAL_SYSTEM_VOLTAGE;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit MinimalSystemVoltage()
        : TPS25751Register(Registers::MINIMAL_SYSTEM_VOLTAGE.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit MinimalSystemVoltage(const uint8_t* data)
        : TPS25751Register(data, Registers::MINIMAL_SYSTEM_VOLTAGE.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    MinimalSystemVoltage(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit MinimalSystemVoltage(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Raw VSYSMIN field — VSYSMIN_5:0 (bits 5:0)
     * @return 6-bit raw value; 0 if not valid
     */
    uint8_t vsysminRaw() const;

    /**
     * @brief Minimal system voltage in millivolts
     *
     * Converts the 6-bit VSYSMIN field using: mV = 2500 + (VSYSMIN * 250)
     * @return Voltage in mV; 0 if not valid
     */
    uint16_t millivolts() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /**
     * @brief Set raw VSYSMIN field — VSYSMIN_5:0 (bits 5:0)
     * @param value 6-bit raw value (masked to 6 bits)
     */
    void setVsysminRaw(uint8_t value);

    /**
     * @brief Set minimal system voltage from millivolts
     *
     * Inverts mV = 2500 + (VSYSMIN * 250): VSYSMIN = (mV - 2500) / 250.
     * Values below the 2500 mV offset clamp to 0.
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
     *   - Reserved bits [7:6] are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t  kExpectedSize   = Registers::MINIMAL_SYSTEM_VOLTAGE.size;
    static constexpr uint8_t  kReservedMask   = 0xC0;  ///< Bits [7:6]
    static constexpr uint16_t kOffsetMv       = 2500;  ///< mV offset
    static constexpr uint16_t kLsbMv          = 250;   ///< mV per LSB
};

}  // namespace BQ25798
