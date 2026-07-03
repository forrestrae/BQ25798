# AGENTS.md — Examples Directory

This file guides AI coding assistants working with the example sketches in this
directory. `CLAUDE.md` is a symlink to this file — edit `AGENTS.md`.

---

## Purpose

This directory holds runnable example sketches for the BQ25798 downstream-charger
driver. Each example is a self-contained folder with a `src/main.cpp` that
demonstrates one focused capability (status/fault reads, charge configuration,
telemetry, writes, direct-bus access, structured fault diagnostics).

For driver development itself (register classes, factory, validation,
decode/encode conventions), see the developer guide at [`../AGENTS.md`](../AGENTS.md).
This file is scoped to the **examples** only.

---

## ⚠️ Keep `README.md` In Sync — Required

**Whenever you add, remove, or rename an example, you MUST update
[`README.md`](README.md) in this directory in the same change.** The README's
"Available Examples" table is the human-facing index of what each example
demonstrates, and it drifts out of date silently if not maintained.

When adding a new example:

1. Create the example folder with a `src/main.cpp`.
2. Add a matching `[env:example-<folder-name>]` environment to this repo's
   `../platformio.ini` (use `build_src_filter = +<*> +<../examples/<folder>/src>`,
   mirroring the existing entries).
3. **Add a row to the "Available Examples" table in [`README.md`](README.md)** with:
   - the folder name (linked),
   - the PlatformIO environment name,
   - a one-line description of what the example demonstrates.
4. If the new example introduces a new category of behavior, also update any
   relevant notes in `README.md`.

When removing or renaming an example, remove or update its README row and its
`platformio.ini` environment accordingly.

The README does **not** need to list every example exhaustively if the set grows
large, but every example that exists should be discoverable and the table must not
reference examples that no longer exist.

---

## Building & Running Examples

Examples build through per-example environments in this repo's `../platformio.ini`,
not from this directory. From the **repo root** (one level up):

```bash
pio run -e example-<folder-name> -t upload    # build + flash (Teensy 4.0)
pio device monitor                            # 115200 baud
```

The per-example `platformio.ini` files inside some example folders are for standalone
consumption (copy-into-your-own-project mode) and are not the primary build path
used in this repo.

---

## Conventions Across Examples

- Sketches are **read-only / non-destructive** unless explicitly stated otherwise.
- Serial is 115200 baud; sketches wait briefly for the USB serial connection in
  `setup()`.
- Debug output is configured via `TPS25751::setDebugLevel()` /
  `setDebugCategories()` rather than build flags.
- BQ25798 (downstream I2Cc) examples pace consecutive same-type I2Cr commands ≥5 s
  apart per the TRM. The `bq25798-direct-i2c` example, which bypasses the I2Cc
  proxy entirely, is the exception.

---

## Further Reading

- [`README.md`](README.md) — human-facing example index (keep this updated!)
- [`../AGENTS.md`](../AGENTS.md) — driver developer guide
- The host TPS25751 library's
  [docs/engineering/CONSTRAINTS.md](https://github.com/forrestrae/TPS25751/blob/main/docs/engineering/CONSTRAINTS.md)
  — I2C / 4CC downstream-device protocol gotchas
