#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Mask 3 Register (REG2Bh, address 0x2B)
 *
 * One-byte read/write register for masking TS and OTG interrupt sources.
 * Bits 7:5 are reserved.
 *
 * Register layout (8 bits):
 *   Bits 7:5 — RESERVED
 *   Bit  4   — VBATOTG_LOW_MASK  Mask VBAT-too-low-for-OTG event
 *   Bit  3   — TS_COLD_MASK      Mask TS cold temperature (T1) crossing
 *   Bit  2   — TS_COOL_MASK      Mask TS cool temperature (T2) crossing
 *   Bit  1   — TS_WARM_MASK      Mask TS warm temperature (T3) crossing
 *   Bit  0   — TS_HOT_MASK       Mask TS hot temperature (T5) crossing
 *
 * Reset value: 0x00
 * Access: Read/Write [R/W] (bits 4:0); [R] (bits 7:5)
 */
class ChargerMask3 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGER_MASK_3;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerMask3()
        : TPS25751Register(Registers::CHARGER_MASK_3.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerMask3(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_MASK_3.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerMask3(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerMask3(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    bool vbatotgLowMask() const;  ///< bit 4
    bool tsColdMask()     const;  ///< bit 3
    bool tsCoolMask()     const;  ///< bit 2
    bool tsWarmMask()     const;  ///< bit 1
    bool tsHotMask()      const;  ///< bit 0

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — true = Masked / no INT)
    // Reserved bits 7:5 have no setter.
    // -----------------------------------------------------------------------

    void setVbatotgLowMask(bool masked);  ///< @brief Set VBATOTG_LOW_MASK (bit 4)
    void setTsColdMask(bool masked);      ///< @brief Set TS_COLD_MASK (bit 3)
    void setTsCoolMask(bool masked);      ///< @brief Set TS_COOL_MASK (bit 2)
    void setTsWarmMask(bool masked);      ///< @brief Set TS_WARM_MASK (bit 1)
    void setTsHotMask(bool masked);       ///< @brief Set TS_HOT_MASK (bit 0)

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    void debugPrint(Stream& s = Serial) const override;
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_MASK_3.size;
    static constexpr uint8_t kReservedMask = 0xE0u;  ///< Bits 7:5
};

}  // namespace BQ25798
