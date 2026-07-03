#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Mask 1 Register (REG29h, address 0x29)
 *
 * One-byte read/write register for masking charger interrupt sources.
 * Bits 5 and 3 are reserved (read-only, always 0).
 *
 * Register layout (8 bits):
 *   Bit 7 — CHG_MASK           Mask charging status change
 *   Bit 6 — ICO_MASK           Mask ICO status change
 *   Bit 5 — RESERVED
 *   Bit 4 — VBUS_MASK          Mask VBUS status change
 *   Bit 3 — RESERVED
 *   Bit 2 — TREG_MASK          Mask thermal regulation entry
 *   Bit 1 — VBAT_PRESENT_MASK  Mask VBAT present status change
 *   Bit 0 — BC12_DONE_MASK     Mask BC1.2 status change
 *
 * Reset value: 0x00
 * Access: Read/Write [R/W] (bits 7:6, 4, 2:0); [R] (bits 5, 3)
 */
class ChargerMask1 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGER_MASK_1;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerMask1()
        : TPS25751Register(Registers::CHARGER_MASK_1.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerMask1(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_MASK_1.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerMask1(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerMask1(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    bool chgMask()         const;  ///< bit 7
    bool icoMask()         const;  ///< bit 6
    bool vbusMask()        const;  ///< bit 4
    bool tregMask()        const;  ///< bit 2
    bool vbatPresentMask() const;  ///< bit 1
    bool bc12DoneMask()    const;  ///< bit 0

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — true = Masked / no INT)
    // Reserved bits 5 and 3 have no setter.
    // -----------------------------------------------------------------------

    void setChgMask(bool masked);          ///< @brief Set CHG_MASK (bit 7)
    void setIcoMask(bool masked);          ///< @brief Set ICO_MASK (bit 6)
    void setVbusMask(bool masked);         ///< @brief Set VBUS_MASK (bit 4)
    void setTregMask(bool masked);         ///< @brief Set TREG_MASK (bit 2)
    void setVbatPresentMask(bool masked);  ///< @brief Set VBAT_PRESENT_MASK (bit 1)
    void setBc12DoneMask(bool masked);     ///< @brief Set BC12_DONE_MASK (bit 0)

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    void debugPrint(Stream& s = Serial) const override;
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize  = Registers::CHARGER_MASK_1.size;
    static constexpr uint8_t kReservedMask  = 0x28u;  ///< Bits 5 and 3
};

}  // namespace BQ25798
