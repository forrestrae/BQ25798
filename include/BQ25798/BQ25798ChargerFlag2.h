#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Flag 2 Register (REG24h, address 0x24)
 *
 * One-byte read-only register containing interrupt flags for D+/D- detection,
 * ADC conversion completion, VSYS regulation, and charge timer expiry events.
 * Each flag latches on the relevant edge and is cleared by reading.
 *
 * Register layout (8 bits):
 *   Bit 7 — RESERVED
 *   Bit 6 — DPDM_DONE_FLAG    D+/D- detection completed
 *   Bit 5 — ADC_DONE_FLAG     ADC one-shot conversion completed
 *   Bit 4 — VSYS_FLAG         Entered or exited VSYSMIN regulation
 *   Bit 3 — CHG_TMR_FLAG      Fast charge timer expired
 *   Bit 2 — TRICHG_TMR_FLAG   Trickle charge timer expired
 *   Bit 1 — PRECHG_TMR_FLAG   Pre-charge timer expired
 *   Bit 0 — TOPOFF_TMR_FLAG   Top-off timer expired
 *
 * Reserved bit: 7 — must be zero in a valid register read.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class ChargerFlag2 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerFlag2()
        : TPS25751Register(Registers::CHARGER_FLAG_2.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerFlag2(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_FLAG_2.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerFlag2(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerFlag2(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors — one per flag bit, bit positions per TRM Table 9-24
    // -----------------------------------------------------------------------

    /// @brief DPDM_DONE_FLAG — bit 6: D+/D- detection completed
    bool dpdmDoneFlag() const;

    /// @brief ADC_DONE_FLAG — bit 5: ADC one-shot conversion completed
    bool adcDoneFlag() const;

    /// @brief VSYS_FLAG — bit 4: Entered or exited VSYSMIN regulation
    bool vsysFlag() const;

    /// @brief CHG_TMR_FLAG — bit 3: Fast charge timer expired
    bool chgTmrFlag() const;

    /// @brief TRICHG_TMR_FLAG — bit 2: Trickle charge timer expired
    bool trichgTmrFlag() const;

    /// @brief PRECHG_TMR_FLAG — bit 1: Pre-charge timer expired
    bool prechgTmrFlag() const;

    /// @brief TOPOFF_TMR_FLAG — bit 0: Top-off timer expired
    bool topoffTmrFlag() const;

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
     * Returns true when:
     *   - Basic validity passes (non-null, correct size)
     *   - Size matches the expected 1-byte width
     *   - Reserved bit 7 is zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize  = Registers::CHARGER_FLAG_2.size;
    static constexpr uint8_t kReservedMask  = (1u << 7);  ///< Bit 7
};

}  // namespace BQ25798
