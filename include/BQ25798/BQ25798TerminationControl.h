#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Termination Control Register (REG09h, address 0x09)
 *
 * One-byte read/write register controlling charge termination: the register
 * reset flag (REG_RST), the watchdog-expiry charge-enable behaviour (STOP_WD_CHG),
 * and the termination current threshold (ITERM).
 *
 * Register layout (8 bits):
 *   Bit  7   — RESERVED
 *   Bit  6   — REG_RST       Reset all registers to default and reset timer
 *   Bit  5   — STOP_WD_CHG  Watchdog expiry disables charging when set
 *   Bits 4:0 — ITERM_4:0    Termination current limit
 *
 * ITERM conversion: milliamps = ITERM * 40
 *   Range: 40 mA (0x01) to 1280 mA (0x20), 40 mA/LSB
 *   (0x00 = 0 mA; disables termination detection)
 *
 * Semantic validity:
 *   - Reserved bit 7 must be zero.
 *
 * Register size: 1 byte
 * Access: Read/Write [R/W]
 * Reset: 0x05 (REG_RST=0, STOP_WD_CHG=0, ITERM=0b00101 [200 mA])
 */
class TerminationControl : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::TERMINATION_CONTROL;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit TerminationControl()
        : TPS25751Register(Registers::TERMINATION_CONTROL.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit TerminationControl(const uint8_t* data)
        : TPS25751Register(data, Registers::TERMINATION_CONTROL.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    TerminationControl(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit TerminationControl(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Register reset flag — REG_RST (bit 6)
     *
     * When written as 1, all registers are reset to default and the timer is
     * reset. The bit self-clears after reset. Reading 1 means a reset is in
     * progress.
     * @return true if REG_RST is set
     */
    bool regRst() const;

    /**
     * @brief Watchdog expiry charge-stop flag — STOP_WD_CHG (bit 5)
     * @return true if watchdog expiry will set EN_CHG=0 (disable charging)
     */
    bool stopWdChg() const;

    /**
     * @brief Raw ITERM field — ITERM_4:0 (bits 4:0)
     * @return 5-bit raw value; 0 if not valid
     */
    uint8_t itermRaw() const;

    /**
     * @brief Termination current threshold in milliamps
     *
     * Converts the 5-bit ITERM field using: mA = ITERM * 40
     * @return Current in mA; 0 if not valid
     */
    uint16_t milliamps() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field;
    // reserved bit 7 is never written)
    // -----------------------------------------------------------------------

    /// @brief Set register reset flag — REG_RST (bit 6); write 1 to reset all registers
    void setRegRst(bool on);

    /// @brief Set watchdog-expiry charge-stop flag — STOP_WD_CHG (bit 5)
    void setStopWdChg(bool on);

    /// @brief Set raw ITERM field — ITERM_4:0 (bits 4:0)
    void setItermRaw(uint8_t raw);

    /// @brief Set termination current threshold in milliamps — ITERM_4:0 (bits 4:0)
    /// @param ma Current in mA; encoded as ITERM = ma / 40 (40 mA/LSB)
    void setMilliamps(uint16_t ma);

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
     *   - Reserved bit 7 is zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t  kExpectedSize  = Registers::TERMINATION_CONTROL.size;
    static constexpr uint8_t  kReservedMask  = 0x80;  ///< Bit 7
    static constexpr uint16_t kLsbMa         = 40;    ///< mA per LSB
};

}  // namespace BQ25798
