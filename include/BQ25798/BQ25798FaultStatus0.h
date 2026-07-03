#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Fault Status 0 Register (REG20h, address 0x20)
 *
 * One-byte read-only register containing over-voltage and over-current
 * protection fault status flags.
 *
 * Register layout (8 bits):
 *   Bit 7 — IBAT_REG_STAT  Battery discharge current regulation status
 *   Bit 6 — VBUS_OVP_STAT  VBUS over-voltage protection
 *   Bit 5 — VBAT_OVP_STAT  VBAT over-voltage protection
 *   Bit 4 — IBUS_OCP_STAT  IBUS over-current protection
 *   Bit 3 — IBAT_OCP_STAT  IBAT over-current protection
 *   Bit 2 — CONV_OCP_STAT  Converter over-current protection
 *   Bit 1 — VAC2_OVP_STAT  VAC2 over-voltage protection
 *   Bit 0 — VAC1_OVP_STAT  VAC1 over-voltage protection
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class FaultStatus0 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit FaultStatus0()
        : TPS25751Register(Registers::FAULT_STATUS_0.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit FaultStatus0(const uint8_t* data)
        : TPS25751Register(data, Registers::FAULT_STATUS_0.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    FaultStatus0(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit FaultStatus0(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Battery discharge current regulation status — bit 7
     * @return true if device is in battery discharging current regulation
     */
    bool ibatRegStat() const;

    /**
     * @brief VBUS over-voltage protection status — bit 6
     * @return true if device is in VBUS over-voltage protection
     */
    bool vbusOvpStat() const;

    /**
     * @brief VBAT over-voltage protection status — bit 5
     * @return true if device is in VBAT over-voltage protection
     */
    bool vbatOvpStat() const;

    /**
     * @brief IBUS over-current protection status — bit 4
     * @return true if device is in IBUS over-current protection
     */
    bool ibusOcpStat() const;

    /**
     * @brief IBAT over-current protection status — bit 3
     * @return true if device is in IBAT over-current protection
     */
    bool ibatOcpStat() const;

    /**
     * @brief Converter over-current protection status — bit 2
     * @return true if converter is in over-current protection
     */
    bool convOcpStat() const;

    /**
     * @brief VAC2 over-voltage protection status — bit 1
     * @return true if device is in VAC2 over-voltage protection
     */
    bool vac2OvpStat() const;

    /**
     * @brief VAC1 over-voltage protection status — bit 0
     * @return true if device is in VAC1 over-voltage protection
     */
    bool vac1OvpStat() const;

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
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::FAULT_STATUS_0.size;
};

}  // namespace BQ25798
