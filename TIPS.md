# TIPS.md

Compiler quirks and matching tricks that keep costing time. Each entry is "what you see in the diff, what to try, where it was seen". Confidence: **HIGH** = seen in several places or fixed by the compiler's rules, **MED** = seen once with a stated reason, **LOW** = folklore. Add what you learn (short, with a source file), and keep entries factual.

The same assembly can come from very different C++ (`add r3,r3,r4` could be `x + y` or a pointer-offset helper). Matching bytes is not enough: pick the version that fits how the game is structured, name things by evidence, and tag guesses with `// HYPOTHESIS:` and match-only hacks with `// MATCH-ONLY:`.

## 0. Check the build flags before the C++
- If a whole class of units is off the same way (scheduling, stack frames, extra weak symbols), the compiler flags are the suspect, not the code. Fighters and `sora_enemy` build with `-O2,s`; Havok uses `-RTTI off -use_lmw_stmw on`, some units `-Cpp_exceptions on` or `-inline noauto`; some units `-RTTI off`. Flags are set per unit in `configure.py` (`extra_cflags`). Seen: `cflags_*` in `configure.py`, commit a5cc934 (ft_purin). **HIGH**
- `-Cpp_exceptions on` makes `.extab/.extabindex` appear; `-RTTI off` removes `__RTTI__` weak data and the dynamic_cast machinery; `-use_lmw_stmw on` gives `lmw/stmw` prologues.
- Optimizer pragmas that exist in MWCC but are not yet used in Brawl code (Petari uses them often): `opt_propagation off`, `opt_common_subs off`, `opt_loop_invariants off`, `opt_lifetimes off`, `global_optimizer off`. Worth trying when one load is extra or missing or a value is spilled. Always bracket with `#pragma push` / `#pragma pop`. **MED** (names real, per-site effect untested here)

## 1. Pragmas
- **A small function must exist on its own** (the original calls it with `bl`, ours got inlined): `#pragma dont_inline on` ... `#pragma dont_inline reset` around its definition. Seen: `src/mo_enemy/sora_enemy/em_extend_param_accesser.cpp`, `gf_file_io_handle.cpp`, Melee `lbfile.c`. **HIGH** (prefer `reset`)
- **Builder constructors in fighter RELs are separate functions:** `include/ft/builder/ft_builder_noinline.h` explicitly instantiates each module builder under `dont_inline`. Include it once per character. **MED-HIGH**
- **Only the instruction order differs** (loads/stores interleaved differently, registers right): `#pragma scheduling 603` around the function, then `reset`. Seen: `mt_matrix.cpp`, `gf_model_animation.cpp`. **MED**
- **A static/data item nothing references gets stripped:** `#pragma force_active on` (dtk generates this at the top of REL units). **HIGH**
- **A zero-initialized global must live in `.data`:** `#pragma section ".data" ".data"` plus `__declspec(section ".data") s32 X = 0;` (upstream `st_onlinetrainning.cpp`). **MED-HIGH**

## 2. Inlining
- A callee that our build inlines but the original calls with `bl`: MWCC inlines by statement count. Padding with dead statements (`if (0) { ... }`) pushes it over the threshold. Seen once with numbers (Melee `ftCo_Guard.c`, 68.76 to 100). **MED**
- Template or inline member functions that must exist as separate weak functions: explicit instantiation (`template Elm& Arr::at(s32);`) in a unit split by address range. This is how the `so_array_*` units work. **HIGH**
- Force a direct (non-virtual) call: qualified name (`p->Base::method()`). **HIGH** (C++ rule)
- Last resorts: inline `asm {}` with `register` locals, or `nofralloc` asm functions (`mt_matrix.cpp`). Mark with `// MATCH-ONLY:` and a reason.

## 3. Floats
- **Constant pool order is wrong, or a constant is present that nothing uses:** MWCC lays constants out in order of first use. Fixes: a dummy function mentioning the constants in order (`(void) 0.5f; (void) 500.0f;`), or an unused local (`float unusedMin = -90.0f;`, as in `ft_status_uniq_process_glide.cpp`), or `extern const float g_...[]` defined in a data split. Same trick for strings and `.bss` order. Seen in Melee (hundreds of sites), Petari and ours. **HIGH**
- **Float literals need the `f` suffix.** Without it you get a double constant (`lfd` plus `frsp`). **HIGH**
- **int to float:** the `lis 0x4330 / xoris 0x8000 / lfd` sequence is just `(float)i`. The source type picks the constant (`u32` has no `xoris`). **HIGH**
- **`fabs` without a trailing `frsp`:** the function is `__fabs` on double (`(float)__fabs(x)` at the use site). A float-typed wrapper adds a `frsp`. **HIGH**
- **`fsub/fsel/fsub/fsel` pairs and no branches:** a clamp via `nw4r::math::FSelect(v - lo, v, lo)`. If you see `fcmpu/ble`, it is a plain branchy clamp. **MED**
- **`fcmpu` operands swapped:** try `x != 0.0f` vs `x`, or `0.0f != x`. **HIGH**
- **A struct copy is `lwz/stw`, a field copy is `lfs/stfs`:** to get word copies, use a union of floats and `u32` pairs (`include/so/templates/so_controller_impl.h`). Tag it `// MATCH-ONLY:`. **HIGH**
- **`sqrt`/`rsqrt`:** Brawl code calls `rsqrtf(x)` (declared in `mt_common.h`), with a guard against tiny values; see `ft_status_uniq_process_glide.cpp`. **MED-HIGH**
- `volatile` hacks (`NtSend::task() volatile`) are a last resort. **MED**

## 4. Classes and the C++ runtime
- **Deleting destructors:** write a normal virtual destructor and `delete p`. Do not write the `if (this)` or the `-1` flag by hand. **MED**
- **Vtables and RTTI:** a vtable is emitted in the unit that defines the class's first non-inline virtual (the key function). To force a vtable and its this-adjusting thunks into a unit, construct and destroy an instance under `dont_inline`: `new (p) V(); delete p;`. Hundreds of `so_*_thunks_*` and `so_vtable_ct_*` units rely on this. **HIGH**
- **`-RTTI off` per unit** when the original has no `__RTTI__`. **HIGH**
- **`__dynamic_cast(..., isRef=1)` with no null check:** write `T* p = &dynamic_cast<T&>(*expr);` (reference cast), not `dynamic_cast<T*>(expr)`. About 60 `em_*_param_accesser.cpp` files and `ft_status_uniq_process_damage_fly.cpp`. **HIGH**
- **Global objects with constructors** produce `__sinit_<file>_cpp` plus `__register_global_object` and a 12-byte `.bss` node. **HIGH**
- **Function-local statics with destructors** put their guard and destructor-chain object in different `.bss` regions, so such a function cannot be matched as one unit. **HIGH** (commit 84262f0)
- **Weak copies (templates, inline functions):** the linker keeps one copy, so the original file boundary for template code is unknowable. Splits are by contiguous address range, which is why file names like `_part2` exist. They are scaffolding. Use `tools/weak_dups.py` to name original weak RTTI/vtable copies, and keep a unit `NonMatching` if the hash check fails. **HIGH**
- **Mangled names depend on exact types** (`int` vs `s32`, enum vs int). Spell the original type. **HIGH**

- **A float move appears in the wrong place among constructor arguments:** verify the float's position in the prototype, not just its register type. Moving a float among pointer arguments preserves the PowerPC argument register assignments but changes MWCC's save/move order and mangling. Restore the builder and callee prototypes together, update forwarded calls and symbols, and check already-exact callers. Model scale is second in `soModelModuleBuilder` and follows node setup in `soModelModuleImpl`; this matched Marth and Kirby's builders while retaining the variable-model constructor. Seen: `include/ft/builder/ft_module_builders.h`, `include/so/model/so_model_module_impl.h`. **HIGH**

## 5. Integers and bools
- The source type decides extension: `u8` gives `clrlwi r,r,24`, `s8` gives `extsb`, `s16` gives `extsh`, `bool` gives `clrlwi 24`. Many "mysterious" extra instructions are a wrong type (often `s8` that should be `int`, or `u8` that should be `s32`). **HIGH**
- **Bitfield reads as `lwz` plus `rlwinm`:** read through a raw `*(u32*)((u8*)p + off)` and shift/mask, not through a declared signed bitfield (`so_damage_module_impl.cpp`). **MED**
- **Loop unrolling happens only for an `int` counter.** `s32` does not unroll. **HIGH** (Melee wiki)
- **Two chained compares** are usually a `switch` with a case range; `if (a < b) x = b; else x = a;` is a ternary/min/max. **HIGH**
- Explicit `== false` / `!= true` comparisons on bool-returning calls match the original codegen in several places (`so_status_module_impl.cpp`). **MED**

## 6. Control flow and registers
Things that moved registers, roughly in the order worth trying:
1. **Reorder local declarations** (declaration order sets virtual register order). Fixed `hkArrayUtil::_reduce`. **HIGH**
2. **Reference temporaries**, the decomp-permuter's output style: `__typeof__(expr)& tmp0 = expr;`. Fixed several Havok functions. **HIGH**
3. **Remove or collapse a temporary** into its single use. **HIGH**
4. **Pre-declare unused temporaries** in the order the original used them (`float y, x;` before computing sin and cos). **MED**
5. **Add a zero or constant temporary** (`float zero = 0.0f;`) to keep a load order. **MED**
6. **Named local reference** to break a common subexpression. **MED**
7. Weaker, seen in Melee: dead reads to keep a value live (`(void) a[i];`), an empty `if (x) {}`, self-assignment, the comma operator `(0, expr)`. All hacks: tag `// MATCH-ONLY:` with the reason. **MED**
- **Stack frame size is wrong:** `PAD_STACK(n)`-style unused arrays, or expand a hand-inlined helper (Melee `placeholder.h`). Note that initialized padding creates fake `.rodata`. **HIGH** in Melee
- **Argument evaluation / load order:** an extra reference or temporary of the first-loaded value sometimes moves it (`so_kinetic_energy_normal.cpp`). Some cases never yielded (`fn_106_D4E4`); stop after a few tries and leave a note.
- **Tail calls:** `return f(x)` at -O4 is `b f`; a virtual tail call ends in `bctr` with no `blr`.
- **`decomp-permuter`** (see `tools/permuter/README.md` on the build server) is worth running once only register differences remain. It matched `execNormalDamageCommon`, `hkArrayUtil::_reduce`, `hkGameCubeDvdReader::isOk` and others. Review its output: results can be unnatural, and a clean temp beats an odd rewrite of the logic.

- **Only helper-copy stack slots differ in a hierarchy visitor:** preserve the recursive owner traversal instead of flattening all leaf calls. Pass the shared helper by const reference through hierarchy levels and by value into each leaf visitor. Recovered `soInstancePool::forEachHolderModuleAccesser` made Marth's `ftKineticMediatorImpl::updateEnergy1` exact without stack padding. Seen: `include/ft/builder/ft_builder_kinetic.h`. **HIGH**

- **Constructor argument pointers are cached on the wrong side of a virtual query:** an inline wrapper can hide the query from MWCC argument scheduling even though its body is inlined. Try the real virtual expression directly in the argument list before changing parameter types or adding temporaries. Replacing `ftGetManageId(acc)` with `static_cast<soEventManager&>(acc->getEventManageModule()).getManageId()` matched Marth's entire motion builder, including its saved registers and stack frame; reference-parameter changes did not. Seen: `include/ft/builder/ft_builder_motion.h`. **MED**

## 7. Data and sections
- REL units build with `-sdata 0 -sdata2 0`, so nothing goes to small data; the DOL has them. From the third reference to `.data` or `.bss` items in one function, MWCC pools them (offsets from one section base), which looks like a struct that does not exist. `.sbss` never pools. **HIGH**
- Strings: `-str reuse` shares identical literals in a unit; compile with `-enc SJIS` or non-ASCII literals differ.
- A lone `int` in `.sdata` shifts following data by 4 because section sizes round to 8. **MED**
- Jump tables for `switch` live in `.rodata` in RELs and are named `jumptable_XXXX` in `symbols.txt`; keep the split configuration identical to verified output. **MED**

## 8. Process
- Prefer real member calls over `extern "C" fn_xxxx`. Name the symbol in `symbols.txt` (mangled) and call it normally. If you find the real name, rename.
- Never rename a REL function to a name that exists elsewhere in the symbols (it breaks the `.rel` hash).
- Before and after a change, check the per-function numbers in `build/RSBE01_02/report.json`, not just the unit total, and run the 127-file hash check.
- Add a tip here when something cost you more than ~15 minutes, with a file path.

- **An unnamed four-byte function follows a near-matching function with one extra terminal return:** verify map boundaries and all references before adding an empty stand-in. It may be the previous function's unreachable epilogue. Marth's `getEntryList` ends at the following `setupDisguiseList`; extending its symbol by four bytes removed the false `fn_106_701C` boundary and matched the entire getter. Function totals change when repairing such boundaries; report that separately from gains. Seen: `config/RSBE01_02/rels/ft_marth/symbols.txt`; full hash check passed. **HIGH**
