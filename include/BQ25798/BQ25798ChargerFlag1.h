#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Flag 1 Register (REG23h, address 0x23)
 *
 * One-byte read-only register containing interrupt flags for charge status,
 * ICO, VBUS status, thermal regulation, VBAT present, and BC1.2 completion.
 * Each flag latches on the relevant edge or status change and is cleared by
 * reading this register.
 *
 * Register layout (8 bits):
 *   Bit 7 — CHG_FLAG           Charge status changed
 *   Bit 6 — ICO_FLAG           ICO status changed
 *   Bit 5 — RESERVED
 *   Bit 4 — VBUS_FLAG          VBUS status changed
 *   Bit 3 — RESERVED
 *   Bit 2 — TREG_FLAG          IC thermal regulation rising threshold detected
 *   Bit 1 — VBAT_PRESENT_FLAG  VBAT present status changed
 *   Bit 0 — BC1.2_DONE_FLAG    BC1.2 detection status changed
 *
 * Reserved bits: 5, 3 — must be zero in a valid register read.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class ChargerFlag1 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerFlag1()
        : TPS25751Register(Registers::CHARGER_FLAG_1.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerFlag1(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_FLAG_1.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerFlag1(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerFlag1(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors — one per flag bit, bit positions per TRM Table 9-23
    // -----------------------------------------------------------------------

    /// @brief CHG_FLAG — bit 7: Charge status changed
    bool chgFlag() const;

    /// @brief ICO_FLAG — bit 6: ICO status changed
    bool icoFlag() const;

    /// @brief VBUS_FLAG — bit 4: VBUS status changed
    bool vbusFlag() const;

    /// @brief TREG_FLAG — bit 2: IC thermal regulation rising threshold detected
    bool tregFlag() const;

    /// @brief VBAT_PRESENT_FLAG — bit 1: VBAT present status changed
    bool vbatPresentFlag() const;

    /// @brief BC1.2_DONE_FLAG — bit 0: BC1.2 detection status changed
    bool bc12DoneFlag() const;

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
     *   - Reserved bits (5, 3) are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize  = Registers::CHARGER_FLAG_1.size;
    static constexpr uint8_t kReservedMask  = (1u << 5) | (1u << 3);  ///< Bits 5 and 3
};

}  // namespace BQ25798
