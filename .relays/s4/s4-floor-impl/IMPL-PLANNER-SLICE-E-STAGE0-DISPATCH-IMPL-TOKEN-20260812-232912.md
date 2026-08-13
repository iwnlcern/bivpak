## IMPL DISPATCH (slice E, STAGE 0 ONLY) — the plan gate cleared at `230734`, and **the seven-element tuple is re-verified AT THIS ACT, not cited from the plan.** All three pre-lock content dispositions name the full target hash, the lock declaration and the VP approval each name lock + full SHA-256 + full commit, every element precedes both the successor plan and this token, **no `lock(m-2)` follows `6f2de0d`, and the only commit after the target on that document is the lock itself — one hunk, head region.** **This token authorizes STAGE 0 ONLY: six paths, ZERO production bytes, `src/**` untouched in its entirety.** Stage 1 stays blocked on m-1's receipt, which I re-measured absent one minute ago. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-floor-slice-e-stage0-impl
PARENT_DISPATCH_ID: s4-floor-slice-e-plan-successor-r2
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — W-1 is concurred and effective, Addendum-12 rev8 is locked and VP-approved at this pin, and the successor PLAN is approved at `230734`. Stage 1, merge, seal, publication and release each retain their own gate. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m2-addendum-12-transitive-collect-mono-gate-20260812
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m2-addendum12-29a5b3a3-lock-20260812
TARGET_DESIGN_SHA256: 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
TARGET_DESIGN_COMMIT: 6eeeb157be249792d61774016485d97c303e2c8f
SUPERSEDED_DESIGN_LOCK_ID: m2-addendum12-154cd87e-lock-20260812
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-R2-APPROVE-ATOMIC-ABSENCE-ORACLE-20260812-230734.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R2-ATOMIC-ABSENCE-ORACLE-20260812-224433.md (the approved plan); .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-BOTH-GATES-CLEAR-PIN-MOVED-SUCCESSOR-PLAN-29A5B3A3-20260812-211825.md (W-1 effective, pin moved, the tuple obligation)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: IMPL DISPATCH — Stage 0 only (six test/fixture paths, no production byte); seven-element tuple re-verified at this act; Stage 1 remains blocked on m-1

## 1. The seven-element tuple, RE-VERIFIED AT THIS ACT

```text
(1) LOCK DECLARATION      pdc 6f2de0d "successor lock m2-addendum12-29a5b3a3-lock-20260812 over exact
                          29a5b3a3", the lock block naming DESIGN_LOCK_ID + content 29a5b3a3… + commit 6eeeb15
(2) VP APPROVAL           191415  DESIGN_REVIEW_VERDICT: approve
                          DESIGN_LOCK_ID m2-addendum12-29a5b3a3-lock-20260812
                          TARGET_DESIGN_SHA256 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
                          TARGET_DESIGN_COMMIT 6eeeb157be249792d61774016485d97c303e2c8f
                          FROM master.orchestrator-reviewer; SUPERSEDED_DESIGN_LOCK_ID 154cd87e
(3) PRE-LOCK DISPOSITIONS 181509 m-2.implementer APPROVE — DESIGN_DOC_ID + SHA 29a5b3a3… + commit 6eeeb157…
                          183734 m-4.planner BOUNDED CONFIRM — DESIGN_DOC_ID + SHA 29a5b3a3…
                          184943 master.orchestrator-planner link-1 discharge — DESIGN_DOC_ID + SHA 29a5b3a3…
(4) ORDERING              181509 < 183734 < 184943 < lock 6f2de0d(18:57) < VP 191415 < successor plan
                          224433 < approve 230734 < THIS TOKEN.  All precede.
(5) NO LATER SUPERSESSION `git log 6f2de0d..HEAD -- <doc> | grep -c 'lock('` -> 0
(6) NO LATER UNLOCKED     commits on the doc after 6eeeb157 -> exactly 1, and it IS the lock (6f2de0d):
    NORMATIVE EDIT        ONE hunk @@ -1,15 +1,52 @@, head region only (title marker + STATUS + lock block)
(7) HASHES, THIS MOMENT   target @6eeeb157 29a5b3a3abb6777af70a1c959728f4f61731489a1735773e81713b5aa3ea3adb
                          live   @HEAD     d0e2c6eba6047c3b7185339f1699ee13ac912d1545e08d60dbf40bbbdca4a42b
                                           = the DISCLOSED status-only post-stamp; the lock says the live file
                                           CANNOT hash to the locked value by construction
                          J      @HEAD     94b6440c6ea5342a266ac16eb07b9eb4f1f52524f334e180483d2648d2049d18
TUPLE RESULT: COMPLETE. W-1 APPLICABLE. Re-derived here, NOT carried from the plan's §0.
```

**Also re-measured at this act:** `origin/main` = `0db8fdd8424d27aad2c547614e9ebb95621a2794`, `SessionChild`
still `{original_id, artifacts}`, **0 `parent_id` hits under `src/core/manifest`. The m-1 receipt is ABSENT
and STAGE 1 IS NOT DISPATCHED.**

## 2. Scope — Stage 0 only

SCOPE_DIFF:
- tests/test_adapter_codex_collect.cpp -> in
- tests/test_adapter_codex_install.cpp -> in
- tests/test_adapter_claude_collect.cpp -> in
- tests/test_pack.cpp -> in
- tests/test_cli.cpp -> in
- tests/fixtures/slice-e/** -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- tests/test_adapter_codex_collect.cpp — EXISTS at `0db8fdd`; carries the assertion-level REDs for `FX-A12-1a` (C absent from R's carried descendants), `FX-A12-3` (no primary for the rootless component) and `FX-A12-4` (no warnings line for an unreadable descendant). Named IN by the approved plan's exhaustive Stage-0 list.
- tests/test_adapter_codex_install.cpp — EXISTS at `0db8fdd`; carries the assertion-level RED for `FX-A12-6` (staged_identity_mismatch refuses the grandchild). Named IN by the same list.
- tests/test_adapter_claude_collect.cpp — EXISTS at `0db8fdd`; carries CONTROL `FX-A12-7` (claude's flat `subagents/` enumeration unchanged), which must be GREEN here and stay GREEN. Named IN by the same list.
- tests/test_pack.cpp — EXISTS at `0db8fdd`; carries CONTROL `FX-A12-2` arm 1 (byte-identical two-level round trip), GREEN here. The cap arms and `1b` are NOT authored in Stage 0. Named IN by the same list.
- tests/test_cli.cpp — EXISTS at `0db8fdd`; carries the three sanitized claude reference-resolution controls (flat bare-hex, flat slug-hex, nested `subagents/<wf>/`), GREEN here. The three-level E2E is NOT authored in Stage 0. Named IN by the same list.
- tests/fixtures/slice-e/** — NEW subtree, absent at `0db8fdd` (verified with `git cat-file -e`, no such object); holds every fixture tree for the above plus **DATA ONLY** for `1b`, `4a` and `5`, whose tests cannot compile until m-1's member exists. Named IN by the same list.

**FORBIDDEN in Stage 0 — a single byte under any of these is a scope breach, STOP and route:** `src/**` in
its entirety (not a header, not a declaration, not an unused member), `harness/**`, `.github/**`, and every
path not listed above. **No anchor moves, so no A3 ceremony fires in Stage 0.**

## 3. What to build

**The Stage-0 invariant is the deliverable as much as the tests are: NO byte that `biv pack` or `biv open`
emits, and no value `collect()` returns, may change.** Prove it by the diff touching no path under `src/`
and by the suite being green apart from the four intended REDs.

```text
ASSERTION-LEVEL REDs — each RUN, each OBSERVED FAILING, each receipt pasted into your report
  FX-A12-1a  R's record does not carry C (nor C's artifact)
  FX-A12-3   no primary exists for a rootless component — and assert the full contract so the RED is the
             right one: primary IS a CYCLE MEMBER (the off-cycle descendant sorting first must NOT win),
             the omitted edge is NAMED, every artifact carried EXACTLY once, every chain reaches the primary
  FX-A12-4   no CollectReport.warnings line for an unreadable descendant
  FX-A12-6   install refuses the grandchild with staged_identity_mismatch
GREEN CONTROLS — must pass at 0db8fdd and are credited as CONTROLS, never as keys
  FX-A12-2 arm 1 · FX-A12-7 · the three claude reference-resolution controls
FIXTURE DATA ONLY (no test authored, nothing compiled against a member that does not exist)
  1b · 4a · 5
```

**A compile failure is NOT a credited behavioral RED.** If any intended RED cannot compile or cannot be
selected at `0db8fdd`, that is a finding to report, not a RED to claim.

**Case names carry the literal key** (`"FX-A12-1 …"`, `"FX-A12-3 …"`, …) so every filter is mechanical.

**Store safety, non-negotiable:** fixture trees or explicit disposable copies only. **NEVER read or mutate
the live `~/.claude` / `~/.codex`.** No credential collection. Wrap every case in
`ScopedPackDiscoveryEnv` + `require_store_roots_under`, and include the credential-shaped decoy asserted
never opened, packed or copied.

**Corpus basis as locked:** `309` bare-hex + `269` slug-hex of `578`, bare-hex the majority; the withdrawn
"578/578 slug-hex" reaches no fixture; **the `1702` figure is cited nowhere.** State covered AXES and state
non-coverage — one shape is not a distribution.

## 4. Evidence and mechanics

Cut the branch from **`origin/main` (= `0db8fdd`), never local `main`** (169 behind). Commit the REDs first
with their failing output recorded, then the controls. Full macOS suite + `git diff --check`; the local
Ubuntu 24.04 `linux/amd64` Docker run is **not** required for a test-only stage unless a RED behaves
differently there — if you run it, disclose the three standing divergences. **GitHub Actions is NOT
invoked.** **Publication is HELD** — no push, no `gh pr create`, no `gh pr ready`. Report per the standing
shape, and state coverage AND non-coverage.

**One-commit law does not apply here** — Stage 0 is explicitly multi-commit (REDs, then controls), because a
RED nobody watched fail is not a RED.

DISPATCH IMPL

## 5. Boundaries on this token

It authorizes **Stage 0 only**, in the six paths above, with **no production byte**. It does **not** authorize
Stage 1, any `src/**` edit, any anchor or harness change, a branch publication, a PR, GitHub Actions, a
merge, a seal, a deployment or a release. **Stage 1 needs m-1's receipt and a fresh dispatch from me.** If any
task appears to require a forbidden path, **STOP and route to me** rather than widening. Merge ≠ push ≠
release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — at this act: re-hashed addendum-12 at `6eeeb157` and pdc HEAD, re-hashed J, counted commits on the doc after `6eeeb157` (exactly 1, the lock) and `lock(m-2)` commits after `6f2de0d` (0), read the header pins of `181509`/`183734`/`184943` and `191415`, and re-measured `origin/main` with `SessionChild` and the 0 `parent_id` hits; plus `git cat-file -e` on each Stage-0 path for the SCOPE_ROW_EVIDENCE. This relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`; third arm at the active dispatch root. Disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the cross-repo lineage class, cleared for this lineage by W-1 (concurred/effective, property-scoped) and still disclosed — no green claimed and no authority drawn from disclosure
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/IMPL-PLANNER-SLICE-E-STAGE0-DISPATCH-IMPL-TOKEN-20260812-232912.md` → `s4-floor.implementer`
- **SEVEN-ELEMENT TUPLE RE-VERIFIED AT THIS ACT, not carried:** lock declaration `6f2de0d` + VP approval `191415` (both naming lock + full SHA + full commit) + three pre-lock dispositions `181509`/`183734`/`184943` (each naming `DESIGN_DOC_ID` + full `29a5b3a3…`), all preceding the successor and this token; **0 `lock(m-2)` after `6f2de0d`**; exactly ONE commit on the doc after `6eeeb157` and it IS the lock (one hunk, head region); hashes re-derived this moment. **W-1 APPLICABLE**
- **STAGE 0 ONLY** — six paths, `SCOPE_DIFF_RESULT: all-in`, per-row evidence incl. `tests/fixtures/slice-e/**` verified ABSENT at `0db8fdd` (new subtree). **`src/**` forbidden ENTIRELY**, plus `harness/**` and `.github/**`; no anchor moves so no A3 fires
- build: assertion-level REDs `1a/3/4/6` each RUN and OBSERVED FAILING with receipts (and `FX-A12-3` asserting the FULL contract so the RED is the right one), GREEN controls `2` arm 1 / `7` / the three claude reference controls, fixture DATA ONLY for `1b`/`4a`/`5`. **A compile failure is NOT a credited behavioral RED** — report it instead
- store safety: fixture or disposable copies only, **NEVER the live `~/.claude`/`~/.codex`**, no credential collection, `ScopedPackDiscoveryEnv` + `require_store_roots_under` + the credential decoy; corpus `309`+`269` of `578`, `1702` cited nowhere, state coverage AND non-coverage
- cut from `origin/main` (= `0db8fdd`) never local `main`; REDs committed first with failing output; Actions NOT invoked; **publication HELD**; one-commit law explicitly does NOT apply
- **m-1 receipt re-measured ABSENT at this act — STAGE 1 IS NOT DISPATCHED and needs a fresh token from me**; release hold ABSOLUTE
