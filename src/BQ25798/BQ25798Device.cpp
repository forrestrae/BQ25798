#include "BQ25798/BQ25798Device.h"

namespace BQ25798 {

// ---------------------------------------------------------------------------
// Convenience setters
// ---------------------------------------------------------------------------

bool Device::enableCharging(bool on) const
{
    return updateRegister<ChargerControl0>(
        [on](ChargerControl0& r) { r.setEnChg(on); });
}

bool Device::enableHiz(bool on) const
{
    return updateRegister<ChargerControl0>(
        [on](ChargerControl0& r) { r.setEnHiz(on); });
}

bool Device::enableADC(bool on) const
{
    return updateRegister<AdcControl>(
        [on](AdcControl& r) { r.setAdcEnabled(on); });
}

bool Device::kickWatchdog() const
{
    return updateRegister<ChargerControl1>(
        [](ChargerControl1& r) { r.setWdRst(true); });
}

bool Device::setWatchdog(ChargerControl1::Watchdog v) const
{
    return updateRegister<ChargerControl1>(
        [v](ChargerControl1& r) { r.setWatchdog(v); });
}

bool Device::setChargeCurrentLimit(uint16_t milliamps) const
{
    return updateRegister<ChargeCurrentLimit>(
        [milliamps](ChargeCurrentLimit& r) { r.setMilliamps(milliamps); });
}

bool Device::setChargeVoltageLimit(uint16_t millivolts) const
{
    return updateRegister<ChargeVoltageLimit>(
        [millivolts](ChargeVoltageLimit& r) { r.setMillivolts(millivolts); });
}

bool Device::setInputCurrentLimit(uint16_t milliamps) const
{
    return updateRegister<InputCurrentLimit>(
        [milliamps](InputCurrentLimit& r) { r.setMilliamps(milliamps); });
}

bool Device::setInputVoltageLimit(uint16_t millivolts) const
{
    return updateRegister<InputVoltageLimit>(
        [millivolts](InputVoltageLimit& r) { r.setMillivolts(millivolts); });
}

bool Device::enableOTG(bool on) const
{
    return updateRegister<ChargerControl3>(
        [on](ChargerControl3& r) { r.setEnOtg(on); });
}

// ---------------------------------------------------------------------------
// readPartInfo
// ---------------------------------------------------------------------------

std::unique_ptr<PartInfo> Device::readPartInfo(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::PART_INFORMATION);
    const size_t  regSize = Registers::PART_INFORMATION.size;
    uint8_t buf[Registers::PART_INFORMATION.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<PartInfo>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

// ---------------------------------------------------------------------------
// Status registers
// ---------------------------------------------------------------------------

std::unique_ptr<ChargerStatus0> Device::readChargerStatus0(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_STATUS_0);
    const size_t  regSize = Registers::CHARGER_STATUS_0.size;
    uint8_t buf[Registers::CHARGER_STATUS_0.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerStatus0>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerStatus1> Device::readChargerStatus1(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_STATUS_1);
    const size_t  regSize = Registers::CHARGER_STATUS_1.size;
    uint8_t buf[Registers::CHARGER_STATUS_1.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerStatus1>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerStatus2> Device::readChargerStatus2(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_STATUS_2);
    const size_t  regSize = Registers::CHARGER_STATUS_2.size;
    uint8_t buf[Registers::CHARGER_STATUS_2.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerStatus2>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerStatus3> Device::readChargerStatus3(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_STATUS_3);
    const size_t  regSize = Registers::CHARGER_STATUS_3.size;
    uint8_t buf[Registers::CHARGER_STATUS_3.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerStatus3>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerStatus4> Device::readChargerStatus4(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_STATUS_4);
    const size_t  regSize = Registers::CHARGER_STATUS_4.size;
    uint8_t buf[Registers::CHARGER_STATUS_4.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerStatus4>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<FaultStatus0> Device::readFaultStatus0(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::FAULT_STATUS_0);
    const size_t  regSize = Registers::FAULT_STATUS_0.size;
    uint8_t buf[Registers::FAULT_STATUS_0.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<FaultStatus0>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<FaultStatus1> Device::readFaultStatus1(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::FAULT_STATUS_1);
    const size_t  regSize = Registers::FAULT_STATUS_1.size;
    uint8_t buf[Registers::FAULT_STATUS_1.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<FaultStatus1>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

// ---------------------------------------------------------------------------
// Flag registers
// ---------------------------------------------------------------------------

std::unique_ptr<ChargerFlag0> Device::readChargerFlag0(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_FLAG_0);
    const size_t  regSize = Registers::CHARGER_FLAG_0.size;
    uint8_t buf[Registers::CHARGER_FLAG_0.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerFlag0>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerFlag1> Device::readChargerFlag1(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_FLAG_1);
    const size_t  regSize = Registers::CHARGER_FLAG_1.size;
    uint8_t buf[Registers::CHARGER_FLAG_1.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerFlag1>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerFlag2> Device::readChargerFlag2(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_FLAG_2);
    const size_t  regSize = Registers::CHARGER_FLAG_2.size;
    uint8_t buf[Registers::CHARGER_FLAG_2.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerFlag2>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerFlag3> Device::readChargerFlag3(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_FLAG_3);
    const size_t  regSize = Registers::CHARGER_FLAG_3.size;
    uint8_t buf[Registers::CHARGER_FLAG_3.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerFlag3>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<FaultFlag0> Device::readFaultFlag0(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::FAULT_FLAG_0);
    const size_t  regSize = Registers::FAULT_FLAG_0.size;
    uint8_t buf[Registers::FAULT_FLAG_0.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<FaultFlag0>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<FaultFlag1> Device::readFaultFlag1(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::FAULT_FLAG_1);
    const size_t  regSize = Registers::FAULT_FLAG_1.size;
    uint8_t buf[Registers::FAULT_FLAG_1.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<FaultFlag1>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

// ---------------------------------------------------------------------------
// ADC registers
// ---------------------------------------------------------------------------

std::unique_ptr<AdcControl> Device::readAdcControl(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::ADC_CONTROL);
    const size_t  regSize = Registers::ADC_CONTROL.size;
    uint8_t buf[Registers::ADC_CONTROL.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<AdcControl>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<AdcFunctionDisable0> Device::readAdcFunctionDisable0(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::ADC_FUNCTION_DISABLE_0);
    const size_t  regSize = Registers::ADC_FUNCTION_DISABLE_0.size;
    uint8_t buf[Registers::ADC_FUNCTION_DISABLE_0.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<AdcFunctionDisable0>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<AdcFunctionDisable1> Device::readAdcFunctionDisable1(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::ADC_FUNCTION_DISABLE_1);
    const size_t  regSize = Registers::ADC_FUNCTION_DISABLE_1.size;
    uint8_t buf[Registers::ADC_FUNCTION_DISABLE_1.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<AdcFunctionDisable1>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<IbusAdc> Device::readIbusAdc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::IBUS_ADC);
    const size_t  regSize = Registers::IBUS_ADC.size;
    uint8_t buf[Registers::IBUS_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<IbusAdc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<IbatAdc> Device::readIbatAdc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::IBAT_ADC);
    const size_t  regSize = Registers::IBAT_ADC.size;
    uint8_t buf[Registers::IBAT_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<IbatAdc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<VbusAdc> Device::readVbusAdc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::VBUS_ADC);
    const size_t  regSize = Registers::VBUS_ADC.size;
    uint8_t buf[Registers::VBUS_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<VbusAdc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<Vac1Adc> Device::readVac1Adc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::VAC1_ADC);
    const size_t  regSize = Registers::VAC1_ADC.size;
    uint8_t buf[Registers::VAC1_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<Vac1Adc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<Vac2Adc> Device::readVac2Adc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::VAC2_ADC);
    const size_t  regSize = Registers::VAC2_ADC.size;
    uint8_t buf[Registers::VAC2_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<Vac2Adc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<VbatAdc> Device::readVbatAdc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::VBAT_ADC);
    const size_t  regSize = Registers::VBAT_ADC.size;
    uint8_t buf[Registers::VBAT_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<VbatAdc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<VsysAdc> Device::readVsysAdc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::VSYS_ADC);
    const size_t  regSize = Registers::VSYS_ADC.size;
    uint8_t buf[Registers::VSYS_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<VsysAdc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<TsAdc> Device::readTsAdc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::TS_ADC);
    const size_t  regSize = Registers::TS_ADC.size;
    uint8_t buf[Registers::TS_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<TsAdc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<TdieAdc> Device::readTdieAdc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::TDIE_ADC);
    const size_t  regSize = Registers::TDIE_ADC.size;
    uint8_t buf[Registers::TDIE_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<TdieAdc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

// ---------------------------------------------------------------------------
// Charge limits / thresholds
// ---------------------------------------------------------------------------

std::unique_ptr<MinimalSystemVoltage> Device::readMinimalSystemVoltage(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::MINIMAL_SYSTEM_VOLTAGE);
    const size_t  regSize = Registers::MINIMAL_SYSTEM_VOLTAGE.size;
    uint8_t buf[Registers::MINIMAL_SYSTEM_VOLTAGE.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<MinimalSystemVoltage>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargeVoltageLimit> Device::readChargeVoltageLimit(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGE_VOLTAGE_LIMIT);
    const size_t  regSize = Registers::CHARGE_VOLTAGE_LIMIT.size;
    uint8_t buf[Registers::CHARGE_VOLTAGE_LIMIT.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargeVoltageLimit>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargeCurrentLimit> Device::readChargeCurrentLimit(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGE_CURRENT_LIMIT);
    const size_t  regSize = Registers::CHARGE_CURRENT_LIMIT.size;
    uint8_t buf[Registers::CHARGE_CURRENT_LIMIT.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargeCurrentLimit>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<InputVoltageLimit> Device::readInputVoltageLimit(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::INPUT_VOLTAGE_LIMIT);
    const size_t  regSize = Registers::INPUT_VOLTAGE_LIMIT.size;
    uint8_t buf[Registers::INPUT_VOLTAGE_LIMIT.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<InputVoltageLimit>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<InputCurrentLimit> Device::readInputCurrentLimit(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::INPUT_CURRENT_LIMIT);
    const size_t  regSize = Registers::INPUT_CURRENT_LIMIT.size;
    uint8_t buf[Registers::INPUT_CURRENT_LIMIT.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<InputCurrentLimit>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<PrechargeControl> Device::readPrechargeControl(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::PRECHARGE_CONTROL);
    const size_t  regSize = Registers::PRECHARGE_CONTROL.size;
    uint8_t buf[Registers::PRECHARGE_CONTROL.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<PrechargeControl>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<TerminationControl> Device::readTerminationControl(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::TERMINATION_CONTROL);
    const size_t  regSize = Registers::TERMINATION_CONTROL.size;
    uint8_t buf[Registers::TERMINATION_CONTROL.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<TerminationControl>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<NtcControl0> Device::readNtcControl0(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::NTC_CONTROL_0);
    const size_t  regSize = Registers::NTC_CONTROL_0.size;
    uint8_t buf[Registers::NTC_CONTROL_0.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<NtcControl0>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<NtcControl1> Device::readNtcControl1(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::NTC_CONTROL_1);
    const size_t  regSize = Registers::NTC_CONTROL_1.size;
    uint8_t buf[Registers::NTC_CONTROL_1.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<NtcControl1>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<IcoCurrentLimit> Device::readIcoCurrentLimit(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::ICO_CURRENT_LIMIT);
    const size_t  regSize = Registers::ICO_CURRENT_LIMIT.size;
    uint8_t buf[Registers::ICO_CURRENT_LIMIT.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<IcoCurrentLimit>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

// ---------------------------------------------------------------------------
// Charger control registers
// ---------------------------------------------------------------------------

std::unique_ptr<ChargerControl0> Device::readChargerControl0(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_CONTROL_0);
    const size_t  regSize = Registers::CHARGER_CONTROL_0.size;
    uint8_t buf[Registers::CHARGER_CONTROL_0.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerControl0>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerControl1> Device::readChargerControl1(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_CONTROL_1);
    const size_t  regSize = Registers::CHARGER_CONTROL_1.size;
    uint8_t buf[Registers::CHARGER_CONTROL_1.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerControl1>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerControl2> Device::readChargerControl2(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_CONTROL_2);
    const size_t  regSize = Registers::CHARGER_CONTROL_2.size;
    uint8_t buf[Registers::CHARGER_CONTROL_2.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerControl2>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerControl3> Device::readChargerControl3(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_CONTROL_3);
    const size_t  regSize = Registers::CHARGER_CONTROL_3.size;
    uint8_t buf[Registers::CHARGER_CONTROL_3.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerControl3>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerControl4> Device::readChargerControl4(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_CONTROL_4);
    const size_t  regSize = Registers::CHARGER_CONTROL_4.size;
    uint8_t buf[Registers::CHARGER_CONTROL_4.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerControl4>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerControl5> Device::readChargerControl5(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_CONTROL_5);
    const size_t  regSize = Registers::CHARGER_CONTROL_5.size;
    uint8_t buf[Registers::CHARGER_CONTROL_5.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerControl5>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

// ---------------------------------------------------------------------------
// Recharge / OTG / Timer / MPPT / Temperature registers
// ---------------------------------------------------------------------------

std::unique_ptr<RechargeControl> Device::readRechargeControl(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::RECHARGE_CONTROL);
    const size_t  regSize = Registers::RECHARGE_CONTROL.size;
    uint8_t buf[Registers::RECHARGE_CONTROL.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<RechargeControl>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<VotgRegulation> Device::readVotgRegulation(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::VOTG_REGULATION);
    const size_t  regSize = Registers::VOTG_REGULATION.size;
    uint8_t buf[Registers::VOTG_REGULATION.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<VotgRegulation>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<IotgRegulation> Device::readIotgRegulation(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::IOTG_REGULATION);
    const size_t  regSize = Registers::IOTG_REGULATION.size;
    uint8_t buf[Registers::IOTG_REGULATION.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<IotgRegulation>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<TimerControl> Device::readTimerControl(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::TIMER_CONTROL);
    const size_t  regSize = Registers::TIMER_CONTROL.size;
    uint8_t buf[Registers::TIMER_CONTROL.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<TimerControl>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<MpptControl> Device::readMpptControl(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::MPPT_CONTROL);
    const size_t  regSize = Registers::MPPT_CONTROL.size;
    uint8_t buf[Registers::MPPT_CONTROL.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<MpptControl>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<TemperatureControl> Device::readTemperatureControl(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::TEMPERATURE_CONTROL);
    const size_t  regSize = Registers::TEMPERATURE_CONTROL.size;
    uint8_t buf[Registers::TEMPERATURE_CONTROL.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<TemperatureControl>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

// ---------------------------------------------------------------------------
// Charger / Fault mask registers
// ---------------------------------------------------------------------------

std::unique_ptr<ChargerMask0> Device::readChargerMask0(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_MASK_0);
    const size_t  regSize = Registers::CHARGER_MASK_0.size;
    uint8_t buf[Registers::CHARGER_MASK_0.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerMask0>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerMask1> Device::readChargerMask1(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_MASK_1);
    const size_t  regSize = Registers::CHARGER_MASK_1.size;
    uint8_t buf[Registers::CHARGER_MASK_1.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerMask1>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerMask2> Device::readChargerMask2(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_MASK_2);
    const size_t  regSize = Registers::CHARGER_MASK_2.size;
    uint8_t buf[Registers::CHARGER_MASK_2.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerMask2>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<ChargerMask3> Device::readChargerMask3(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::CHARGER_MASK_3);
    const size_t  regSize = Registers::CHARGER_MASK_3.size;
    uint8_t buf[Registers::CHARGER_MASK_3.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<ChargerMask3>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<FaultMask0> Device::readFaultMask0(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::FAULT_MASK_0);
    const size_t  regSize = Registers::FAULT_MASK_0.size;
    uint8_t buf[Registers::FAULT_MASK_0.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<FaultMask0>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<FaultMask1> Device::readFaultMask1(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::FAULT_MASK_1);
    const size_t  regSize = Registers::FAULT_MASK_1.size;
    uint8_t buf[Registers::FAULT_MASK_1.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<FaultMask1>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

// ---------------------------------------------------------------------------
// D+/D- ADC and DPDM driver registers
// ---------------------------------------------------------------------------

std::unique_ptr<DplusAdc> Device::readDplusAdc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::DPLUS_ADC);
    const size_t  regSize = Registers::DPLUS_ADC.size;
    uint8_t buf[Registers::DPLUS_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<DplusAdc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<DminusAdc> Device::readDminusAdc(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::DMINUS_ADC);
    const size_t  regSize = Registers::DMINUS_ADC.size;
    uint8_t buf[Registers::DMINUS_ADC.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<DminusAdc>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

std::unique_ptr<DpdmDriver> Device::readDpdmDriver(bool validate) const
{
    const uint8_t regAddr = static_cast<uint8_t>(Registers::Address::DPDM_DRIVER);
    const size_t  regSize = Registers::DPDM_DRIVER.size;
    uint8_t buf[Registers::DPDM_DRIVER.size];
    if (!readRegister(regAddr, buf, regSize)) {
        return nullptr;
    }
    auto reg = std::make_unique<DpdmDriver>(buf, regSize);
    if (validate && !reg->isSemanticallyValid()) {
        return nullptr;
    }
    return reg;
}

}  // namespace BQ25798
