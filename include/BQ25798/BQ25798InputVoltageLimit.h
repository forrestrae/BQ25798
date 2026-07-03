#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Input Voltage Limit Register (REG05h, address 0x05)
 *
 * One-byte read/write register setting the absolute VINDPM threshold. When
 * VBUS drops below this threshold the charger enters VINDPM regulation.
 *
 * The register resets to 3600 mV on adapter removal (not by REG_RST or watchdog).
 * On adapter plug-in it is set automatically based on the measured VBUS level.
 *
 * Register layout (8 bits):
 *   Bits 7:0 — VINDPM_7:0   Absolute VINDPM threshold
 *
 * Conversion: millivolts = VINDPM * 100
 *   Range: 0 mV (0x00) to 25500 mV (0xFF), 100 mV/LSB
 *
 * Semantic validity:
 *   - No reserved bits; any 8-bit value is structurally valid.
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W]
 */
class InputVoltageLimit : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::INPUT_VOLTAGE_LIMIT;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit InputVoltageLimit()
        : TPS25751Register(Registers::INPUT_VOLTAGE_LIMIT.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit InputVoltageLimit(const uint8_t* data)
        : TPS25751Register(data, Registers::INPUT_VOLTAGE_LIMIT.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    InputVoltageLimit(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit InputVoltageLimit(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Raw VINDPM field — VINDPM_7:0 (bits 7:0)
     * @return 8-bit raw value; 0 if not valid
     */
    uint8_t vindpmRaw() const;

    /**
     * @brief Absolute VINDPM threshold in millivolts
     *
     * Converts the 8-bit VINDPM field using: mV = VINDPM * 100
     * @return Voltage in mV; 0 if not valid
     */
    uint16_t millivolts() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /**
     * @brief Set raw VINDPM field — VINDPM_7:0 (bits 7:0)
     * @param value 8-bit raw value
     */
    void setVindpmRaw(uint8_t value);

    /**
     * @brief Set absolute VINDPM threshold from millivolts
     *
     * Inverts mV = VINDPM * 100: VINDPM = mV / 100.
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
     * Returns true when basic validity passes (non-null, correct size).
     * No reserved bits to check in this register.
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t  kExpectedSize  = Registers::INPUT_VOLTAGE_LIMIT.size;
    static constexpr uint16_t kLsbMv         = 100;  ///< mV per LSB
};

}  // namespace BQ25798
