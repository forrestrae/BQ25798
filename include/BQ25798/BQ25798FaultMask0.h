#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Fault Mask 0 Register (REG2Ch, address 0x2C)
 *
 * One-byte read/write register for masking fault interrupt sources.
 * All bits are defined (no reserved bits).
 *
 * Register layout (8 bits):
 *   Bit 7 — IBAT_REG_MASK   Mask IBAT regulation entry/exit
 *   Bit 6 — VBUS_OVP_MASK   Mask VBUS over-voltage
 *   Bit 5 — VBAT_OVP_MASK   Mask VBAT over-voltage
 *   Bit 4 — IBUS_OCP_MASK   Mask IBUS over-current
 *   Bit 3 — IBAT_OCP_MASK   Mask IBAT over-current
 *   Bit 2 — CONV_OCP_MASK   Mask converter over-current
 *   Bit 1 — VAC2_OVP_MASK   Mask VAC2 over-voltage
 *   Bit 0 — VAC1_OVP_MASK   Mask VAC1 over-voltage
 *
 * Reset value: 0x00
 * Access: Read/Write [R/W]
 */
class FaultMask0 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::FAULT_MASK_0;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit FaultMask0()
        : TPS25751Register(Registers::FAULT_MASK_0.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit FaultMask0(const uint8_t* data)
        : TPS25751Register(data, Registers::FAULT_MASK_0.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    FaultMask0(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit FaultMask0(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    bool ibatRegMask()  const;  ///< bit 7
    bool vbusOvpMask()  const;  ///< bit 6
    bool vbatOvpMask()  const;  ///< bit 5
    bool ibusOcpMask()  const;  ///< bit 4
    bool ibatOcpMask()  const;  ///< bit 3
    bool convOcpMask()  const;  ///< bit 2
    bool vac2OvpMask()  const;  ///< bit 1
    bool vac1OvpMask()  const;  ///< bit 0

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — true = Masked / no INT)
    // -----------------------------------------------------------------------

    void setIbatRegMask(bool masked);  ///< @brief Set IBAT_REG_MASK (bit 7)
    void setVbusOvpMask(bool masked);  ///< @brief Set VBUS_OVP_MASK (bit 6)
    void setVbatOvpMask(bool masked);  ///< @brief Set VBAT_OVP_MASK (bit 5)
    void setIbusOcpMask(bool masked);  ///< @brief Set IBUS_OCP_MASK (bit 4)
    void setIbatOcpMask(bool masked);  ///< @brief Set IBAT_OCP_MASK (bit 3)
    void setConvOcpMask(bool masked);  ///< @brief Set CONV_OCP_MASK (bit 2)
    void setVac2OvpMask(bool masked);  ///< @brief Set VAC2_OVP_MASK (bit 1)
    void setVac1OvpMask(bool masked);  ///< @brief Set VAC1_OVP_MASK (bit 0)

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    void debugPrint(Stream& s = Serial) const override;
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::FAULT_MASK_0.size;
};

}  // namespace BQ25798
