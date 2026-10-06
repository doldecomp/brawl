Super Smash Bros. Brawl  
[![Build Status]][actions] [![Code Progress]][progress] [![Data Progress]][progress]
=============

[Build Status]: https://github.com/doldecomp/brawl/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/doldecomp/brawl/actions/workflows/build.yml
[Code Progress]: https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fhumboldt123%2Fbrawl%2Fmain%2F.github%2Fbadges%2Fcode.json
[Data Progress]: https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fhumboldt123%2Fbrawl%2Fmain%2F.github%2Fbadges%2Fdata.json
[progress]: https://github.com/humboldt123/brawl

A work-in-progress decompilation of Super Smash Bros. Brawl.

![Progress treemap](https://raw.githubusercontent.com/humboldt123/brawl/main/.github/progress/treemap.png)

Each rectangle is a unit sized by its code; green is fully matched, blue is partially matched, grey is not started.

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

## Contributors and AI agents

Much of the work in this fork is done by AI agents (Claude, Codex) working for a person. Commits should show **who ran the agent and which agent it was**:

- **Author and committer** = the human whose account or credits run the agent (for example `humboldt123`, `DanielDavis05`). Use that person's GitHub noreply address (`<id>+<username>@users.noreply.github.com`).
- **Co-author** = the agent, as a trailer at the end of the message, so GitHub shows "Human and Agent":
  - `Co-Authored-By: Claude <noreply@anthropic.com>` (include the model name if known, e.g. `Claude Sonnet 5.5`)
  - `Co-Authored-By: Codex <noreply@openai.com>`
- Never commit as just `Claude` or `codex`, never leave session links in messages, and keep other people's authorship intact when importing their commits.

Agents: set this before your first commit in a clone or worktree:

```
git config user.name  "<HUMAN NAME>"
git config user.email "<ID>+<USERNAME>@users.noreply.github.com"
```

Supported versions:

<!--
- `RSBJ01_00`: Japan Rev 0
- `RSBJ01_01`: Japan Rev 1
- `RSBE01_01`: USA Rev 1
-->
- `RSBE01_02`: USA Rev 2
<!--
- `RSBP01_00`: PAL Rev 0
- `RSBP01_01`: PAL Rev 1
- `RSBK01_00`: Korea Rev 0
-->

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
