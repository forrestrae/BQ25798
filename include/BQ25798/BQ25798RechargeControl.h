#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Re-Charge Control Register (REG0Ah, address 0x0A)
 *
 * One-byte read/write register controlling battery cell count, recharge
 * debounce time, and recharge threshold voltage offset below VREG.
 *
 * Register layout (8 bits):
 *   Bits 7:6 — CELL_1:0       Battery cell count (enum 1s/2s/3s/4s)
 *   Bits 5:4 — TRECHG_1:0    Recharge debounce time (enum)
 *   Bits 3:0 — VRECHG_3:0    Recharge threshold offset below VREG
 *
 * Conversion for VRECHG_3:0:
 *   millivoltsBelowVreg = (VRECHG_3:0 * 50) + 50  [mV]
 *   (50 mV/LSB, 50 mV minimum offset)
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W]
 */
class RechargeControl : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::RECHARGE_CONTROL;

    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief CELL_1:0 — battery cell count (bits 7:6)
     */
    enum class Cell : uint8_t {
        S1 = 0,  ///< 1-cell (1s)
        S2 = 1,  ///< 2-cell (2s)
        S3 = 2,  ///< 3-cell (3s)
        S4 = 3,  ///< 4-cell (4s)
    };

    /**
     * @brief TRECHG_1:0 — recharge debounce time (bits 5:4)
     */
    enum class Trechg : uint8_t {
        Ms64   = 0,  ///< 64 ms
        Ms256  = 1,  ///< 256 ms
        Ms1024 = 2,  ///< 1024 ms (default)
        Ms2048 = 3,  ///< 2048 ms
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit RechargeControl()
        : TPS25751Register(Registers::RECHARGE_CONTROL.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit RechargeControl(const uint8_t* data)
        : TPS25751Register(data, Registers::RECHARGE_CONTROL.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    RechargeControl(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit RechargeControl(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Battery cell count — CELL_1:0 (bits 7:6)
     * @return Cell enum value
     */
    Cell cell() const;

    /**
     * @brief Recharge debounce time — TRECHG_1:0 (bits 5:4)
     * @return Trechg enum value
     */
    Trechg trechg() const;

    /**
     * @brief Raw VRECHG field — VRECHG_3:0 (bits 3:0)
     * @return 4-bit raw value (0–15)
     */
    uint8_t vrechgRaw() const;

    /**
     * @brief Recharge threshold offset below VREG in millivolts
     * @return Offset in mV: (VRECHG_3:0 * 50) + 50
     */
    uint16_t millivoltsBelowVreg() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Set battery cell count — CELL_1:0 (bits 7:6)
    void setCell(Cell v);

    /// @brief Set recharge debounce time — TRECHG_1:0 (bits 5:4)
    void setTrechg(Trechg v);

    /// @brief Set raw VRECHG field — VRECHG_3:0 (bits 3:0)
    void setVrechgRaw(uint8_t raw);

    /// @brief Set recharge threshold offset below VREG in millivolts — VRECHG_3:0 (bits 3:0)
    /// @param mv Offset in mV; encoded as VRECHG = (mv - 50) / 50 (50 mV/LSB, 50 mV min)
    void setMillivoltsBelowVreg(uint16_t mv);

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
     * Returns true when basic validity and correct register size pass.
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::RECHARGE_CONTROL.size;
};

}  // namespace BQ25798
