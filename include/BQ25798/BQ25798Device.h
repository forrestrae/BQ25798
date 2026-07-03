#pragma once

#include <memory>
#include "TPS25751DownstreamDevice.h"
#include "BQ25798/BQ25798Registers.h"
#include "BQ25798/BQ25798PartInfo.h"
#include "BQ25798/BQ25798ChargerStatus0.h"
#include "BQ25798/BQ25798ChargerStatus1.h"
#include "BQ25798/BQ25798ChargerStatus2.h"
#include "BQ25798/BQ25798ChargerStatus3.h"
#include "BQ25798/BQ25798ChargerStatus4.h"
#include "BQ25798/BQ25798FaultStatus0.h"
#include "BQ25798/BQ25798FaultStatus1.h"
#include "BQ25798/BQ25798ChargerFlag0.h"
#include "BQ25798/BQ25798ChargerFlag1.h"
#include "BQ25798/BQ25798ChargerFlag2.h"
#include "BQ25798/BQ25798ChargerFlag3.h"
#include "BQ25798/BQ25798FaultFlag0.h"
#include "BQ25798/BQ25798FaultFlag1.h"
#include "BQ25798/BQ25798AdcControl.h"
#include "BQ25798/BQ25798AdcFunctionDisable0.h"
#include "BQ25798/BQ25798AdcFunctionDisable1.h"
#include "BQ25798/BQ25798IbusAdc.h"
#include "BQ25798/BQ25798IbatAdc.h"
#include "BQ25798/BQ25798VbusAdc.h"
#include "BQ25798/BQ25798Vac1Adc.h"
#include "BQ25798/BQ25798Vac2Adc.h"
#include "BQ25798/BQ25798VbatAdc.h"
#include "BQ25798/BQ25798VsysAdc.h"
#include "BQ25798/BQ25798TsAdc.h"
#include "BQ25798/BQ25798TdieAdc.h"
#include "BQ25798/BQ25798MinimalSystemVoltage.h"
#include "BQ25798/BQ25798ChargeVoltageLimit.h"
#include "BQ25798/BQ25798ChargeCurrentLimit.h"
#include "BQ25798/BQ25798InputVoltageLimit.h"
#include "BQ25798/BQ25798InputCurrentLimit.h"
#include "BQ25798/BQ25798PrechargeControl.h"
#include "BQ25798/BQ25798TerminationControl.h"
#include "BQ25798/BQ25798NtcControl0.h"
#include "BQ25798/BQ25798NtcControl1.h"
#include "BQ25798/BQ25798IcoCurrentLimit.h"
#include "BQ25798/BQ25798ChargerControl0.h"
#include "BQ25798/BQ25798ChargerControl1.h"
#include "BQ25798/BQ25798ChargerControl2.h"
#include "BQ25798/BQ25798ChargerControl3.h"
#include "BQ25798/BQ25798ChargerControl4.h"
#include "BQ25798/BQ25798ChargerControl5.h"
#include "BQ25798/BQ25798RechargeControl.h"
#include "BQ25798/BQ25798VotgRegulation.h"
#include "BQ25798/BQ25798IotgRegulation.h"
#include "BQ25798/BQ25798TimerControl.h"
#include "BQ25798/BQ25798MpptControl.h"
#include "BQ25798/BQ25798TemperatureControl.h"
#include "BQ25798/BQ25798ChargerMask0.h"
#include "BQ25798/BQ25798ChargerMask1.h"
#include "BQ25798/BQ25798ChargerMask2.h"
#include "BQ25798/BQ25798ChargerMask3.h"
#include "BQ25798/BQ25798FaultMask0.h"
#include "BQ25798/BQ25798FaultMask1.h"
#include "BQ25798/BQ25798DplusAdc.h"
#include "BQ25798/BQ25798DminusAdc.h"
#include "BQ25798/BQ25798DpdmDriver.h"

namespace BQ25798 {

/**
 * @brief BQ25798 charger driver — typed register access, proxied or direct
 *
 * The driver can reach the charger two ways, selected by which constructor is
 * used; the typed API below is identical either way:
 *   - **Proxied** (Device(host, addr)): relayed through the TPS25751 host's
 *     executeCommand() via the inherited TPS25751DownstreamDevice interface
 *     (I2Cr / I2Cw 4CC tasks) — for a charger on the TPS25751's I2Cc bus.
 *   - **Direct** (Device(wire, addr)): plain Arduino-`Wire` register transactions
 *     straight to the part on the MCU's own I2C bus — for bench/bring-up. None of
 *     the proxy constraints (TRM 5 s spacing, 63/11-byte caps) apply.
 *
 * Design:
 *   - Inherits TPS25751DownstreamDevice (composition-by-inheritance, exactly
 *     like TPS25751 register classes inherit TPS25751Register).
 *   - Exposes typed accessor methods that return std::unique_ptr<RegisterClass>.
 *   - Does NOT subclass TPS25751 — the host is composed, not extended.
 *
 * Adding registers (Stage 3):
 *   1. Include the group header (e.g. BQ25798ChargerStatus.h).
 *   2. Add a typed accessor (e.g. readChargerStatus0(bool validate=true) const).
 *   3. Mark the TODO comment below at the accessor boundary.
 *
 * @note The default 7-bit address kDefaultI2CAddress = 0x6B must NOT have its
 *       R/W bit included — TPS25751DownstreamDevice masks bit 7 internally.
 */
class Device : public TPS25751DownstreamDevice
{
public:
    /**
     * @brief Construct a BQ25798 driver proxied through @p host
     * @param host TPS25751 instance whose executeCommand() relays I2Cr/I2Cw tasks
     * @param addr 7-bit I2C address of the BQ25798 (default: kDefaultI2CAddress)
     */
    explicit Device(const TPS25751& host,
                    uint8_t addr = BQ25798::kDefaultI2CAddress)
        : TPS25751DownstreamDevice(host, addr)
    {}

    /**
     * @brief Construct a BQ25798 driver that talks to the part **directly** on @p wire
     *
     * Direct (non-proxied) transport: register reads/writes are plain Arduino-`Wire`
     * transactions to the charger on the MCU's own I2C bus, with no TPS25751 relay.
     * For bench/bring-up where the BQ25798 is wired to @p wire rather than the
     * TPS25751's I2Cc bus. The typed accessors and write tier are identical to the
     * proxied constructor.
     *
     * @param wire I2C bus the BQ25798 is wired to (caller is responsible for wire.begin())
     * @param addr 7-bit I2C address of the BQ25798 (default: kDefaultI2CAddress)
     */
    explicit Device(TwoWire& wire,
                    uint8_t addr = BQ25798::kDefaultI2CAddress)
        : TPS25751DownstreamDevice(wire, addr)
    {}

    // -----------------------------------------------------------------------
    // Typed register writes
    // -----------------------------------------------------------------------

    // Keep the inherited raw writeRegister(uint8_t, const uint8_t*, size_t)
    // visible for unqualified calls; the typed template below would otherwise
    // hide it via name lookup. They overload cleanly (distinct signatures).
    using TPS25751DownstreamDevice::writeRegister;

    /**
     * @brief Generic typed write: writes @p reg back to its own register address.
     *
     * Sends reg.raw()/reg.size() to T::kAddress via the inherited raw I2Cw path.
     *
     * @tparam T Register decoder type exposing a static T::kAddress and raw()/size().
     * @param reg Register value object to write.
     * @return true if the I2Cw task reported success (queued).
     */
    template<typename T>
    bool writeRegister(const T& reg) const {
        return TPS25751DownstreamDevice::writeRegister(
            static_cast<uint8_t>(T::kAddress), reg.raw(), reg.size());
    }

    /**
     * @brief Read-modify-write: read T live, apply @p mutate, write it back.
     *
     * @tparam T  Register decoder type with a static T::kAddress.
     * @tparam Fn Callable invoked as mutate(T&).
     * @param mutate Mutator applied to the freshly read register before write-back.
     * @return false on any I/O failure (read or write), true otherwise.
     */
    template<typename T, typename Fn>
    bool updateRegister(Fn&& mutate) const {
        T reg;
        const uint8_t addr = static_cast<uint8_t>(T::kAddress);
        const size_t  sz   = Registers::getRegisterSize(T::kAddress);
        if (!readRegister(addr, reg, sz)) return false;
        mutate(reg);
        return writeRegister(reg);
    }

    // -----------------------------------------------------------------------
    // Convenience setters (L3) — one-call read-modify-write helpers
    // -----------------------------------------------------------------------

    /**
     * @brief Enable or disable charging — ChargerControl0 EN_CHG (bit 5).
     *
     * One-call read-modify-write: reads ChargerControl0 live, sets EN_CHG to
     * @p on, and writes the register back (all other bits preserved).
     *
     * @param on true to enable charging, false to disable.
     * @return false on any I/O failure, true otherwise.
     */
    bool enableCharging(bool on) const;

    /**
     * @brief Enable or disable HIZ mode — ChargerControl0 EN_HIZ (bit 2).
     * @param on true to enter HIZ (input current to zero), false to exit.
     * @return false on any I/O failure, true otherwise.
     */
    bool enableHiz(bool on) const;

    /**
     * @brief Enable or disable the ADC — AdcControl ADC_EN (bit 7).
     * @param on true to enable the ADC, false to disable.
     * @return false on any I/O failure, true otherwise.
     */
    bool enableADC(bool on) const;

    /**
     * @brief Kick the I2C watchdog — ChargerControl1 WD_RST (bit 3, self-clearing).
     *
     * Sets WD_RST=1; the BQ25798 resets the watchdog timer and clears the bit in
     * hardware, so a subsequent read reports 0.
     * @return false on any I/O failure, true otherwise.
     */
    bool kickWatchdog() const;

    /**
     * @brief Set the watchdog timer period — ChargerControl1 WATCHDOG_2:0 (bits 2:0).
     * @param v Watchdog enum value (Disable, 0.5s … 160s).
     * @return false on any I/O failure, true otherwise.
     */
    bool setWatchdog(ChargerControl1::Watchdog v) const;

    /**
     * @brief Set the fast-charge current limit — ChargeCurrentLimit ICHG (10 mA/LSB).
     * @param milliamps Target current in mA (rounded down to the 10 mA step).
     * @return false on any I/O failure, true otherwise.
     */
    bool setChargeCurrentLimit(uint16_t milliamps) const;

    /**
     * @brief Set the battery voltage regulation limit — ChargeVoltageLimit VREG (10 mV/LSB).
     * @param millivolts Target voltage in mV (rounded down to the 10 mV step).
     * @return false on any I/O failure, true otherwise.
     */
    bool setChargeVoltageLimit(uint16_t millivolts) const;

    /**
     * @brief Set the input current limit — InputCurrentLimit IINDPM (10 mA/LSB).
     * @param milliamps Target current in mA (rounded down to the 10 mA step).
     * @return false on any I/O failure, true otherwise.
     */
    bool setInputCurrentLimit(uint16_t milliamps) const;

    /**
     * @brief Set the input voltage (VINDPM) limit — InputVoltageLimit VINDPM (100 mV/LSB).
     * @param millivolts Target voltage in mV (rounded down to the 100 mV step).
     * @return false on any I/O failure, true otherwise.
     */
    bool setInputVoltageLimit(uint16_t millivolts) const;

    /**
     * @brief Enable or disable OTG (boost) mode — ChargerControl3 EN_OTG (bit 6).
     * @param on true to enable OTG sourcing, false to disable.
     * @return false on any I/O failure, true otherwise.
     */
    bool enableOTG(bool on) const;

    // -----------------------------------------------------------------------
    // Typed register accessors
    // Each method reads the register via I2Cr, constructs the typed object,
    // and optionally verifies isSemanticallyValid() before returning.
    // Returns nullptr on I2C failure or (if validate=true) semantic failure.
    // -----------------------------------------------------------------------

    /**
     * @brief Read and decode the Part Information register (REG48h)
     * @param validate If true, returns nullptr when isSemanticallyValid() fails.
     * @return Decoded PartInfo, or nullptr on I2C failure or (if validate) semantic failure.
     */
    std::unique_ptr<PartInfo> readPartInfo(bool validate = true) const;

    // --- Status ---
    std::unique_ptr<ChargerStatus0> readChargerStatus0(bool validate = true) const;
    std::unique_ptr<ChargerStatus1> readChargerStatus1(bool validate = true) const;
    std::unique_ptr<ChargerStatus2> readChargerStatus2(bool validate = true) const;
    std::unique_ptr<ChargerStatus3> readChargerStatus3(bool validate = true) const;
    std::unique_ptr<ChargerStatus4> readChargerStatus4(bool validate = true) const;
    std::unique_ptr<FaultStatus0>   readFaultStatus0(bool validate = true) const;
    std::unique_ptr<FaultStatus1>   readFaultStatus1(bool validate = true) const;

    // --- Flags ---
    std::unique_ptr<ChargerFlag0> readChargerFlag0(bool validate = true) const;
    std::unique_ptr<ChargerFlag1> readChargerFlag1(bool validate = true) const;
    std::unique_ptr<ChargerFlag2> readChargerFlag2(bool validate = true) const;
    std::unique_ptr<ChargerFlag3> readChargerFlag3(bool validate = true) const;
    std::unique_ptr<FaultFlag0>   readFaultFlag0(bool validate = true) const;
    std::unique_ptr<FaultFlag1>   readFaultFlag1(bool validate = true) const;

    // --- ADC ---
    std::unique_ptr<AdcControl>          readAdcControl(bool validate = true) const;
    std::unique_ptr<AdcFunctionDisable0> readAdcFunctionDisable0(bool validate = true) const;
    std::unique_ptr<AdcFunctionDisable1> readAdcFunctionDisable1(bool validate = true) const;
    std::unique_ptr<IbusAdc>             readIbusAdc(bool validate = true) const;
    std::unique_ptr<IbatAdc>             readIbatAdc(bool validate = true) const;
    std::unique_ptr<VbusAdc>             readVbusAdc(bool validate = true) const;
    std::unique_ptr<Vac1Adc>             readVac1Adc(bool validate = true) const;
    std::unique_ptr<Vac2Adc>             readVac2Adc(bool validate = true) const;
    std::unique_ptr<VbatAdc>             readVbatAdc(bool validate = true) const;
    std::unique_ptr<VsysAdc>             readVsysAdc(bool validate = true) const;
    std::unique_ptr<TsAdc>               readTsAdc(bool validate = true) const;
    std::unique_ptr<TdieAdc>             readTdieAdc(bool validate = true) const;

    // --- Charge limits / thresholds ---
    std::unique_ptr<MinimalSystemVoltage> readMinimalSystemVoltage(bool validate = true) const;
    std::unique_ptr<ChargeVoltageLimit>   readChargeVoltageLimit(bool validate = true) const;
    std::unique_ptr<ChargeCurrentLimit>   readChargeCurrentLimit(bool validate = true) const;
    std::unique_ptr<InputVoltageLimit>    readInputVoltageLimit(bool validate = true) const;
    std::unique_ptr<InputCurrentLimit>    readInputCurrentLimit(bool validate = true) const;
    std::unique_ptr<PrechargeControl>     readPrechargeControl(bool validate = true) const;
    std::unique_ptr<TerminationControl>   readTerminationControl(bool validate = true) const;
    std::unique_ptr<NtcControl0>          readNtcControl0(bool validate = true) const;
    std::unique_ptr<NtcControl1>          readNtcControl1(bool validate = true) const;
    std::unique_ptr<IcoCurrentLimit>      readIcoCurrentLimit(bool validate = true) const;

    // --- Charger control ---
    std::unique_ptr<ChargerControl0> readChargerControl0(bool validate = true) const;
    std::unique_ptr<ChargerControl1> readChargerControl1(bool validate = true) const;
    std::unique_ptr<ChargerControl2> readChargerControl2(bool validate = true) const;
    std::unique_ptr<ChargerControl3> readChargerControl3(bool validate = true) const;
    std::unique_ptr<ChargerControl4> readChargerControl4(bool validate = true) const;
    std::unique_ptr<ChargerControl5> readChargerControl5(bool validate = true) const;

    // --- Recharge / OTG / Timer / MPPT / Temperature ---
    std::unique_ptr<RechargeControl>    readRechargeControl(bool validate = true) const;
    std::unique_ptr<VotgRegulation>     readVotgRegulation(bool validate = true) const;
    std::unique_ptr<IotgRegulation>     readIotgRegulation(bool validate = true) const;
    std::unique_ptr<TimerControl>       readTimerControl(bool validate = true) const;
    std::unique_ptr<MpptControl>        readMpptControl(bool validate = true) const;
    std::unique_ptr<TemperatureControl> readTemperatureControl(bool validate = true) const;

    // --- Charger / Fault masks ---
    std::unique_ptr<ChargerMask0> readChargerMask0(bool validate = true) const;
    std::unique_ptr<ChargerMask1> readChargerMask1(bool validate = true) const;
    std::unique_ptr<ChargerMask2> readChargerMask2(bool validate = true) const;
    std::unique_ptr<ChargerMask3> readChargerMask3(bool validate = true) const;
    std::unique_ptr<FaultMask0>   readFaultMask0(bool validate = true) const;
    std::unique_ptr<FaultMask1>   readFaultMask1(bool validate = true) const;

    // --- D+/D- ADC and DPDM driver ---
    std::unique_ptr<DplusAdc>   readDplusAdc(bool validate = true) const;
    std::unique_ptr<DminusAdc>  readDminusAdc(bool validate = true) const;
    std::unique_ptr<DpdmDriver> readDpdmDriver(bool validate = true) const;
};

}  // namespace BQ25798
