#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 MPPT Control Register (REG15h, address 0x15)
 *
 * One-byte read/write register controlling Maximum Power Point Tracking.
 *
 * Register layout (8 bits):
 *   Bits 7:5 — VOC_PCT_2:0   VINDPM as a % of VBUS open-circuit voltage (enum)
 *   Bits 4:3 — VOC_DLY_1:0  Delay before VOC measurement after converter stops (enum)
 *   Bits 2:1 — VOC_RATE_1:0 Interval between VBUS open-circuit measurements (enum)
 *   Bit  0   — EN_MPPT       Enable MPPT
 *
 * Reset value: 0xAA
 * Access: Read/Write [R/W]
 */
class MpptControl : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::MPPT_CONTROL;

    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief VOC_PCT_2:0 — VINDPM as percentage of open-circuit voltage (bits 7:5)
     */
    enum class VocPct : uint8_t {
        Pct56p25 = 0,  ///< 0.5625 (56.25%)
        Pct62p5  = 1,  ///< 0.625  (62.5%)
        Pct68p75 = 2,  ///< 0.6875 (68.75%)
        Pct75    = 3,  ///< 0.75   (75%)
        Pct81p25 = 4,  ///< 0.8125 (81.25%)
        Pct87p5  = 5,  ///< 0.875  (87.5%) — default
        Pct93p75 = 6,  ///< 0.9375 (93.75%)
        Pct100   = 7,  ///< 1.0    (100%)
    };

    /**
     * @brief VOC_DLY_1:0 — delay before VOC measurement (bits 4:3)
     */
    enum class VocDly : uint8_t {
        Ms50   = 0,  ///< 50 ms
        Ms300  = 1,  ///< 300 ms (default)
        S2     = 2,  ///< 2 s
        S5     = 3,  ///< 5 s
    };

    /**
     * @brief VOC_RATE_1:0 — interval between VOC measurements (bits 2:1)
     */
    enum class VocRate : uint8_t {
        S30    = 0,  ///< 30 seconds
        Min2   = 1,  ///< 2 minutes (default)
        Min10  = 2,  ///< 10 minutes
        Min30  = 3,  ///< 30 minutes
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit MpptControl()
        : TPS25751Register(Registers::MPPT_CONTROL.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit MpptControl(const uint8_t* data)
        : TPS25751Register(data, Registers::MPPT_CONTROL.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    MpptControl(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit MpptControl(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief VINDPM percentage of open-circuit voltage — VOC_PCT_2:0 (bits 7:5)
     * @return VocPct enum value
     */
    VocPct vocPct() const;

    /**
     * @brief Delay before VOC measurement — VOC_DLY_1:0 (bits 4:3)
     * @return VocDly enum value
     */
    VocDly vocDly() const;

    /**
     * @brief Interval between VOC measurements — VOC_RATE_1:0 (bits 2:1)
     * @return VocRate enum value
     */
    VocRate vocRate() const;

    /**
     * @brief Enable MPPT — EN_MPPT (bit 0)
     * @return true if MPPT is enabled
     */
    bool enMppt() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Set VINDPM percentage of open-circuit voltage — VOC_PCT_2:0 (bits 7:5)
    void setVocPct(VocPct v);

    /// @brief Set delay before VOC measurement — VOC_DLY_1:0 (bits 4:3)
    void setVocDly(VocDly v);

    /// @brief Set interval between VOC measurements — VOC_RATE_1:0 (bits 2:1)
    void setVocRate(VocRate v);

    /// @brief Set enable MPPT — EN_MPPT (bit 0)
    void setEnMppt(bool on);

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
    static constexpr uint8_t kExpectedSize = Registers::MPPT_CONTROL.size;
};

}  // namespace BQ25798
