# BQ25798 Arduino Library

An object-oriented C++ driver for the **Texas Instruments BQ25798** buck-boost
battery charger, built as a downstream-device extension of the
[**TPS25751**](https://github.com/forrestrae/TPS25751) USB-C PD controller library.

The BQ25798 typically sits on the TPS25751's secondary I2Cc bus and is reached
through the controller's 4CC command-task interface (I2Cr/I2Cw), but this driver
also supports talking to the charger **directly** over the MCU's own I2C bus when
it's wired that way instead.

Designed for **Teensy 4.x** (ARM Cortex-M7) and the Arduino framework.

## Highlights

- **Type-safe register access** — all 57 BQ25798 registers decode into dedicated
  classes with named accessors, mirroring the host TPS25751 library's style.
- **Dual transport** — reach the charger either proxied over a `TPS25751` host's
  I2Cc bus (`BQ25798::Device(host, addr)`) or directly on a `TwoWire` bus
  (`BQ25798::Device(wire, addr)`), with the same typed API either way.
- **Typed write tier** — a generic read-modify-write `updateRegister<T>()`, a
  `writeRegister<T>()` keyed on each register's own address, and 10 L3 convenience
  setters (`enableCharging`, `setChargeCurrentLimit`, …) that touch only their own
  field's bits.
- **Validation and debug** — reuses `TPS25751Register` as the decode base, so
  every register gets the same three-tier validation and debug-print
  infrastructure as the host library.
- **Embedded-friendly** — RAII / `std::unique_ptr` ownership, no RTTI, no
  exceptions.

## Hardware Requirements

| Component     | Details                                             |
|---------------|------------------------------------------------------|
| MCU           | Teensy 4.0 or 4.1 (ARM Cortex-M7)                    |
| IC            | Texas Instruments BQ25798 buck-boost charger         |
| Interface     | I2C — either proxied via a TPS25751's I2Cc bus, or direct on the MCU's own bus |
| I2C address   | 0x6B                                                 |

## Quick Start

```cpp
#include <TPS25751.h>
#include <BQ25798/BQ25798.h>

const TPS25751 pd;
BQ25798::Device charger(pd, 0x6B);   // proxied over the TPS25751's I2Cc bus

void setup() {
    Serial.begin(115200);
    while (!Serial && millis() < 3000) delay(10);
    pd.begin();
}

void loop() {
    if (auto info = charger.readPartInfo()) {
        info->debugPrint();
    }
    delay(5000);   // TRM requires >=5s between same-type I2Cr commands
}
```

To talk to the charger directly instead of through the TPS25751 proxy, construct
`BQ25798::Device` with a `TwoWire&` and address instead:

```cpp
BQ25798::Device charger(Wire, 0x6B);  // direct bus, no TPS25751 proxy, no 5s pacing
```

Read methods return a `std::unique_ptr` to the decoded register, or `nullptr` on
failure. See the [examples](examples/) for runnable sketches covering status,
charge configuration, telemetry, writes, direct-bus access, and structured fault
diagnostics.

## Running the Examples

Each example is a small sketch under [`examples/`](examples/), built through a
dedicated PlatformIO environment defined in this repo's `platformio.ini`. Build
and flash from **this repo's root** directory:

```bash
# List the available example environments
pio project config

# Build, upload, and monitor one example (Teensy 4.0)
pio run -e example-bq25798-status -t upload
pio device monitor          # 115200 baud
```

This repo's `platformio.ini` resolves the TPS25751 dependency via
`lib_deps = symlink://../TPS25751`, assuming the sibling-checkout layout
(`lib/TPS25751` next to `lib/BQ25798`). See
[`examples/README.md`](examples/README.md) for a description of what each
example demonstrates.

## Documentation

This README is intentionally brief. For deeper detail, see:

- **[examples/README.md](examples/README.md)** — what each bundled example demonstrates
- **[AGENTS.md](AGENTS.md)** — developer guide: decode/encode conventions, factory
  pattern, dual transport, MCP usage, build commands
- The host [TPS25751 library](https://github.com/forrestrae/TPS25751)'s
  `docs/engineering/ARCHITECTURE.md` (ADR-008/009/010) documents the generic
  downstream-device extension point this driver implements

Official Texas Instruments references:

- [BQ25798 Datasheet](https://www.ti.com/product/BQ25798) (SLUSE02)

## Platform Notes

- Compiled with `-fno-rtti`; the library uses `static_cast` and a factory pattern
  instead of `dynamic_cast` / `typeid`.
- Requires C++17 or later.
- Tested on Teensy 4.0 and 4.1; may work on other Arduino-compatible ARM platforms.
- Depends on the [TPS25751](https://github.com/forrestrae/TPS25751) library for
  the `TPS25751Register` decode base and, when using the proxied transport, the
  `TPS25751DownstreamDevice` I2Cc plumbing.

## Contributing

Contributions are welcome for non-commercial purposes. New register classes
should follow the established decode/encode conventions — see `AGENTS.md`.

## License

Copyright (c) 2025-2026 Forrest Rae

Licensed under the **Apache License, Version 2.0**. You may use, copy, modify, and
redistribute this software, including for commercial purposes, subject to the terms
of the license. See [`LICENSE`](LICENSE) for full terms.
