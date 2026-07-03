#include "BQ25798/BQ25798RegisterFactory.h"
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

// ---------------------------------------------------------------------------
// Static singleton storage
// ---------------------------------------------------------------------------
std::unique_ptr<RegisterFactory> Factory::instance_;

// ---------------------------------------------------------------------------
// createRegister(Address) — empty / zero-initialised objects
// ---------------------------------------------------------------------------

std::unique_ptr<TPS25751Register>
RegisterFactoryImpl::createRegister(Registers::Address addr)
{
    switch (addr) {
        case Registers::Address::PART_INFORMATION:
            return std::make_unique<PartInfo>();
        case Registers::Address::CHARGER_STATUS_0:
            return std::make_unique<ChargerStatus0>();
        case Registers::Address::CHARGER_STATUS_1:
            return std::make_unique<ChargerStatus1>();
        case Registers::Address::CHARGER_STATUS_2:
            return std::make_unique<ChargerStatus2>();
        case Registers::Address::CHARGER_STATUS_3:
            return std::make_unique<ChargerStatus3>();
        case Registers::Address::CHARGER_STATUS_4:
            return std::make_unique<ChargerStatus4>();
        case Registers::Address::FAULT_STATUS_0:
            return std::make_unique<FaultStatus0>();
        case Registers::Address::FAULT_STATUS_1:
            return std::make_unique<FaultStatus1>();
        case Registers::Address::CHARGER_FLAG_0:
            return std::make_unique<ChargerFlag0>();
        case Registers::Address::CHARGER_FLAG_1:
            return std::make_unique<ChargerFlag1>();
        case Registers::Address::CHARGER_FLAG_2:
            return std::make_unique<ChargerFlag2>();
        case Registers::Address::CHARGER_FLAG_3:
            return std::make_unique<ChargerFlag3>();
        case Registers::Address::FAULT_FLAG_0:
            return std::make_unique<FaultFlag0>();
        case Registers::Address::FAULT_FLAG_1:
            return std::make_unique<FaultFlag1>();
        case Registers::Address::ADC_CONTROL:
            return std::make_unique<AdcControl>();
        case Registers::Address::ADC_FUNCTION_DISABLE_0:
            return std::make_unique<AdcFunctionDisable0>();
        case Registers::Address::ADC_FUNCTION_DISABLE_1:
            return std::make_unique<AdcFunctionDisable1>();
        case Registers::Address::IBUS_ADC:
            return std::make_unique<IbusAdc>();
        case Registers::Address::IBAT_ADC:
            return std::make_unique<IbatAdc>();
        case Registers::Address::VBUS_ADC:
            return std::make_unique<VbusAdc>();
        case Registers::Address::VAC1_ADC:
            return std::make_unique<Vac1Adc>();
        case Registers::Address::VAC2_ADC:
            return std::make_unique<Vac2Adc>();
        case Registers::Address::VBAT_ADC:
            return std::make_unique<VbatAdc>();
        case Registers::Address::VSYS_ADC:
            return std::make_unique<VsysAdc>();
        case Registers::Address::TS_ADC:
            return std::make_unique<TsAdc>();
        case Registers::Address::TDIE_ADC:
            return std::make_unique<TdieAdc>();
        case Registers::Address::MINIMAL_SYSTEM_VOLTAGE:
            return std::make_unique<MinimalSystemVoltage>();
        case Registers::Address::CHARGE_VOLTAGE_LIMIT:
            return std::make_unique<ChargeVoltageLimit>();
        case Registers::Address::CHARGE_CURRENT_LIMIT:
            return std::make_unique<ChargeCurrentLimit>();
        case Registers::Address::INPUT_VOLTAGE_LIMIT:
            return std::make_unique<InputVoltageLimit>();
        case Registers::Address::INPUT_CURRENT_LIMIT:
            return std::make_unique<InputCurrentLimit>();
        case Registers::Address::PRECHARGE_CONTROL:
            return std::make_unique<PrechargeControl>();
        case Registers::Address::TERMINATION_CONTROL:
            return std::make_unique<TerminationControl>();
        case Registers::Address::NTC_CONTROL_0:
            return std::make_unique<NtcControl0>();
        case Registers::Address::NTC_CONTROL_1:
            return std::make_unique<NtcControl1>();
        case Registers::Address::ICO_CURRENT_LIMIT:
            return std::make_unique<IcoCurrentLimit>();
        case Registers::Address::CHARGER_CONTROL_0:
            return std::make_unique<ChargerControl0>();
        case Registers::Address::CHARGER_CONTROL_1:
            return std::make_unique<ChargerControl1>();
        case Registers::Address::CHARGER_CONTROL_2:
            return std::make_unique<ChargerControl2>();
        case Registers::Address::CHARGER_CONTROL_3:
            return std::make_unique<ChargerControl3>();
        case Registers::Address::CHARGER_CONTROL_4:
            return std::make_unique<ChargerControl4>();
        case Registers::Address::CHARGER_CONTROL_5:
            return std::make_unique<ChargerControl5>();
        case Registers::Address::RECHARGE_CONTROL:
            return std::make_unique<RechargeControl>();
        case Registers::Address::VOTG_REGULATION:
            return std::make_unique<VotgRegulation>();
        case Registers::Address::IOTG_REGULATION:
            return std::make_unique<IotgRegulation>();
        case Registers::Address::TIMER_CONTROL:
            return std::make_unique<TimerControl>();
        case Registers::Address::MPPT_CONTROL:
            return std::make_unique<MpptControl>();
        case Registers::Address::TEMPERATURE_CONTROL:
            return std::make_unique<TemperatureControl>();
        case Registers::Address::CHARGER_MASK_0:
            return std::make_unique<ChargerMask0>();
        case Registers::Address::CHARGER_MASK_1:
            return std::make_unique<ChargerMask1>();
        case Registers::Address::CHARGER_MASK_2:
            return std::make_unique<ChargerMask2>();
        case Registers::Address::CHARGER_MASK_3:
            return std::make_unique<ChargerMask3>();
        case Registers::Address::FAULT_MASK_0:
            return std::make_unique<FaultMask0>();
        case Registers::Address::FAULT_MASK_1:
            return std::make_unique<FaultMask1>();
        case Registers::Address::DPLUS_ADC:
            return std::make_unique<DplusAdc>();
        case Registers::Address::DMINUS_ADC:
            return std::make_unique<DminusAdc>();
        case Registers::Address::DPDM_DRIVER:
            return std::make_unique<DpdmDriver>();
        default:
            return nullptr;
    }
}

// ---------------------------------------------------------------------------
// createRegister(Address, data, length) — pre-loaded objects
// ---------------------------------------------------------------------------

std::unique_ptr<TPS25751Register>
RegisterFactoryImpl::createRegister(Registers::Address addr,
                                    const uint8_t* data,
                                    size_t length)
{
    if (!data) {
        return nullptr;
    }

    switch (addr) {
        case Registers::Address::PART_INFORMATION:
            return std::make_unique<PartInfo>(data, length);
        case Registers::Address::CHARGER_STATUS_0:
            return std::make_unique<ChargerStatus0>(data, length);
        case Registers::Address::CHARGER_STATUS_1:
            return std::make_unique<ChargerStatus1>(data, length);
        case Registers::Address::CHARGER_STATUS_2:
            return std::make_unique<ChargerStatus2>(data, length);
        case Registers::Address::CHARGER_STATUS_3:
            return std::make_unique<ChargerStatus3>(data, length);
        case Registers::Address::CHARGER_STATUS_4:
            return std::make_unique<ChargerStatus4>(data, length);
        case Registers::Address::FAULT_STATUS_0:
            return std::make_unique<FaultStatus0>(data, length);
        case Registers::Address::FAULT_STATUS_1:
            return std::make_unique<FaultStatus1>(data, length);
        case Registers::Address::CHARGER_FLAG_0:
            return std::make_unique<ChargerFlag0>(data, length);
        case Registers::Address::CHARGER_FLAG_1:
            return std::make_unique<ChargerFlag1>(data, length);
        case Registers::Address::CHARGER_FLAG_2:
            return std::make_unique<ChargerFlag2>(data, length);
        case Registers::Address::CHARGER_FLAG_3:
            return std::make_unique<ChargerFlag3>(data, length);
        case Registers::Address::FAULT_FLAG_0:
            return std::make_unique<FaultFlag0>(data, length);
        case Registers::Address::FAULT_FLAG_1:
            return std::make_unique<FaultFlag1>(data, length);
        case Registers::Address::ADC_CONTROL:
            return std::make_unique<AdcControl>(data, length);
        case Registers::Address::ADC_FUNCTION_DISABLE_0:
            return std::make_unique<AdcFunctionDisable0>(data, length);
        case Registers::Address::ADC_FUNCTION_DISABLE_1:
            return std::make_unique<AdcFunctionDisable1>(data, length);
        case Registers::Address::IBUS_ADC:
            return std::make_unique<IbusAdc>(data, length);
        case Registers::Address::IBAT_ADC:
            return std::make_unique<IbatAdc>(data, length);
        case Registers::Address::VBUS_ADC:
            return std::make_unique<VbusAdc>(data, length);
        case Registers::Address::VAC1_ADC:
            return std::make_unique<Vac1Adc>(data, length);
        case Registers::Address::VAC2_ADC:
            return std::make_unique<Vac2Adc>(data, length);
        case Registers::Address::VBAT_ADC:
            return std::make_unique<VbatAdc>(data, length);
        case Registers::Address::VSYS_ADC:
            return std::make_unique<VsysAdc>(data, length);
        case Registers::Address::TS_ADC:
            return std::make_unique<TsAdc>(data, length);
        case Registers::Address::TDIE_ADC:
            return std::make_unique<TdieAdc>(data, length);
        case Registers::Address::MINIMAL_SYSTEM_VOLTAGE:
            return std::make_unique<MinimalSystemVoltage>(data, length);
        case Registers::Address::CHARGE_VOLTAGE_LIMIT:
            return std::make_unique<ChargeVoltageLimit>(data, length);
        case Registers::Address::CHARGE_CURRENT_LIMIT:
            return std::make_unique<ChargeCurrentLimit>(data, length);
        case Registers::Address::INPUT_VOLTAGE_LIMIT:
            return std::make_unique<InputVoltageLimit>(data, length);
        case Registers::Address::INPUT_CURRENT_LIMIT:
            return std::make_unique<InputCurrentLimit>(data, length);
        case Registers::Address::PRECHARGE_CONTROL:
            return std::make_unique<PrechargeControl>(data, length);
        case Registers::Address::TERMINATION_CONTROL:
            return std::make_unique<TerminationControl>(data, length);
        case Registers::Address::NTC_CONTROL_0:
            return std::make_unique<NtcControl0>(data, length);
        case Registers::Address::NTC_CONTROL_1:
            return std::make_unique<NtcControl1>(data, length);
        case Registers::Address::ICO_CURRENT_LIMIT:
            return std::make_unique<IcoCurrentLimit>(data, length);
        case Registers::Address::CHARGER_CONTROL_0:
            return std::make_unique<ChargerControl0>(data, length);
        case Registers::Address::CHARGER_CONTROL_1:
            return std::make_unique<ChargerControl1>(data, length);
        case Registers::Address::CHARGER_CONTROL_2:
            return std::make_unique<ChargerControl2>(data, length);
        case Registers::Address::CHARGER_CONTROL_3:
            return std::make_unique<ChargerControl3>(data, length);
        case Registers::Address::CHARGER_CONTROL_4:
            return std::make_unique<ChargerControl4>(data, length);
        case Registers::Address::CHARGER_CONTROL_5:
            return std::make_unique<ChargerControl5>(data, length);
        case Registers::Address::RECHARGE_CONTROL:
            return std::make_unique<RechargeControl>(data, length);
        case Registers::Address::VOTG_REGULATION:
            return std::make_unique<VotgRegulation>(data, length);
        case Registers::Address::IOTG_REGULATION:
            return std::make_unique<IotgRegulation>(data, length);
        case Registers::Address::TIMER_CONTROL:
            return std::make_unique<TimerControl>(data, length);
        case Registers::Address::MPPT_CONTROL:
            return std::make_unique<MpptControl>(data, length);
        case Registers::Address::TEMPERATURE_CONTROL:
            return std::make_unique<TemperatureControl>(data, length);
        case Registers::Address::CHARGER_MASK_0:
            return std::make_unique<ChargerMask0>(data, length);
        case Registers::Address::CHARGER_MASK_1:
            return std::make_unique<ChargerMask1>(data, length);
        case Registers::Address::CHARGER_MASK_2:
            return std::make_unique<ChargerMask2>(data, length);
        case Registers::Address::CHARGER_MASK_3:
            return std::make_unique<ChargerMask3>(data, length);
        case Registers::Address::FAULT_MASK_0:
            return std::make_unique<FaultMask0>(data, length);
        case Registers::Address::FAULT_MASK_1:
            return std::make_unique<FaultMask1>(data, length);
        case Registers::Address::DPLUS_ADC:
            return std::make_unique<DplusAdc>(data, length);
        case Registers::Address::DMINUS_ADC:
            return std::make_unique<DminusAdc>(data, length);
        case Registers::Address::DPDM_DRIVER:
            return std::make_unique<DpdmDriver>(data, length);
        default:
            return nullptr;
    }
}

// ---------------------------------------------------------------------------
// createRegister(RegisterInfo) — size-from-info, empty objects
// ---------------------------------------------------------------------------

std::unique_ptr<TPS25751Register>
RegisterFactoryImpl::createRegister(const Registers::RegisterInfo& regInfo)
{
    switch (regInfo.address) {
        case Registers::Address::PART_INFORMATION:
            return std::make_unique<PartInfo>(regInfo);
        case Registers::Address::CHARGER_STATUS_0:
            return std::make_unique<ChargerStatus0>(regInfo);
        case Registers::Address::CHARGER_STATUS_1:
            return std::make_unique<ChargerStatus1>(regInfo);
        case Registers::Address::CHARGER_STATUS_2:
            return std::make_unique<ChargerStatus2>(regInfo);
        case Registers::Address::CHARGER_STATUS_3:
            return std::make_unique<ChargerStatus3>(regInfo);
        case Registers::Address::CHARGER_STATUS_4:
            return std::make_unique<ChargerStatus4>(regInfo);
        case Registers::Address::FAULT_STATUS_0:
            return std::make_unique<FaultStatus0>(regInfo);
        case Registers::Address::FAULT_STATUS_1:
            return std::make_unique<FaultStatus1>(regInfo);
        case Registers::Address::CHARGER_FLAG_0:
            return std::make_unique<ChargerFlag0>(regInfo);
        case Registers::Address::CHARGER_FLAG_1:
            return std::make_unique<ChargerFlag1>(regInfo);
        case Registers::Address::CHARGER_FLAG_2:
            return std::make_unique<ChargerFlag2>(regInfo);
        case Registers::Address::CHARGER_FLAG_3:
            return std::make_unique<ChargerFlag3>(regInfo);
        case Registers::Address::FAULT_FLAG_0:
            return std::make_unique<FaultFlag0>(regInfo);
        case Registers::Address::FAULT_FLAG_1:
            return std::make_unique<FaultFlag1>(regInfo);
        case Registers::Address::ADC_CONTROL:
            return std::make_unique<AdcControl>(regInfo);
        case Registers::Address::ADC_FUNCTION_DISABLE_0:
            return std::make_unique<AdcFunctionDisable0>(regInfo);
        case Registers::Address::ADC_FUNCTION_DISABLE_1:
            return std::make_unique<AdcFunctionDisable1>(regInfo);
        case Registers::Address::IBUS_ADC:
            return std::make_unique<IbusAdc>(regInfo);
        case Registers::Address::IBAT_ADC:
            return std::make_unique<IbatAdc>(regInfo);
        case Registers::Address::VBUS_ADC:
            return std::make_unique<VbusAdc>(regInfo);
        case Registers::Address::VAC1_ADC:
            return std::make_unique<Vac1Adc>(regInfo);
        case Registers::Address::VAC2_ADC:
            return std::make_unique<Vac2Adc>(regInfo);
        case Registers::Address::VBAT_ADC:
            return std::make_unique<VbatAdc>(regInfo);
        case Registers::Address::VSYS_ADC:
            return std::make_unique<VsysAdc>(regInfo);
        case Registers::Address::TS_ADC:
            return std::make_unique<TsAdc>(regInfo);
        case Registers::Address::TDIE_ADC:
            return std::make_unique<TdieAdc>(regInfo);
        case Registers::Address::MINIMAL_SYSTEM_VOLTAGE:
            return std::make_unique<MinimalSystemVoltage>(regInfo);
        case Registers::Address::CHARGE_VOLTAGE_LIMIT:
            return std::make_unique<ChargeVoltageLimit>(regInfo);
        case Registers::Address::CHARGE_CURRENT_LIMIT:
            return std::make_unique<ChargeCurrentLimit>(regInfo);
        case Registers::Address::INPUT_VOLTAGE_LIMIT:
            return std::make_unique<InputVoltageLimit>(regInfo);
        case Registers::Address::INPUT_CURRENT_LIMIT:
            return std::make_unique<InputCurrentLimit>(regInfo);
        case Registers::Address::PRECHARGE_CONTROL:
            return std::make_unique<PrechargeControl>(regInfo);
        case Registers::Address::TERMINATION_CONTROL:
            return std::make_unique<TerminationControl>(regInfo);
        case Registers::Address::NTC_CONTROL_0:
            return std::make_unique<NtcControl0>(regInfo);
        case Registers::Address::NTC_CONTROL_1:
            return std::make_unique<NtcControl1>(regInfo);
        case Registers::Address::ICO_CURRENT_LIMIT:
            return std::make_unique<IcoCurrentLimit>(regInfo);
        case Registers::Address::CHARGER_CONTROL_0:
            return std::make_unique<ChargerControl0>(regInfo);
        case Registers::Address::CHARGER_CONTROL_1:
            return std::make_unique<ChargerControl1>(regInfo);
        case Registers::Address::CHARGER_CONTROL_2:
            return std::make_unique<ChargerControl2>(regInfo);
        case Registers::Address::CHARGER_CONTROL_3:
            return std::make_unique<ChargerControl3>(regInfo);
        case Registers::Address::CHARGER_CONTROL_4:
            return std::make_unique<ChargerControl4>(regInfo);
        case Registers::Address::CHARGER_CONTROL_5:
            return std::make_unique<ChargerControl5>(regInfo);
        case Registers::Address::RECHARGE_CONTROL:
            return std::make_unique<RechargeControl>(regInfo);
        case Registers::Address::VOTG_REGULATION:
            return std::make_unique<VotgRegulation>(regInfo);
        case Registers::Address::IOTG_REGULATION:
            return std::make_unique<IotgRegulation>(regInfo);
        case Registers::Address::TIMER_CONTROL:
            return std::make_unique<TimerControl>(regInfo);
        case Registers::Address::MPPT_CONTROL:
            return std::make_unique<MpptControl>(regInfo);
        case Registers::Address::TEMPERATURE_CONTROL:
            return std::make_unique<TemperatureControl>(regInfo);
        case Registers::Address::CHARGER_MASK_0:
            return std::make_unique<ChargerMask0>(regInfo);
        case Registers::Address::CHARGER_MASK_1:
            return std::make_unique<ChargerMask1>(regInfo);
        case Registers::Address::CHARGER_MASK_2:
            return std::make_unique<ChargerMask2>(regInfo);
        case Registers::Address::CHARGER_MASK_3:
            return std::make_unique<ChargerMask3>(regInfo);
        case Registers::Address::FAULT_MASK_0:
            return std::make_unique<FaultMask0>(regInfo);
        case Registers::Address::FAULT_MASK_1:
            return std::make_unique<FaultMask1>(regInfo);
        case Registers::Address::DPLUS_ADC:
            return std::make_unique<DplusAdc>(regInfo);
        case Registers::Address::DMINUS_ADC:
            return std::make_unique<DminusAdc>(regInfo);
        case Registers::Address::DPDM_DRIVER:
            return std::make_unique<DpdmDriver>(regInfo);
        default:
            return nullptr;
    }
}

// ---------------------------------------------------------------------------
// Factory singleton
// ---------------------------------------------------------------------------

RegisterFactory& Factory::getInstance()
{
    if (!instance_) {
        instance_ = std::make_unique<RegisterFactoryImpl>();
    }
    return *instance_;
}

void Factory::setFactory(std::unique_ptr<RegisterFactory> factory)
{
    instance_ = std::move(factory);
}

}  // namespace BQ25798
