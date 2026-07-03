#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 VOTG Regulation Register (REG0Bh, address 0x0B)
 *
 * Two-byte read/write register controlling OTG mode regulation voltage.
 *
 * Register layout (16 bits, big-endian on the wire):
 *   _raw[0] = MSB (lower register address byte)
 *   _raw[1] = LSB
 *   Bits 15:11 — RESERVED (must be 0)
 *   Bits 10:0  — VOTG_10:0  OTG regulation voltage
 *
 * Conversion:
 *   millivolts = (VOTG_10:0 * 10) + 2800  [mV]
 *   (10 mV/LSB, 2800 mV offset)
 *
 * Register size: 2 bytes
 * Access: Read/Write [R/W]
 */
class VotgRegulation : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::VOTG_REGULATION;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 2-byte register
    explicit VotgRegulation()
        : TPS25751Register(Registers::VOTG_REGULATION.size) {}

    /// @brief Construct from raw byte array (fixed 2-byte size)
    explicit VotgRegulation(const uint8_t* data)
        : TPS25751Register(data, Registers::VOTG_REGULATION.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    VotgRegulation(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit VotgRegulation(Registers::RegisterInfo regInfo)
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
     * @brief Raw VOTG_10:0 field value (bits 10:0)
     * @return 11-bit raw value
     */
    uint16_t votgRaw() const;

    /**
     * @brief OTG regulation voltage in millivolts
     * @return Millivolts: (VOTG_10:0 * 10) + 2800
     */
    uint16_t millivolts() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /**
     * @brief Set raw VOTG_10:0 field value (bits 10:0)
     * @param value 11-bit raw value (masked to 11 bits)
     */
    void setVotgRaw(uint16_t value);

    /**
     * @brief Set OTG regulation voltage from millivolts
     *
     * Inverts mV = (VOTG * 10) + 2800: VOTG = (mV - 2800) / 10.
     * Values below the 2800 mV offset clamp to 0.
     * @param mV Voltage in millivolts
     */
    void setMillivolts(uint16_t mV);

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    /**
     * @brief Print register fields to @p s in a human-readable format.
     *
     * Uses F() for every string literal (flash storage on AVR/Teensy).
     */
    void debugPrint(Stream& s = Serial) const override;

    /**
     * @brief Semantic validation — isValid() + correct size + reserved bits zero.
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t  kExpectedSize  = Registers::VOTG_REGULATION.size;
    static constexpr uint16_t kReservedMask  = 0xF800u;  ///< Bits 15:11
    static constexpr uint16_t kVotgMask      = 0x07FFu;  ///< Bits 10:0
};

}  // namespace BQ25798
