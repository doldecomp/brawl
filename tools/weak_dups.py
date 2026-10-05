#!/usr/bin/env python3
"""
Name the original copies of weak (COMDAT-like) symbols that a compiled source
unit duplicates, so mwld dedupes ours against them and the unit can be linked
as Matching (see the symbol-naming rule: same mangled name + `scope:weak`).

  python tools/weak_dups.py scan <module> <unit.cpp> [--apply]
  python tools/weak_dups.py diff <base.MAP> <new.MAP>

scan:  reads build/<ver>/src/<unit>.o and, for every weak
         - __RTTI__* / __vt__* data symbol
         - function that has no named line in symbols.txt
       finds the identical object in the original split objects
       (build/<ver>/<module>/obj) and prints (or with --apply, writes) the
       symbols.txt rename `<mangled> = ...; ... scope:weak`.
diff:  compares two link maps (all-NonMatching vs unit Matching, built with
       `configure.py --map` + `ninja build/<ver>/<module>/<module>.rel`) and
       lists symbols present only in the new one / moved: the duplicates
       that still need naming (or real code mismatches).
"""
import glob
import os
import re
import sys

from elftools.elf.elffile import ELFFile

VER = "RSBE01_02"
AUTO = re.compile(r"^(lbl_|fn_|jumptable_|gap_|@|\.|$)")


def load_obj(path):
    f = ELFFile(open(path, "rb"))
    return f, f.get_section_by_name(".symtab")


def sec_relocs(f, st, secname):
    """offset -> (target symbol name, target symbol, addend)."""
    rs = f.get_section_by_name(".rela" + secname)
    out = {}
    if rs:
        for r in rs.iter_relocations():
            s = st.get_symbol(r["r_info_sym"])
            out[r["r_offset"]] = (s.name, s, r["r_addend"])
    return out


def orig_addr(path, module, off, sec="data"):
    """Absolute address of `off` in .`sec` of original split object `path`."""
    base = os.path.basename(path)
    m = re.match(r"auto_\d+_([0-9A-F]+)_%s\.o" % sec, base)
    if m:
        return int(m.group(1), 16) + off
    rel = os.path.relpath(path, f"build/{VER}/{module}/obj").replace("\\", "/")
    cur = None
    for l in open(f"config/{VER}/rels/{module}/splits.txt"):
        if not l.startswith(("\t", " ")) and l.strip().endswith(":"):
            cur = l.strip()[:-1]
        elif cur == rel:
            m = re.match(r"\s*\.%s\s+start:0x([0-9A-Fa-f]+)" % sec, l)
            if m:
                return int(m.group(1), 16) + off
    return None


def func_sig(code, rel, off, size):
    """Code bytes plus relocs (target name, '?' if auto-named, addend)."""
    rl = tuple(
        (o - off, "?" if AUTO.match(v[0]) else v[0], 0 if AUTO.match(v[0]) else v[2])
        for o, v in sorted(rel.items())
        if off <= o < off + size
    )
    return bytes(code[off:off + size]), rl


def sig_equal(a, b):
    if a[0] != b[0] or len(a[1]) != len(b[1]):
        return False
    return all(x[0] == y[0] and ("?" in (x[1], y[1]) or x[1:] == y[1:]) for x, y in zip(a[1], b[1]))


def scan(module, unit, apply):
    unit = unit[4:] if unit.startswith("src/") else unit
    f, st = load_obj(f"build/{VER}/src/{os.path.splitext(unit)[0]}.o")
    sym = f"config/{VER}/rels/{module}/symbols.txt"
    text = open(sym, newline="").read()
    objs = glob.glob(f"build/{VER}/{module}/obj/**/*.o", recursive=True)
    renames = []  # (our name, section, address-or-origname, size)

    # ---- data: __RTTI__ / __vt__
    didx = f.get_section_index(".data")
    data = f.get_section_by_name(".data").data() if didx else b""
    relocs = sec_relocs(f, st, ".data") if didx else {}
    weak_data = [s for s in st.iter_symbols()
                 if s["st_info"]["bind"] == "STB_WEAK" and didx and s["st_shndx"] == didx
                 and s.name.startswith(("__RTTI__", "__vt__"))]
    if weak_data:
        rtti_idx, vt_idx = {}, {}
        for path in objs:
            of, ost = load_obj(path)
            od = of.get_section_by_name(".data")
            if not od:
                continue
            odd, oidx = od.data(), of.get_section_index(".data")
            orel = sec_relocs(of, ost, ".data")
            for o, (tn, ts2, ad) in orel.items():
                vt_idx.setdefault((tn, ad), []).append((path, o, orel))
                if ts2["st_shndx"] == oidx and odd[o + 4:o + 8] == b"\x00\x00\x00\x00":
                    a_ = ts2["st_value"] + ad
                    e = odd.find(b"\x00", a_)
                    if e > 0:
                        rtti_idx.setdefault(odd[a_:e + 1], []).append((path, o))
        for s in weak_data:
            name, off, size = s.name, s["st_value"], s["st_size"]
            if name.startswith("__RTTI__"):
                tgt = relocs.get(off)
                if not tgt:
                    continue
                s_off = tgt[1]["st_value"] + tgt[2]
                string = data[s_off:data.index(b"\x00", s_off) + 1]
                for p, o in rtti_idx.get(string, []):
                    a = orig_addr(p, module, o)
                    if a is not None:
                        renames.append((name, "data", a, 8))
            else:
                fn = [(o - off, relocs[o][0], relocs[o][2]) for o in sorted(relocs)
                      if off <= o < off + size and relocs[o][1]["st_shndx"] != didx and relocs[o][0]]
                if not fn:
                    continue
                for p, o, orel in vt_idx.get((fn[0][1], fn[0][2]), []):
                    base = o - fn[0][0]
                    if all(orel.get(base + w[0], (None, None, None))[0::2] == (w[1], w[2]) for w in fn):
                        a = orig_addr(p, module, base)
                        if a is not None:
                            renames.append((name, "data", a, size))

    # ---- text: weak functions not named in symbols.txt
    tidx = f.get_section_index(".text")
    tdata = f.get_section_by_name(".text").data()
    trel = sec_relocs(f, st, ".text")
    want = {}
    for s in st.iter_symbols():
        if (s["st_info"]["bind"] == "STB_WEAK" and s["st_shndx"] == tidx
                and s["st_info"]["type"] == "STT_FUNC"
                and not re.search(r"^" + re.escape(s.name) + r" = \.text:", text, re.M)):
            want.setdefault(s["st_size"], []).append((s.name, func_sig(tdata, trel, s["st_value"], s["st_size"])))
    if want:
        for path in objs:
            of, ost = load_obj(path)
            ts_ = of.get_section_by_name(".text")
            if not ts_:
                continue
            oi = of.get_section_index(".text")
            cands = [x for x in ost.iter_symbols()
                     if x["st_shndx"] == oi and x["st_info"]["type"] == "STT_FUNC"
                     and x["st_size"] in want and AUTO.match(x.name)]
            if not cands:
                continue
            od, orl = ts_.data(), sec_relocs(of, ost, ".text")
            for x in cands:
                osig = func_sig(od, orl, x["st_value"], x["st_size"])
                for n, wsig in want[x["st_size"]]:
                    if sig_equal(wsig, osig):
                        renames.append((n, "text", x.name, x["st_size"]))
                        want[x["st_size"]] = [w for w in want[x["st_size"]] if w[0] != n]
                        break

    # ---- report / apply
    seen = set()
    for name, sec, where, size in renames:
        if name in seen:
            continue
        seen.add(name)
        if sec == "data":
            pat = r"^(\S+) = \.data:0x%08X;( // type:object size:0x[0-9A-F]+)([^\r\n]*)" % where
        else:
            pat = r"^(%s) = \.text:0x[0-9A-F]+;( // type:function size:0x[0-9A-F]+)([^\r\n]*)" % re.escape(where)
        m = re.search(pat, text, re.M)
        if not m:
            print(f"# {name}: original ({where}) has no matching symbols.txt line")
            continue
        if m.group(1) == name:
            print(f"# {name}: already named")
            continue
        addr = re.search(r"= (\.\w+:0x[0-9A-F]+);", m.group(0)).group(1)
        line = f"{name} = {addr};{m.group(2)}{m.group(3)}"
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
        addr_a = {v[0] for v in sa.values()}  # same address == just a rename
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
