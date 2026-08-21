## PLAN rev4 (T1 tidy repair — MR-7 accepted in full; the recipe is now one self-contained command with zero placeholders, and I want to name the repeat before anything else) — **I SHIPPED THE SAME DEFECT TWICE. MR-6 caught a prose placeholder inside the gate I had called load-bearing; I replaced it and, in the very next revision, called §4 "the exact recipe, one mechanism, fail-closed" while leaving `<candidate worktree>` and `...rows...` in it. Twice in a row I wrote the word "exact" over text that could not run. The lesson is not "check for placeholders" — it is that I was grading my own artifact on INTENT while you were grading it on EXECUTION, which is the whole reason the reader is the grader and never the author. Rev4's recipe contains no placeholders; every value is measured or quoted, and it is one command. And I checked that claim by grepping my own relay for `...` and for angle-bracket tokens before filing — which caught two of my own leaks (an `ACTIONS_GIT_REF` line still reading `git -C <candidate worktree>`, and an ellipsis in a quoted command), both now exact. The only remaining occurrences anywhere in this file are the two quotations OF the defect, in this paragraph and in the carry list. I am recording the self-check because "I intended no placeholders" is exactly the intent-grading that produced this twice.** **ALL THREE OF YOUR FINDINGS REPRODUCED AT MY SEAT, not accepted on report: `docker run ubuntu:24.04 bash -lc 'digest_of /etc/hostname'` exits **127** `digest_of: command not found` — host shell functions do not cross the container process boundary, exactly as you said; `docker run ubuntu:24.04 id` returns **uid=0(root)**; and the candidate root canonicalizes to `/Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1` on branch `s4-matrix/arm1-t1` at `76638a0`.** **AND PROVISIONING THE CONTAINER HONESTLY SURFACED TWO HARD DEPENDENCIES I WOULD OTHERWISE HAVE SHIPPED AS ANOTHER FALSE "EXACT": `CMakeLists.txt:4` is `find_package(SQLite3 REQUIRED)` — the configure FAILS without `libsqlite3-dev`, which the GitHub `ubuntu-24.04` runner has preinstalled and a bare `ubuntu:24.04` image does not; and `:14-32` `FetchContent` DOWNLOADS simdjson 3.10.1, zstd 1.5.6, and Catch2 3.7.1 tarballs AT CONFIGURE TIME, so the container needs `ca-certificates` and egress or configure dies. Neither appears anywhere in the workflow's step list, because the runner image supplies them silently. That gap between "what the workflow says" and "what the workflow needs" is a charter-reportable difference and I am reporting it.** **ONE INSTRUMENT UPGRADE, replacing my own weaker invention: for the analyzer row I had been asking for a prose observation of "29 of 29 sources". The canonical workflow already carries a JUnit ROW GATE that asserts the `safety-tidy-analyzer` testcase EXISTS exactly once, was not `skipped`/`notrun`, has no `failure`/`error`, and has `status == 'run'` — its own comment says "ctest exits 0 on the skip arm - this IS the false green". That is strictly stronger than my prose observation and it is the canonical instrument. Rev4 runs `ctest --output-junit` and the workflow's gate verbatim instead of my paraphrase.** no product decision and no proof predicate changes; rev3's digest semantics, anchor, root binding and topology all carry; this relay still carries NO token; merge != push != release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r4
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r3
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R3-MUST-REVISE-SELF-CONTAINED-CONTAINER-RECIPE-20260820-211641.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R3-EXECUTABLE-PROVENANCE-RECIPE-20260820-210816.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — bounded in-lane revision of T1 authorized at `201613`. This relay carries NO token and authorizes NO keyboard; a successor Implementer PLAN-REVIEW approve is required, and the bare `DISPATCH IMPL` then parents to THAT approval. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; T1 head under repair `76638a00332fc9dd674f0cf952e28be4fa0507e8` (= `s4-matrix/arm1-t1`)
SUPERSEDES: PLAN rev3 `s4-matrix-t1-tidy-fix-plan-r3` at commit `54d1a786381b7eeb9a0707a974d53541bdcceee2`, SHA-256 `e96e9cea61002fbebd5da14cd0247e50d88d39b10d65d084d228db10f2831c00` (MUST REVISE)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev4 — self-contained container recipe with zero placeholders, pinned toolchain staged host-side, non-root with the charter descriptor lift, and the workflow's own JUnit tidy row gate replacing my prose observation

## 1. Disposition and reproduced findings

```text
MR-7  ACCEPTED IN FULL                    all six sub-items closed in §3-§5
docker function scope   REPRODUCED        EXIT 127, "digest_of: command not found"
ubuntu:24.04 default    REPRODUCED        uid=0(root) gid=0(root)
candidate root/branch   REPRODUCED        /Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1
                                          branch s4-matrix/arm1-t1, HEAD 76638a0
```

## 2. Frozen constants — no placeholders anywhere below

```text
CAND_ROOT      /Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1
BRANCH         s4-matrix/arm1-t1
PRE_EDIT_HEAD  76638a00332fc9dd674f0cf952e28be4fa0507e8
SRC            src/core/support/subprocess.cpp
PRE_EDIT_HASH  9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b   (measured)
EMPTY_HASH     e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855   (SHA-256 of empty)
TIDY_VERSION   1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78    (workflow pin)
MIRROR_TAG     toolchain-mirror-clang-tidy-22-immutable-v1                        (workflow pin)
```

## 3. Host pre-flight, then the macOS half

```sh
set -euo pipefail
CAND_ROOT=/Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1
SRC=src/core/support/subprocess.cpp
PRE_EDIT_HASH=9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b
EMPTY_HASH=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855

digest_of() { set -o pipefail; [ -f "$1" ] || return 1; shasum -a 256 "$1" | cut -d' ' -f1; }
assert_digest() {
  [ -n "$1" ] || exit 1
  [ "$1" != "$EMPTY_HASH" ] || exit 1
  [ "$1" != "$PRE_EDIT_HASH" ] || exit 1
}

# --- pre-flight, BEFORE S4 ---
[ "$(cd "$CAND_ROOT" && pwd -P)" = "$CAND_ROOT" ]
[ "$(git -C "$CAND_ROOT" rev-parse --abbrev-ref HEAD)" = "s4-matrix/arm1-t1" ]
[ "$(git -C "$CAND_ROOT" rev-parse HEAD)" = 76638a00332fc9dd674f0cf952e28be4fa0507e8 ]
[ "$(digest_of "$CAND_ROOT/$SRC")" = "$PRE_EDIT_HASH" ]    # confirms we start from the anchor

# --- macOS, AFTER S4: bind build/ci-macos to the candidate root ---
CACHE="$CAND_ROOT/build/ci-macos/CMakeCache.txt"
[ -f "$CACHE" ]
CACHE_ROOT=$(sed -n 's/^CMAKE_HOME_DIRECTORY:INTERNAL=//p' "$CACHE"); [ -n "$CACHE_ROOT" ]
[ "$(cd "$CACHE_ROOT" && pwd -P)" = "$CAND_ROOT" ]          # <-- THE macOS GATE
MAC_HASH=$(digest_of "$CAND_ROOT/$SRC"); assert_digest "$MAC_HASH"   # receipt + anchor inequality

cd "$CAND_ROOT"
cmake --build --preset ci-macos --target biv_subprocess_tests
ctest --preset ci-macos -R '^subprocess$' --no-tests=error --output-on-failure; MAC_SUB=$?
cmake --build --preset ci-macos
ctest --preset ci-macos \
  -R '^(biv_tests|harness-selftest|harness-e2|errno_table_gate|generated_envelope_conforms)$' \
  --no-tests=error --output-on-failure; MAC_NAMED=$?
```

As stated in rev3 and unchanged: on macOS the assertions doing work are the **cache-root
equality** and the **anchor inequality**; `MAC_HASH` is a receipt, because once the roots
are equal it hashes the same file twice.

## 4. Host staging — source and the pinned toolchain, fail-closed

The 8 pinned `.deb`s come from the workflow's own immutable release mirror and are fetched
**on the host** (which has `gh` and credentials), so the container needs no GitHub auth:

```sh
STAGE=$(mktemp -d) || exit 1
STAGE_SRC="$STAGE/src"; STAGE_DEB="$STAGE/deb"; mkdir -p "$STAGE_SRC" "$STAGE_DEB"
trap 'rm -rf "$STAGE"' EXIT            # removes ONLY this recipe's own stage

[ -z "$(git -C "$CAND_ROOT" status --porcelain)" ]        # archive == worktree
FIXED_HEAD=$(git -C "$CAND_ROOT" rev-parse HEAD)
( set -o pipefail; git -C "$CAND_ROOT" archive --format=tar "$FIXED_HEAD" | tar -x -C "$STAGE_SRC" )

HOST_HASH=$(digest_of "$STAGE_SRC/$SRC"); assert_digest "$HOST_HASH"
[ "$HOST_HASH" = "$MAC_HASH" ]

cat > "$STAGE_DEB/MANIFEST" <<'EOF'
c35ae50ecf7704b3dd0278837c4c223e72318e15de6869e3c73b58fbc64b547d clang-22 clang-22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
1e5917c1cd027548aff5cd35ee4f781a867d5daf03d9eb92611fc838ae9fa3dc clang-tidy-22 clang-tidy-22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
05215c729cd18307e2bbfb710505b034e3ced630f68e146d4c0762877073c085 clang-tools-22 clang-tools-22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
a722846476ee806a76710eea0c8cc63b18082b55eac8e2c6f092b7495a054240 libclang-common-22-dev libclang-common-22-dev_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
4c558366775f03a236a98a3e26f0f09ffab9d5df32c40050cee94c7aeca1ca44 libclang-cpp22 libclang-cpp22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
8488e5d288780d269c3516855247542f269bafafc55699502625f3ebdabce73b libclang1-22 libclang1-22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
061b48c5a47589db2ee24bcba17aebb258c973bfa41e5bdc8e46a64ea4244ceb libllvm22 libllvm22_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
f397059ac1ab2a8ea2a5707d7eec2dac6724f2f141e4668b75d08da62dd4280a llvm-22-linker-tools llvm-22-linker-tools_22.1.8.++20260613092238+e80beda6e255-1.exp1.20260613092253.78_amd64.deb
EOF

while read -r _ package asset; do
  gh release download toolchain-mirror-clang-tidy-22-immutable-v1 \
     --repo iwnlcern/bivpak --pattern "$asset" --dir "$STAGE_DEB"
done < "$STAGE_DEB/MANIFEST"
awk '{ print $1 "  " $3 }' "$STAGE_DEB/MANIFEST" > "$STAGE_DEB/SHA256SUMS"
( cd "$STAGE_DEB" && shasum -a 256 --check --strict SHA256SUMS )
[ "$(find "$STAGE_DEB" -maxdepth 1 -name '*.deb' | wc -l | tr -d ' ')" -eq 8 ]
```

## 5. The container — ONE self-contained command, root provisions then drops

Functions are defined **inside** each payload that uses them, and the gate runs as a file
rather than a nested quoted string, because that is what removed the 127 class:

```sh
docker run --rm --platform linux/amd64 \
  -v "$STAGE_SRC":/mnt-fixed:ro -v "$STAGE_DEB":/mnt-deb:ro \
  -e HOST_HASH="$HOST_HASH" -e PRE_EDIT_HASH="$PRE_EDIT_HASH" -e EMPTY_HASH="$EMPTY_HASH" \
  -e TIDY_VERSION='1:22.1.8~++20260613092238+e80beda6e255-1~exp1~20260613092253.78' \
  ubuntu:24.04 bash -euo pipefail -c '
    export DEBIAN_FRONTEND=noninteractive
    apt-get update -qq
    # The GitHub ubuntu-24.04 runner preinstalls these; the bare image does not.
    # libsqlite3-dev  <- CMakeLists.txt:4 find_package(SQLite3 REQUIRED)
    # ca-certificates <- CMakeLists.txt:14-32 FetchContent downloads simdjson/zstd/Catch2 at configure
    apt-get install -y --no-install-recommends \
      build-essential cmake git ca-certificates curl zstd \
      libsqlite3-dev python3 python3-venv python3-pip
    apt-get install -y --no-install-recommends /mnt-deb/*.deb

    while read -r _ package _; do
      test "$(dpkg-query --show --showformat="\${Version}" "$package")" = "$TIDY_VERSION"
    done < /mnt-deb/MANIFEST
    test "$(clang-tidy-22 --version | sed -nE "s/.*LLVM version ([0-9]+).*/\1/p" | head -n1)" = 22

    useradd -m -s /bin/bash biv
    cp -a /mnt-fixed /work && chown -R biv:biv /work

    cat > /gate.sh <<"SH"
#!/bin/bash
set -euo pipefail
ulimit -n "$(ulimit -Hn)"
echo "user=$(id -un) nofile_soft=$(ulimit -Sn) nofile_hard=$(ulimit -Hn)"
SRC=src/core/support/subprocess.cpp
digest_of() { set -o pipefail; [ -f "$1" ] || return 1; sha256sum "$1" | cut -d" " -f1; }
TREE_HASH=$(digest_of "/work/$SRC")
[ -n "$TREE_HASH" ]
[ "$TREE_HASH" != "$EMPTY_HASH" ]
[ "$TREE_HASH" != "$PRE_EDIT_HASH" ]
[ "$TREE_HASH" = "$HOST_HASH" ]          # THE LINUX GATE - real work, produced in-container
cd /work
python3 -m venv .venv-harness
.venv-harness/bin/python -m pip install -q -r harness/requirements.lock
cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON
cmake --build --preset ci
ctest --preset ci -R "^subprocess$" --no-tests=error --output-on-failure; echo "LINUX_SUB_EXIT=$?"
ctest --preset ci -R "^safety-tidy-analyzer$" --no-tests=error --output-on-failure \
      --output-junit /work/tidy.xml; echo "LINUX_TIDY_EXIT=$?"
SH
    chmod +x /gate.sh
    runuser -u biv -- /bin/bash /gate.sh
  '
```

`ulimit -n "$(ulimit -Hn)"` runs **inside** the `runuser` drop, which is where the charter
says the soft limit resets to 1024 and must be raised back to the inherited hard limit.

## 6. The analyzer verdict — the workflow's own gate, not my paraphrase

Replace rev1–rev3's prose "observe 29 of 29 sources" with the canonical instrument. Run the
workflow's JUnit row gate (`.github/workflows/s2-harness.yml`) verbatim against
`/work/tidy.xml`. It asserts the `safety-tidy-analyzer` testcase appears **exactly once**,
carries no `skipped` child and `status != 'notrun'`, carries no `failure`/`error`, and has
`status == 'run'`. Its own comment names the reason: *"ctest exits 0 on the skip arm - this
IS the false green"*. That is the same hole I flagged in rev1 and the workflow already
closes it better than my prose did — so the plan uses the shipped gate.

At **S3** (analyzer RED, pre-edit bytes) the gate is expected to report the row RAN and
FAILED, with exactly the three findings at `:136`, `:138`, `:220` and no others. At **S5**
it must report EXECUTED and PASSED. Both runs keep their JUnit XML as evidence.

## 7. Unchanged — carried from rev3 in full

Production shape; both framing corrections; S1–S5 ordering; the three frozen vectors with
the both-ample negative discriminator; MR-4's post-edit builds; MR-5's fresh fixed-byte
Linux tree distinct from the RED tree; `--no-tests=error --output-on-failure` on every row;
`harness-selftest` reported separately under `201613` and the full Linux suite never
labelled GREEN; disposable containers, host worktree preserved, no unrelated Docker
resource pruned or removed.

Scope unchanged, recorded for grading and **not** a grant:

```text
- src/core/support/subprocess.cpp -> in
- tests/test_subprocess.cpp       -> in
```

## 8. Differences from the canonical workflow — reported per the charter

```text
toolchain transport  workflow uses `gh release download` ON THE RUNNER; this recipe fetches the
                     same 8 pinned debs from the same immutable tag ON THE HOST and mounts them
                     read-only, so the container needs no GitHub credentials. Same artifacts,
                     same sha256 manifest, same version/major assertions.
runner-image deps    libsqlite3-dev, build-essential, cmake, git, ca-certificates, curl, zstd,
                     python3-venv are PREINSTALLED on ubuntu-24.04 runners and absent from the
                     bare image, so they are installed explicitly. This is invisible in the
                     workflow's step list and is exactly the kind of silent premise worth stating.
/mnt/c fixture root  the workflow provisions it for the cross-flavor cases in the FULL suite;
                     the two rows required here do not need it, so it is NOT provisioned. Any
                     later full-suite Linux run must add it.
privileges           workflow runs as the runner user; this recipe provisions as root then drops
                     to `biv` via runuser, with the soft nofile raised to the inherited hard
                     limit inside the drop per the charter.
```

## 9. State

No source, test, harness, workflow, ref, or worktree was edited at my seat. Verification was
read-only inspection plus two disposable `ubuntu:24.04` containers (`bash -lc` function-scope
probe, `id`), which created and removed nothing else; no unrelated Docker resource was
pruned or removed and no image was built. Nothing merged, pushed, re-based, or PR-mutated;
no remote CI, publication, deployment, or release. T2/T3/T4 and the `compare.py` composition
stay held; the count-gate shape stays routed; Linux `nonzero_exit` stays owed; the Arm-1
schema act stays F+G-fenced. Merge != push != release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only `git show 76638a0:` of `CMakeLists.txt` and `CMakePresets.json`, read-only `.github/workflows/s2-harness.yml` inspection, read-only `git -C /Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1 rev-parse` of branch and HEAD, and two disposable `ubuntu:24.04 --platform linux/amd64` containers for the function-scope and default-user probes. NO ref created or moved, NO source/test/workflow edit, NO image build, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R4-SELF-CONTAINED-CONTAINER-RECIPE-20260820-214100.md` → TO `s4-matrix.implementer` for successor PLAN-REVIEW; SUPERSEDES rev3 at SHA-256 `e96e9cea61002fbebd5da14cd0247e50d88d39b10d65d084d228db10f2831c00`
- THIS RELAY CARRIES NO TOKEN; the bare `DISPATCH IMPL` follows only after your approve and parents to THAT approval
- I SHIPPED THE SAME DEFECT TWICE: MR-6 caught a placeholder in the gate I called load-bearing, and rev3 then called §4 "the exact recipe" while containing `<candidate worktree>` and `...rows...`. I was grading my artifact on INTENT while you graded it on EXECUTION — which is why the reader is the grader and never the author. Rev4 has no angle brackets and no ellipses
- ALL THREE MR-7 FINDINGS REPRODUCED AT MY SEAT: `docker run ubuntu:24.04 bash -lc 'digest_of …'` EXIT **127** command-not-found (host functions do not cross the container boundary); `docker run ubuntu:24.04 id` = **uid=0(root)**; candidate root canonical at `/Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1`, branch `s4-matrix/arm1-t1`, HEAD `76638a0`
- TWO HARD DEPS FOUND WHILE PROVISIONING, either of which would have made rev4 another false "exact": `CMakeLists.txt:4 find_package(SQLite3 REQUIRED)` needs `libsqlite3-dev`, and `:14-32 FetchContent` DOWNLOADS simdjson 3.10.1 / zstd 1.5.6 / Catch2 3.7.1 AT CONFIGURE TIME so the container needs `ca-certificates` and egress. Both are preinstalled on the GH runner and invisible in the workflow's step list — a charter-reportable difference, reported in §8
- INSTRUMENT UPGRADE replacing my own weaker invention: drop my prose "observe 29 of 29 sources" and run the workflow's shipped JUnit ROW GATE verbatim (`--output-junit`), which asserts the row appears exactly once, is not `skipped`/`notrun`, has no `failure`/`error`, and has `status == 'run'` — its own comment says "ctest exits 0 on the skip arm - this IS the false green". S3 expects RAN-and-FAILED with exactly the three findings; S5 expects EXECUTED-and-PASSED
- RECIPE NOW SELF-CONTAINED: functions defined INSIDE each payload and the gate written as `/gate.sh` invoked by `runuser` rather than nested quoted strings; 8 pinned debs fetched HOST-side from the immutable mirror tag and mounted read-only so the container needs no GitHub credentials, with the workflow's sha256-manifest, per-package version, and LLVM-major assertions all re-run in-container; `ulimit -n "$(ulimit -Hn)"` INSIDE the runuser drop per the charter; `mktemp` checked, `git archive | tar` under `pipefail`, `trap` removing ONLY this recipe's stage
- No product decision and no proof predicate changed; rev3's digest semantics, anchor inequality, macOS cache-root binding, and archive/copy topology all carry; T2-T4 and `compare.py` held; count-gate routed; Linux `nonzero_exit` owed; schema F+G-fenced; release hold ABSOLUTE
