#!/usr/bin/env python3

"""Report .text ranges that splits.txt does not claim yet.

Every translation unit has to be carved out of dtk's auto_* blobs before it can
be decompiled, and the hard part is proving where one unit ends. This looks for
holes between the .text ranges already in splits.txt, then reports which data
each hole references. Data that no other block touches pins the boundary down:
a hole whose constants belong to nobody else is a translation unit.

Run it after a build, so build/<version>/asm exists:

    python tools/split_gaps.py
    python tools/split_gaps.py --min-size 1024 --exclusive-only
"""

from argparse import ArgumentParser
from collections import defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple
import os
import re

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.abspath(os.path.join(script_dir, ".."))

DATA_SECTIONS = ("sdata2", "sdata", "data", "rodata", "sbss", "bss")

Range = Tuple[int, int, str]
Owned = Tuple[str, int, int, bool]

SPLIT_UNIT = re.compile(r"^(\S+\.(?:cpp|c)):\s*$")
SPLIT_SECTION = re.compile(r"^\s+\.(\w+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)")
SYMBOL = re.compile(r"^(\S+) = \.(\w+):0x([0-9A-Fa-f]+);(.*)")
SIZE = re.compile(r"size:0x([0-9A-Fa-f]+)")
SDA_REF = re.compile(r"\b([A-Za-z_]\w*)@(?:sda21|ha|l)\b")
AUTO_UNIT = re.compile(r"^auto_\d+_([0-9A-Fa-f]+)_text$")


def read_splits(path: Path) -> Dict[str, List[Range]]:
    sections: Dict[str, List[Range]] = defaultdict(list)
    unit: Optional[str] = None
    for line in path.read_text().splitlines():
        match = SPLIT_UNIT.match(line)
        if match:
            unit = match.group(1)
            continue
        match = SPLIT_SECTION.match(line)
        if match and unit:
            sections[match.group(1)].append(
                (int(match.group(2), 16), int(match.group(3), 16), unit)
            )
    for ranges in sections.values():
        ranges.sort()
    return sections


def read_symbols(path: Path) -> Tuple[Dict[str, Tuple[str, int]], List[Tuple[int, str, int]]]:
    by_name: Dict[str, Tuple[str, int]] = {}
    functions: List[Tuple[int, str, int]] = []
    for line in path.read_text().splitlines():
        match = SYMBOL.match(line)
        if not match:
            continue
        name, section, address = match.group(1), match.group(2), int(match.group(3), 16)
        by_name[name] = (section, address)
        if section == "text":
            size = SIZE.search(match.group(4))
            functions.append((address, name, int(size.group(1), 16) if size else 0))
    functions.sort()
    return by_name, functions


def read_asm_refs(asm_dir: Path, known: Set[str]) -> Dict[str, Set[str]]:
    """Symbol references per assembly file, skipping stale output.

    dtk leaves the .s of a unit behind when it disappears from splits.txt, and a
    leftover file would look like a second user of every constant it mentions,
    hiding the boundary. Only files that still correspond to a unit or to an
    auto_* block are counted.
    """
    refs: Dict[str, Set[str]] = {}
    for path in asm_dir.rglob("*.s"):
        if path.stem not in known and not AUTO_UNIT.match(path.stem):
            continue
        refs[path.stem] = set(SDA_REF.findall(path.read_text()))
    return refs


def holes(ranges: List[Range]) -> List[Tuple[int, int, str, str]]:
    return [
        (ranges[i][1], ranges[i + 1][0], ranges[i][2], ranges[i + 1][2])
        for i in range(len(ranges) - 1)
        if ranges[i + 1][0] > ranges[i][1]
    ]


def owned_data(
    used: Set[str],
    elsewhere: Set[str],
    by_name: Dict[str, Tuple[str, int]],
    sections: Dict[str, List[Range]],
) -> List[Owned]:
    """Data the hole references, split into exclusive and shared.

    A hole can hold data from several units, so exclusivity is decided per
    symbol rather than per hole -- otherwise a single shared constant hides
    every boundary in the range.
    """
    owned: List[Owned] = []
    for section in DATA_SECTIONS:
        unclaimed = holes(sections.get(section, []))
        mine = [
            name
            for name in used
            if by_name.get(name, ("", 0))[0] == section
            and any(lo <= by_name[name][1] < hi for lo, hi, _, _ in unclaimed)
        ]
        for names, exclusive in ((set(mine) - elsewhere, True), (set(mine) & elsewhere, False)):
            if not names:
                continue
            addresses = [by_name[name][1] for name in names]
            owned.append((section, min(addresses), max(addresses) + 4, exclusive))
    return owned


def main() -> None:
    parser = ArgumentParser(description=__doc__)
    parser.add_argument("--version", default="RSBE01_02", help="version to inspect")
    parser.add_argument("--min-size", type=int, default=0, help="skip holes smaller than this")
    parser.add_argument("--max-size", type=int, default=0, help="skip holes larger than this")
    parser.add_argument(
        "--exclusive-only",
        action="store_true",
        help="only report holes that own data outright",
    )
    args = parser.parse_args()

    config = Path(root_dir, "config", args.version)
    asm_dir = Path(root_dir, "build", args.version, "asm")
    if not asm_dir.is_dir():
        parser.error(f"{asm_dir} not found; build first")

    sections = read_splits(config / "splits.txt")
    by_name, functions = read_symbols(config / "symbols.txt")
    known = {Path(unit).stem for ranges in sections.values() for _, _, unit in ranges}
    refs = read_asm_refs(asm_dir, known)

    auto_start = {}
    for stem in refs:
        match = AUTO_UNIT.match(stem)
        if match:
            auto_start[stem] = int(match.group(1), 16)

    reported = 0
    for lo, hi, before, after in holes(sections["text"]):
        owners = {stem for stem, start in auto_start.items() if lo <= start < hi}
        if not owners:
            continue
        size = hi - lo
        if size < args.min_size or (args.max_size and size > args.max_size):
            continue

        used: Set[str] = set().union(*(refs[owner] for owner in owners))
        elsewhere: Set[str] = set().union(
            *(names for stem, names in refs.items() if stem not in owners)
        )
        owned = owned_data(used, elsewhere, by_name, sections)
        if args.exclusive_only and not any(entry[3] for entry in owned):
            continue

        count = sum(1 for address, _, _ in functions if lo <= address < hi)
        print(f"0x{lo:08X}-0x{hi:08X}  {size:>7} bytes  {count:>4} functions")
        print(f"    between {before} and {after}")
        for section, start, end, exclusive in owned:
            kind = "exclusive" if exclusive else "shared"
            print(f"    .{section:<7} 0x{start:08X}-0x{end:08X} {kind}")
        reported += 1

    print(f"\n{reported} unclaimed .text range(s)")


if __name__ == "__main__":
    main()
