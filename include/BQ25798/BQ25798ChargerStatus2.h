#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Status 2 Register (REG1Dh, address 0x1D)
 *
 * One-byte read-only register containing ICO, thermal regulation, D+/D-
 * detection, and battery presence status.
 *
 * Register layout (8 bits):
 *   Bits [7:6] — ICO_STAT[1:0]    Input Current Optimizer status (2-bit enum)
 *   Bits [5:3] — RESERVED
 *   Bit  2     — TREG_STAT         IC thermal regulation status
 *   Bit  1     — DPDM_STAT         D+/D- detection ongoing status
 *   Bit  0     — VBAT_PRESENT_STAT Battery present status
 *
 * Semantic validity:
 *   - Reserved bits [5:3] must be zero.
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class ChargerStatus2 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief ICO_STAT[1:0] — Input Current Optimizer status (bits [7:6])
     */
    enum class IcoStat : uint8_t {
        Disabled          = 0,  ///< ICO disabled
        InProgress        = 1,  ///< ICO optimization in progress
        MaxCurrentFound   = 2,  ///< Maximum input current detected
        Reserved          = 3,  ///< Reserved
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerStatus2()
        : TPS25751Register(Registers::CHARGER_STATUS_2.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerStatus2(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_STATUS_2.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerStatus2(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerStatus2(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief ICO status — ICO_STAT[1:0] (bits [7:6])
     * @return IcoStat enum value
     */
    IcoStat icoStat() const;

    /**
     * @brief IC thermal regulation status — bit 2
     * @return true if device is in thermal regulation
     */
    bool tregStat() const;

    /**
     * @brief D+/D- detection status — bit 1
     * @return true if D+/D- detection is ongoing
     */
    bool dpdmStat() const;

    /**
     * @brief Battery present status — bit 0
     * @return true if VBAT is present (above VBAT_UVLOZ threshold)
     */
    bool vbatPresentStat() const;

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
     *   - Reserved bits [5:3] are zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_STATUS_2.size;
    static constexpr uint8_t kReservedMask = 0x38;  ///< Bits [5:3]
};

}  // namespace BQ25798
