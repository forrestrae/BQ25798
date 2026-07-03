#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 IOTG Regulation Register (REG0Dh, address 0x0D)
 *
 * One-byte read/write register controlling OTG current limit and
 * pre-charge safety timer setting.
 *
 * Register layout (8 bits):
 *   Bit  7   — PRECHG_TMR   Pre-charge safety timer (enum 2hrs/0.5hrs)
 *   Bits 6:0 — IOTG_6:0    OTG current limit
 *
 * Conversion for IOTG_6:0:
 *   milliamps = IOTG_6:0 * 40  [mA]
 *   (40 mA/LSB, no offset)
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W]
 */
class IotgRegulation : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::IOTG_REGULATION;

    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief PRECHG_TMR — pre-charge safety timer setting (bit 7)
     */
    enum class PrechgTmr : uint8_t {
        Hours2   = 0,  ///< 2 hours (default)
        Hours0p5 = 1,  ///< 0.5 hours
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit IotgRegulation()
        : TPS25751Register(Registers::IOTG_REGULATION.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit IotgRegulation(const uint8_t* data)
        : TPS25751Register(data, Registers::IOTG_REGULATION.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    IotgRegulation(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit IotgRegulation(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Pre-charge safety timer setting — PRECHG_TMR (bit 7)
     * @return PrechgTmr enum value
     */
    PrechgTmr prechgTmr() const;

    /**
     * @brief Raw IOTG field — IOTG_6:0 (bits 6:0)
     * @return 7-bit raw value
     */
    uint8_t iotgRaw() const;

    /**
     * @brief OTG current limit in milliamps
     * @return Current in mA: IOTG_6:0 * 40
     */
    uint16_t milliamps() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /**
     * @brief Set pre-charge safety timer setting — PRECHG_TMR (bit 7)
     * @param value PrechgTmr enum value
     */
    void setPrechgTmr(PrechgTmr value);

    /**
     * @brief Set raw IOTG field — IOTG_6:0 (bits 6:0)
     * @param value 7-bit raw value (masked to 7 bits)
     */
    void setIotgRaw(uint8_t value);

    /**
     * @brief Set OTG current limit from milliamps
     *
     * Inverts mA = IOTG * 40: IOTG = mA / 40.
     * @param mA Current in milliamps
     */
    void setMilliamps(uint16_t mA);

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
     * @brief Semantic validation.
     *
     * Returns true when basic validity and correct register size pass.
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::IOTG_REGULATION.size;
};

}  // namespace BQ25798
