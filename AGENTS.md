# BQ25798 Driver Library - Developer Guide

This file provides guidance for working with the BQ25798 buck-boost battery
charger Arduino driver library.

---

## Library Overview

`BQ25798::Device` is a typed C++ driver for the Texas Instruments **BQ25798**
buck-boost battery charger. It is the reference implementation of the
**downstream-device driver tier** defined by the sibling **TPS25751** library:
the charger is normally reached *through* a TPS25751 USB-C PD controller's
secondary I2Cc bus (proxied over the I2Cr/I2Cw 4CC command-tasks), or optionally
**directly** on one of the MCU's own I2C buses.

- 57 typed register classes (`REG00`–`REG48`) with named accessors, three-tier
  validation, and debug printing — all inheriting the TPS25751 library's
  `TPS25751Register` decoder base
- A typed **write tier** for the ~31 R/W registers: generic `writeRegister<T>()`
  (keyed on `T::kAddress`), `updateRegister<T>()` read-modify-write helper, and
  10 L3 convenience setters (`enableCharging`, `setChargeCurrentLimit`, …)
- Dual transport (ADR-010): proxied `Device(tps, addr)` or direct
  `Device(wire, addr)` — all 57+ typed accessors work identically over either
- Platform-optimized for Teensy 4.x (ARM Cortex-M7, no RTTI)

**Dependency:** this library depends on the sibling **`lib/TPS25751`** library
(`TPS25751Register`, `TPS25751DownstreamDevice`, and their transitive public
headers). Nothing in TPS25751 depends on this repo. For local development the
dependency resolves via `lib_deps = symlink://../TPS25751` in `platformio.ini`
(side-by-side checkout in the parent project's `lib/`).

---

## Device Register Documentation (MCP)

**IMPORTANT**: When working with BQ25798 registers, use the `bq25798-docs`
register-docs MCP server for accurate register information extracted from the TI
datasheet. The generic server engine and the device definitions live in the
sibling **`lib/device-register-docs`** repository; this repo's `.mcp.json`
invokes it cross-repo (`uv run ../device-register-docs/server.py` with
`DEVICE_CONFIG=devices/bq25798/device.json` — a relative `DEVICE_CONFIG`
resolves against `server.py`'s own directory).

| MCP server | Tool prefix | Device | Use for |
|---|---|---|---|
| `bq25798-docs` | `mcp__bq25798-docs__*` | BQ25798 buck-boost charger (57 registers) | REG00–REG48: charge control, limits, ADC channels, status/flags |

**Available tools:** `search_register`, `explain_bitfield`, `get_register`.

> **ADC LSB step sizes are NOT in the MCP definitions** — source unit-conversion
> factors from the BQ25798 datasheet (SLUSE02). See
> [docs/engineering/CONVENTIONS.md](docs/engineering/CONVENTIONS.md).

**Detailed documentation:** See `../device-register-docs/AGENTS.md` (sibling repo).

---

## Usage

```cpp
#include <BQ25798/BQ25798.h>

// Proxied: charger on the TPS25751's I2Cc bus (production topology)
BQ25798::Device charger(tps, 0x6B);

// Direct: charger on the MCU's own bus (bench / bring-up; no proxy constraints)
// BQ25798::Device charger(Wire1, 0x6B);

auto info = charger.readPartInfo();   // returns unique_ptr<BQ25798::PartInfo>
auto adc  = charger.readIbusAdc();    // returns unique_ptr<BQ25798::IbusAdc>

// Typed write tier (read-modify-write value objects):
charger.setChargeVoltageLimit(8400);  // L3 convenience setter (mV)
charger.enableCharging(true);         // EN_CHG, preserves all other bits
charger.updateRegister<BQ25798::ChargerControl0>(   // generic RMW
    [](BQ25798::ChargerControl0& r){ r.setEnHiz(false); });
```

Read methods return a `std::unique_ptr` to the decoded register, or `nullptr` on
failure. **Proxied transport pacing:** the TPS25751 TRM requires ≥ 5 s between
consecutive I2Cr (or consecutive I2Cw) commands; the base class warns via
`DEBUG_CAT_TASK` if violated (it does not hard-block). The direct transport has
no such constraint.

---

## Architecture

### Structure (mirrors the TPS25751 host-side pattern)

- **`BQ25798::Device`** (`include/BQ25798/BQ25798Device.h`): inherits
  `TPS25751DownstreamDevice`; adds 57 typed `read<Register>(bool validate=true)`
  accessors plus the typed write tier
- **`BQ25798::Registers::Address`** enum + **`RegisterInfo`** table: the single
  source of register identity (addresses, sizes)
- **Register classes** (`include/BQ25798/`, `src/BQ25798/`): one class per
  register, inheriting `TPS25751Register`. R/W registers carry a
  `static constexpr Registers::Address kAddress` + field setters (encode via
  `include/BQ25798/BQ25798Encode.h`); read-only registers (Status, Flags, ADC
  results, IcoCurrentLimit, PartInfo) are decode-only
- **Per-device factory**: `BQ25798::RegisterFactory` (abstract) →
  `BQ25798::RegisterFactoryImpl` (switch on `Registers::Address`, `default`
  returns `nullptr`) → `BQ25798::Factory` (singleton)

### Key correctness conventions

Full detail and code examples in
[docs/engineering/CONVENTIONS.md](docs/engineering/CONVENTIONS.md) — in brief:

- **16-bit registers are big-endian**: assemble as `(raw[0] << 8) | raw[1]` on
  decode, encode with `setField16BE` — never `TPS25751BitUtils::extractBits16`
  (little-endian; silently byte-swaps)
- **Signed ADC channels** (IBUS, IBAT, TDIE): reinterpret via `int16_t` after
  assembly
- **ADC LSB step sizes** come from the datasheet (SLUSE02), not the MCP definitions
- **Write encoders are read-modify-write**: each setter touches only its own
  field's bits (reserved + sibling bits preserved) and inverts the class's *own*
  decode LSB/offset constant

### Governing design records (in the TPS25751 repo)

The extension-point contract this driver implements is recorded in the sibling
repo's `../TPS25751/docs/engineering/ARCHITECTURE.md`:

- **ADR-007** — 4CC command-task layer + I2Cr/I2Cw proxy (the transport this
  driver rides in proxied mode)
- **ADR-008** — downstream-device driver tier (decode): namespace, factory,
  `TPS25751Register` reuse
- **ADR-009** — write encoders: read-modify-write value objects, `kAddress`,
  encode/decode constant sharing
- **ADR-010** — dual transport: optional direct-I2C constructor

The TPS25751 repo's `docs/engineering/STANDARDS.md` ("Downstream Device Register
Classes") defines the mandatory register-class template; its `CONSTRAINTS.md`
covers the platform rules (no RTTI, `F()` macro, I2Cr/I2Cw framing) that apply
here unchanged.

---

## Building & Testing

This directory is a **library** with a root `platformio.ini` that defines one
PlatformIO environment per bundled example (`[env:example-<name>]`), pulling in
the sibling TPS25751 library via `lib_deps = symlink://../TPS25751`.

```bash
# From this library root (where platformio.ini lives):
pio run -e example-bq25798-status            # compile one example
pio run                                       # compile all example environments
pio run -e example-bq25798-status -t upload  # build + flash to Teensy 4.0
pio device monitor                            # serial monitor @ 115200 baud
```

See [`examples/README.md`](examples/README.md) for the full list of examples and
what each demonstrates.

> **No unit tests exist yet** — same status as the TPS25751 library; the test
> harness is still pending there and here.

---

## Documentation Structure

```
/
├── AGENTS.md                       # This file (CLAUDE.md is a symlink -> AGENTS.md; edit AGENTS.md)
├── .mcp.json                       # Claude Code MCP config (bq25798-docs → sibling server repo)
├── library.json                    # PlatformIO library manifest (depends on TPS25751)
├── library.properties              # Arduino library manifest
├── include/BQ25798/                # Public headers (Device, register classes, Encode helpers)
├── src/BQ25798/                    # Implementation files
├── examples/                       # Example sketches (see examples/README.md)
└── docs/
    └── engineering/
        └── CONVENTIONS.md          # Decode/encode conventions + typed-write-flow walkthrough
```

Sibling repositories (side-by-side in the parent project's `lib/`):

```
../TPS25751/                # Host PD-controller library (this repo's dependency)
../device-register-docs/    # Generic register-docs MCP server + device definitions
```

**Navigation:**
- **Conventions & review traps:** [docs/engineering/CONVENTIONS.md](docs/engineering/CONVENTIONS.md)
- **Extension-point contract / platform rules:** `../TPS25751/docs/engineering/` (ARCHITECTURE, STANDARDS, CONSTRAINTS)
- **Examples:** [examples/README.md](examples/README.md)
- **MCP server:** `../device-register-docs/AGENTS.md`
