#!/usr/bin/env python3
"""Bump the library version in library.json and library.properties.

Usage: bump_version.py {major|minor|patch}

Prints the new version to stdout. Run from anywhere; paths resolve
relative to this script's repository root.
"""

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LIBRARY_JSON = ROOT / "library.json"
LIBRARY_PROPERTIES = ROOT / "library.properties"


def bump(version: str, level: str) -> str:
    match = re.fullmatch(r"(\d+)\.(\d+)\.(\d+)", version)
    if not match:
        sys.exit(f"error: version {version!r} in library.json is not MAJOR.MINOR.PATCH")
    major, minor, patch = (int(part) for part in match.groups())
    if level == "major":
        return f"{major + 1}.0.0"
    if level == "minor":
        return f"{major}.{minor + 1}.0"
    return f"{major}.{minor}.{patch + 1}"


def main() -> None:
    if len(sys.argv) != 2 or sys.argv[1] not in ("major", "minor", "patch"):
        sys.exit(f"usage: {sys.argv[0]} {{major|minor|patch}}")
    level = sys.argv[1]

    manifest = json.loads(LIBRARY_JSON.read_text())
    new_version = bump(manifest["version"], level)
    manifest["version"] = new_version
    LIBRARY_JSON.write_text(json.dumps(manifest, indent=2) + "\n")

    properties = LIBRARY_PROPERTIES.read_text()
    properties, count = re.subn(
        r"^version=.*$", f"version={new_version}", properties, count=1, flags=re.M
    )
    if count != 1:
        sys.exit("error: no version= line found in library.properties")
    LIBRARY_PROPERTIES.write_text(properties)

    print(new_version)


if __name__ == "__main__":
    main()