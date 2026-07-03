#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 DPDM Driver Register (REG47h, address 0x47)
 *
 * One-byte read/write register controlling D+ and D- output drivers.
 * Bits 1:0 are reserved.
 *
 * Register layout (8 bits):
 *   Bits 7:5 — DPLUS_DAC_2:0   D+ output driver setting (enum)
 *   Bits 4:2 — DMINUS_DAC_2:0  D- output driver setting (enum, value 7h reserved)
 *   Bits 1:0 — RESERVED
 *
 * Reset value: 0x00
 * Access: Read/Write [R/W]
 */
class DpdmDriver : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::DPDM_DRIVER;

    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief DPLUS_DAC_2:0 — D+ output driver setting (bits 7:5)
     */
    enum class DplusDac : uint8_t {
        HIZ      = 0,  ///< Hi-Z (default)
        V0       = 1,  ///< 0 V
        V0p6     = 2,  ///< 0.6 V
        V1p2     = 3,  ///< 1.2 V
        V2p0     = 4,  ///< 2.0 V
        V2p7     = 5,  ///< 2.7 V
        V3p3     = 6,  ///< 3.3 V
        Short    = 7,  ///< D+/D- short
    };

    /**
     * @brief DMINUS_DAC_2:0 — D- output driver setting (bits 4:2)
     * Note: value 7h (0b111) is reserved by the datasheet.
     */
    enum class DminusDac : uint8_t {
        HIZ      = 0,  ///< Hi-Z (default)
        V0       = 1,  ///< 0 V
        V0p6     = 2,  ///< 0.6 V
        V1p2     = 3,  ///< 1.2 V
        V2p0     = 4,  ///< 2.0 V
        V2p7     = 5,  ///< 2.7 V
        V3p3     = 6,  ///< 3.3 V
        Reserved = 7,  ///< Reserved (do not use)
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit DpdmDriver()
        : TPS25751Register(Registers::DPDM_DRIVER.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit DpdmDriver(const uint8_t* data)
        : TPS25751Register(data, Registers::DPDM_DRIVER.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    DpdmDriver(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit DpdmDriver(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief D+ output driver setting — DPLUS_DAC_2:0 (bits 7:5)
     * @return DplusDac enum value
     */
    DplusDac dplusDac() const;

    /**
     * @brief D- output driver setting — DMINUS_DAC_2:0 (bits 4:2)
     * @return DminusDac enum value
     */
    DminusDac dminusDac() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // Reserved bits 1:0 have no setter.
    // -----------------------------------------------------------------------

    /// @brief Set D+ output driver setting — DPLUS_DAC_2:0 (bits 7:5)
    void setDplusDac(DplusDac v);

    /// @brief Set D- output driver setting — DMINUS_DAC_2:0 (bits 4:2)
    void setDminusDac(DminusDac v);

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
     * Returns true when basic validity, correct size, reserved bits zero,
     * and DMINUS_DAC != Reserved.
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::DPDM_DRIVER.size;
    static constexpr uint8_t kReservedMask = 0x03u;  ///< Bits 1:0
};

}  // namespace BQ25798
