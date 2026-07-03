#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Fault Flag 1 Register (REG27h, address 0x27)
 *
 * One-byte read-only register containing interrupt flags for system short,
 * system over-voltage, OTG over/under-voltage, and thermal shutdown events.
 * Each flag latches on the relevant rising edge and is cleared by reading.
 *
 * Register layout (8 bits):
 *   Bit 7 — VSYS_SHORT_FLAG  Stop switching due to system short
 *   Bit 6 — VSYS_OVP_FLAG    Stop switching due to system over-voltage
 *   Bit 5 — OTG_OVP_FLAG     Stop OTG due to VBUS over-voltage
 *   Bit 4 — OTG_UVP_FLAG     Stop OTG due to VBUS under-voltage
 *   Bit 3 — RESERVED
 *   Bit 2 — TSHUT_FLAG       Thermal shutdown rising threshold detected
 *   Bits 1:0 — RESERVED
 *
 * Reserved bits: 3, 1:0 — must be zero in a valid register read.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class FaultFlag1 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit FaultFlag1()
        : TPS25751Register(Registers::FAULT_FLAG_1.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit FaultFlag1(const uint8_t* data)
        : TPS25751Register(data, Registers::FAULT_FLAG_1.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    FaultFlag1(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit FaultFlag1(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors — one per flag bit, bit positions per TRM Table 9-27
    // -----------------------------------------------------------------------

    /// @brief VSYS_SHORT_FLAG — bit 7: Stop switching due to system short circuit
    bool vsysShortFlag() const;

    /// @brief VSYS_OVP_FLAG — bit 6: Stop switching due to system over-voltage
    bool vsysOvpFlag() const;

    /// @brief OTG_OVP_FLAG — bit 5: Stop OTG due to VBUS over-voltage
    bool otgOvpFlag() const;

    /// @brief OTG_UVP_FLAG — bit 4: Stop OTG due to VBUS under-voltage
    bool otgUvpFlag() const;

    /// @brief TSHUT_FLAG — bit 2: IC thermal shutdown rising threshold detected
    bool tshutFlag() const;

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
     *   - Reserved bits (3, 1:0) are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize  = Registers::FAULT_FLAG_1.size;
    /// Bits 3, 1, 0 are reserved
    static constexpr uint8_t kReservedMask  = (1u << 3) | (1u << 1) | (1u << 0);
};

}  // namespace BQ25798
