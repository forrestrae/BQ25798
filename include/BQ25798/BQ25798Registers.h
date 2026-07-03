#pragma once

#include <cstdint>

// ---------------------------------------------------------------------------
// BQ25798 Register Map
//
// All 57 registers for the Texas Instruments BQ25798 buck-boost battery charger,
// as defined in the BQ25798 Technical Reference Manual.
//
// Sizes:
//   1 byte  — 8-bit registers
//   2 bytes — 16-bit registers: CHARGE_VOLTAGE_LIMIT (0x01), CHARGE_CURRENT_LIMIT
//             (0x03), INPUT_CURRENT_LIMIT (0x06), VOTG_REGULATION (0x0B),
//             ICO_CURRENT_LIMIT (0x19), and all ADC result registers
//             (0x31, 0x33, 0x35, 0x37, 0x39, 0x3B, 0x3D, 0x3F, 0x41, 0x43, 0x45)
//
// Endianness note: 16-bit registers are big-endian on the wire (byte[0] = MSB).
// Single-byte registers are unaffected.
//
// Device I2C address: 0x6B (7-bit; do NOT include an R/W bit — the TPS25751
// I2Cr/I2Cw DATA payload expects a 7-bit target address with bit 7 = 0).
// ---------------------------------------------------------------------------

namespace BQ25798 {

/// @brief Default 7-bit I2C address of the BQ25798
constexpr uint8_t kDefaultI2CAddress = 0x6B;

namespace Registers {

/**
 * @brief Strongly typed enum for BQ25798 register addresses
 *
 * This is the single source of truth for register identity throughout the
 * BQ25798 driver; the factory dispatches register-object creation directly on it.
 */
enum class Address : uint8_t {
    MINIMAL_SYSTEM_VOLTAGE    = 0x00,
    CHARGE_VOLTAGE_LIMIT      = 0x01,  // 16-bit
    CHARGE_CURRENT_LIMIT      = 0x03,  // 16-bit
    INPUT_VOLTAGE_LIMIT       = 0x05,
    INPUT_CURRENT_LIMIT       = 0x06,  // 16-bit
    PRECHARGE_CONTROL         = 0x08,
    TERMINATION_CONTROL       = 0x09,
    RECHARGE_CONTROL          = 0x0A,
    VOTG_REGULATION           = 0x0B,  // 16-bit
    IOTG_REGULATION           = 0x0D,
    TIMER_CONTROL             = 0x0E,
    CHARGER_CONTROL_0         = 0x0F,
    CHARGER_CONTROL_1         = 0x10,
    CHARGER_CONTROL_2         = 0x11,
    CHARGER_CONTROL_3         = 0x12,
    CHARGER_CONTROL_4         = 0x13,
    CHARGER_CONTROL_5         = 0x14,
    MPPT_CONTROL              = 0x15,
    TEMPERATURE_CONTROL       = 0x16,
    NTC_CONTROL_0             = 0x17,
    NTC_CONTROL_1             = 0x18,
    ICO_CURRENT_LIMIT         = 0x19,  // 16-bit
    CHARGER_STATUS_0          = 0x1B,
    CHARGER_STATUS_1          = 0x1C,
    CHARGER_STATUS_2          = 0x1D,
    CHARGER_STATUS_3          = 0x1E,
    CHARGER_STATUS_4          = 0x1F,
    FAULT_STATUS_0            = 0x20,
    FAULT_STATUS_1            = 0x21,
    CHARGER_FLAG_0            = 0x22,
    CHARGER_FLAG_1            = 0x23,
    CHARGER_FLAG_2            = 0x24,
    CHARGER_FLAG_3            = 0x25,
    FAULT_FLAG_0              = 0x26,
    FAULT_FLAG_1              = 0x27,
    CHARGER_MASK_0            = 0x28,
    CHARGER_MASK_1            = 0x29,
    CHARGER_MASK_2            = 0x2A,
    CHARGER_MASK_3            = 0x2B,
    FAULT_MASK_0              = 0x2C,
    FAULT_MASK_1              = 0x2D,
    ADC_CONTROL               = 0x2E,
    ADC_FUNCTION_DISABLE_0    = 0x2F,
    ADC_FUNCTION_DISABLE_1    = 0x30,
    IBUS_ADC                  = 0x31,  // 16-bit
    IBAT_ADC                  = 0x33,  // 16-bit
    VBUS_ADC                  = 0x35,  // 16-bit
    VAC1_ADC                  = 0x37,  // 16-bit
    VAC2_ADC                  = 0x39,  // 16-bit
    VBAT_ADC                  = 0x3B,  // 16-bit
    VSYS_ADC                  = 0x3D,  // 16-bit
    TS_ADC                    = 0x3F,  // 16-bit
    TDIE_ADC                  = 0x41,  // 16-bit
    DPLUS_ADC                 = 0x43,  // 16-bit
    DMINUS_ADC                = 0x45,  // 16-bit
    DPDM_DRIVER               = 0x47,
    PART_INFORMATION          = 0x48,
};

/**
 * @brief Register information structure — address + byte size
 *
 * Kept separate from TPS25751Registers::RegisterInfo so the two device
 * namespaces remain fully independent.
 */
struct RegisterInfo {
    Address address;
    uint8_t size;  ///< Byte width: 1 for 8-bit registers, 2 for 16-bit registers

    constexpr RegisterInfo(Address addr, uint8_t sz) : address(addr), size(sz) {}

    /// Implicit conversion to the raw address byte for use as a register offset
    constexpr operator uint8_t() const {
        return static_cast<uint8_t>(address);
    }
};

// -------------------------------------------------------------------------
// Type-safe register constants with compile-time address/size pairing
// 16-bit registers: CHARGE_VOLTAGE_LIMIT, CHARGE_CURRENT_LIMIT,
//   INPUT_CURRENT_LIMIT, VOTG_REGULATION, ICO_CURRENT_LIMIT,
//   and all ADC result registers (0x31–0x45).
// All others: 1 byte.
// -------------------------------------------------------------------------

constexpr RegisterInfo MINIMAL_SYSTEM_VOLTAGE  { Address::MINIMAL_SYSTEM_VOLTAGE,  1 };
constexpr RegisterInfo CHARGE_VOLTAGE_LIMIT    { Address::CHARGE_VOLTAGE_LIMIT,    2 };
constexpr RegisterInfo CHARGE_CURRENT_LIMIT    { Address::CHARGE_CURRENT_LIMIT,    2 };
constexpr RegisterInfo INPUT_VOLTAGE_LIMIT     { Address::INPUT_VOLTAGE_LIMIT,     1 };
constexpr RegisterInfo INPUT_CURRENT_LIMIT     { Address::INPUT_CURRENT_LIMIT,     2 };
constexpr RegisterInfo PRECHARGE_CONTROL       { Address::PRECHARGE_CONTROL,       1 };
constexpr RegisterInfo TERMINATION_CONTROL     { Address::TERMINATION_CONTROL,     1 };
constexpr RegisterInfo RECHARGE_CONTROL        { Address::RECHARGE_CONTROL,        1 };
constexpr RegisterInfo VOTG_REGULATION         { Address::VOTG_REGULATION,         2 };
constexpr RegisterInfo IOTG_REGULATION         { Address::IOTG_REGULATION,         1 };
constexpr RegisterInfo TIMER_CONTROL           { Address::TIMER_CONTROL,           1 };
constexpr RegisterInfo CHARGER_CONTROL_0       { Address::CHARGER_CONTROL_0,       1 };
constexpr RegisterInfo CHARGER_CONTROL_1       { Address::CHARGER_CONTROL_1,       1 };
constexpr RegisterInfo CHARGER_CONTROL_2       { Address::CHARGER_CONTROL_2,       1 };
constexpr RegisterInfo CHARGER_CONTROL_3       { Address::CHARGER_CONTROL_3,       1 };
constexpr RegisterInfo CHARGER_CONTROL_4       { Address::CHARGER_CONTROL_4,       1 };
constexpr RegisterInfo CHARGER_CONTROL_5       { Address::CHARGER_CONTROL_5,       1 };
constexpr RegisterInfo MPPT_CONTROL            { Address::MPPT_CONTROL,            1 };
constexpr RegisterInfo TEMPERATURE_CONTROL     { Address::TEMPERATURE_CONTROL,     1 };
constexpr RegisterInfo NTC_CONTROL_0           { Address::NTC_CONTROL_0,           1 };
constexpr RegisterInfo NTC_CONTROL_1           { Address::NTC_CONTROL_1,           1 };
constexpr RegisterInfo ICO_CURRENT_LIMIT       { Address::ICO_CURRENT_LIMIT,       2 };
constexpr RegisterInfo CHARGER_STATUS_0        { Address::CHARGER_STATUS_0,        1 };
constexpr RegisterInfo CHARGER_STATUS_1        { Address::CHARGER_STATUS_1,        1 };
constexpr RegisterInfo CHARGER_STATUS_2        { Address::CHARGER_STATUS_2,        1 };
constexpr RegisterInfo CHARGER_STATUS_3        { Address::CHARGER_STATUS_3,        1 };
constexpr RegisterInfo CHARGER_STATUS_4        { Address::CHARGER_STATUS_4,        1 };
constexpr RegisterInfo FAULT_STATUS_0          { Address::FAULT_STATUS_0,          1 };
constexpr RegisterInfo FAULT_STATUS_1          { Address::FAULT_STATUS_1,          1 };
constexpr RegisterInfo CHARGER_FLAG_0          { Address::CHARGER_FLAG_0,          1 };
constexpr RegisterInfo CHARGER_FLAG_1          { Address::CHARGER_FLAG_1,          1 };
constexpr RegisterInfo CHARGER_FLAG_2          { Address::CHARGER_FLAG_2,          1 };
constexpr RegisterInfo CHARGER_FLAG_3          { Address::CHARGER_FLAG_3,          1 };
constexpr RegisterInfo FAULT_FLAG_0            { Address::FAULT_FLAG_0,            1 };
constexpr RegisterInfo FAULT_FLAG_1            { Address::FAULT_FLAG_1,            1 };
constexpr RegisterInfo CHARGER_MASK_0          { Address::CHARGER_MASK_0,          1 };
constexpr RegisterInfo CHARGER_MASK_1          { Address::CHARGER_MASK_1,          1 };
constexpr RegisterInfo CHARGER_MASK_2          { Address::CHARGER_MASK_2,          1 };
constexpr RegisterInfo CHARGER_MASK_3          { Address::CHARGER_MASK_3,          1 };
constexpr RegisterInfo FAULT_MASK_0            { Address::FAULT_MASK_0,            1 };
constexpr RegisterInfo FAULT_MASK_1            { Address::FAULT_MASK_1,            1 };
constexpr RegisterInfo ADC_CONTROL             { Address::ADC_CONTROL,             1 };
constexpr RegisterInfo ADC_FUNCTION_DISABLE_0  { Address::ADC_FUNCTION_DISABLE_0,  1 };
constexpr RegisterInfo ADC_FUNCTION_DISABLE_1  { Address::ADC_FUNCTION_DISABLE_1,  1 };
constexpr RegisterInfo IBUS_ADC                { Address::IBUS_ADC,                2 };
constexpr RegisterInfo IBAT_ADC                { Address::IBAT_ADC,                2 };
constexpr RegisterInfo VBUS_ADC                { Address::VBUS_ADC,                2 };
constexpr RegisterInfo VAC1_ADC                { Address::VAC1_ADC,                2 };
constexpr RegisterInfo VAC2_ADC                { Address::VAC2_ADC,                2 };
constexpr RegisterInfo VBAT_ADC                { Address::VBAT_ADC,                2 };
constexpr RegisterInfo VSYS_ADC                { Address::VSYS_ADC,                2 };
constexpr RegisterInfo TS_ADC                  { Address::TS_ADC,                  2 };
constexpr RegisterInfo TDIE_ADC                { Address::TDIE_ADC,                2 };
constexpr RegisterInfo DPLUS_ADC               { Address::DPLUS_ADC,               2 };
constexpr RegisterInfo DMINUS_ADC              { Address::DMINUS_ADC,              2 };
constexpr RegisterInfo DPDM_DRIVER             { Address::DPDM_DRIVER,             1 };
constexpr RegisterInfo PART_INFORMATION        { Address::PART_INFORMATION,        1 };

/**
 * @brief Get register size in bytes for a given address
 * @param addr Register address
 * @return Size in bytes, or 0 if unknown
 */
constexpr uint8_t getRegisterSize(Address addr) {
    switch (addr) {
        case Address::MINIMAL_SYSTEM_VOLTAGE:  return MINIMAL_SYSTEM_VOLTAGE.size;
        case Address::CHARGE_VOLTAGE_LIMIT:    return CHARGE_VOLTAGE_LIMIT.size;
        case Address::CHARGE_CURRENT_LIMIT:    return CHARGE_CURRENT_LIMIT.size;
        case Address::INPUT_VOLTAGE_LIMIT:     return INPUT_VOLTAGE_LIMIT.size;
        case Address::INPUT_CURRENT_LIMIT:     return INPUT_CURRENT_LIMIT.size;
        case Address::PRECHARGE_CONTROL:       return PRECHARGE_CONTROL.size;
        case Address::TERMINATION_CONTROL:     return TERMINATION_CONTROL.size;
        case Address::RECHARGE_CONTROL:        return RECHARGE_CONTROL.size;
        case Address::VOTG_REGULATION:         return VOTG_REGULATION.size;
        case Address::IOTG_REGULATION:         return IOTG_REGULATION.size;
        case Address::TIMER_CONTROL:           return TIMER_CONTROL.size;
        case Address::CHARGER_CONTROL_0:       return CHARGER_CONTROL_0.size;
        case Address::CHARGER_CONTROL_1:       return CHARGER_CONTROL_1.size;
        case Address::CHARGER_CONTROL_2:       return CHARGER_CONTROL_2.size;
        case Address::CHARGER_CONTROL_3:       return CHARGER_CONTROL_3.size;
        case Address::CHARGER_CONTROL_4:       return CHARGER_CONTROL_4.size;
        case Address::CHARGER_CONTROL_5:       return CHARGER_CONTROL_5.size;
        case Address::MPPT_CONTROL:            return MPPT_CONTROL.size;
        case Address::TEMPERATURE_CONTROL:     return TEMPERATURE_CONTROL.size;
        case Address::NTC_CONTROL_0:           return NTC_CONTROL_0.size;
        case Address::NTC_CONTROL_1:           return NTC_CONTROL_1.size;
        case Address::ICO_CURRENT_LIMIT:       return ICO_CURRENT_LIMIT.size;
        case Address::CHARGER_STATUS_0:        return CHARGER_STATUS_0.size;
        case Address::CHARGER_STATUS_1:        return CHARGER_STATUS_1.size;
        case Address::CHARGER_STATUS_2:        return CHARGER_STATUS_2.size;
        case Address::CHARGER_STATUS_3:        return CHARGER_STATUS_3.size;
        case Address::CHARGER_STATUS_4:        return CHARGER_STATUS_4.size;
        case Address::FAULT_STATUS_0:          return FAULT_STATUS_0.size;
        case Address::FAULT_STATUS_1:          return FAULT_STATUS_1.size;
        case Address::CHARGER_FLAG_0:          return CHARGER_FLAG_0.size;
        case Address::CHARGER_FLAG_1:          return CHARGER_FLAG_1.size;
        case Address::CHARGER_FLAG_2:          return CHARGER_FLAG_2.size;
        case Address::CHARGER_FLAG_3:          return CHARGER_FLAG_3.size;
        case Address::FAULT_FLAG_0:            return FAULT_FLAG_0.size;
        case Address::FAULT_FLAG_1:            return FAULT_FLAG_1.size;
        case Address::CHARGER_MASK_0:          return CHARGER_MASK_0.size;
        case Address::CHARGER_MASK_1:          return CHARGER_MASK_1.size;
        case Address::CHARGER_MASK_2:          return CHARGER_MASK_2.size;
        case Address::CHARGER_MASK_3:          return CHARGER_MASK_3.size;
        case Address::FAULT_MASK_0:            return FAULT_MASK_0.size;
        case Address::FAULT_MASK_1:            return FAULT_MASK_1.size;
        case Address::ADC_CONTROL:             return ADC_CONTROL.size;
        case Address::ADC_FUNCTION_DISABLE_0:  return ADC_FUNCTION_DISABLE_0.size;
        case Address::ADC_FUNCTION_DISABLE_1:  return ADC_FUNCTION_DISABLE_1.size;
        case Address::IBUS_ADC:                return IBUS_ADC.size;
        case Address::IBAT_ADC:                return IBAT_ADC.size;
        case Address::VBUS_ADC:                return VBUS_ADC.size;
        case Address::VAC1_ADC:                return VAC1_ADC.size;
        case Address::VAC2_ADC:                return VAC2_ADC.size;
        case Address::VBAT_ADC:                return VBAT_ADC.size;
        case Address::VSYS_ADC:                return VSYS_ADC.size;
        case Address::TS_ADC:                  return TS_ADC.size;
        case Address::TDIE_ADC:                return TDIE_ADC.size;
        case Address::DPLUS_ADC:               return DPLUS_ADC.size;
        case Address::DMINUS_ADC:              return DMINUS_ADC.size;
        case Address::DPDM_DRIVER:             return DPDM_DRIVER.size;
        case Address::PART_INFORMATION:        return PART_INFORMATION.size;
        default: return 0;
    }
}

/**
 * @brief Get register information for a given address
 * @param addr Register address
 * @return Pointer to RegisterInfo if found, nullptr otherwise
 */
inline const RegisterInfo* getRegisterInfo(Address addr) {
    switch (addr) {
        case Address::MINIMAL_SYSTEM_VOLTAGE:  return &MINIMAL_SYSTEM_VOLTAGE;
        case Address::CHARGE_VOLTAGE_LIMIT:    return &CHARGE_VOLTAGE_LIMIT;
        case Address::CHARGE_CURRENT_LIMIT:    return &CHARGE_CURRENT_LIMIT;
        case Address::INPUT_VOLTAGE_LIMIT:     return &INPUT_VOLTAGE_LIMIT;
        case Address::INPUT_CURRENT_LIMIT:     return &INPUT_CURRENT_LIMIT;
        case Address::PRECHARGE_CONTROL:       return &PRECHARGE_CONTROL;
        case Address::TERMINATION_CONTROL:     return &TERMINATION_CONTROL;
        case Address::RECHARGE_CONTROL:        return &RECHARGE_CONTROL;
        case Address::VOTG_REGULATION:         return &VOTG_REGULATION;
        case Address::IOTG_REGULATION:         return &IOTG_REGULATION;
        case Address::TIMER_CONTROL:           return &TIMER_CONTROL;
        case Address::CHARGER_CONTROL_0:       return &CHARGER_CONTROL_0;
        case Address::CHARGER_CONTROL_1:       return &CHARGER_CONTROL_1;
        case Address::CHARGER_CONTROL_2:       return &CHARGER_CONTROL_2;
        case Address::CHARGER_CONTROL_3:       return &CHARGER_CONTROL_3;
        case Address::CHARGER_CONTROL_4:       return &CHARGER_CONTROL_4;
        case Address::CHARGER_CONTROL_5:       return &CHARGER_CONTROL_5;
        case Address::MPPT_CONTROL:            return &MPPT_CONTROL;
        case Address::TEMPERATURE_CONTROL:     return &TEMPERATURE_CONTROL;
        case Address::NTC_CONTROL_0:           return &NTC_CONTROL_0;
        case Address::NTC_CONTROL_1:           return &NTC_CONTROL_1;
        case Address::ICO_CURRENT_LIMIT:       return &ICO_CURRENT_LIMIT;
        case Address::CHARGER_STATUS_0:        return &CHARGER_STATUS_0;
        case Address::CHARGER_STATUS_1:        return &CHARGER_STATUS_1;
        case Address::CHARGER_STATUS_2:        return &CHARGER_STATUS_2;
        case Address::CHARGER_STATUS_3:        return &CHARGER_STATUS_3;
        case Address::CHARGER_STATUS_4:        return &CHARGER_STATUS_4;
        case Address::FAULT_STATUS_0:          return &FAULT_STATUS_0;
        case Address::FAULT_STATUS_1:          return &FAULT_STATUS_1;
        case Address::CHARGER_FLAG_0:          return &CHARGER_FLAG_0;
        case Address::CHARGER_FLAG_1:          return &CHARGER_FLAG_1;
        case Address::CHARGER_FLAG_2:          return &CHARGER_FLAG_2;
        case Address::CHARGER_FLAG_3:          return &CHARGER_FLAG_3;
        case Address::FAULT_FLAG_0:            return &FAULT_FLAG_0;
        case Address::FAULT_FLAG_1:            return &FAULT_FLAG_1;
        case Address::CHARGER_MASK_0:          return &CHARGER_MASK_0;
        case Address::CHARGER_MASK_1:          return &CHARGER_MASK_1;
        case Address::CHARGER_MASK_2:          return &CHARGER_MASK_2;
        case Address::CHARGER_MASK_3:          return &CHARGER_MASK_3;
        case Address::FAULT_MASK_0:            return &FAULT_MASK_0;
        case Address::FAULT_MASK_1:            return &FAULT_MASK_1;
        case Address::ADC_CONTROL:             return &ADC_CONTROL;
        case Address::ADC_FUNCTION_DISABLE_0:  return &ADC_FUNCTION_DISABLE_0;
        case Address::ADC_FUNCTION_DISABLE_1:  return &ADC_FUNCTION_DISABLE_1;
        case Address::IBUS_ADC:                return &IBUS_ADC;
        case Address::IBAT_ADC:                return &IBAT_ADC;
        case Address::VBUS_ADC:                return &VBUS_ADC;
        case Address::VAC1_ADC:                return &VAC1_ADC;
        case Address::VAC2_ADC:                return &VAC2_ADC;
        case Address::VBAT_ADC:                return &VBAT_ADC;
        case Address::VSYS_ADC:                return &VSYS_ADC;
        case Address::TS_ADC:                  return &TS_ADC;
        case Address::TDIE_ADC:                return &TDIE_ADC;
        case Address::DPLUS_ADC:               return &DPLUS_ADC;
        case Address::DMINUS_ADC:              return &DMINUS_ADC;
        case Address::DPDM_DRIVER:             return &DPDM_DRIVER;
        case Address::PART_INFORMATION:        return &PART_INFORMATION;
        default: return nullptr;
    }
}

}  // namespace Registers
}  // namespace BQ25798
