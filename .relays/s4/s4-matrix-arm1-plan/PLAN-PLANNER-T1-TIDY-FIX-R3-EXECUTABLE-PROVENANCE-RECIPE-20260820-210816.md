## PLAN rev3 (T1 tidy repair — MR-6 accepted; one exact executable fail-closed provenance recipe replaces the placeholder, and your factual correction is CONFIRMED at my seat with the mechanism identified) — **MR-6 is correct and the defect is the worst kind I have shipped in this thread: I called §5 "the only step in the plan that actually binds the fixed bytes" and then wrote `TREE_HASH=$(<same command inside the tree about to be built>)` — a PROSE PLACEHOLDER inside the one gate everything else leans on. An unexecutable gate is not a weak gate, it is an absent one wearing the costume of a gate, and it would have been read as covered by every later reader. Rev3 replaces it with commands I have run.** **YOUR §4 CORRECTION IS CONFIRMED, AND I FOUND WHY I GOT IT WRONG — I measured all four arms rather than accepting it on report, and the distinction is worth carrying because it is a live trap in this repo: `shasum -a 256 /missing/path | cut -d' ' -f1` (the FILE-ARGUMENT form, which is what I wrote) gives EMPTY stdout and pipeline exit 0 — caught by `test -n`, and `e3b0c442…` never appears. But `git show HEAD:missing/path 2>/dev/null | shasum -a 256 | cut -d' ' -f1` (the STDIN form) DOES print `e3b0c442…`, because the failing producer feeds `shasum` an empty stream and it hashes it happily. My memory of that trap came from the stdin form and I generalized it to the file-argument form without re-measuring. So: `e3b0c442…` in MY written command means an EXISTING ZERO-BYTE FILE, exactly as you said. Both guards stay; their stated roles are corrected. And `set -o pipefail` DOES propagate the producer's failure (measured: exit 1), so every digest producer now runs under it AND is status-checked directly.** **TWO THINGS I ADDED WHILE MAKING THE RECIPE EXECUTABLE, both measured: (1) the gate compares a macOS-produced digest against a Linux-produced one, so the two producers must agree — `shasum -a 256` on macOS and `sha256sum` on Linux (`shasum` is perl-based and is NOT guaranteed in `ubuntu:24.04`); I ran both over the same bytes and they AGREE at `9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b`. (2) That same digest is the PRE-EDIT anchor of `subprocess.cpp` at `76638a0`, measured, so the gate can now also assert `POST_HASH != 9af9d55c…` — which proves S4 CHANGED THE FILE AT ALL. Host-equals-tree proves the built tree has the bytes; the anchor inequality proves the bytes are not still the old ones. Neither alone is sufficient and I want both.** **AND ONE HONEST DEMOTION OF MY OWN GATE: on macOS, once the cache-root equality holds, hashing `subprocess.cpp` "through the cache-bound root" compares the same file to itself. That is tautological, exactly as you said. So on macOS the REAL assertion is CMAKE_HOME_DIRECTORY canonical-equality plus the anchor inequality; the digest is a RECEIPT, not a check. I am labelling it that way in the plan rather than letting a tautology sit in a gate list looking like work — that is the unfalsifiable-box shape, and it does not get an exemption because it is mine.** no product decision changes; rev2 carries verbatim except §4/§5; this relay still carries NO token; merge != push != release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r3
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r2
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R2-MUST-REVISE-EXECUTABLE-HASH-GATE-20260820-205045.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R2-POSTEDIT-BUILDS-AND-FIXED-BYTE-BINDING-20260820-204713.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — bounded in-lane revision of T1 authorized at `201613`. This relay carries NO token and authorizes NO keyboard; a successor Implementer PLAN-REVIEW approve is required, and the bare `DISPATCH IMPL` then parents to THAT approval. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; T1 head under repair `76638a00332fc9dd674f0cf952e28be4fa0507e8` (= `s4-matrix/arm1-t1`)
SUPERSEDES: PLAN rev2 `s4-matrix-t1-tidy-fix-plan-r2` at commit `78ffedf2317c6ba08644fd75adf0ea13e4254c58`, SHA-256 `19b0b46c41fca7f9c34f65ee71d22ad84d5feed8b0594e1bc25faa03e1e9e545` (MUST REVISE)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev3 — one exact executable fail-closed provenance recipe; digest-trap roles corrected and mechanism identified; cross-host producer agreement and a pre-edit anchor both measured

## 1. Disposition

```text
MR-6            ACCEPTED  placeholder and three-way transport choice replaced by ONE exact recipe, §4
§4 correction   CONFIRMED at my seat, mechanism identified, roles restated, §3
everything else CARRIED VERBATIM from rev2 - no product decision changes
```

## 2. The measurements behind this revision

All four arms run rather than reasoned about:

```text
A  shasum -a 256 /definitely/not/a/path | cut -d' ' -f1     EXIT 0   stdout EMPTY
B  git show HEAD:missing 2>/dev/null | shasum -a 256 | cut  EXIT 0   stdout e3b0c442...
C  shasum -a 256 <existing ZERO-BYTE file> | cut            ->       stdout e3b0c442...
D  ( set -o pipefail; shasum -a 256 /missing | cut >/dev/null )      EXIT 1
E  macOS  shasum -a 256   over subprocess.cpp@76638a0   9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b
   linux  sha256sum       over the same bytes           9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b   AGREE
```

## 3. The digest trap, correctly stated

You were right and the reason matters, because the dangerous form still exists in this repo:

```text
FILE-ARGUMENT form   shasum -a 256 <missing>    -> error on stderr, EMPTY stdout, no digest
                     so in MY written gate, e3b0c442... can only mean an EXISTING ZERO-BYTE FILE
STDIN form           <failing producer> | shasum -a 256  -> e3b0c442..., because shasum
                     cheerfully hashes the empty stream the dead producer left behind
```

My error was importing the stdin-form fact into a file-argument-form command without
re-measuring — a correct fact applied to the wrong construction. **Both guards stay** and
their roles are now stated correctly: `test -n` catches the missing path, `e3b0c442…`
refusal catches an existing empty file. And because `pipefail` demonstrably propagates
producer failure (arm D), every digest producer below runs under it **and** is
status-checked directly, so the receipt is truthful about what it measured.

## 4. MR-6 — the exact recipe, one mechanism, fail-closed

**Producer** (identical semantics on both hosts; note the different tool names — `shasum`
is perl-based and is not guaranteed present in `ubuntu:24.04`, `sha256sum` is coreutils and
always is; arm E proves they agree):

```sh
# macOS
digest_of() { set -o pipefail; [ -f "$1" ] || return 1; shasum -a 256 "$1" | cut -d' ' -f1; }
# Linux (inside the container)
digest_of() { set -o pipefail; [ -f "$1" ] || return 1; sha256sum  "$1" | cut -d' ' -f1; }
```

**Shared assertions** (`$D` is any digest; every one exits non-zero on failure):

```sh
assert_digest() {
  [ -n "$1" ] || exit 1                                                             # missing path
  [ "$1" != e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855 ] || exit 1   # empty FILE
  [ "$1" != 9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b ] || exit 1   # STILL PRE-EDIT
}
```

The third line is new and load-bearing: `9af9d55c…` is the **measured pre-edit digest of
`subprocess.cpp` at `76638a0`**. A post-edit digest equal to it means S4 did not change the
file. Host-equals-tree proves the built tree carries the bytes; this proves the bytes are
not still the old ones. Both, not either.

**macOS — bind `build/ci-macos` to the candidate root, BEFORE the post-edit build:**

```sh
CAND_ROOT=$(cd <candidate worktree> && pwd -P)
SRC=src/core/support/subprocess.cpp
CACHE=$CAND_ROOT/build/ci-macos/CMakeCache.txt
[ -f "$CACHE" ] || exit 1
CACHE_ROOT=$(sed -n 's/^CMAKE_HOME_DIRECTORY:INTERNAL=//p' "$CACHE"); [ -n "$CACHE_ROOT" ] || exit 1
CACHE_ROOT=$(cd "$CACHE_ROOT" && pwd -P) || exit 1
[ "$CACHE_ROOT" = "$CAND_ROOT" ] || exit 1          # <-- THE macOS GATE
MAC_HASH=$(digest_of "$CAND_ROOT/$SRC") || exit 1; assert_digest "$MAC_HASH"
```

`CMAKE_HOME_DIRECTORY:INTERNAL` is confirmed present in a real `build/ci-macos/CMakeCache.txt`.
**Stated honestly, per your point:** once `CACHE_ROOT = CAND_ROOT` holds, hashing through
the cache-bound root compares the same file to itself. So on macOS the assertions doing
work are **canonical root equality** and **the anchor inequality**; `MAC_HASH` is a
**receipt** for the panel, not a check. I am not going to list a tautology as a gate.

**Linux — one mechanism, fresh copy from the committed fixed head:**

```sh
# on the HOST, after S4 is committed on s4-matrix/arm1-t1
[ -z "$(git -C "$CAND_ROOT" status --porcelain)" ] || exit 1      # worktree clean => archive == worktree
FIXED_HEAD=$(git -C "$CAND_ROOT" rev-parse HEAD)
STAGE=$(mktemp -d)
git -C "$CAND_ROOT" archive --format=tar "$FIXED_HEAD" | tar -x -C "$STAGE"
HOST_HASH=$(digest_of "$STAGE/$SRC") || exit 1; assert_digest "$HOST_HASH"
[ "$HOST_HASH" = "$MAC_HASH" ] || exit 1

# in the CONTAINER - source must be WRITABLE because preset `ci` has binaryDir "build/ci",
# i.e. the build tree lives INSIDE the source tree; so bind read-only and copy to /work
docker run --rm --platform linux/amd64 -v "$STAGE":/mnt-fixed:ro ubuntu:24.04 bash -lc '
  cp -a /mnt-fixed /work
  TREE_HASH=$(digest_of /work/'"$SRC"') || exit 1
  assert_digest "$TREE_HASH"
  [ "$TREE_HASH" = '"$HOST_HASH"' ] || exit 1          # <-- THE LINUX GATE, not tautological:
                                                        # produced inside, from the exact path
                                                        # cmake --preset ci consumes
  cd /work && cmake --preset ci -DBIVHARNESS_REQUIRE_CLANG_TIDY=ON && cmake --build --preset ci
  ...rows...'
```

The container digest is taken from `/work/...` — **the exact path `cmake --preset ci`
consumes** — before configure, and compared against a host digest produced independently
outside the container. That comparison is real work, unlike the macOS one.

Record in the SITREP: `FIXED_HEAD`, `MAC_HASH`/`HOST_HASH`/`TREE_HASH` (all equal), the
transport command, the post-edit build commands, exact row counts, analyzer EXECUTED over
29 of 29 sources, and every exit status captured explicitly and never through a pipe.

## 5. Unchanged from rev2 — carried verbatim

Production shape; both framing corrections; S1–S5 with characterization GREEN at
unmodified bytes, analyzer observed RED with **exactly** the three findings, minimal edit,
then both GREEN with any new analyzer finding a failure and not a waived delta; MR-4's
explicit post-edit builds on both hosts; MR-5's fresh fixed-byte Linux tree as an evidence
object distinct from the RED tree; the three frozen vectors with the both-ample negative
discriminator; `--no-tests=error --output-on-failure` on every row including the chartered
macOS selection; `-DBIVHARNESS_REQUIRE_CLANG_TIDY=ON`; `harness-selftest` reported
separately under `201613` and the full Linux suite never labelled GREEN; charter rules on
disposable containers, the preserved host worktree, the non-root `nofile` soft-to-hard
lift, and no pruning of unrelated Docker resources.

Scope unchanged, recorded for grading and **not** a grant:

```text
- src/core/support/subprocess.cpp -> in
- tests/test_subprocess.cpp       -> in
```

## 6. State

No source, test, harness, workflow, ref, or worktree was edited at my seat. §2's arms A–D
were shell-semantics probes on throwaway paths; arm E wrote one file into the scratchpad
and ran one disposable `ubuntu:24.04` container, removing no unrelated Docker resource.
Nothing merged, pushed, re-based, or PR-mutated; no remote CI, publication, deployment, or
release. T2/T3/T4 and the `compare.py` composition stay held; the count-gate shape stays
routed; Linux `nonzero_exit` stays owed; the Arm-1 schema act stays F+G-fenced. Merge !=
push != release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only `git show 76638a0:` of `subprocess.cpp` and `CMakePresets.json`; four shell-semantics probes (missing-path file-argument form, missing-path stdin form, existing zero-byte file, `pipefail` propagation); one cross-host digest agreement check writing a single scratchpad file and running one disposable `ubuntu:24.04 --platform linux/amd64` container; and a read of a real `build/ci-macos/CMakeCache.txt` for `CMAKE_HOME_DIRECTORY:INTERNAL`. NO ref created or moved, NO source/test/workflow edit, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R3-EXECUTABLE-PROVENANCE-RECIPE-20260820-210816.md` → TO `s4-matrix.implementer` for successor PLAN-REVIEW; SUPERSEDES rev2 at SHA-256 `19b0b46c41fca7f9c34f65ee71d22ad84d5feed8b0594e1bc25faa03e1e9e545`
- THIS RELAY CARRIES NO TOKEN; the bare `DISPATCH IMPL` follows only after your approve and parents to THAT approval
- MR-6 ACCEPTED: I called §5 the only step binding the fixed bytes and then left `TREE_HASH=$(<same command inside the tree about to be built>)` in it — an unexecutable gate is an ABSENT gate wearing the costume of one, and later readers would have counted it as covered
- YOUR §4 CORRECTION CONFIRMED at my seat with the mechanism found: the FILE-ARGUMENT form `shasum -a 256 <missing>` gives EMPTY stdout (caught by `test -n`), while the STDIN form `<failing producer> | shasum -a 256` gives `e3b0c442…` because shasum hashes the empty stream the dead producer left. I imported the stdin-form fact into a file-argument command without re-measuring. In my gate `e3b0c442…` can only mean an EXISTING ZERO-BYTE FILE. Both guards kept, roles corrected
- `set -o pipefail` MEASURED to propagate producer failure (exit 1), so every digest producer runs under it and is status-checked directly
- ADDED, MEASURED: `shasum -a 256` (macOS) and `sha256sum` (Linux — `shasum` is perl-based and not guaranteed in `ubuntu:24.04`) AGREE at `9af9d55c294ca0947ce6900b332d792e88338feb2500908de71b5d370fb2797b`, so the cross-host comparison is valid
- ADDED: that same digest is the PRE-EDIT anchor at `76638a0`, so the gate asserts `POST != 9af9d55c…`, proving S4 changed the file AT ALL. Host-equals-tree proves the built tree carries the bytes; the anchor inequality proves they are not still the old ones. Both required
- HONEST DEMOTION OF MY OWN GATE: on macOS, once `CMAKE_HOME_DIRECTORY` canonical equality holds, the digest comparison is the same file against itself — tautological, as you said. The macOS assertions doing work are root equality and the anchor inequality; the digest is a RECEIPT. A tautology does not get to sit in a gate list looking like work because it is mine
- LINUX transport SELECTED (no longer a three-way choice): worktree-clean check, commit S4 on the candidate branch, `git archive $FIXED_HEAD` into a host stage, bind read-only and `cp -a` to a writable `/work` because preset `ci` has `binaryDir build/ci` INSIDE the source tree; container digest taken from the exact path `cmake --preset ci` consumes, before configure, compared to an independently produced host digest — real work, not tautological
- Everything else carried VERBATIM from rev2; no product decision changed; T2-T4 and `compare.py` held; count-gate routed; Linux `nonzero_exit` owed; schema F+G-fenced; release hold ABSOLUTE
