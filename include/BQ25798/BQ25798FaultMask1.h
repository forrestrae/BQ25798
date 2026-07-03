#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Fault Mask 1 Register (REG2Dh, address 0x2D)
 *
 * One-byte read/write register for masking fault interrupt sources.
 * Bits 3, 1, and 0 are reserved.
 *
 * Register layout (8 bits):
 *   Bit 7 — VSYS_SHORT_MASK  Mask system short circuit fault
 *   Bit 6 — VSYS_OVP_MASK   Mask system over-voltage fault
 *   Bit 5 — OTG_OVP_MASK    Mask OTG VBUS over-voltage fault
 *   Bit 4 — OTG_UVP_MASK    Mask OTG VBUS under-voltage fault
 *   Bit 3 — RESERVED
 *   Bit 2 — TSHUT_MASK      Mask IC thermal shutdown
 *   Bits 1:0 — RESERVED
 *
 * Reset value: 0x00
 * Access: Read/Write [R/W] (bits 7:4, 2); [R] (bits 3, 1:0)
 */
class FaultMask1 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::FAULT_MASK_1;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit FaultMask1()
        : TPS25751Register(Registers::FAULT_MASK_1.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit FaultMask1(const uint8_t* data)
        : TPS25751Register(data, Registers::FAULT_MASK_1.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    FaultMask1(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit FaultMask1(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    bool vsysShortMask() const;  ///< bit 7
    bool vsysOvpMask()   const;  ///< bit 6
    bool otgOvpMask()    const;  ///< bit 5
    bool otgUvpMask()    const;  ///< bit 4
    bool tshutMask()     const;  ///< bit 2

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — true = Masked / no INT)
    // Reserved bits 3 and 1:0 have no setter.
    // -----------------------------------------------------------------------

    void setVsysShortMask(bool masked);  ///< @brief Set VSYS_SHORT_MASK (bit 7)
    void setVsysOvpMask(bool masked);    ///< @brief Set VSYS_OVP_MASK (bit 6)
    void setOtgOvpMask(bool masked);     ///< @brief Set OTG_OVP_MASK (bit 5)
    void setOtgUvpMask(bool masked);     ///< @brief Set OTG_UVP_MASK (bit 4)
    void setTshutMask(bool masked);      ///< @brief Set TSHUT_MASK (bit 2)

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    void debugPrint(Stream& s = Serial) const override;
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::FAULT_MASK_1.size;
    static constexpr uint8_t kReservedMask = 0x0Bu;  ///< Bits 3, 1, 0
};

}  // namespace BQ25798
