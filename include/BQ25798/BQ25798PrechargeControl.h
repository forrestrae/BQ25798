#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Precharge Control Register (REG08h, address 0x08)
 *
 * One-byte read/write register controlling the precharge phase: the voltage
 * threshold for the precharge-to-fast-charge transition (VBAT_LOWV) and the
 * precharge current limit (IPRECHG).
 *
 * Register layout (8 bits):
 *   Bits 7:6 — VBAT_LOWV_1:0   Precharge-to-fast-charge transition threshold
 *                               (as a ratio of VREG)
 *   Bits 5:0 — IPRECHG_5:0     Precharge current limit
 *
 * IPRECHG conversion: milliamps = IPRECHG * 40
 *   Range: 40 mA (0x01) to 2560 mA (0x40), 40 mA/LSB
 *   (0x00 = 0 mA; effectively disables precharging)
 *
 * Semantic validity:
 *   - All bit fields are defined; no reserved bits to check.
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W]
 * Reset: 0xC3 (VBAT_LOWV=0b11 [71.4%], IPRECHG=0b000011 [120 mA])
 */
class PrechargeControl : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::PRECHARGE_CONTROL;

    // -----------------------------------------------------------------------
    // VBAT_LOWV enum — precharge-to-fast-charge threshold (bits 7:6)
    // -----------------------------------------------------------------------

    /**
     * @brief Battery voltage threshold for precharge-to-fast-charge transition
     *
     * Each value is a percentage of VREG (the battery voltage regulation limit).
     * The transition from precharge to fast-charge occurs when VBAT exceeds this
     * threshold.
     */
    enum class VbatLowv : uint8_t {
        Pct15   = 0,  ///< 15% of VREG
        Pct62p2 = 1,  ///< 62.2% of VREG
        Pct66p7 = 2,  ///< 66.7% of VREG
        Pct71p4 = 3,  ///< 71.4% of VREG (default)
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit PrechargeControl()
        : TPS25751Register(Registers::PRECHARGE_CONTROL.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit PrechargeControl(const uint8_t* data)
        : TPS25751Register(data, Registers::PRECHARGE_CONTROL.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    PrechargeControl(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit PrechargeControl(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Precharge-to-fast-charge transition threshold — VBAT_LOWV_1:0 (bits 7:6)
     * @return VbatLowv enum value
     */
    VbatLowv vbatLowv() const;

    /**
     * @brief Raw IPRECHG field — IPRECHG_5:0 (bits 5:0)
     * @return 6-bit raw value; 0 if not valid
     */
    uint8_t iprechgRaw() const;

    /**
     * @brief Precharge current limit in milliamps
     *
     * Converts the 6-bit IPRECHG field using: mA = IPRECHG * 40
     * @return Current in mA; 0 if not valid
     */
    uint16_t milliamps() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Set precharge-to-fast-charge transition threshold — VBAT_LOWV_1:0 (bits 7:6)
    void setVbatLowv(VbatLowv v);

    /// @brief Set raw IPRECHG field — IPRECHG_5:0 (bits 5:0)
    void setIprechgRaw(uint8_t raw);

    /// @brief Set precharge current limit in milliamps — IPRECHG_5:0 (bits 5:0)
    /// @param ma Current in mA; encoded as IPRECHG = ma / 40 (40 mA/LSB)
    void setMilliamps(uint16_t ma);

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    /**
     * @brief Print register fields to @p s in a human-readable format
     *
     * Uses F() for every string literal (flash storage on AVR/Teensy).
     * Decodes VBAT_LOWV to its percentage-of-VREG description.
     */
    void debugPrint(Stream& s = Serial) const override;

    /**
     * @brief Semantic validation
     *
     * Returns true when basic validity passes (non-null, correct size).
     * All bit fields are defined; no reserved bits to check.
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t  kExpectedSize  = Registers::PRECHARGE_CONTROL.size;
    static constexpr uint16_t kLsbMa         = 40;  ///< mA per LSB
};

}  // namespace BQ25798
