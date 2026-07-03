# BQ25798 Library Examples

Runnable sketches demonstrating the BQ25798 downstream-charger driver, reached
either proxied over a TPS25751 host's I2Cc bus or directly on the MCU's own I2C
bus. Each example lives in its own folder with a `src/main.cpp`.

## Running an Example

Each example has a matching PlatformIO environment (`example-<folder-name>`) defined
in this repo's `platformio.ini` one level up. Build and flash from the **repo
root** directory (the parent of this folder):

```bash
cd ..                                          # -> repo root
pio run -e example-bq25798-status -t upload    # build + flash (Teensy 4.0)
pio device monitor                             # 115200 baud
```

Replace `example-bq25798-status` with any environment from the table below. The
root `platformio.ini` resolves the TPS25751 dependency via
`lib_deps = symlink://../TPS25751` (sibling-checkout layout).

## Available Examples

| Example | Environment | Demonstrates |
|---|---|---|
| [`read-downstream-bq25798-reg`](read-downstream-bq25798-reg/) | `example-read-downstream-bq25798-reg` | The minimal **downstream I2Cc** path: reads the BQ25798 Part Information register (REG48h) once per loop over the 4CC I2Cr command-task. Useful for validating the downstream read path against a logic-analyzer capture. |
| [`bq25798-direct-i2c`](bq25798-direct-i2c/) | `example-bq25798-direct-i2c` | The **direct-bus** variant of the above: constructs `BQ25798::Device` with the `(TwoWire&, addr)` constructor and reads Part Info + a few ADC channels straight over the Teensy's own `Wire` bus — no TPS25751 proxy, plain I2C, no 5 s pacing. For boards/bench setups where the charger is wired to the MCU directly. |
| [`bq25798-status`](bq25798-status/) | `example-bq25798-status` | Reading all BQ25798 **status and fault** registers (ChargerStatus0–4, ChargerFlag0–3, FaultStatus0–1, FaultFlag0–1) through the typed `BQ25798::Device` driver. |
| [`bq25798-charge-config`](bq25798-charge-config/) | `example-bq25798-charge-config` | Reading the BQ25798 **charge-configuration** registers (voltage/current limits, precharge/termination, charger control, NTC thresholds). |
| [`bq25798-telemetry`](bq25798-telemetry/) | `example-bq25798-telemetry` | Reading the BQ25798 **ADC telemetry** channels (VBUS, VBAT, VSYS, VAC1/2, IBUS, IBAT, TS, TDIE) and printing converted engineering units. |
| [`bq25798-set-charge`](bq25798-set-charge/) | `example-bq25798-set-charge` | The downstream **I2Cw write** path: a guarded, reversible round-trip that toggles ChargerControl0 EN_CHG via `enableCharging()`, verifies only that bit changed, then restores the original value. |
| [`bq25798-fault-investigator`](bq25798-fault-investigator/) | `example-bq25798-fault-investigator` | **Structured fault diagnostics**: reads BQ25798 status/fault/flag/config/ADC registers, decodes them, runs heuristic checks, and prints a likely-cause report for symptoms like a 1 Hz STAT blink plus inductor whine. Always enables the ADC at startup (the only write in the otherwise read-only default build); an optional compile-time `ENABLE_SAFE_DIAGNOSTIC_SETUP` additionally applies a conservative safe config (VREG 16.8 V, VSYSMIN 12.0 V, low ICHG/IINDPM, OTG/backup off) once, and `RESTORE_CHARGER_DEFAULTS` undoes it (REG_RST the charger, then GAID cold-reset the TPS25751 so it re-applies the charger config from EEPROM). VAC1/VAC2 reads are compiled out by default (`READ_VAC1_VAC2`, they mirror VBUS on this board). Verbose or CSV output via a compile-time flag. |

> **Note on BQ25798 examples:** the charger sits on the TPS25751's secondary I2Cc
> bus and is reached through 4CC command-tasks. The TRM requires ≥5 s between
> consecutive I2Cr commands of the same type, so these sketches pace themselves with
> a delay between reads. The `bq25798-direct-i2c` example is the exception — it
> talks to the charger directly and has no such pacing requirement.

## Further Reading

- [`../README.md`](../README.md) — repo overview and quick start
- [`../AGENTS.md`](../AGENTS.md) — developer guide (decode/encode conventions,
  factory pattern, dual transport)
- The host [TPS25751 library](https://github.com/forrestrae/TPS25751)'s
  `examples/README.md` — host-controller examples (`read-registers`,
  `load-patch-bundle`)
