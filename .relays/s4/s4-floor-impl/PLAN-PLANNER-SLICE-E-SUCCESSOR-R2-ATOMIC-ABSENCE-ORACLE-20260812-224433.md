## PLAN (successor r2, slice E) — **R3 confirmed and it is the sharpest kind of defect: an oracle that cannot run.** I asked the cap+1 arm to prove no `agent_sessions` entry exists **in the image**, for a behavior whose entire point is that **no image is produced.** There is nothing to open. Replaced with the atomic-absence oracle the codebase already uses. **One precision correction to your wording, in your favour:** the absent paths are derived from the **SOURCE directory name at its parent**, not from the entry — `pack.cpp:479-480` builds `<source.parent_path()>/<name>.bvpk.partial|.spool` and `:727` renames partial→`<name>.bvpk` only at the successful end. `<entry>.bvpk` would assert a path that never exists under any outcome, so the test would pass against a broken build. Pins re-derived at THIS act.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-r2
PARENT_DISPATCH_ID: s4-slice-e-cap-carrier-routeup-charter-act-review
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — W-1 is effective and Addendum-12 rev8 is locked and VP-approved at this pin. Remaining gates are mine: this PLAN's review, token-time tuple re-verification, then merge/seal/publication/release. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
SUPERSEDED_DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R1-MUST-REVISE-NO-IMAGE-ORACLE-20260812-221451.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R1-ARCHIVEWRITEFAILED-CARRIER-BOUND-20260812-220539.md (successor r1, superseded by this relay — its carrier selection and checkpoint fix PASSED and carry forward)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: PLAN (successor r2) — cap+1 oracle replaced with atomic absence of the three source-derived output paths; carrier, checkpoints and all prior corrections carry unchanged

## 0. Pins re-derived AT THIS ACT

```text
addendum-12 @ 6eeeb157   29a5b3a3abb6777a…   == the lock's declared content        MATCH
addendum-12 @ pdc HEAD   d0e2c6eba6047c3b…   the disclosed one-hunk lock post-stamp
J           @ pdc HEAD   94b6440c6ea5342a…   UNMOVED                               MATCH
origin/main              0db8fdd             m-1 receipt STILL ABSENT -> Stage 1 BLOCKED
```

## 1. R3 — the oracle, replaced

**Why mine could not run.** J's producer-closure leg is that over any cap **no `.bvpk` is produced at all**.
My arm then asked for `no agent_sessions entry for that session … in the image` — **an assertion over an
artifact the behavior under test guarantees does not exist.** It is the same class as an unreachable warning
line: a test that reads like the remedy and can never execute. Worse than useless, because the natural
"fix" under build pressure is to weaken it or to manufacture a fixture archive to inspect.

**Measured at `0db8fdd`, the observable boundary the codebase already exposes:**

```text
pack.cpp:479-480   partial_path = source.parent_path() / (name + ".bvpk.partial")
                   spool_path   = source.parent_path() / (name + ".bvpk.spool")
                   -- `name` derives from the SOURCE DIRECTORY, never from an entry or session id
pack.cpp:498-503   cleanup_error: removes partial_path AND spool_path, returns the error
pack.cpp:727       rename(partial_path, image_path) -- the final .bvpk exists ONLY after success
tests/test_pack.cpp:683/746/877/905/932   the established precedent:
                   CHECK_FALSE(std::filesystem::exists(root / "proj.bvpk"))
```

**Your finding stands exactly; one path expression in it does not.** You wrote `<entry>.bvpk`. The archive is
named from the **source directory at its parent**, so `<entry>.bvpk` names a path that exists under **no**
outcome — success or refusal — and an absence assertion on it **passes against a completely broken build.**
That is a check blind to what it claims to measure, so I am binding the source-derived expression instead.

**The replacement oracle:**

```text
tests/test_pack.cpp — per cap, the cap+1 arm (FRESH output directory per arm)
  1. pack() returns an ERROR, not a PackReport
  2. kind == ArchiveWriteFailed
  3. detail CONTAINS the entry's original_session_id AND the cap name
  4. facts carries "entry", "cap", "limit", "observed" with correct values
  5. ATOMIC ABSENCE — all three of
       <source.parent_path()>/<name>.bvpk
       <source.parent_path()>/<name>.bvpk.partial
       <source.parent_path()>/<name>.bvpk.spool
     do NOT exist after the refusal
tests/test_pack.cpp — the matching at-cap arm
  6. SUCCEEDS and round-trips the COMPLETE entry (this is what proves the fixture is packable at the
     boundary, so arm 5's absence means "refused" and not "the fixture never packed")
tests/test_cli.cpp — actual binary, text and JSON, FRESH output directory per arm
  7. exit code == 4
  8. text: STDERR carries BOTH names.  JSON: the error object carries kind/detail/facts with both names
  9. the SAME three paths absent
```

**Why the pairing kills both mutants, stated so the reasoning is checkable rather than asserted:** a
**truncating** implementation and a **whole-over-cap-emitting** implementation both necessarily **publish an
archive**, so both fail arm 5/9; and an implementation that refuses *everything* — including at-cap — fails
arm 6. Neither mutant survives, and neither arm alone would catch both.

**One collision check I ran while binding `facts`.** `cleanup_error` routes through `with_temp_facts`
(`pack.cpp:61-67`), which does `try_emplace` on `partial_path` and `spool_path`. **`try_emplace` means a
pre-existing key WINS and the later write is silently dropped** — so a cap fact named `partial_path` would
vanish without a diagnostic. My four keys (`entry`, `cap`, `limit`, `observed`) do not collide, and the arm
asserting all four present would catch it if that ever changed. Named because M4-CG-0's duplicate-known-key
discipline is the same lesson one layer up.

**No path widens:** the correction lives entirely in `tests/test_pack.cpp` and `tests/test_cli.cpp`, both
already in scope.

## 2. Everything else carries unchanged (your PASS on R1 and R2 included)

**Carrier** (PASSED at `221451`): existing `ErrKind::ArchiveWriteFailed`, exit **4** inherited, BOTH names in
`detail` because `cli/main.cpp:34-40` prints only `kind` and `detail`, `facts` as the structured duplicate,
`path` = the entry id; **no new kind and no `error.hpp`/`error.cpp`/`envelope.cpp`/`main.cpp`/`exit_map.hpp`
change**; the route-branch if a new kind is judged necessary is **STOP and route**, never add one mid-build.
Wording states FACTS — cap, limit, observed, entry — **never a verdict that the operator's sessions are too
large**, per J's mis-pricing calibration.

**Checkpoints** (PASSED at `221451`): Stage-0 assertion REDs `1a/3/4/6` plus GREEN controls `2` arm 1, `7`
and the three claude reference controls at `0db8fdd`; rebase onto the m-1 receipt (`0db8fdd` remains the
AUDIT cut, both named); post-rebase key-2 arm 2 GREEN — a **dependency-integrity stop** if RED — plus REDs
`1b`, `4a` and atomic `5`; then the single coupled Stage 1; then all green with the actual-binary E2E.
**Compile failure earns no behavioral-RED credit; no implementation byte lands before every key it greens has
been observed failing.**

**And unchanged from before that:** the cap BASIS (outside `§A12.4.1` by its operative predicate;
`§A12.4.2` + J carry it; the rejected "typed error discharges the clause" reasoning appears **nowhere**);
all four caps (1024 / 64 / 256 / 4096, per entry, whole-entry refusal, never truncation); the three semantic
killing arms including the one that stops the ruling being over-read into "warnings are optional"; the
exhaustive six-path Stage 0 with **no production byte**; the coupled Stage 1 and why it cannot split
(transitive `child_ids` on the flat writer emits C as a DIRECT CHILD of R under J's absence license — false
data, not missing data); the m-1 stop gate; A3's four checks on ONE `codex.cpp` head carrying its ONE pin,
the five read-side literal classes **re-located at the head**, `codex/install.cpp` moving no pin, the claude
pin frozen; the E2E matrix, sandbox guards and credential decoy, **NEVER the live `~/.claude`/`~/.codex`**;
macOS plus **governing** local Ubuntu 24.04 `linux/amd64` Docker, **Actions NOT invoked**, three disclosed
divergences, the base-container control, the inherited `.github` count-gate disclosure; branch cut from
`origin/main` never local `main`; publication HELD; D-5.5(a) at hand-up; R-4.20's mint sites, MONO, M4-CG-0,
R-4.24 not ours; and the stale-`STATUS` disclosure.

**Token-time:** the seven-element tuple re-verified with **both design hashes re-derived at that moment** —
§0 is a measurement with a timestamp, not a property of this plan — and the live `d0e2c6eb` re-shown as the
disclosed one-hunk status-only post-stamp. A miss makes W-1 INAPPLICABLE / NO TOKEN.

## 3. What I am asking of you

**A plan review.** Is the atomic-absence oracle executable exactly as written — the three source-derived
paths, fresh output directory per arm, and the at-cap positive arm carrying the weight of "packable at the
boundary"? Does the mutant argument hold? Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict
line BARE — no bold, no backticks; remarks via em-dash only, per the matcher's recorded grammar). **On
approve, Stage 0 is dispatchable and Stage 1 still waits on m-1's receipt.** Merge ≠ push ≠ release; the
release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — at this filing act: re-hashed addendum-12 at `6eeeb157` (`29a5b3a3`) and pdc HEAD (`d0e2c6eb`), re-hashed J (`94b6440c`), re-measured `origin/main` (`0db8fdd`, m-1 receipt absent); and read the atomic-refusal boundary at `0db8fdd` — `pack.cpp:479-480` source-derived partial/spool paths, `:498-503` `cleanup_error` removing both, `:727` the success-only rename, `:61-67` `with_temp_facts`' `try_emplace` on `partial_path`/`spool_path`, and the existing `CHECK_FALSE(exists(...))` precedent at `tests/test_pack.cpp:683/746/877/905/932`; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`; third arm at the active dispatch root. Disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the cross-repo lineage class, cleared for this lineage by W-1 and still disclosed — no green claimed and no authority drawn from disclosure
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R2-ATOMIC-ABSENCE-ORACLE-20260812-224433.md` → `s4-floor.implementer` (plan review = slice E's plan gate); successor r1 `220539` SUPERSEDED, its PASSED carrier and checkpoint corrections carried forward
- **R3 CONFIRMED — my cap+1 arm asserted over an image the behavior guarantees does not exist.** Same class as an unreachable warning line: reads like the remedy, can never execute, and invites a manufactured fixture or a weakened assertion under build pressure
- **precision correction to the finding's wording, in its favour:** the absent paths are SOURCE-DERIVED at the source's PARENT (`pack.cpp:479-480` `<name>.bvpk.partial|.spool`, `:727` success-only rename), NOT `<entry>.bvpk` — which names a path existing under NO outcome, so an absence assertion on it would PASS AGAINST A BROKEN BUILD
- replacement oracle: error kind + both names in `detail` + four `facts` keys + **atomic absence of `<name>.bvpk`, `.bvpk.partial`, `.bvpk.spool`**, fresh output dir per arm, in-process AND actual-binary (exit 4, text stderr, JSON error object); the at-cap arm SUCCEEDS and round-trips so absence means refused, not unpackable
- **mutant argument, checkable:** truncating and whole-over-cap-emitting implementations both PUBLISH an archive and fail the absence arms; a refuse-everything implementation fails the at-cap arm; neither arm alone catches both
- **`facts` collision check run:** `with_temp_facts` (`pack.cpp:61-67`) `try_emplace`s `partial_path`/`spool_path`, and `try_emplace` means a pre-existing key WINS and the later write is SILENTLY DROPPED — my four keys do not collide, and the all-four-present assertion would catch it if that changed
- no path widens (`test_pack.cpp` + `test_cli.cpp`, both in scope); carrier, checkpoints, caps, stages, A3, E2E, Docker/Actions posture, branch mechanics and token-time obligations all carry; m-1 receipt ABSENT so Stage 1 stays blocked; release hold ABSOLUTE
