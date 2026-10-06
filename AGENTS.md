# AGENTS.md

Instructions for AI agents (Claude, Codex, ...) working on this matching decompilation of Super Smash Bros. Brawl (NTSC-U Rev 2, `RSBE01_02`, MWCC GC/3.0a5.2). A human gives you a task, a name to use, credentials and their identity. Everything else is here.

"Matching" = C++ that compiles to byte-identical code. Progress is `build/RSBE01_02/report.json` (per-function match %) plus the SHA-1 check: **all 127 files must stay OK**. The README explains the project layout and building.

## 0. Ground rules

- **You do not have the game image and must never obtain, copy, print or commit it** (or anything extracted from it: `orig/`, `build/`, assets, asm dumps, maps, codesets, Ghidra output). It lives on the build server.
- Pick a short name for yourself (lowercase, e.g. `hawk`). Use it for your claims, worktrees and branches.
- Work alone: **do not use subagents, background agents, parallel tasks or workflow/multi-agent features.** One thread, so you can run for hours on little usage.
- **Do not ask questions** and do not wait for replies. Decide with the rules below and keep going until your queue is done or you are blocked.
- If a command is refused, an approval is needed, or the server returns a TLS/auth error: stop and print a 3-line report (what blocked you, what you finished, where your branch is). Do not work around a block.
- No docs/notes files in this repo (this file and the README are the exceptions). Keep notes outside the repo (on the server in `/srv/brawl-native/notes/`).
- Never push to `doldecomp/brawl`. Never put keys, tokens or server details in commits.

## 1. The build server

Builds and diffs run on the maintainer's server, because the game image is there. You reach it with a small signed-HTTPS client. Your human gives you `BX_URL` and `BX_KEY`.

```bash
mkdir -p ~/bin && cat > ~/bin/bx.py <<'PY'
#!/usr/bin/env python3
"""bx: run commands / move files on the build server over signed HTTPS.
env: BX_URL, BX_KEY.   bx.py exec '<shell cmd>' | bx.py get /remote/path local | bx.py put local /remote/path"""
import hashlib, hmac, json, os, sys, time, uuid, urllib.request, urllib.error
URL = os.environ["BX_URL"].rstrip("/"); KEY = os.environ["BX_KEY"].encode()
def call(ep, body=b"", query=""):
    ts = str(time.time()); nonce = uuid.uuid4().hex
    msg = "\n".join(["POST", ep + (("?" + query) if query else ""), ts, nonce, hashlib.sha256(body).hexdigest()])
    sig = hmac.new(KEY, msg.encode(), hashlib.sha256).hexdigest()
    r = urllib.request.Request(URL + "/" + ep + (("?" + query) if query else ""), data=body, method="POST",
        headers={"X-Ts": ts, "X-Nonce": nonce, "X-Sig": sig, "User-Agent": "bx/1", "Content-Type": "application/octet-stream"})
    try: return urllib.request.urlopen(r, timeout=120).read()
    except urllib.error.HTTPError as e: sys.exit("HTTP %s %s" % (e.code, e.read()[:200]))
def main():
    a = sys.argv[1:]
    if a[0] == "exec":
        r = json.loads(call("exec", json.dumps({"cmd": a[1], "wait": 40}).encode()))
        while True:
            sys.stdout.write(r["data"]); sys.stdout.flush()
            if r["done"]: sys.exit(r["rc"])
            r = json.loads(call("job", json.dumps({"id": r["id"], "offset": r["offset"], "wait": 40}).encode()))
    elif a[0] == "get": open(a[2], "wb").write(call("get", json.dumps({"path": a[1]}).encode()))
    elif a[0] == "put": print(call("put", open(a[1], "rb").read(), "path=" + a[2]).decode())
    else: sys.exit(__doc__)
main()
PY
export BX_URL=...   # given by your human
export BX_KEY=...   # given by your human
python3 ~/bin/bx.py exec 'whoami; ls /srv/brawl-native'    # expect: claude, then folders
python3 ~/bin/bx.py exec "git config --global --add safe.directory '*'"
```

If you get a TLS/certificate error: stop and report it (do not disable verification). You are the unprivileged user `claude` on the server (no sudo). Always use `nice`, at most 4 build jobs, and stay inside `/srv/brawl-native`.

Server layout (`/srv/brawl-native`): `brawl/` (reference checkout, do not edit), `private/Brawl.wbfs` (never touch), `tools/`, `notes/` (`WORK_QUEUE.md`, `map_labels.csv`, `gecko/`, `sibling_status.md`, ...), `references/maps/maps/<module>.map` (symbol names; offsets match `fn_<module id>_<offset>`, 1-6% are wrong, verify), `references/BrawlRE/` (status IDs, module table, PSA events), `ghidra-*` (pseudocode), `CLAIMS.txt`.

## 2. Claims and your work queue

- Read the queue first: `bx exec 'cat /srv/brawl-native/notes/WORK_QUEUE.md'`. Work it top to bottom. Its first item is template instantiations in `sora_melee`; prove the approach on ONE template, report how many functions turn green, then scale it. If instantiations cannot be matched without the original translation-unit boundaries, say so and move to the next item instead of guessing boundaries.
- Other agents work at the same time. Before starting a unit: `bx exec 'cat /srv/brawl-native/CLAIMS.txt; ls -d /srv/brawl-native/wt-*'`, and check `grep -n "<unit file>" configure.py` on main (skip anything `Matching`). Take a unit nobody claimed, in a different class or file family from other agents. Then claim it: `echo "<your name> | <unit> | <your worktree> | in progress" >> /srv/brawl-native/CLAIMS.txt`, and update the line (`done`/`abandoned`) when finished. The line already in CLAIMS.txt wins a conflict.
- `notes/gecko/next_targets.md` is stale at the top; verify against `configure.py` before using it.
- Skip Nintendo SDK, online (DWC/NHTTP/NWC24/GameSpy/TMCC) and nw4r g3d code: not worth matching.

## 3. Workflow

1. **Worktree** (reuse ONE per agent across units; each costs several GB). Your human's identity is set here, see section 5:
   `bx exec 'HUMAN_NAME="<Human Name>" HUMAN_EMAIL="<id>+<user>@users.noreply.github.com" /srv/brawl-native/tools/remote/newwt.sh <name>-<topic>'` creates `/srv/brawl-native/wt-<name>-<topic>` on branch `agent/<name>-<topic>`.
2. **Build and check** (first build ~10+ min, output streams): `bx exec '/srv/brawl-native/tools/remote/rbuild.sh <name>-<topic>'` (hash check must be 127 ok / 0 bad). Per-function results: `bx exec 'python3 /srv/brawl-native/tools/report.py /srv/brawl-native/wt-<name>-<topic> <unit filter>'`. For quick iteration rebuild only the object you edit (`ninja build/RSBE01_02/src/<unit>.o` inside the worktree); run the full build before committing.
3. **Edit** with `bx put <local> /srv/brawl-native/wt-<name>-<topic>/<path>` or remote sed/python. Mark a unit `Matching` in `configure.py` only if every function is 100% AND all 127 hashes are OK.
4. **Pseudocode** (draft only: raw offsets, unresolved virtual calls, unreliable paired-single code): `bx exec 'cd /srv/brawl-native && export BRAWL_ROOT=$PWD BRAWL_GHIDRA_PROJDIR=/srv/brawl-native/ghidra-proj-claude && python3 tools/ghidra/decomp.py <module> <hex offset>'` (whole unit: `decomp_unit.py <module> <start> <end>`). If the module is not loaded, run `python3 tools/ghidra/add_module.py <module>` first (stops the decompiler, 2-4 min).
5. **Near-misses** (90-99%) are usually register allocation or instruction order: temporaries, early returns, `int` vs `u8`, inline helpers, `#pragma scheduling 603`, or the permuter (`tools/permuter/README.md`).
6. **Commit often** (every 20-30 min) and push your branch; open a pull request when a unit or a coherent batch is done.

## 4. Branches and pull requests

- Preferred branch name: `agent/<name>-<descriptive-topic>` (for example `agent/hawk-so-array-vector-templates`, `agent/lynx-ft-sonic-builder`). One topic per branch, small enough to review.
- **Use the GitHub access your environment already has.** In Claude Code on the web the repo is already connected: commit on your session's branch and push it, and open the PR with the tools you have (GitHub tools or `gh`). If the environment forces a branch name (for example `claude/...`), keep it and put the topic in the PR title instead. Only if you have NO GitHub access, and your human gave you `GH_TOKEN`, push with `git push https://x-access-token:$GH_TOKEN@github.com/humboldt123/brawl.git <branch>` and open the PR with `curl -s -X POST -H "Authorization: Bearer $GH_TOKEN" -H "Accept: application/vnd.github+json" https://api.github.com/repos/humboldt123/brawl/pulls -d '{"title":"<title>","head":"<branch>","base":"main","body":"<body>"}'` (never store the token in the repo or in a remote URL). If you can push no way at all, commit on the server worktree and report the branch name.
- The build happens on the server worktree, but your commits must also reach GitHub: the server worktree cannot push, so when you have a batch ready, copy the changed files into your GitHub checkout (`bx get`) and commit them there with the identity in section 5, or tell your human the server branch name.
- PR body: what you matched, how many functions went green, what you are unsure about, and that all 127 hashes are OK. Do not merge your own PRs; the maintainer merges. Keep branches rebased on `main`. The maintainer deletes merged branches.

## 5. Commit identity (required)

Commits show who ran the agent and which agent. The worktree author is already set by `newwt.sh` from `HUMAN_NAME` / `HUMAN_EMAIL`. All worktrees on the server share one git dir, so **never** run plain `git config user.name`; use `git config --worktree ...` if you must. Check: `git log -1 --format='%an <%ae>'`.

End every commit message with a blank line and exactly one trailer for the agent you are, including your model name if you know it (leave it out if you do not):

- `Co-Authored-By: Claude <model name> <noreply@anthropic.com>`, for example `Co-Authored-By: Claude Sonnet 5.5 <noreply@anthropic.com>`
- `Co-Authored-By: Codex <model name> <noreply@openai.com>`, for example `Co-Authored-By: Codex GPT-5 <noreply@openai.com>`

No other trailers, no session links. Imported commits from other people keep only their original authors. GitHub then shows "Human and Agent".

## 6. Code conventions

- Mark guesses `// HYPOTHESIS:`, code that exists only to force a byte match `// MATCH-ONLY:`, unknown fields `unkN`. Names need evidence (callers, vtables, maps, BrawlRE docs, `RSBE01.lst` in BrawlHeaders). Do not invent names.
- Study merged examples first: `src/mo_melee/sora_melee/ft/ft_status_uniq_process_*.cpp`, `src/sora/mu/mu_menu.cpp`, `src/mo_fighter/ft_marth/ft_marth.cpp`, `include/ft/builder/*`.
- Prefer real member calls over `extern "C" fn_xxxx` stand-ins: name the symbol in `symbols.txt` (mangled name) and call it normally.
- Never rename a REL function to a name that already exists elsewhere in the symbols (breaks the `.rel` hash). Weak-symbol duplicates: see the `tools/weak_dups.py` recipe.
- The BrawlHeaders submodule cannot be edited. To add members to one of its classes, add a local header that shadows it (`-I include` comes first) and say so in a comment, as `include/gf/gf_scene.h` does.
- Always check `git diff --stat` before committing. Never write a source file from a script that can crash halfway (compute the whole new text first).
- Finish small units and near-misses before huge ones. Report what you matched, what is left and what you were unsure about every hour and when you stop.
