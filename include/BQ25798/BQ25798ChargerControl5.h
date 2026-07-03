#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Control 5 Register (REG14h, address 0x14)
 *
 * One-byte read/write register controlling ship FET presence, battery discharge
 * current sensing, OTG discharge current regulation, IINDPM, external ILIM,
 * and battery OCP.
 *
 * Register layout (8 bits):
 *   Bit  7   — SFET_PRESENT    Ship FET populated flag
 *   Bit  6   — RESERVED        Reserved [R]
 *   Bit  5   — EN_IBAT         IBAT discharge sensing enable
 *   Bits 4:3 — IBAT_REG_1:0   Battery discharge current regulation in OTG mode (enum)
 *   Bit  2   — EN_IINDPM       Enable internal IINDPM / IOTG regulation
 *   Bit  1   — EN_EXTILIM      Enable external ILIM_HIZ pin regulation
 *   Bit  0   — EN_BATOC        Enable battery discharge current OCP
 *
 * Reset value: 0x16 (EN_IINDPM=1, EN_EXTILIM=1, IBAT_REG=3 [Disable])
 * Access: Read/Write [R/W]
 */
class ChargerControl5 : public TPS25751Register
{
public:
    /// @brief Register address — single source of register identity for typed writes.
    static constexpr Registers::Address kAddress = Registers::Address::CHARGER_CONTROL_5;

    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief IBAT_REG_1:0 — battery discharge current regulation in OTG mode (bits 4:3)
     */
    enum class IbatReg : uint8_t {
        A3      = 0,  ///< 3 A
        A4      = 1,  ///< 4 A
        A5      = 2,  ///< 5 A
        Disable = 3,  ///< Disabled (default)
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerControl5()
        : TPS25751Register(Registers::CHARGER_CONTROL_5.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerControl5(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_CONTROL_5.size) {}

    /// @brief Construct from raw byte array with explicit length.
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerControl5(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerControl5(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Ship FET populated — SFET_PRESENT (bit 7)
     * @return true if a ship FET is populated; enables ship-FET-related features
     */
    bool sfetPresent() const;

    /**
     * @brief IBAT discharge sensing enable — EN_IBAT (bit 5)
     * @return true if IBAT discharge sensing is enabled in battery-only/HIZ mode
     */
    bool enIbat() const;

    /**
     * @brief Battery discharge current regulation in OTG mode — IBAT_REG_1:0 (bits 4:3)
     * @return IbatReg enum value
     */
    IbatReg ibatReg() const;

    /**
     * @brief Enable internal IINDPM / IOTG regulation — EN_IINDPM (bit 2)
     * @return true if internal IINDPM and IOTG registers are enabled
     */
    bool enIindpm() const;

    /**
     * @brief Enable external ILIM_HIZ pin regulation — EN_EXTILIM (bit 1)
     * @return true if the external ILIM_HIZ pin input current regulation is enabled
     */
    bool enExtilim() const;

    /**
     * @brief Battery discharge current OCP enable — EN_BATOC (bit 0)
     * @return true if battery discharge OCP is enabled
     */
    bool enBatoc() const;

    // -----------------------------------------------------------------------
    // Field setters (read-modify-write — each touches only its own field)
    // -----------------------------------------------------------------------

    /// @brief Set ship FET populated flag — SFET_PRESENT (bit 7)
    void setSfetPresent(bool on);

    /// @brief Enable IBAT discharge sensing — EN_IBAT (bit 5)
    void setEnIbat(bool on);

    /// @brief Set battery discharge current regulation in OTG mode — IBAT_REG_1:0 (bits 4:3)
    void setIbatReg(IbatReg v);

    /// @brief Enable internal IINDPM / IOTG regulation — EN_IINDPM (bit 2)
    void setEnIindpm(bool on);

    /// @brief Enable external ILIM_HIZ pin regulation — EN_EXTILIM (bit 1)
    void setEnExtilim(bool on);

    /// @brief Enable battery discharge current OCP — EN_BATOC (bit 0)
    void setEnBatoc(bool on);

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
     *   - Reserved bit 6 is zero
     */
    bool isSemanticallyValid() const override;

private:
    static constexpr uint8_t kExpectedSize  = Registers::CHARGER_CONTROL_5.size;
    static constexpr uint8_t kReservedMask  = 0x40;  ///< Bit 6
};

}  // namespace BQ25798
