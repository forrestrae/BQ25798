#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Status 3 Register (REG1Eh, address 0x1E)
 *
 * One-byte read-only register containing ACFET/RBFET placement status,
 * ADC conversion status, VSYS regulation, and safety timer status flags.
 *
 * Register layout (8 bits):
 *   Bit 7 — ACRB2_STAT       ACFET2-RBFET2 placed status
 *   Bit 6 — ACRB1_STAT       ACFET1-RBFET1 placed status
 *   Bit 5 — ADC_DONE_STAT    ADC conversion complete (one-shot mode)
 *   Bit 4 — VSYS_STAT        VSYS regulation status (VBAT < VSYSMIN)
 *   Bit 3 — CHG_TMR_STAT     Fast charge safety timer expired
 *   Bit 2 — TRICHG_TMR_STAT  Trickle charge safety timer expired
 *   Bit 1 — PRECHG_TMR_STAT  Pre-charge safety timer expired
 *   Bit 0 — RESERVED
 *
 * Semantic validity:
 *   - Reserved bit 0 must be zero.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class ChargerStatus3 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerStatus3()
        : TPS25751Register(Registers::CHARGER_STATUS_3.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerStatus3(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_STATUS_3.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerStatus3(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerStatus3(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief ACFET2-RBFET2 placed status — bit 7
     * @return true if ACFET2-RBFET2 is placed
     */
    bool acrb2Stat() const;

    /**
     * @brief ACFET1-RBFET1 placed status — bit 6
     * @return true if ACFET1-RBFET1 is placed
     */
    bool acrb1Stat() const;

    /**
     * @brief ADC conversion complete status (one-shot mode) — bit 5
     * @return true if conversion is complete
     */
    bool adcDoneStat() const;

    /**
     * @brief VSYS regulation status — bit 4
     * @return true if in VSYSMIN regulation (VBAT < VSYSMIN)
     */
    bool vsysStat() const;

    /**
     * @brief Fast charge safety timer expired — bit 3
     * @return true if safety timer has expired
     */
    bool chgTmrStat() const;

    /**
     * @brief Trickle charge safety timer expired — bit 2
     * @return true if safety timer has expired
     */
    bool trichgTmrStat() const;

    /**
     * @brief Pre-charge safety timer expired — bit 1
     * @return true if safety timer has expired
     */
    bool prechgTmrStat() const;

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
     *   - Reserved bit 0 is zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_STATUS_3.size;
    static constexpr uint8_t kReservedMask = 0x01;  ///< Bit 0
};

}  // namespace BQ25798
