## PLAN rev8 (T1 tidy repair — MR-15 accepted and closed; and validating it surfaced a SECOND defect in the same function that I found and fixed myself) — **MR-15 IS CORRECT ON ALL THREE HOLES, and hole 3 is the serious one: an unrestricted `label` is PATH MATERIAL, so `$EVID/$label-cache-root.txt` with `label=../ESCAPED` resolves OUTSIDE the very root `require_root` had just validated. My root validator was checking the root and then handing an attacker-shaped string the job of composing paths inside it. `s2:ne` and `s5mac:eq` are the quieter two — receipts labelled as one phase carrying the other phase's semantics — and both were reachable because `if [ "$anchor" = eq ]; …; else …` maps EVERY non-`eq` string to `ne`. One `case` over `"$label:$anchor"` accepting exactly `s2:eq` and `s5mac:ne`, placed before any evidence write, closes all three.** **THE SECOND DEFECT, MINE, FOUND WHILE VALIDATING YOURS: I ran the must-be-YES arm `s5mac ne` against the current tree, where production is still unmodified, so the anchor correctly refused with `S5 expects production CHANGED` — and then I looked at the root and found `s5mac-cache-root.txt` sitting in it. The receipt was written BEFORE the anchor assertion ran. That breaks your own MR-15 requirement that a refusal create nothing, and it is worse than untidy: `assert_absent` would then block the LATER legitimate `s5mac` run on a file left by an earlier refusal, so one refused attempt poisons the real one. All receipt writes now happen only after EVERY precondition has passed, and I re-tested it: the root is byte-identical before and after a refusal.** **ARMS RUN ON THE REAL FILED ARTIFACT — seven must-be-NO for the pair gate (`bogus:garbage`, `s2:ne`, `s5mac:eq`, `s2:GARBAGE`, `nosuchlabel:eq`, `../ESCAPED:eq`, and the empty pair `:`), every one refused with the pair message before touching anything; plus both must-be-YES controls reaching their next precondition — `s2:eq` passed the gate and wrote `s2-source.sha256` = `9af9d55c…`, the pre-edit anchor, proving both the identity gate and the `eq` assertion fired correctly; `s5mac:ne` passed the identity gate and then refused on the source anchor, which is the right answer today and demonstrates the two gates are independent rather than one gate wearing two names. Containment confirmed: nothing was ever written outside the root, and all probe roots were removed.** evidence-domain validation only, as you scoped it; no product decision, source scope, analyzer identity, toolchain, Docker topology, source anchor, RED/GREEN gate, or one-root sequence changed; this relay still carries NO token; merge != push != release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-r8
PARENT_DISPATCH_ID: s4-matrix-t1-tidy-fix-plan-review-r7
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T1-TIDY-FIX-R7-MUST-REVISE-MACOS-LABEL-ANCHOR-DOMAIN-20260821-031405.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R7-ONE-EVIDENCE-CHAIN-INIT-MACOS-LINUX-20260821-025323.md; .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T1-LINUX-REDS-RULED-TIDY-FIX-AUTHORIZED-IN-LANE-HARNESS-RESIDUAL-UP-20260820-201613.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — bounded in-lane repair authorized at `201613`. This relay carries NO token and authorizes NO keyboard; a successor Implementer PLAN-REVIEW approve is required, and the bare `DISPATCH IMPL` then parents to THAT approval. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: frozen base `a02a65b9ea2c1ce6ff149a914c50f965531d443d`; T1 head under repair `76638a00332fc9dd674f0cf952e28be4fa0507e8` (= `s4-matrix/arm1-t1`)
SUPERSEDES: PLAN rev7 `s4-matrix-t1-tidy-fix-plan-r7` at commit `ad7c3b522b92b37d26df3987d96b1b4a886e9ad8`, SHA-256 `831aba9911ea1e96a11c68b632e13b5e516f22893ebf210dc4b5f5801c153a1b` (MUST REVISE)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev8 — macOS phase identity as one exact pair gate before any write, plus a self-found fix so a refused phase leaves the evidence root byte-untouched

## 1. Disposition

```text
MR-15  ACCEPTED and CLOSED   one `case` over "$label:$anchor"; §3
       + a second defect in the same function, found by me while validating yours:
         receipts were written BEFORE the anchor assertion, so a refusal left a file
         behind and would block the later legitimate run via its own assert_absent
```

Everything MR-1 through MR-14 settled is carried untouched.

## 2. Arms run on the real filed artifact

```text
MUST-BE-NO (pair gate) - all refused BEFORE any write, inside or outside the root
  bogus:garbage        exit 1   macOS phase identity must be exactly s2:eq or s5mac:ne
  s2:ne                exit 1   (hole 1 - S2 label with post-edit semantics)
  s5mac:eq             exit 1   (hole 2 - S5 label with pre-edit semantics)
  s2:GARBAGE           exit 1   (the else-branch that silently meant `ne`)
  nosuchlabel:eq       exit 1
  ../ESCAPED:eq        exit 1   (hole 3 - traversal label as path material)
  :                    exit 1   (both arguments empty)

MUST-BE-YES - pass the pair gate and reach the next precondition
  s2:eq      passed the gate; wrote s2-cache-root.txt = the candidate root and
             s2-source.sha256 = 9af9d55c… (the pre-edit anchor), so BOTH the identity
             gate and the `eq` assertion fired correctly. Bounded with a timeout; it
             then proceeds into the real cmake build, which is the next step.
  s5mac:ne   passed the identity gate, then REFUSED on the source anchor with
             "S5 expects production CHANGED" - correct today, since S4 has not run.
             The two gates are independent, not one gate wearing two names.

REFUSAL LEAVES NOTHING (the self-found defect, after the fix)
  root contents before a refused s5mac:ne : [RECEIPTS.sha256]
  root contents after                      : [RECEIPTS.sha256]      byte-identical

CONTAINMENT
  no artefact ever appeared outside the root, including for ../ESCAPED
  all probe roots removed; none remain under .superpowers/sdd/
```

## 3. `cmd_macos` — the only function that changed

```bash
cmd_macos() {             # $1 root  $2 label(s2|s5mac)  $3 eq|ne  (anchor expectation)
  require_root "${1:-}"
  local label="${2-}" anchor="${3-}" f rc=0 nrc=0
  # PHASE IDENTITY: exactly two accepted pairs. Checked BEFORE any evidence write,
  # because an unrestricted label is path material and would escape the validated root.
  case "$label:$anchor" in
    s2:eq|s5mac:ne) : ;;
    *) echo "macOS phase identity must be exactly s2:eq or s5mac:ne (got '${label}:${anchor}')"; exit 1 ;;
  esac
  local files="subprocess.log named.log status.txt cache-root.txt source.sha256"
  for f in $files; do assert_absent "$EVID/$label-$f"; done
  local cache="$CAND_ROOT/build/ci-macos/CMakeCache.txt" croot mac
  [ -f "$cache" ] || { echo "no ci-macos cache at $cache"; exit 1; }
  croot=$(sed -n 's/^CMAKE_HOME_DIRECTORY:INTERNAL=//p' "$cache"); [ -n "$croot" ]
  croot=$(cd "$croot" && pwd -P)
  [ "$croot" = "$CAND_ROOT" ] || { echo "cache root $croot != candidate root"; exit 1; }
  mac=$(digest_of "$CAND_ROOT/$SRC"); [ -n "$mac" ] && [ "$mac" != "$EMPTY_HASH" ]
  if [ "$anchor" = eq ]; then [ "$mac" = "$PRE_EDIT_HASH" ] || { echo "S2 expects production UNCHANGED"; exit 1; }
  else [ "$mac" != "$PRE_EDIT_HASH" ] || { echo "S5 expects production CHANGED"; exit 1; }; fi
  # Every precondition has passed; ONLY NOW may a receipt exist. A refused phase must
  # leave the root byte-untouched, or its own assert_absent blocks the later real run.
  printf '%s\n' "$croot" > "$EVID/$label-cache-root.txt"
  printf '%s\n' "$mac" > "$EVID/$label-source.sha256"
  cd "$CAND_ROOT"
  cmake --build --preset ci-macos --target biv_subprocess_tests
  ctest --preset ci-macos -R '^subprocess$' --no-tests=error --output-on-failure \
    > "$EVID/$label-subprocess.log" 2>&1 || rc=$?
  printf 'SUBPROCESS_RC=%s\n' "$rc" > "$EVID/$label-status.txt"
  cmake --build --preset ci-macos
  ctest --preset ci-macos -R "$NAMED_ROWS" --no-tests=error --output-on-failure \
    > "$EVID/$label-named.log" 2>&1 || nrc=$?
  printf 'NAMED_RC=%s\n' "$nrc" >> "$EVID/$label-status.txt"
  for f in $files; do assert_written "$EVID/$label-$f"; record "$EVID/$label-$f"; done
  [ "$rc" -eq 0 ] && [ "$nrc" -eq 0 ] || { echo "macOS $label FAILED; evidence at $EVID"; exit 1; }
  echo "macOS $label OK; evidence at $EVID"
}
```

Two changes only, both inside this function: the `case` pair gate, and moving the two
`printf` receipt writes below every precondition. `${2-}`/`${3-}` replace `${2:?}`/`${3:?}`
so a missing argument produces the pair-gate message rather than a bash diagnostic.

Every other part of `t1_tidy_evidence.sh` — `digest_of`, `assert_absent`, `assert_written`,
`record`, `require_root`, `cmd_init`, `run_phase`, `cmd_linux`, and the dispatch `case` — is
**byte-identical to rev7 §4**, as are `phase.sh`, `s3_red_gate.py`, `s5_green_gate.py`, and
`MANIFEST` in rev7 §5. Those are separate files on disk, not text spliced into a command
string, so this is a statement about unchanged files rather than an elision inside an
executable path — the distinction that cost rev5 a cycle.

## 4. Validated before filing

```text
t1_tidy_evidence.sh   bash -n OK   + 7 must-be-NO pair arms, 2 must-be-YES controls,
                                     1 refusal-leaves-nothing check (before == after)
every fenced block re-extracted FROM THIS RELAY and re-checked
```

## 5. Unchanged, and the residual still owed

The one residual is unchanged: the S3 finding-membership predicate has been exercised only
against a **synthetic** clang-tidy-shaped log, never a real captured `clang-tidy-22` log. It
is fail-closed, and S3 is its real must-be-YES case — a mismatch there is a **gate defect to
correct and report**, never a product finding and never a reason to touch `subprocess.cpp`.

Scope unchanged, recorded for grading and **not** a grant:

```text
- src/core/support/subprocess.cpp -> in
- tests/test_subprocess.cpp       -> in
```

## 6. A process observation, offered once and not repeated

This is the eighth revision. The repair itself has not moved since rev0: seven lines in
`subprocess.cpp` and three test cases. Revisions 4 through 8 have all been defects in the
**evidence apparatus**, and they have been real ones — MR-9, MR-10, MR-13 and MR-15 each
closed a path that would have produced a false GREEN or an escaped write, and two of the
last three were found by me only because I ran the arms rather than reasoning about them.
So the rigour is earning its keep and I am not asking to shorten it.

What I would flag for the Orchestrator, without acting on it: the apparatus is now
substantially larger than the repair it gates, and each round has found its defects in the
newest layer rather than in older ones. If rev9 turns up another apparatus defect rather
than a product one, that is worth a deliberate ruling on proportionality — whether this
scaffold should be hardened once, registered, and reused across T2/T3/T4 rather than
re-derived per repair. That is the Orchestrator's call, not mine, and nothing in this plan
waits on it.

## 7. State

No source, test, harness, workflow, ref, or worktree was edited at my seat. Validation ran
`bash -n` and the arms above; three `init` probe roots were created beneath the ignored
`.superpowers/sdd/` parent and **all were removed** — none remains. Two throwaway probe
directories were created and removed. **Disclosed:** the bounded `s2:eq` must-be-YES arm
proceeded past the gate into `cmake --build --preset ci-macos` before its timeout, which ran
an incremental build inside the candidate worktree's **pre-existing** `build/ci-macos`
(`cmd_macos` hard-requires that cache to exist, so the run could not have created it);
`build/` is gitignored, and I verified afterwards that the candidate worktree is clean
(`git status --porcelain` empty) and HEAD is unchanged at `76638a0`, so the S5
archive-cleanliness assertion is unaffected. No container was started, no Docker resource
created or removed, no image built. Nothing merged, pushed, re-based, or PR-mutated; no
remote CI, publication, deployment, or release. T2/T3/T4 and the `compare.py` composition
stay held; the count-gate shape stays routed; Linux `nonzero_exit` stays owed; the Arm-1
schema act stays F+G-fenced. Merge != push != release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: edited and validated scratchpad artifacts only; ran `bash -n`, seven must-be-NO pair arms, two must-be-YES controls, a refusal-leaves-nothing check, and `git -C /Users/jack/.config/superpowers/worktrees/bivpak/s4-matrix-arm1-t1 status --porcelain` / `rev-parse HEAD` / `check-ignore build` to confirm the worktree was unaffected. Three `init` probe roots and two throwaway directories created and ALL removed. NO container started, NO ref created or moved, NO source/test/workflow edit, NO merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T1-TIDY-FIX-R8-MACOS-PHASE-IDENTITY-PAIR-GATE-20260821-033237.md` → TO `s4-matrix.implementer` for successor PLAN-REVIEW; SUPERSEDES rev7 at SHA-256 `831aba9911ea1e96a11c68b632e13b5e516f22893ebf210dc4b5f5801c153a1b`
- THIS RELAY CARRIES NO TOKEN; the bare `DISPATCH IMPL` follows only after your approve and parents to THAT approval
- MR-15 ACCEPTED on all three holes; hole 3 is the serious one — an unrestricted `label` is PATH MATERIAL, so `../ESCAPED` composes a write OUTSIDE the root `require_root` had just validated; holes 1 and 2 are mislabelled-phase receipts, both reachable because `if eq … else` mapped EVERY non-`eq` string to `ne`. Closed by one `case` over `"$label:$anchor"` accepting exactly `s2:eq` and `s5mac:ne`, placed before any evidence write
- SECOND DEFECT, MINE, FOUND WHILE VALIDATING YOURS: `s5mac-cache-root.txt` was written BEFORE the anchor assertion, so a refused phase left a receipt behind — breaking your create-nothing-on-refusal requirement AND poisoning the later legitimate run, whose own `assert_absent` would trip on it. All receipt writes moved below every precondition; re-tested, root byte-identical before and after a refusal
- ARMS ON THE REAL ARTIFACT: 7 must-be-NO (`bogus:garbage`, `s2:ne`, `s5mac:eq`, `s2:GARBAGE`, `nosuchlabel:eq`, `../ESCAPED:eq`, `:`) all refused before any write; 2 must-be-YES — `s2:eq` reached and wrote `s2-source.sha256` = `9af9d55c…` the pre-edit anchor, `s5mac:ne` passed the identity gate then correctly refused on the source anchor, showing the two gates are independent
- CONTAINMENT CONFIRMED: nothing written outside the root for any arm including `../ESCAPED`; all probe roots removed, none remain under `.superpowers/sdd/`
- DISCLOSED SIDE EFFECT: the bounded `s2:eq` arm entered `cmake --build --preset ci-macos` before its timeout, an incremental build inside the candidate worktree's PRE-EXISTING `build/ci-macos` (the command hard-requires that cache, so it cannot have created it); `build/` is gitignored and the worktree verified clean with HEAD unchanged at `76638a0`, so the S5 archive-cleanliness assertion is unaffected
- Evidence-domain validation ONLY; no product decision, source scope, analyzer identity, toolchain, Docker topology, source anchor, RED/GREEN gate, or one-root sequence changed
- RESIDUAL unchanged and still owed: the S3 predicate has met only a SYNTHETIC log; fail-closed, and S3 is its real must-be-YES case where a mismatch is a GATE defect to correct and report, never a product finding
- PROCESS OBSERVATION offered once for the Orchestrator and NOT acted on: revisions 4-8 have all been apparatus defects, each real, each in the newest layer; the scaffold is now larger than the seven-line repair it gates, and if rev9 finds another apparatus defect rather than a product one it may warrant a proportionality ruling on hardening this scaffold ONCE and reusing it across T2/T3/T4 rather than re-deriving it per repair. Nothing in this plan waits on that
- T2-T4 and `compare.py` held; count-gate routed; Linux `nonzero_exit` owed; harness-selftest separate under `201613`; schema F+G-fenced; release hold ABSOLUTE
