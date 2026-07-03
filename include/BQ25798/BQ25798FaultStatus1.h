#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Fault Status 1 Register (REG21h, address 0x21)
 *
 * One-byte read-only register containing VSYS, OTG, and thermal shutdown
 * fault status flags.
 *
 * Register layout (8 bits):
 *   Bit 7 — VSYS_SHORT_STAT  VSYS short circuit protection
 *   Bit 6 — VSYS_OVP_STAT    VSYS over-voltage protection
 *   Bit 5 — OTG_OVP_STAT     OTG over-voltage protection
 *   Bit 4 — OTG_UVP_STAT     OTG under-voltage protection
 *   Bit 3 — RESERVED
 *   Bit 2 — TSHUT_STAT       IC thermal shutdown protection
 *   Bits [1:0] — RESERVED
 *
 * Semantic validity:
 *   - Reserved bits (bit 3, bits [1:0]) must be zero.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class FaultStatus1 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit FaultStatus1()
        : TPS25751Register(Registers::FAULT_STATUS_1.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit FaultStatus1(const uint8_t* data)
        : TPS25751Register(data, Registers::FAULT_STATUS_1.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    FaultStatus1(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit FaultStatus1(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief VSYS short circuit protection status — bit 7
     * @return true if device is in VSYS short circuit protection
     */
    bool vsysShortStat() const;

    /**
     * @brief VSYS over-voltage protection status — bit 6
     * @return true if device is in VSYS over-voltage protection
     */
    bool vsysOvpStat() const;

    /**
     * @brief OTG over-voltage protection status — bit 5
     * @return true if device is in OTG over-voltage protection
     */
    bool otgOvpStat() const;

    /**
     * @brief OTG under-voltage protection status — bit 4
     * @return true if device is in OTG under-voltage protection
     */
    bool otgUvpStat() const;

    /**
     * @brief IC thermal shutdown protection status — bit 2
     * @return true if device is in thermal shutdown protection
     */
    bool tshutStat() const;

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
     *   - Reserved bits (bit 3, bits [1:0]) are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::FAULT_STATUS_1.size;
    static constexpr uint8_t kReservedMask = 0x0B;  ///< Bit 3 + bits [1:0]
};

}  // namespace BQ25798
