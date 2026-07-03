# BQ25798 Driver - Decode & Encode Conventions

**Last Updated:** 2026-07-02
**Status:** Active

---

## Overview

This document collects the BQ25798-specific correctness conventions and review
traps for the driver's register classes. It is the device-specific companion to
the generic downstream-device extension-point contract defined in the TPS25751
library — see **ADR-008 (decode tier), ADR-009 (write encoders), and ADR-010
(dual transport)** in the TPS25751 repo's
[docs/engineering/ARCHITECTURE.md](https://github.com/forrestrae/TPS25751/blob/main/docs/engineering/ARCHITECTURE.md),
and the generic I2Cr/I2Cw framing rules in its
[CONSTRAINTS.md](https://github.com/forrestrae/TPS25751/blob/main/docs/engineering/CONSTRAINTS.md)
("4CC Command Interface & I2Cc Downstream-Device Proxy").

These conventions apply to all BQ25798 register classes and, by analogy, to any
downstream device whose registers are big-endian. Conventions 1–3 cover **decode**
(read); conventions 4–6 cover **encode** (write) of the R/W registers.

---

## Decode & Encode Conventions

### 1. 16-Bit Registers Are Big-Endian — Do Not Use `extractBits16`

`TPS25751BitUtils::extractBits16` assembles `raw[0]` as the **LSB** (little-endian).
BQ25798 stores 16-bit registers with `raw[0]` as the **MSB** (big-endian). Using
`extractBits16` silently byte-swaps every 16-bit value.

**Wrong:**
```cpp
uint16_t v = TPS25751BitUtils::extractBits16(data_.data(), 0, 16, 0); // byte-swapped!
```

**Right:**
```cpp
uint16_t v = (static_cast<uint16_t>(data_[0]) << 8) | data_[1];
```

### 2. Signed ADC Channels — Reinterpret as `int16_t`

The BQ25798 IBUS, IBAT, and TDIE ADC registers return 2's-complement signed
values. After big-endian assembly, reinterpret as `int16_t`:

**Wrong:**
```cpp
uint16_t raw = (static_cast<uint16_t>(data_[0]) << 8) | data_[1];
float ibus_mA = raw * 1.0f;   // wrong sign for negative currents
```

**Right:**
```cpp
uint16_t raw = (static_cast<uint16_t>(data_[0]) << 8) | data_[1];
int16_t signed_raw = static_cast<int16_t>(raw);
float ibus_mA = signed_raw * lsb_mA;  // correct sign
```

### 3. ADC LSB Step Sizes Come from the Datasheet, Not the MCP Definitions

The `bq25798-docs` MCP server provides register field descriptions but does **not**
carry unit-conversion factors (ADC LSB step sizes). Source these from the BQ25798
datasheet (SLUSE02, Table 9-xx for each ADC channel):

| Channel | LSB | Notes |
|---------|-----|-------|
| IBUS | 1 mA | Signed |
| IBAT | 1 mA | Signed |
| VBUS | 1 mV | Unsigned |
| VAC1/VAC2 | 1 mV | Unsigned |
| VBAT | 1 mV | Unsigned |
| VSYS | 1 mV | Unsigned |
| TS | 0.09765625 % | Unsigned (NTC ratio) |
| TDIE | 0.5 °C | Signed |

Hardcoding the wrong LSB (e.g. 1.0 for TDIE) produces silently wrong physical values.

### 4. Encode Is Read-Modify-Write — Preserve Reserved Bits

Field setters on R/W registers mutate **only their field's bits** in the register's own
raw buffer (`TPS25751Register::raw()`); reserved and sibling-field bits are preserved by
construction. Never reassemble the whole register from a subset of fields (that risks
zeroing reserved bits the device expects to read back unchanged). The encode helpers
`setField8` / `setField16BE` (`include/BQ25798/BQ25798Encode.h`) do this read-modify-write
and mask the value to the field width.

### 5. Field Placement Is Big-Endian on Encode Too — Use `setField16BE`

The encode side mirrors convention 1: for 16-bit registers, `setField16BE` writes the
high byte to `raw[0]` (big-endian), matching the decode-side `(raw[0]<<8)|raw[1]`
assembly. Never use a little-endian helper to encode a downstream 16-bit field — it
byte-swaps the value just as `extractBits16` does on decode.

### 6. Inverse Unit Conversion Reuses the Class's Own Decode Constant

An engineering-unit setter (e.g. `setMillivolts`) inverts the same LSB/offset constant
its decode accessor uses, so encode and decode can never drift apart. Where decode adds
an offset, the inverse must **guard against unsigned underflow** (clamp inputs below the
offset to 0 before subtracting):

```cpp
// decode: mV = kOffsetMv + code * kLsbMv
// encode (with underflow guard):
const uint16_t code = (mV <= kOffsetMv) ? 0
                      : static_cast<uint16_t>((mV - kOffsetMv) / kLsbMv);
```

### Encode Reuses the Existing I2Cw Framing (proxied transport)

Typed writes (`Device::writeRegister<T>()`) over the **proxied** transport ride the same
I2Cw 4CC task as the raw write path, so the framing constraints from the TPS25751
library's
[CONSTRAINTS.md](https://github.com/forrestrae/TPS25751/blob/main/docs/engineering/CONSTRAINTS.md)
("4CC Command Interface & I2Cc Downstream-Device Proxy")
apply unchanged: payload `len ≤ 11`, and `Length = payload + 1` (counts the
register-offset byte). Self-clearing command bits (REG_RST, WD_RST, FORCE_*) are written
as a `setX(true)`; the device clears them in hardware, so a subsequent read returns 0.
Over the **direct** transport (ADR-010) none of the proxy caps apply — the only bound
is the `TwoWire` buffer.

---

## Typed Write Flow (ADR-009 walkthrough)

The typed write tier is a **read-modify-write of a value object** layered on the I2Cw
proxy. The convenience setters and `updateRegister<T>()` follow the read → mutate →
write path; `writeRegister<T>()` is the write-back leg on its own:

```
1. Application calls a convenience setter:
   - charger.setChargeVoltageLimit(8400)   // mV
        │
        ▼
2. updateRegister<ChargeVoltageLimit>(mutate):
   - readRegister(kAddress, reg, size)      // live read via I2Cr
        │
        ▼
3. mutate(reg) applies one field setter:
   - reg.setMillivolts(8400)
       → inverts the class's own kLsbMv (VREG = mV / 10)
       → setField16BE(_raw, 0, 11, code)    // big-endian, masks to 11 bits,
                                              // touches ONLY VREG; reserved [15:11] kept
        │
        ▼
4. writeRegister<ChargeVoltageLimit>(reg):
   - keys on T::kAddress
   - sends reg.raw()/reg.size() via inherited TPS25751DownstreamDevice::writeRegister()
     → encodes an I2Cw 4CC task (len ≤ 11, Length = payload + 1; see ADR-007)
        │
        ▼
5. Returns false on any I/O failure (read or write), true otherwise
```

Self-clearing command bits (e.g. WD_RST via `kickWatchdog()`) use the same path with a
plain `setX(true)`; the device clears the bit in hardware, so a later read reports 0.

Canonical examples: `BQ25798ChargerControl0` (single-bit setters),
`BQ25798ChargeVoltageLimit` (16-bit big-endian + unit inversion),
`BQ25798MinimalSystemVoltage` (offset inversion with underflow guard).

---

## Revision History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-07-02 | Claude Code | Extracted from the TPS25751 library's CONSTRAINTS.md ("BQ25798 Downstream Device Decode & Encode Conventions") and ARCHITECTURE.md (typed write flow) when the driver split into its own repository |
