## PLAN (revision 10 — the three R9 execution defects closed at their exact mechanisms) — Phase H now OWNS canonical :141-151 (the download loop AND the SHA256SUMS derivation/strict check, both completing host-side BEFORE the asset dir mounts read-only) with Phase R starting at :153; the clone source is the READ-ONLY MAIN-REPOSITORY bind at /repo-ro via --no-hardlinks (the linked worktree's host-absolute gitdir pointer named as the trap it is); and the bare-24.04 base set is ENUMERATED as one executable apt command derived from the build system's own bytes, with its own ledger rc and a record-not-silence rule for any amendment — R9-C1..C3 and every earlier closed surface byte-preserved; delta review to approve/must-revise

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep1-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-115204.md
RELATED_CONTEXT: intg-substep1/PLAN-REVIEW-pair-implementer-20260828-113259.md; ../../.github/workflows/s2-harness.yml; ../../CMakeLists.txt; ../../CMakePresets.json
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
PLAN_LOCK_ID: intg-substep1-plan-20260827 @ sha256 3acc283bd9f346d9a7a11e8ce304fc5035a9329de300de4056d8ddcf3b952000
BASE: main@02b51435a5b50363df7f595dd827af107424b0c3
BRANCH: intg/consent-fabric@3cd31e4823d40c1c9ea020fcb51917618368533b (untouched)
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-3.implementer
SUBJECT: PLAN revision 10 — artifact @ sha256 3acc283b (dead priors: c89e408a and lineage; both W-3 identities preserved); ONE delta, Task 5 Step 3: (R9-F1) Phase H owns :141-151 whole — SHA256SUMS derived and strict-checked HOST-SIDE before the read-only mount; Phase R begins at :153, the first read-only-safe operation; (R9-F2) clone source = the read-only MAIN-repo bind /repo-ro with --no-hardlinks (the linked worktree's gitdir: pointer is host-absolute and container-invisible — named in the text so nobody re-trips it), rev-parse receipt kept; (R9-F3) the bare-24.04 base set enumerated as ONE executable command — ca-certificates git g++ make cmake python3 python3-venv python3-pip libsqlite3-dev binutils zstd — each package tied to the build system's own bytes (system SQLite3 CMakeLists:4, FetchContent network :14-32, objcopy :205, default Makefiles, harness venv, the Linux runtime zstd binary), its rc a distinct ledger entry, any later missing-package amendment RECORDED beside the amended command; WSL fixture root provisioning added at root (:198-202 semantics); delta review then the fresh Task-5 token

## The three findings, folded

```text
R9-F1  verified at the workflow bytes: :149-150 derive and WRITE SHA256SUMS into the
       asset dir, :151 strict-checks it — impossible on a read-only bind, and my
       "exactly :141-147" boundary contradicted my own host verification — folded:
       Phase H owns :141-151 whole (download + derivation + strict check, host-side,
       BEFORE the read-only mount); Phase R begins at :153
R9-F2  verified: the candidate worktree's .git is `gitdir: <host-absolute path>` —
       invisible in-container, so the /src-ro clone could never see a repository —
       folded: bind the MAIN repository read-only at /repo-ro (its common .git holds
       the branch); `git clone --no-hardlinks --branch intg/consent-fabric /repo-ro
       /work`; the rev-parse == 3cd31e4 receipt kept; the worktree-pointer trap
       named in the text
R9-F3  verified: bare 24.04 ships none of git/cmake/g++/python3, and the workflow's
       apt lines install only ca-certificates + the debs because the hosted runner
       presupplies the toolchain — folded: the enumerated one-command base set (each
       package justified from the build system's own bytes: system SQLite3 per
       CMakeLists:4; FetchContent simdjson/zstd/catch2 need git+network+ca-certs per
       :14-32; objcopy per :205 -> binutils; default generator -> make; g++; the
       harness venv -> python3/python3-venv/python3-pip; the Linux runtime zstd
       binary the E2 verbs require), captured as its OWN ledger rc, with the
       record-not-silence amendment rule; the WSL fixture root (:198-202 semantics)
       provisioned by root in Phase R
kept   R9-C1 (writable /work + exact-tree receipt), R9-C2 (privilege split + nofile
       raise + ledger), R9-C3 (host-only credentials + all earlier closed proof
       contracts); include/isatty commands byte-for-byte; Tasks 1-4, the series, the
       18-path fence, STOP-1 bytes, and the accepted implementation-complete status
       untouched; candidate clean at 3cd31e4
```

On your approve of this delta, I issue the FRESH bare token (handoff `intg-substep1-impl-2`, parented to your approving review) for Task-5 completion at the same candidate head under the rev10 instruments.

ACTIONS_GIT_REF: docs-lane writes only — the rev10 artifact (3acc283b; one Step-3 rewrite) and this relay via the engine; the candidate branch untouched; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the W-3 fired set re-measures at this revision with the archived sweep
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP1-REVISION10-EXECUTABLE.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
