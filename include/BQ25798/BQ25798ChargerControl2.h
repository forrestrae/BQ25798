#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Control 2 Register (REG11h, address 0x11)
 *
 * One-byte read/write register controlling D+/D- detection, HVDCP voltage
 * selection, ship FET control, and ship FET delay.
 *
 * Register layout (8 bits):
 *   Bit  7   — FORCE_INDET      Force D+/D- detection
 *   Bit  6   — AUTO_INDET_EN    Automatic D+/D- detection enable
 *   Bit  5   — EN_12V           Enable 12 V mode in HVDCP
 *   Bit  4   — EN_9V            Enable 9 V mode in HVDCP
 *   Bit  3   — HVDCP_EN         Enable HVDCP handshake
 *   Bits 2:1 — SDRV_CTRL_1:0   Ship FET control mode (enum)
 *   Bit  0   — SDRV_DLY         Ship FET action delay
 *
 * Reset value: 0x40 (AUTO_INDET_EN=1)
 * Access: Read/Write [R/W]
 */
class ChargerControl2 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGER_CONTROL_2;

    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief SDRV_CTRL_1:0 — external ship FET control mode (bits 2:1)
     */
    enum class SdrvCtrl : uint8_t {
        Idle             = 0,  ///< IDLE (default)
        ShutdownMode     = 1,  ///< Shutdown Mode
        ShipMode         = 2,  ///< Ship Mode
        SystemPowerReset = 3,  ///< System Power Reset
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerControl2()
        : TPS25751Register(Registers::CHARGER_CONTROL_2.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerControl2(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_CONTROL_2.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerControl2(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerControl2(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Force D+/D- detection — FORCE_INDET (bit 7)
     * @return true if D+/D- detection is forced (self-clears when done)
     */
    bool forceIndet() const;

    /**
     * @brief Automatic D+/D- detection enable — AUTO_INDET_EN (bit 6)
     * @return true if automatic detection on VBUS plug-in is enabled
     */
    bool autoIndetEn() const;

    /**
     * @brief Enable 12 V mode in HVDCP — EN_12V (bit 5)
     * @return true if 12 V HVDCP mode is enabled
     */
    bool en12v() const;

    /**
     * @brief Enable 9 V mode in HVDCP — EN_9V (bit 4)
     * @return true if 9 V HVDCP mode is enabled
     */
    bool en9v() const;

    /**
     * @brief HVDCP handshake enable — HVDCP_EN (bit 3)
     * @return true if HVDCP handshake is enabled
     */
    bool hvdcpEn() const;

    /**
     * @brief Ship FET control mode — SDRV_CTRL_1:0 (bits 2:1)
     * @return SdrvCtrl enum value
     */
    SdrvCtrl sdrvCtrl() const;

    /**
     * @brief Ship FET action delay — SDRV_DLY (bit 0)
     * @return true = no 10 s delay; false = add 10 s delay (default)
     */
    bool sdrvDly() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Set force D+/D- detection — FORCE_INDET (bit 7).
    /// The bit self-clears in hardware when detection completes.
    void setForceIndet(bool on);

    /// @brief Set automatic D+/D- detection enable — AUTO_INDET_EN (bit 6)
    void setAutoIndetEn(bool on);

    /// @brief Set enable 12 V mode in HVDCP — EN_12V (bit 5)
    void setEn12v(bool on);

    /// @brief Set enable 9 V mode in HVDCP — EN_9V (bit 4)
    void setEn9v(bool on);

    /// @brief Set HVDCP handshake enable — HVDCP_EN (bit 3)
    void setHvdcpEn(bool on);

    /// @brief Set ship FET control mode — SDRV_CTRL_1:0 (bits 2:1)
    void setSdrvCtrl(SdrvCtrl v);

    /// @brief Set ship FET action delay — SDRV_DLY (bit 0); true = no 10 s delay
    void setSdrvDly(bool on);

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
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_CONTROL_2.size;
};

}  // namespace BQ25798
