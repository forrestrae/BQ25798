#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 NTC Control 0 Register (REG17h, address 0x17)
 *
 * One-byte read/write register configuring JEITA temperature-protection
 * behaviour: the voltage adjustment in the hot range (JEITA_VSET), and the
 * current adjustments in the hot (JEITA_ISETH) and cool (JEITA_ISETC) ranges.
 *
 * Register layout (8 bits):
 *   Bits 7:5 — JEITA_VSET_2:0   Hot-range charge voltage setting (enum)
 *   Bits 4:3 — JEITA_ISETH_1:0  Hot-range charge current setting (enum)
 *   Bits 2:1 — JEITA_ISETC_1:0  Cool-range charge current setting (enum)
 *   Bit  0   — RESERVED
 *
 * Semantic validity:
 *   - Reserved bit 0 must be zero.
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W]
 * Reset: 0x7A (JEITA_VSET=0b011 [-400mV], JEITA_ISETH=0b11 [unchanged],
 *              JEITA_ISETC=0b01 [20% ICHG])
 */
class NtcControl0 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::NTC_CONTROL_0;

    // -----------------------------------------------------------------------
    // JEITA_VSET enum — hot-range charge voltage adjustment (bits 7:5)
    // -----------------------------------------------------------------------

    /**
     * @brief JEITA hot-range (TWARM–THOT) charge voltage setting
     *
     * Controls the battery voltage limit when the NTC temperature is in the
     * hot range (between TWARM and THOT thresholds).
     */
    enum class JeitaVset : uint8_t {
        Suspend      = 0,  ///< Charge suspended
        VregMinus800 = 1,  ///< VREG - 800 mV
        VregMinus600 = 2,  ///< VREG - 600 mV
        VregMinus400 = 3,  ///< VREG - 400 mV (default)
        VregMinus300 = 4,  ///< VREG - 300 mV
        VregMinus200 = 5,  ///< VREG - 200 mV
        VregMinus100 = 6,  ///< VREG - 100 mV
        VregUnchanged = 7, ///< VREG unchanged
    };

    // -----------------------------------------------------------------------
    // JEITA_ISETH enum — hot-range charge current adjustment (bits 4:3)
    // -----------------------------------------------------------------------

    /**
     * @brief JEITA hot-range (TWARM–THOT) charge current setting
     *
     * Controls the charge current when the NTC temperature is in the hot range.
     */
    enum class JeitaIseth : uint8_t {
        Suspend       = 0,  ///< Charge suspended
        Ichg20Pct     = 1,  ///< 20% of ICHG
        Ichg40Pct     = 2,  ///< 40% of ICHG
        IchgUnchanged = 3,  ///< ICHG unchanged (default)
    };

    // -----------------------------------------------------------------------
    // JEITA_ISETC enum — cool-range charge current adjustment (bits 2:1)
    // -----------------------------------------------------------------------

    /**
     * @brief JEITA cool-range (TCOLD–TCOOL) charge current setting
     *
     * Controls the charge current when the NTC temperature is in the cool range.
     */
    enum class JeitaIsetc : uint8_t {
        Suspend       = 0,  ///< Charge suspended
        Ichg20Pct     = 1,  ///< 20% of ICHG (default)
        Ichg40Pct     = 2,  ///< 40% of ICHG
        IchgUnchanged = 3,  ///< ICHG unchanged
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit NtcControl0()
        : TPS25751Register(Registers::NTC_CONTROL_0.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit NtcControl0(const uint8_t* data)
        : TPS25751Register(data, Registers::NTC_CONTROL_0.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    NtcControl0(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit NtcControl0(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief JEITA hot-range voltage setting — JEITA_VSET_2:0 (bits 7:5)
     * @return JeitaVset enum value
     */
    JeitaVset jeitaVset() const;

    /**
     * @brief JEITA hot-range current setting — JEITA_ISETH_1:0 (bits 4:3)
     * @return JeitaIseth enum value
     */
    JeitaIseth jeitaIseth() const;

    /**
     * @brief JEITA cool-range current setting — JEITA_ISETC_1:0 (bits 2:1)
     * @return JeitaIsetc enum value
     */
    JeitaIsetc jeitaIsetc() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field;
    // reserved bit 0 is never written)
    // -----------------------------------------------------------------------

    /// @brief Set JEITA hot-range voltage setting — JEITA_VSET_2:0 (bits 7:5)
    void setJeitaVset(JeitaVset v);

    /// @brief Set JEITA hot-range current setting — JEITA_ISETH_1:0 (bits 4:3)
    void setJeitaIseth(JeitaIseth v);

    /// @brief Set JEITA cool-range current setting — JEITA_ISETC_1:0 (bits 2:1)
    void setJeitaIsetc(JeitaIsetc v);

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    /**
     * @brief Print register fields to @p s in a human-readable format
     *
     * Uses F() for every string literal (flash storage on AVR/Teensy).
     * Decodes all three enum fields to their descriptive text.
     */
    void debugPrint(Stream& s = Serial) const override;

    /**
     * @brief Semantic validation
     *
     * Returns true when:
     *   - Basic validity passes (non-null, correct size)
     *   - Reserved bit 0 is zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize  = Registers::NTC_CONTROL_0.size;
    static constexpr uint8_t kReservedMask  = 0x01;  ///< Bit 0
};

}  // namespace BQ25798
