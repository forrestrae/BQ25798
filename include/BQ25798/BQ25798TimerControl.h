#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Timer Control Register (REG0Eh, address 0x0E)
 *
 * One-byte read/write register controlling charge timer settings.
 *
 * Register layout (8 bits):
 *   Bits 7:6 — TOPOFF_TMR_1:0  Top-off timer control (enum)
 *   Bit  5   — EN_TRICHG_TMR   Enable trickle charge timer
 *   Bit  4   — EN_PRECHG_TMR   Enable pre-charge timer
 *   Bit  3   — EN_CHG_TMR      Enable fast charge timer
 *   Bits 2:1 — CHG_TMR_1:0    Fast charge timer setting (enum)
 *   Bit  0   — TMR2X_EN        Slow timers 2x during DPM/thermal regulation
 *
 * Reset value: 0x3D
 * Access: Read/Write [R/W]
 */
class TimerControl : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::TIMER_CONTROL;

    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief TOPOFF_TMR_1:0 — top-off timer control (bits 7:6)
     */
    enum class TopoffTmr : uint8_t {
        Disabled = 0,  ///< Disabled (default)
        Min15    = 1,  ///< 15 minutes
        Min30    = 2,  ///< 30 minutes
        Min45    = 3,  ///< 45 minutes
    };

    /**
     * @brief CHG_TMR_1:0 — fast charge timer setting (bits 2:1)
     */
    enum class ChgTmr : uint8_t {
        Hours5  = 0,  ///< 5 hours
        Hours8  = 1,  ///< 8 hours
        Hours12 = 2,  ///< 12 hours (default)
        Hours24 = 3,  ///< 24 hours
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit TimerControl()
        : TPS25751Register(Registers::TIMER_CONTROL.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit TimerControl(const uint8_t* data)
        : TPS25751Register(data, Registers::TIMER_CONTROL.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    TimerControl(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit TimerControl(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Top-off timer control — TOPOFF_TMR_1:0 (bits 7:6)
     * @return TopoffTmr enum value
     */
    TopoffTmr topoffTmr() const;

    /**
     * @brief Enable trickle charge timer — EN_TRICHG_TMR (bit 5)
     * @return true if enabled
     */
    bool enTrichgTmr() const;

    /**
     * @brief Enable pre-charge timer — EN_PRECHG_TMR (bit 4)
     * @return true if enabled
     */
    bool enPrechgTmr() const;

    /**
     * @brief Enable fast charge timer — EN_CHG_TMR (bit 3)
     * @return true if enabled
     */
    bool enChgTmr() const;

    /**
     * @brief Fast charge timer setting — CHG_TMR_1:0 (bits 2:1)
     * @return ChgTmr enum value
     */
    ChgTmr chgTmr() const;

    /**
     * @brief 2x timer slowdown during DPM/thermal regulation — TMR2X_EN (bit 0)
     * @return true if 2x slowdown is enabled (default)
     */
    bool tmr2xEn() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Set top-off timer control — TOPOFF_TMR_1:0 (bits 7:6)
    void setTopoffTmr(TopoffTmr v);

    /// @brief Set enable trickle charge timer — EN_TRICHG_TMR (bit 5)
    void setEnTrichgTmr(bool on);

    /// @brief Set enable pre-charge timer — EN_PRECHG_TMR (bit 4)
    void setEnPrechgTmr(bool on);

    /// @brief Set enable fast charge timer — EN_CHG_TMR (bit 3)
    void setEnChgTmr(bool on);

    /// @brief Set fast charge timer setting — CHG_TMR_1:0 (bits 2:1)
    void setChgTmr(ChgTmr v);

    /// @brief Set 2x timer slowdown during DPM/thermal regulation — TMR2X_EN (bit 0)
    void setTmr2xEn(bool on);

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
    static constexpr uint8_t kExpectedSize = Registers::TIMER_CONTROL.size;
};

}  // namespace BQ25798
