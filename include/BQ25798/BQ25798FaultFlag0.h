#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Fault Flag 0 Register (REG26h, address 0x26)
 *
 * One-byte read-only register containing interrupt flags for over-voltage and
 * over-current fault events. Each flag latches on the entry edge (or any
 * enter/exit transition for IBAT_REG_FLAG) and is cleared by reading.
 *
 * Register layout (8 bits):
 *   Bit 7 — IBAT_REG_FLAG  Enter or exit IBAT regulation
 *   Bit 6 — VBUS_OVP_FLAG  Enter VBUS OVP
 *   Bit 5 — VBAT_OVP_FLAG  Enter VBAT OVP
 *   Bit 4 — IBUS_OCP_FLAG  Enter IBUS OCP
 *   Bit 3 — IBAT_OCP_FLAG  Enter discharged OCP
 *   Bit 2 — CONV_OCP_FLAG  Enter converter cycle-by-cycle OCP
 *   Bit 1 — VAC2_OVP_FLAG  Enter VAC2 OVP
 *   Bit 0 — VAC1_OVP_FLAG  Enter VAC1 OVP
 *
 * No reserved bits — all 8 bits are defined flags.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class FaultFlag0 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit FaultFlag0()
        : TPS25751Register(Registers::FAULT_FLAG_0.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit FaultFlag0(const uint8_t* data)
        : TPS25751Register(data, Registers::FAULT_FLAG_0.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    FaultFlag0(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit FaultFlag0(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors — one per flag bit, bit positions per TRM Table 9-26
    // -----------------------------------------------------------------------

    /// @brief IBAT_REG_FLAG — bit 7: Enter or exit IBAT regulation
    bool ibatRegFlag() const;

    /// @brief VBUS_OVP_FLAG — bit 6: Enter VBUS over-voltage protection
    bool vbusOvpFlag() const;

    /// @brief VBAT_OVP_FLAG — bit 5: Enter VBAT over-voltage protection
    bool vbatOvpFlag() const;

    /// @brief IBUS_OCP_FLAG — bit 4: Enter IBUS over-current protection
    bool ibusOcpFlag() const;

    /// @brief IBAT_OCP_FLAG — bit 3: Enter discharged (IBAT) over-current protection
    bool ibatOcpFlag() const;

    /// @brief CONV_OCP_FLAG — bit 2: Enter converter cycle-by-cycle over-current protection
    bool convOcpFlag() const;

    /// @brief VAC2_OVP_FLAG — bit 1: Enter VAC2 over-voltage protection
    bool vac2OvpFlag() const;

    /// @brief VAC1_OVP_FLAG — bit 0: Enter VAC1 over-voltage protection
    bool vac1OvpFlag() const;

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
     *
     * All 8 bits are defined flags (no reserved bits), so no reserved-bit
     * check is needed.
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::FAULT_FLAG_0.size;
};

}  // namespace BQ25798
