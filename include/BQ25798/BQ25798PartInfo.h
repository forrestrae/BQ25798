#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Part Information Register (REG48h, address 0x48)
 *
 * One-byte read-only register containing the device part number and hardware
 * revision. This is the canonical reference register class for the BQ25798
 * driver tier — all subsequent BQ25798 register classes (added in Stage 3)
 * should mirror this file's structure exactly.
 *
 * Register layout (8 bits, big-endian / single byte — no byte-order concern):
 *   Bits [7:6] — RESERVED (must be 0)
 *   Bits [5:3] — PN[2:0]      Device Part Number (0b011 = BQ25798)
 *   Bits [2:0] — DEV_REV[2:0] Device Revision    (0b001 = BQ25798)
 *
 * Semantic validity:
 *   - Reserved bits [7:6] must be zero.
 *   - PN must equal 0b011 (3) to identify a genuine BQ25798.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 *
 * @note This class extends TPS25751Register — the same device-agnostic decoder
 *       base used by all TPS25751 register classes — because downstream BQ25798
 *       register objects are decoded by the same extractBits/debugPrint/
 *       isValid/isSemanticallyValid machinery.
 */
class PartInfo : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // Mirrors TPS25751GPIOStatus (and all other existing register classes):
    //   default            — zero-initialised, size-aware (for factory create-empty)
    //   (data)             — copy from raw byte pointer, known fixed size
    //   (data, len)        — REQUIRED for the typed readRegister<T> template in
    //                        TPS25751DownstreamDevice; T must be constructible as
    //                        T(const uint8_t*, size_t)
    //   (RegisterInfo)     — size-from-info constructor (for factory create-from-info)
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit PartInfo()
        : TPS25751Register(Registers::PART_INFORMATION.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit PartInfo(const uint8_t* data)
        : TPS25751Register(data, Registers::PART_INFORMATION.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    PartInfo(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit PartInfo(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Device Part Number — PN[5:3] (bits 5:3 of byte 0)
     * @return 3-bit value; 0b011 (3) identifies a BQ25798
     */
    uint8_t partNumber() const;

    /**
     * @brief Device Revision — DEV_REV[2:0] (bits 2:0 of byte 0)
     * @return 3-bit revision code; 0b001 (1) for BQ25798 initial silicon
     */
    uint8_t deviceRevision() const;

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    /**
     * @brief Print register fields to @p s in a human-readable format
     *
     * Uses F() for every string literal (flash storage on AVR/Teensy).
     * Format mirrors TPS25751GPIOStatus::debugPrint exactly.
     */
    void debugPrint(Stream& s = Serial) const override;

    /**
     * @brief Semantic validation
     *
     * Returns true when:
     *   - Basic validity passes (non-null, correct size)
     *   - Reserved bits [7:6] are zero
     *   - PN == 0b011 (BQ25798 part number)
     */
    bool isSemanticallyValid() const override;

private:
    // -----------------------------------------------------------------------
    // Constants
    // -----------------------------------------------------------------------
    static constexpr uint8_t kExpectedPN        = 0b011;  ///< BQ25798 part number
    static constexpr uint8_t kExpectedSize      = Registers::PART_INFORMATION.size;
    static constexpr uint8_t kReservedMask      = 0xC0;   ///< Bits [7:6]
};

}  // namespace BQ25798
