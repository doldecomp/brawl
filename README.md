Super Smash Bros. Brawl  
[![Build Status]][actions] [![Code Progress]][progress] [![Data Progress]][progress]
=============

[Build Status]: https://github.com/doldecomp/brawl/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/doldecomp/brawl/actions/workflows/build.yml
[Code Progress]: https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fhumboldt123%2Fbrawl%2Fmain%2F.github%2Fbadges%2Fcode.json
[Data Progress]: https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fhumboldt123%2Fbrawl%2Fmain%2F.github%2Fbadges%2Fdata.json
[progress]: https://github.com/humboldt123/brawl

A work-in-progress slopcoded decompilation of Super Smash Bros. Brawl.

![Progress treemap](https://raw.githubusercontent.com/humboldt123/brawl/main/.github/progress/treemap.png)

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

Supported versions:

- `RSBE01_02`: USA Rev 2

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

- Install [wine-crossover](https://github.com/Gcenx/homebrew-wine):

  ```sh
  brew install --cask --no-quarantine gcenx/wine/wine-crossover
  ```

After OS upgrades, if macOS complains about `Wine Crossover.app` being unverified, you can unquarantine it using:

```sh
sudo xattr -rd com.apple.quarantine '/Applications/Wine Crossover.app'
```

Linux
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
- For non-x86(_64) platforms: Install wine from your package manager.
  - For x86(_64), [wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

- Clone the repository:

  ```sh
  git clone https://github.com/doldecomp/brawl.git
  ```

- Update and Initialize submodules:

  ```sh
  git submodule update --init --recursive
  ```

- Copy your game's disc image to `orig/RSBE01_02` (or the appropriate version).
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:

  ```sh
  python configure.py
  ```

  To use a version other than `RSBE01_02` (USA Rev 2), specify it with `--version`.

- Build:

  ```sh
  ninja
  ```

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![](assets/objdiff.png)

## Contributors and AI agents

See [AGENTS.md](AGENTS.md) for the full agent instructions.

Much of the work in this fork is done by AI agents (Claude, Codex) working for a person. Commits should show **who ran the agent and which agent it was**:

- **Author and committer** = the human whose account or credits run the agent (for example Brendan, GitHub `brendan-hoenn`, or May, GitHub `may-petalburg`). Use that person's GitHub noreply address (`<id>+<username>@users.noreply.github.com`, for example `4410221+brendan-hoenn@users.noreply.github.com`).
- **Co-author** = the agent, as one trailer at the end of the message, with your model name if you know it, so GitHub shows "Human and Agent":
  - `Co-Authored-By: Claude <model name> <noreply@anthropic.com>` (for example `Co-Authored-By: Claude Sonnet 5.5 <noreply@anthropic.com>`)
  - `Co-Authored-By: Codex <model name> <267193182+codex@users.noreply.github.com>` (for example `Co-Authored-By: Codex GPT-6.1 Sol <267193182+codex@users.noreply.github.com>`; use the exact model name your environment reports, never a guess)
  - If you do not know your model name, leave it out (`Claude` / `Codex` alone).
- Never commit as just `Claude` or `codex`, never leave session links in messages, and keep other people's authorship intact when importing their commits.

Agents: set this before your first commit in a clone or worktree:

```
git config user.name  "<HUMAN NAME>"
git config user.email "<ID>+<USERNAME>@users.noreply.github.com"
```

Decompilation workflow tools
============================

The standard-library Python tools below keep investigation and validation evidence
outside the checkout. Use Python 3.10 or newer. Generated packets can contain
original-game information: do not commit or publish them. These tools do not
rename symbols, promote units to Matching, or merge changes automatically.

Validation snapshots
--------------------

`tools/decomp_build.py` runs on the POSIX build host with `nice`, Ninja, DTK,
and objdiff available. Start with an initialized, warm checkout. Choose a fresh
external output directory for every run and the same external lock path for all
cooperating workers:

```sh
python3 tools/decomp_build.py baseline --mode full --jobs 4 \
  --output ../validation/baseline --lock ../validation/team.lock
```

The tool configures the selected version, builds, checks all 127 output hashes,
and generates a report. Existing comparison objects are refreshed; absent
unlinked draft objects are recorded as unavailable rather than compiled implicitly.
Candidate runs can reuse the entire validated baseline report when its complete
comparison configuration, object contents (including unavailable objects), and
report-generation inputs are identical. This does not skip the build, output-hash
checks, or source-drift checks. Changed compatible inputs regenerate the report;
incompatible tools or original binaries still require a new baseline. Older
evidence without a reuse key also regenerates. Use `--fresh-report` to force
independent generation. The manifest records whether the report was generated
or reused and identifies the evidence it came from.
`validation.json` records command logs and timings,
working-source/configuration/tool/artifact fingerprints, and the Git revision.
The working snapshot is identified separately from its Git HEAD; it may include
uncommitted files. This is a provenance record, not a content-addressed build cache.
Normal Ninja dependency correctness remains required; avoid copying build caches
between checkout paths. Source inputs must remain unchanged while validation runs.

Read the full revision and source fingerprint from the baseline's
`validation.json`, then pass them explicitly when checking a candidate:

```sh
python3 tools/decomp_build.py run --mode full --jobs 4 \
  --baseline ../validation/baseline \
  --expected-baseline-revision "$BASELINE_REVISION" \
  --expected-baseline-fingerprint "$BASELINE_FINGERPRINT" \
  --output ../validation/candidate --lock ../validation/team.lock
python3 tools/decomp_build.py compare ../validation/baseline ../validation/candidate
```

For iteration, use `--mode objects --target build/RSBE01_02/src/path/to/unit.o`
with a target listed in the checkout's objdiff configuration. Repeat `--target`
for related units. A scoped check is explicitly not the full 127-output gate.
Comparison uses original module/address/size identities, so a symbol rename
cannot hide a lost exact function. Missing or ambiguous identities fail clearly.
Jobs are limited to four; the shared lock serializes cooperating runs. It does
not coordinate unrelated manual builds. Failed and interrupted runs never qualify
as successful baseline evidence, and an existing lock is not removed automatically.

Evidence packets
----------------

`tools/decomp_evidence.py` keeps imported observations, interpretations,
hypotheses, and reviews in SQLite. Supply the original binary for each imported
module explicitly. For example, after setting `WARIO_ORIGINAL_REL` to the actual
original REL path:

```sh
python3 tools/decomp_evidence.py --root . --db ../evidence/index.sqlite import \
  --version RSBE01_02 --report build/RSBE01_02/report.json --objdiff objdiff.json \
  --binary "ft_wario=$WARIO_ORIGINAL_REL" \
  --unit ft_wario/mo_fighter/ft_wario/wn_wario_bike_status_uniq_process_wheelie
python3 tools/decomp_evidence.py --root . --db ../evidence/index.sqlite packet \
  --unit ft_wario/mo_fighter/ft_wario/wn_wario_bike_status_uniq_process_wheelie --out ../evidence/packets
```

Packets include stable binary-hash/module/address/size function identities,
reported object comparisons, source/header and symbol/split context, and hashed
evidence references. Optional `--assembly UNIT=FILE` and `--map MODULE=FILE`
inputs add observed direct-call operands and labels. Lexical declarations,
map labels, and percentages are not semantic or ABI proof, and importing a
report does not validate that report against current source.

Use `claim` to append an interpretation or hypothesis with a subject ID and
explicit artifact IDs from a packet; use `review` to record a separate review.
See each subcommand's `--help` for required arguments. Conflicting claims remain
visible, and changed evidence is flagged for renewed review rather than silently
replacing history. Keep generated databases and packets outside Git.

When parallel work is explicitly authorized, assign each reconstruction worker
a related behavior family and exclusive source ownership. Give a separate reviewer
the evidence packet and original behavior to check independently. Assign one owner
for shared interfaces, freeze the combined source during validation, and publish
only the exact source tree that passed. Preserve unfinished candidates separately.

Link diagnostics
----------------

Normal REL builds link the original object list directly to `.plf`. Preliminary
`-r` links are independent diagnostic targets, not prerequisites for the final
`-r1` link. To request one explicitly:

```sh
ninja build/RSBE01_02/sora_melee/sora_melee.preplf
```

Synthetic tooling tests require no game assets:

```sh
python3 -m unittest discover -s tests -p 'test_decomp_*.py'
```
