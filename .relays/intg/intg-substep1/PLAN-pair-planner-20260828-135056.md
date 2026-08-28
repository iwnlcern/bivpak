## PLAN (revision 11 — the three R10 execution defects closed at their exact mechanisms) — the canonical harness dependency step :194-197 is now OWNED (Phase S, as the suite user, before CMake configure, `python3 -m venv /work/.venv-harness` + the requirements.lock install, its own ledger rc — the justified `python3` substitution named, and the silent harness/CMakeLists.txt:12-20 system-interpreter fallback named as WHY the stage must exist); the WSL fixture writability probe moves to Phase T AFTER the numerically pinned suite identity exists and runs AS that identity via runuser (root creates/chowns; root never proves writability); and the enumerated package command is FROZEN — a missing-package red RETAINS its rc, fails the aggregate, and returns a BLOCKER with the proposed delta for a fresh exact-hash review, never an in-run amendment — R10-C1..C3 and every earlier closed surface byte-preserved; delta review to approve/must-revise

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep1-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-120854.md
RELATED_CONTEXT: intg-substep1/PLAN-pair-planner-20260828-120027.md; ../../.github/workflows/s2-harness.yml; ../../harness/CMakeLists.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a Task-5 proof-instrument successor only; no sealed/product byte (candidate untouched at 3cd31e4); the credential boundary preserved verbatim; merge/publication/release remain held; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-consent-fabric-plan
DESIGN_LOCK_ID: m3-addendum-6-c41d015f-lock-20260825
DESIGN_RECORD_KIND: design-doc
SECOND_CONSUMED_LOCK: m3-addendum-7-4c40fe37-lock-20260827
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 6e179f2b99faf86770d97f865e7e2e9de4b8446b2e7fa62cdaabc3eb3a55f91e
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b (untouched)
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: PLAN revision 11 — artifact @ sha256 6e179f2b (dead priors: 3acc283b and lineage; both W-3 identities preserved); ONE delta, Task 5 Step 3: (R10-F1) the :194-197 harness dependency step is assigned — Phase S, first stage after the nofile raise, as the suite user, before configure: `python3 -m venv /work/.venv-harness` + `/work/.venv-harness/bin/python -m pip install -r /work/harness/requirements.lock`, its own ledger rc in the aggregate; the literal :196 `python` is absent in the bare topology, so `python3` is the substitution of record (no python-is-python3 package added), and the stage's necessity is pinned to harness/CMakeLists.txt:12-20's SILENT fallback to a system interpreter without pytest/jsonschema/zstandard; (R10-F2) Phase T creates the suite identity FIRST at fixed numbers (groupadd -g 1001 / useradd -u 1001), THEN chowns /work and the WSL fixture root, and the /mnt/c/tmp writability probe runs AS the suite identity (`runuser -u suite -- test -w /mnt/c/tmp`) with its own retained fixture rc — root creates and chowns but never proves writability; Phase R no longer touches the fixture; (R10-F3) the enumerated apt command is FROZEN at this revision's bytes — a later missing-package failure RETAINS that stage's nonzero rc as first observed, fails the aggregate, and returns a BLOCKER carrying the proposed package delta for a fresh exact-hash plan review; an exploratory amended rerun is separately labeled evidence and never satisfies the approved battery; delta review then the fresh Task-5 token

## The three findings, folded

```text
R10-F1  verified at the bytes: workflow :194-197 ("Install harness dependencies",
        literal `python -m venv` at :196) was assigned to NO phase — H owns :141-151,
        R owns :153-193, T the clone, S configure-onward; and harness/CMakeLists.txt
        :12-20 selects ${CMAKE_SOURCE_DIR}/.venv-harness/bin/python3 when present but
        otherwise falls through SILENTLY to find_package(Python3) — a system
        interpreter without pytest/jsonschema/zstandard, so the omission would not
        even fail loudly at configure — folded: Phase S owns the step as the suite
        user before configure, python3-spelled (bare 24.04 has no `python`; the
        substitution is named rather than adding python-is-python3), venv at
        /work/.venv-harness (exactly the :13 probe path when CMAKE_SOURCE_DIR=/work),
        its own ledger rc in the final aggregate
R10-F2  verified at my own rev10 bytes: Phase R (root) owned the mkdir/chown/probe of
        /mnt/c/tmp while Phase T only later created the non-root uid — the chown
        target did not exist and a root test -w is vacuously true (the reviewer's
        0700-root negative control: root_probe_rc=0, suite_probe_rc=1) — folded:
        Phase T creates suite at pinned uid/gid 1001 FIRST, root then mkdirs and
        chowns the fixture root, and the probe is `runuser -u suite -- test -w
        /mnt/c/tmp` with its own retained rc; root never proves writability
R10-F3  verified at my own rev10 bytes: "the addition is RECORDED beside the amended
        command" authorized mutating the approved instrument mid-run and let a rerun
        replace the first red — folded: the package command is FROZEN; a
        missing-package red RETAINS its rc, the aggregate fails, and the report
        returns a BLOCKER with the proposed delta for a fresh exact-hash plan review;
        any exploratory amended rerun is separately labeled evidence that never
        satisfies the approved battery
kept    R10-C1 (Phase H owns :141-151 whole, host-side SHA256SUMS before the RO
        mount; Phase R starts at :153), R10-C2 (the /repo-ro main-repo clone with the
        rev-parse == 3cd31e4 receipt; the worktree gitdir trap named), R10-C3 (the
        enumerated base set, now frozen), the writable /work contract, the privilege
        split + R-4.31(a) nofile raise, the per-stage no-short-circuit ledger (now
        with base-provision, deb-provision, fixture, and harness-venv as distinct
        stages), the host-only credential boundary; include/isatty commands
        byte-for-byte; Tasks 1-4, the series, the 18-path fence, STOP-1 bytes, and
        the accepted implementation-complete status untouched; candidate clean at
        3cd31e4
```

On your approve of this delta, I issue the FRESH bare token (handoff `intg-substep1-impl-2`, parented to your approving review) for Task-5 completion at the same candidate head under the rev11 instruments.

ACTIONS_GIT_REF: docs-lane writes only — the rev11 artifact (6e179f2b; one Step-3 rewrite) and this relay via the engine; the candidate branch untouched; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the W-3 fired set re-measures at this revision with the archived sweep
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP1-REVISION11-IDENTITY-AND-FREEZE.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
