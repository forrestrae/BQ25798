#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Mask 0 Register (REG28h, address 0x28)
 *
 * One-byte read/write register for masking charger interrupt sources.
 * Setting a bit to 1 prevents the corresponding event from generating
 * an INT pulse.
 *
 * Register layout (8 bits):
 *   Bit 7 — IINDPM_MASK         Mask IINDPM/IOTG event
 *   Bit 6 — VINDPM_MASK         Mask VINDPM/VOTG event
 *   Bit 5 — WD_MASK             Mask watchdog timer expiry
 *   Bit 4 — POORSRC_MASK        Mask poor source detection
 *   Bit 3 — PG_MASK             Mask power-good toggle
 *   Bit 2 — AC2_PRESENT_MASK    Mask VAC2 present status change
 *   Bit 1 — AC1_PRESENT_MASK    Mask VAC1 present status change
 *   Bit 0 — VBUS_PRESENT_MASK   Mask VBUS present status change
 *
 * Reset value: 0x00
 * Access: Read/Write [R/W]
 */
class ChargerMask0 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGER_MASK_0;

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerMask0()
        : TPS25751Register(Registers::CHARGER_MASK_0.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerMask0(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_MASK_0.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerMask0(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerMask0(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    bool iindpmMask()       const;  ///< bit 7
    bool vindpmMask()       const;  ///< bit 6
    bool wdMask()           const;  ///< bit 5
    bool poorsrcMask()      const;  ///< bit 4
    bool pgMask()           const;  ///< bit 3
    bool ac2PresentMask()   const;  ///< bit 2
    bool ac1PresentMask()   const;  ///< bit 1
    bool vbusPresentMask()  const;  ///< bit 0

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — true = Masked / no INT)
    // -----------------------------------------------------------------------

    void setIindpmMask(bool masked);       ///< @brief Set IINDPM_MASK (bit 7)
    void setVindpmMask(bool masked);       ///< @brief Set VINDPM_MASK (bit 6)
    void setWdMask(bool masked);           ///< @brief Set WD_MASK (bit 5)
    void setPoorsrcMask(bool masked);      ///< @brief Set POORSRC_MASK (bit 4)
    void setPgMask(bool masked);           ///< @brief Set PG_MASK (bit 3)
    void setAc2PresentMask(bool masked);   ///< @brief Set AC2_PRESENT_MASK (bit 2)
    void setAc1PresentMask(bool masked);   ///< @brief Set AC1_PRESENT_MASK (bit 1)
    void setVbusPresentMask(bool masked);  ///< @brief Set VBUS_PRESENT_MASK (bit 0)

    // -----------------------------------------------------------------------
    // TPS25751Register overrides
    // -----------------------------------------------------------------------

    void debugPrint(Stream& s = Serial) const override;
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_MASK_0.size;
};

}  // namespace BQ25798
