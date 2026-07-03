#pragma once

#include <memory>
#include "TPS25751Register.h"
#include "BQ25798/BQ25798Registers.h"

// Forward declarations — one per implemented register class.
namespace BQ25798 {
class PartInfo;
class ChargerStatus0;
class ChargerStatus1;
class ChargerStatus2;
class ChargerStatus3;
class ChargerStatus4;
class FaultStatus0;
class FaultStatus1;
class ChargerFlag0;
class ChargerFlag1;
class ChargerFlag2;
class ChargerFlag3;
class FaultFlag0;
class FaultFlag1;
class AdcControl;
class AdcFunctionDisable0;
class AdcFunctionDisable1;
class IbusAdc;
class IbatAdc;
class VbusAdc;
class Vac1Adc;
class Vac2Adc;
class VbatAdc;
class VsysAdc;
class TsAdc;
class TdieAdc;
class MinimalSystemVoltage;
class ChargeVoltageLimit;
class ChargeCurrentLimit;
class InputVoltageLimit;
class InputCurrentLimit;
class PrechargeControl;
class TerminationControl;
class NtcControl0;
class NtcControl1;
class IcoCurrentLimit;
class ChargerControl0;
class ChargerControl1;
class ChargerControl2;
class ChargerControl3;
class ChargerControl4;
class ChargerControl5;
class RechargeControl;
class VotgRegulation;
class IotgRegulation;
class TimerControl;
class MpptControl;
class TemperatureControl;
class ChargerMask0;
class ChargerMask1;
class ChargerMask2;
class ChargerMask3;
class FaultMask0;
class FaultMask1;
class DplusAdc;
class DminusAdc;
class DpdmDriver;
}

namespace BQ25798 {

/**
 * @brief Abstract factory interface for creating BQ25798 register objects
 *
 * Registers are identified by their hardware address (BQ25798::Registers::Address),
 * which is the single source of truth for register identity. Addresses without a
 * decoder class yield nullptr from createRegister().
 *
 * Mirrors TPS25751RegisterFactory exactly, adapted for the BQ25798 namespace and
 * register set.
 */
class RegisterFactory
{
public:
    virtual ~RegisterFactory() = default;

    /**
     * @brief Create an empty (zero-initialised) register object by address
     * @param addr Register address
     * @return Unique pointer to created register (nullptr if address unsupported)
     */
    virtual std::unique_ptr<TPS25751Register>
    createRegister(Registers::Address addr) = 0;

    /**
     * @brief Create a register object pre-loaded with raw data
     * @param addr   Register address
     * @param data   Raw data bytes
     * @param length Number of bytes in @p data
     * @return Unique pointer to created register (nullptr on failure)
     */
    virtual std::unique_ptr<TPS25751Register>
    createRegister(Registers::Address addr, const uint8_t* data, size_t length) = 0;

    /**
     * @brief Create an empty register object from RegisterInfo
     * @param regInfo Address + size info for the register
     * @return Unique pointer to created register (nullptr if address unsupported)
     */
    virtual std::unique_ptr<TPS25751Register>
    createRegister(const Registers::RegisterInfo& regInfo) = 0;
};

/**
 * @brief Concrete factory for creating BQ25798 register objects
 *
 * Switch shape mirrors TPS25751RegisterFactoryImpl. All 42 implemented register
 * classes are wired in via inline std::make_unique<> calls in each switch case.
 */
class RegisterFactoryImpl : public RegisterFactory
{
public:
    std::unique_ptr<TPS25751Register>
    createRegister(Registers::Address addr) override;

    std::unique_ptr<TPS25751Register>
    createRegister(Registers::Address addr, const uint8_t* data, size_t length) override;

    std::unique_ptr<TPS25751Register>
    createRegister(const Registers::RegisterInfo& regInfo) override;
};

/**
 * @brief Singleton factory instance for convenient access
 *
 * Mirrors TPS25751Factory. Swap the implementation via setFactory() in tests.
 */
class Factory
{
public:
    /**
     * @brief Get (or lazily create) the singleton factory instance
     * @return Reference to the active RegisterFactory implementation
     */
    static RegisterFactory& getInstance();

    /**
     * @brief Replace the singleton factory (e.g. with a test double)
     * @param factory New factory instance (ownership transferred)
     */
    static void setFactory(std::unique_ptr<RegisterFactory> factory);

private:
    static std::unique_ptr<RegisterFactory> instance_;
};

}  // namespace BQ25798
