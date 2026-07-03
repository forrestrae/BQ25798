#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Mask 2 Register (REG2Ah, address 0x2A)
 *
 * One-byte read/write register for masking charger interrupt sources.
 * Bit 7 is reserved.
 *
 * Register layout (8 bits):
 *   Bit 7 — RESERVED
 *   Bit 6 — DPDM_DONE_MASK    Mask D+/D- detection done
 *   Bit 5 — ADC_DONE_MASK     Mask ADC conversion done (one-shot mode)
 *   Bit 4 — VSYS_MASK         Mask VSYS min regulation entry/exit
 *   Bit 3 — CHG_TMR_MASK      Mask fast charge timer expiry
 *   Bit 2 — TRICHG_TMR_MASK   Mask trickle charge timer expiry
 *   Bit 1 — PRECHG_TMR_MASK   Mask pre-charge timer expiry
 *   Bit 0 — TOPOFF_TMR_MASK   Mask top-off timer expiry
 *
 * Reset value: 0x00
 * Access: Read/Write [R/W] (bits 6:0); [R] (bit 7)
 */
class ChargerMask2 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGER_MASK_2;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerMask2()
        : TPS25751Register(Registers::CHARGER_MASK_2.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerMask2(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_MASK_2.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerMask2(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerMask2(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    bool dpdmDoneMask()   const;  ///< bit 6
    bool adcDoneMask()    const;  ///< bit 5
    bool vsysMask()       const;  ///< bit 4
    bool chgTmrMask()     const;  ///< bit 3
    bool trichgTmrMask()  const;  ///< bit 2
    bool prechgTmrMask()  const;  ///< bit 1
    bool topoffTmrMask()  const;  ///< bit 0

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — true = Masked / no INT)
    // Reserved bit 7 has no setter.
    // -----------------------------------------------------------------------

    void setDpdmDoneMask(bool masked);    ///< @brief Set DPDM_DONE_MASK (bit 6)
    void setAdcDoneMask(bool masked);     ///< @brief Set ADC_DONE_MASK (bit 5)
    void setVsysMask(bool masked);        ///< @brief Set VSYS_MASK (bit 4)
    void setChgTmrMask(bool masked);      ///< @brief Set CHG_TMR_MASK (bit 3)
    void setTrichgTmrMask(bool masked);   ///< @brief Set TRICHG_TMR_MASK (bit 2)
    void setPrechgTmrMask(bool masked);   ///< @brief Set PRECHG_TMR_MASK (bit 1)
    void setTopoffTmrMask(bool masked);   ///< @brief Set TOPOFF_TMR_MASK (bit 0)

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    void debugPrint(Stream& s = Serial) const override;
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_MASK_2.size;
    static constexpr uint8_t kReservedMask = 0x80u;  ///< Bit 7
};

}  // namespace BQ25798
