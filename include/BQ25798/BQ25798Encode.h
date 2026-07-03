#pragma once

#include <cstdint>

// ---------------------------------------------------------------------------
// BQ25798 field-encode helpers
//
// Inverse of the decode side's bitfield extraction. Centralised so the ~150
// per-field setters don't each re-derive the mask/shift math. These mirror the
// read side's BIG-ENDIAN convention for 16-bit registers (raw[0] = MSB).
//
// Each helper read-modify-writes only its field's bits, preserving the rest of
// the register, and masks @p value to the field width (silent clamp).
// ---------------------------------------------------------------------------

namespace BQ25798 {

/**
 * @brief Set a field within a single-byte register.
 *
 * Byte-order is irrelevant for a 1-byte register. The other bits of @p raw[0]
 * are preserved; @p value is masked to @p bitLen bits (silent clamp).
 *
 * @param raw    Pointer to the register buffer (must be non-null, >= 1 byte).
 * @param bitPos Bit offset of the field's LSB within the byte.
 * @param bitLen Field width in bits (1..8).
 * @param value  New field value (masked to @p bitLen bits).
 */
inline void setField8(uint8_t* raw, uint8_t bitPos, uint8_t bitLen, uint8_t value)
{
    const uint8_t mask = static_cast<uint8_t>(((1u << bitLen) - 1u) << bitPos);
    raw[0] = static_cast<uint8_t>((raw[0] & ~mask) | ((value << bitPos) & mask));
}

/**
 * @brief Set a field within a 16-bit BIG-ENDIAN register (raw[0]=MSB, raw[1]=LSB).
 *
 * Matches the read side's (raw[0]<<8)|raw[1] assembly convention. The other
 * bits of the 16-bit word are preserved; @p value is masked to @p bitLen bits
 * (silent clamp).
 *
 * @param raw    Pointer to the register buffer (must be non-null, >= 2 bytes).
 * @param bitPos Bit offset of the field's LSB within the 16-bit word.
 * @param bitLen Field width in bits (1..16).
 * @param value  New field value (masked to @p bitLen bits).
 */
inline void setField16BE(uint8_t* raw, uint8_t bitPos, uint8_t bitLen, uint16_t value)
{
    const uint16_t mask = static_cast<uint16_t>(((1u << bitLen) - 1u) << bitPos);
    uint16_t v = static_cast<uint16_t>((raw[0] << 8) | raw[1]);
    v = static_cast<uint16_t>((v & ~mask) | ((static_cast<uint16_t>(value) << bitPos) & mask));
    raw[0] = static_cast<uint8_t>(v >> 8);
    raw[1] = static_cast<uint8_t>(v & 0xFF);
}

}  // namespace BQ25798
