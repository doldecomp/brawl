#!/usr/bin/env python3
"""
Find weak (COMDAT-like) symbols that a compiled source unit duplicates from
the original REL/DOL and name the original copies in symbols.txt, so that
mwld dedupes ours against them and the unit can be linked as Matching.

  python tools/weak_dups.py scan  <module> <unit.cpp> [--apply]
  python tools/weak_dups.py diff  <base.MAP> <new.MAP>

scan:  looks at the weak data symbols (__RTTI__*, __vt__*) of
       build/<ver>/src/<unit>.o, locates the identical object in the original
       split objects (build/<ver>/<module>/obj) and prints (or with --apply,
       writes) a symbols.txt rename `<name> = ...; scope:weak`.
diff:  compares two link maps (all-NonMatching vs unit Matching, built with
       `configure.py --map`) and lists symbols that appear only in the new one
       or moved; these are the duplicates that still need naming.
"""
import glob
import os
import re
import sys

from elftools.elf.elffile import ELFFile

VER = "RSBE01_02"


def load_obj(path):
    f = ELFFile(open(path, "rb"))
    return f, f.get_section_by_name(".symtab")


def sec_relocs(f, st, secname):
    """offset -> (target symbol name, target symbol, addend)."""
    rs = f.get_section_by_name(".rela" + secname)
    out = {}
    if not rs:
        return out
    for r in rs.iter_relocations():
        s = st.get_symbol(r["r_info_sym"])
        out[r["r_offset"]] = (s.name, s, r["r_addend"])
    return out


def orig_addr(path, module, off):
    """Absolute .data address of `off` inside original split object `path`."""
    base = os.path.basename(path)
    m = re.match(r"auto_\d+_([0-9A-F]+)_data\.o", base)
    if m:
        return int(m.group(1), 16) + off
    # named unit: look up .data start in splits.txt
    rel = os.path.relpath(path, f"build/{VER}/{module}/obj").replace("\\", "/")
    cur = None
    for l in open(f"config/{VER}/rels/{module}/splits.txt"):
        if not l.startswith(("\t", " ")) and l.strip().endswith(":"):
            cur = l.strip()[:-1]
        elif cur == rel:
            m = re.match(r"\s*\.data\s+start:0x([0-9A-Fa-f]+)", l)
            if m:
                return int(m.group(1), 16) + off
    return None


def scan(module, unit, apply):
    src = f"build/{VER}/src/{os.path.splitext(unit)[0]}.o"
    if unit.startswith("src/"):
        src = f"build/{VER}/{os.path.splitext(unit)[0]}.o"
    f, st = load_obj(src)
    data = f.get_section_by_name(".data").data()
    didx = f.get_section_index(".data")
    relocs = sec_relocs(f, st, ".data")
    # index the original split objects once
    rtti_idx = {}  # string bytes -> [(path, offset)]
    vt_idx = {}  # (target name, addend) -> [(path, offset, relocs)]
    for path in glob.glob(f"build/{VER}/{module}/obj/**/*.o", recursive=True):
        of, ost = load_obj(path)
        od = of.get_section_by_name(".data")
        if not od:
            continue
        odd = od.data()
        oidx = of.get_section_index(".data")
        orel = sec_relocs(of, ost, ".data")
        for o, (tn, ts2, ad) in orel.items():
            vt_idx.setdefault((tn, ad), []).append((path, o, orel))
            if ts2["st_shndx"] == oidx and odd[o + 4:o + 8] == b"\x00\x00\x00\x00":
                a_ = ts2["st_value"] + ad
                e = odd.find(b"\x00", a_)
                if e > 0:
                    rtti_idx.setdefault(odd[a_:e + 1], []).append((path, o))
    found = []
    for s in st.iter_symbols():
        if s["st_info"]["bind"] != "STB_WEAK" or s["st_shndx"] != didx:
            continue
        name, off, size = s.name, s["st_value"], s["st_size"]
        if name.startswith("__RTTI__"):
            tgt = relocs.get(off)
            if not tgt:
                continue
            s_off = tgt[1]["st_value"] + tgt[2]
            string = data[s_off:data.index(b"\x00", s_off) + 1]
            for p, o in rtti_idx.get(string, []):
                addr = orig_addr(p, module, o)
                if addr is not None:
                    found.append((name, addr, 8))
        elif name.startswith("__vt__"):
            # match by the (non-data) function relocs of the vtable
            fn = [(o - off, relocs[o][0], relocs[o][2]) for o in sorted(relocs)
                  if off <= o < off + size and relocs[o][1]["st_shndx"] != didx and relocs[o][0]]
            if not fn:
                continue
            for p, o, orel in vt_idx.get((fn[0][1], fn[0][2]), []):
                base = o - fn[0][0]
                if all((orel.get(base + w[0], (None, None, None))[0], orel.get(base + w[0], (None, None, None))[2]) == (w[1], w[2]) for w in fn):
                    addr = orig_addr(p, module, base)
                    if addr is not None:
                        found.append((name, addr, size))
    seen = set()
    sym = f"config/{VER}/rels/{module}/symbols.txt"
    text = open(sym, newline="").read()
    for name, addr, size in found:
        if name in seen:
            continue
        seen.add(name)
        pat = re.compile(r"^(\S+) = \.data:0x%08X;( // type:object size:0x[0-9A-F]+)([^\r\n]*)" % addr, re.M)
        m = pat.search(text)
        if not m:
            print(f"# {name}: original at .data:0x{addr:X} has no symbol line (split/size?)")
            continue
        if m.group(1) == name:
            print(f"# {name}: already named")
            continue
        line = f"{name} = .data:0x{addr:08X};{m.group(2)}{m.group(3)}"
        if "scope:weak" not in line:
            line += " scope:weak"
        print(f"{m.group(1)} -> {line}")
        if apply:
            text = text[:m.start()] + line + text[m.end():]
    if apply:
        open(sym, "w", newline="").write(text)


def load_map(p):
    d, sec = {}, None
    for l in open(p, errors="replace"):
        m = re.match(r"^(\.\w+) section layout", l)
        if m:
            sec = m.group(1)
            continue
        m = re.match(r"\s+([0-9a-f]{8}) ([0-9a-f]{6}) [0-9a-f]{8} [0-9a-f]{8}\s+\d+ (\S+)\s+(\S+)", l)
        if m and sec:
            d.setdefault(sec, {})[(m.group(3), m.group(4))] = (int(m.group(1), 16), int(m.group(2), 16))
    return d


def diff(a, b):
    A, B = load_map(a), load_map(b)
    for sec in A:
        sa, sb = A[sec], B.get(sec, {})
        # ignore pure renames: same address+size
        addr_a = {v[0] for v in sa.values()}
        new = [k for k in sb if k not in sa and sb[k][0] not in addr_a]
        moved = [k for k in sa if k in sb and sa[k] != sb[k]]
        print(f"{sec}: new-only {len(new)}, moved {len(moved)}")
        for k in new[:40]:
            print(f"   new  {k[0]} ({k[1]}) @0x{sb[k][0]:X} size 0x{sb[k][1]:X}")
        for k in moved[:5]:
            print(f"   moved {k[0]} ({k[1]}) 0x{sa[k][0]:X} -> 0x{sb[k][0]:X}")


if __name__ == "__main__":
    if len(sys.argv) >= 4 and sys.argv[1] == "scan":
        scan(sys.argv[2], sys.argv[3], "--apply" in sys.argv)
    elif len(sys.argv) == 4 and sys.argv[1] == "diff":
        diff(sys.argv[2], sys.argv[3])
    else:
        print(__doc__)
