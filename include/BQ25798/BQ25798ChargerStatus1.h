#pragma once

#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

namespace BQ25798 {

/**
 * @brief BQ25798 Charger Status 1 Register (REG1Ch, address 0x1C)
 *
 * One-byte read-only register containing charge state, VBUS type, and BC1.2
 * detection status.
 *
 * Register layout (8 bits):
 *   Bits [7:5] — CHG_STAT[2:0]  Charge status (3-bit enum)
 *   Bits [4:1] — VBUS_STAT[3:0] VBUS status (4-bit enum)
 *   Bit  0     — BC1.2_DONE_STAT BC1.2 / non-standard detection complete
 *
 * Register size: 1 byte
 * Access: Read-only [R]
 */
class ChargerStatus1 : public TPS25751Register
{
public:
    // -----------------------------------------------------------------------
    // Enumerations
    // -----------------------------------------------------------------------

    /**
     * @brief CHG_STAT[2:0] — charge state (bits [7:5])
     */
    enum class ChgStat : uint8_t {
        NotCharging       = 0,  ///< Not charging
        TrickleCharge     = 1,  ///< Trickle charge
        Precharge         = 2,  ///< Pre-charge
        FastCharge        = 3,  ///< Fast charge (CC mode)
        TaperCharge       = 4,  ///< Taper charge (CV mode)
        Reserved          = 5,  ///< Reserved
        TopOff            = 6,  ///< Top-off timer active charging
        TerminationDone   = 7,  ///< Charge termination done
    };

    /**
     * @brief VBUS_STAT[3:0] — VBUS / adapter type (bits [4:1])
     */
    enum class VbusStat : uint8_t {
        NoInputOrOtg         = 0x0,  ///< No input, or BHOT/BCOLD in OTG mode
        UsbSdp               = 0x1,  ///< USB SDP (500 mA)
        UsbCdp               = 0x2,  ///< USB CDP (1.5 A)
        UsbDcp               = 0x3,  ///< USB DCP (3.25 A)
        Hvdcp                = 0x4,  ///< Adjustable High Voltage DCP (HVDCP, 1.5 A)
        UnknownAdapter       = 0x5,  ///< Unknown adapter (3 A)
        NonStandardAdapter   = 0x6,  ///< Non-standard adapter (1/2/2.1/2.4 A)
        OtgMode              = 0x7,  ///< Device in OTG mode
        NotQualified         = 0x8,  ///< Not qualified adapter
        Reserved9            = 0x9,  ///< Reserved
        ReservedA            = 0xA,  ///< Reserved
        DirectVbus           = 0xB,  ///< Device directly powered from VBUS
        BackupMode           = 0xC,  ///< Backup mode
        ReservedD            = 0xD,  ///< Reserved
        ReservedE            = 0xE,  ///< Reserved
        ReservedF            = 0xF,  ///< Reserved
    };

    // -----------------------------------------------------------------------
    // Constructors
    // -----------------------------------------------------------------------

    /// @brief Default constructor — zero-initialised, 1-byte register
    explicit ChargerStatus1()
        : TPS25751Register(Registers::CHARGER_STATUS_1.size) {}

    /// @brief Construct from raw byte array (fixed 1-byte size)
    explicit ChargerStatus1(const uint8_t* data)
        : TPS25751Register(data, Registers::CHARGER_STATUS_1.size) {}

    /// @brief Construct from raw byte array with explicit length
    /// Required for the typed readRegister<T>(devReg, T&, size_t) template.
    ChargerStatus1(const uint8_t* data, size_t len)
        : TPS25751Register(data, len) {}

    /// @brief Construct from RegisterInfo (factory path)
    explicit ChargerStatus1(Registers::RegisterInfo regInfo)
        : TPS25751Register(regInfo.size) {}

    // -----------------------------------------------------------------------
    // Accessors
    // -----------------------------------------------------------------------

    /**
     * @brief Charge status — CHG_STAT[2:0] (bits [7:5])
     * @return ChgStat enum value
     */
    ChgStat chgStat() const;

    /**
     * @brief VBUS status — VBUS_STAT[3:0] (bits [4:1])
     * @return VbusStat enum value
     */
    VbusStat vbusStat() const;

    /**
     * @brief BC1.2 / non-standard detection complete — bit 0
     * @return true if detection is complete
     */
    bool bc12DoneStat() const;

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
    static constexpr uint8_t kExpectedSize = Registers::CHARGER_STATUS_1.size;
};

}  // namespace BQ25798
