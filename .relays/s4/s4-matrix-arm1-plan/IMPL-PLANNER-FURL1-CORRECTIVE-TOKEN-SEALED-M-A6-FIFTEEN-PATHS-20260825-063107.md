## IMPLEMENTATION TOKEN — F-URL-1 fenced bounded corrective: fifteen IN paths with measured preimages, the sealed bytes as the sole authority, one commit, both platforms

ROLE: Planner
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: s4-matrix-furl1-corrective-impl-token
PARENT_DISPATCH_ID: s4-matrix-furl1-corrective-plan-review-r2
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-FURL1-CORRECTIVE-R2-APPROVE-FOOTER-MEASURED-CARRY-SELF-ROUTED-20260825-062319.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-FURL1-CORRECTIVE-R2-FOOTER-MEASURED-CARRY-SELF-ROUTED-20260825-061535.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
DESIGN_DOC_ID: m3-addendum-6-20260824
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m3-addendum-6-ae7ca0b2-lock-20260825
LOCKED_DESIGN_SHA256: ae7ca0b24a85d296e12ade58219dc651e95f10191684c421c3f2a5a87473c883
POST_STAMP_SHA256: 9d2a915c874ce5fa90902868610ae98bdf64f7b1b3607447a77f366b0733f295
CONSUMED_CONTRACT: m1-addendum-M-20260823 (4a61da224cce34a6084a4a6a39b231c98c325b5bdc671d28d70add52a43913e9)
SECOND_CONSUMED_CONTRACT: m4-sr-url-family-20260823 (a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798)
HUMAN_GATE_REQUIRED: no new operator gate — this token spends the R2 plan gate approved at `062319` under master's `051923` authorization and the operator's standing 2026-08-23 directive. It authorizes product/test/schema edits ONLY inside the fifteen scope rows below. It authorizes NO merge, push, PR mutation, remote CI, publication, deployment, or release, and NO scope widening. Any STOP halts before the next obligation and routes to this seat. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
AUTHORIZING_PLAN: `s4-matrix-furl1-corrective-impl-plan-r2`, blob `c2a03978184a77d8ccb26be9e6cef7ad1b305a69`, SHA-256 `a8430f31d1fd8a86f4e0302ae07bc41b1dc75aeb95fbf009bf649494842238d9`, commit `68de9e03399e209a05bb1b4bb2059b09aa6f1e47`
AUTHORIZING_REVIEW: `PLAN-REVIEW-IMPLEMENTER-FURL1-CORRECTIVE-R2-APPROVE-FOOTER-MEASURED-CARRY-SELF-ROUTED-20260825-062319.md`, commit `03e5d94`, `VERDICT: approve`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner, m-4.planner
SUBJECT: Bare implementation token for the F-URL-1 corrective — fifteen IN paths each with a measured base preimage; the sealed M + A6 bytes are the sole authority and this token reproduces no golden text; A6-R1's one-commit rule, the 33 legs / 37 markers, both-platform local CI, and all four fence families ride unchanged

I re-derived the gate at my seat before issuing. `plan_review_approved` returns True on the
approval bytes and False on a trailing-period control, so the verdict separates rather than merely
reads. The R2 identity the approval cites re-derives exactly here — blob
`c2a03978184a77d8ccb26be9e6cef7ad1b305a69`, SHA-256
`a8430f31d1fd8a86f4e0302ae07bc41b1dc75aeb95fbf009bf649494842238d9`, commit
`68de9e03399e209a05bb1b4bb2059b09aa6f1e47`. Holder counts: the approving review 1, the authorizing
plan 1, this token's own id 0 before this relay.

SCOPE_DIFF:
- src/core/repo/git_exec.hpp -> in
- src/core/repo/git_exec.cpp -> in
- src/core/repo/types.hpp -> in
- src/core/repo/eligibility.cpp -> in
- src/core/repo/restore.cpp -> in
- src/core/report/exit_map.hpp -> in
- src/core/report/envelope.cpp -> in
- src/cli/args.cpp -> in
- src/cli/main.cpp -> in
- schemas/biv-json-envelope.v1.schema.json -> in
- schemas/biv-exit-map.v1.json -> in
- tests/test_envelope.cpp -> in
- tests/test_cli.cpp -> in
- tests/test_repo_engine.cpp -> in
- harness/selftest/test_envelope.py -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- src/core/repo/git_exec.hpp -> preimage at 6ba01ef 2500 bytes SHA-256 523e13186cb4bc7d9e6eb12b0a64ea0f56c8c6819068b30f3fc54c4052d87f0a; M-R4's typed endpoint carrier on GitInvokeOptions
- src/core/repo/git_exec.cpp -> preimage at 6ba01ef 10844 bytes SHA-256 cfd9c69e2396ef7486156f645ad8f5c859181f29b0b0351c767fefa4e96f7cbf; the ONE class-keyed check before spawn at the existing GitCallClass switch, resolution, comparator, hook
- src/core/repo/types.hpp -> preimage at 6ba01ef 6253 bytes SHA-256 744ba6c694b984a8f88a04828e293900e5a8b7ef6e0bdcc8ab90cc25db180f18; the new snake_case EngineErrorKind member url_divergence_refused
- src/core/repo/eligibility.cpp -> preimage at 6ba01ef 8085 bytes SHA-256 d06af9cb04fea8eeade594481712c99ad24939661009010e0ded015f882a622d; carrier population at the pack outbound site, per-remote grain, no laundering into a downgrade
- src/core/repo/restore.cpp -> preimage at 6ba01ef 19919 bytes SHA-256 a3fb265816822427d30795807665574a6341dc934740e9d3d7d4002dcbb6258b; carrier population at the three restore outbound sites
- src/core/report/exit_map.hpp -> preimage at 6ba01ef 320 bytes SHA-256 974a5ae7ea3789827cf983cde0e537bce6d44c1454b6bb5d7cda608aa5104e1c; the two ErrKind rows and exit_for_error consumption
- src/core/report/envelope.cpp -> preimage at 6ba01ef 15872 bytes SHA-256 064366d9df73c066bcb29b65d9efde2f6ab15de7bc4eed3d6ec13d5c5cbe40b7; the three A6-R1 emission sites and their presence predicates
- src/cli/args.cpp -> preimage at 6ba01ef 8080 bytes SHA-256 3854160109a2a10b583fd97c9f899facbd145323d0ea319e3d2b21db79c1c5cc; the flag in the residual grammar and the one new help line's exact placement
- src/cli/main.cpp -> preimage at 6ba01ef 15934 bytes SHA-256 a0b473ce830ac11898e7662f5f7d59884fbbfc9b842fba28b4d8ea13d0bfec9a; the hook implementation, rendering, and the widened exit composition
- schemas/biv-json-envelope.v1.schema.json -> preimage at 6ba01ef 8142 bytes SHA-256 d9c8bf206c5c5312ec122cf4db02583f9866c834c3760132a12a3ab377de879c; the three A6-R1 schema sites, same commit
- schemas/biv-exit-map.v1.json -> preimage at 6ba01ef 2086 bytes SHA-256 2de0b4e8562d1dbabe537f019fc41de1c5e8cd64bf00a47f76ed239aeaa07bc5; both exit-map rows, same commit
- tests/test_envelope.cpp -> preimage at 6ba01ef 34647 bytes SHA-256 2033e65c8efdbb2e51daeeef774e86139000568c7d7a9311fc62153b86bc2b58; the two parity rows via the template and exit_for_error, never a copied literal
- tests/test_cli.cpp -> preimage at 6ba01ef 85620 bytes SHA-256 c9ff1ac77152b783bc042155f5d9dba3441388050575bfd38061450cd6385e93; the byte-whole open --help golden, instrument home of the preserved --agent-bin line
- tests/test_repo_engine.cpp -> preimage at 6ba01ef 54027 bytes SHA-256 1dd44d5ce09b682f97b991b7edcef10eda4688e9ddc07ea4add0b319f5aee98c; engine-side fixture legs
- harness/selftest/test_envelope.py -> preimage at 6ba01ef 1595 bytes SHA-256 f62fb9fa8f8c2e2c515a69c4580ecb9a27d3cf1d4464343007f403e85e953737; BOTH CURRENT_LOCKED_SCHEMA_BLOBS pins RECOMPUTED from the landed schema bytes, same commit

## The authority is the sealed bytes, not this token

Read and implement from the sealed documents at the hashes their locks declare. This token
reproduces NO golden text, prompt, template, grammar line, or schema fragment, for the same reason
the plan does not: every one is byte-golden and fenced, and a second copy is a second thing that
can drift.

```text
A6  master/domains/m-3-restore-cli/design/2026-08-24-addendum-6-url-consent-consumer-surface.md
    sha256 9d2a915c874ce5fa90902868610ae98bdf64f7b1b3607447a77f366b0733f295
M   master/domains/m-1-format-engine/design/2026-08-23-ADDENDUM-M-url-effective-endpoint-consent.md
    sha256 4a61da224cce34a6084a4a6a39b231c98c325b5bdc671d28d70add52a43913e9
SR  master/domains/m-4-hostile-image/design/2026-08-23-sr-url-effective-endpoint-consent.md
    sha256 a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798
```

Re-hash all three at your seat before the first edit. If any differs, STOP.

## Obligations, unchanged from the approved plan

```text
O-1  the 33 fixture legs implemented AS SEALED — M's (a)–(o) with 12 markers, A6's (a6.1)–(a6.18)
     with 25. EACH named mutant SHOWN to RED at its own leg; a marker whose mutant is not
     demonstrated is an unwitnessed correction. No "OR" in a requested form; one coordinate per
     discriminating arm.
O-2  ONE COMMIT per A6-R1: code + both exit-map rows + all three schema sites + the two parity
     rows via template and exit_for_error + BOTH selftest pins recomputed from landed bytes.
O-3  LOCAL CI GREEN BOTH PLATFORMS — macOS ci-macos; Linux disposable Ubuntu 24.04 linux/amd64
     with --init and nofile soft raised to the inherited hard limit. Remote CI is NOT evidence
     and must not be triggered. Linux residuals classified against R-4.35; anything outside STOPS.
     No whole-suite-green claim.
O-4  fail-safe PROVEN: M leg (g), absent hook must REFUSE.
O-5  class closure by POPULATION: (a)+(b)+(i)+(j) with (k) the carrier invariant; the two-of-four
     and three-of-four per-site mutants each RED at their own leg.
O-6  non-persistence WITNESSED across runs: A6 leg (a6.13).
O-7  byte-exactness of every golden surface asserted against the SEALED BYTES, never against any
     relay.
```

## Fences and the execution rule

m-1's vetoes 1–8; m-3's V-A6-1..5 including the double-anchored envelope veto; m-4's triggers
(any auto-classification, any persistence, any equivalence widening = STOP); A6-R1's one-commit
rule. None relaxable by you, by me, or by agreement between us.

Execute where the sealed texts determine. Where they defer or are silent, STOP and route up
through me — the owning seat owns the answer. **A disagreement with a sealed byte is a STOP, not
an edit.** M-R7's four STOPs and A6-R7's four STOPs are the pre-stated routes.

Verify each cited locus at the base as you touch it. The sealed docs' CLI pin `b9bbdd8` is NOT an
ancestor of `6ba01ef`; do not resolve it, and do not read its absence as drift. A locus that does
not match at the base is a STOP, never a silent re-anchor.

Not in scope: any sealed text, any surface A6 does not cut, PROMPT A/B/C, the `bundle`/`local`
classes, `.github/` (the R-4.38 count-gate repair is m-3's parallel pre-merge gate), T1/T2/T3
bytes, the stage-5 report. Merge is not push and neither is release; the release hold is ABSOLUTE.

DISPATCH IMPL

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, schema, branch, ref or worktree moved and no candidate exists beyond base `6ba01ef`. Read-only at my seat: `plan_review_approved` measured True on the approval bytes with a trailing-period must-be-NO control returning False; unique dispatch-holder counts for the approving review, the authorizing plan, and this token's own id; re-derivation of the R2 blob, SHA-256 and commit; and `git cat-file -s` plus `git show | shasum -a 256` preimages for all fifteen IN paths at the base. No merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `src/`, `tests/`, `harness/`, `schemas/`, `CMakeLists.txt`, `.github/` is empty; the shared checkout carries 31 pre-existing sibling-authored untracked relay paths, preserved and unclaimed
RELAY_LINT: all three arms before commit — exact-file WITH freshness; `--index` error set path-normalized and diffed against the pre-append blob; `--relay-root` run PRESENT and MOVED ASIDE with the delta MEASURED and reported by class, not asserted identical. Predicates measured on the finished bytes with the relocated linter, and `operational_token_text` confirmed to carry exactly ONE live bare token. Commit executed as a SEPARATE step after these gates reported.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/IMPL-PLANNER-FURL1-CORRECTIVE-TOKEN-SEALED-M-A6-FIFTEEN-PATHS-20260825-063107.md` → TO `s4-matrix.implementer`
- BARE TOKEN ISSUED to `s4-matrix.implementer`, parented to the APPROVING PLAN-REVIEW `s4-matrix-furl1-corrective-plan-review-r2` at commit `03e5d94` — never to the plan and never to the orchestrator dispatch. Verdict canonicality MEASURED not read: `plan_review_approved` True on the bytes, False on a trailing-period control. R2's identity re-derives exactly (blob `c2a03978…`, SHA-256 `a8430f31…`, commit `68de9e03…`); holder counts are review 1, plan 1, this token id 0 before filing
- FIFTEEN IN PATHS, each with a MEASURED base preimage and its sealed purpose: `git_exec.hpp` 2500B, `git_exec.cpp` 10844B, `types.hpp` 6253B, `eligibility.cpp` 8085B, `restore.cpp` 19919B, `exit_map.hpp` 320B, `envelope.cpp` 15872B, `args.cpp` 8080B, `main.cpp` 15934B, `biv-json-envelope.v1.schema.json` 8142B, `biv-exit-map.v1.json` 2086B, `test_envelope.cpp` 34647B, `test_cli.cpp` 85620B, `test_repo_engine.cpp` 54027B, `harness/selftest/test_envelope.py` 1595B. `SCOPE_DIFF_RESULT: all-in`
- THE AUTHORITY IS THE SEALED BYTES AND NOT THIS TOKEN: A6 `9d2a915c…`, M `4a61da22…`, SR-URL `a2f777c2…` — RE-HASH ALL THREE AT YOUR SEAT BEFORE THE FIRST EDIT and STOP on any difference. This token reproduces NO golden text, prompt, template, grammar line or schema fragment, for the same reason the plan does not: every one is byte-golden and fenced, and a second copy is a second thing that can drift
- OBLIGATIONS unchanged from the approved plan: O-1 the 33 legs AS SEALED with EACH named mutant SHOWN to RED at its own leg; O-2 the ONE-COMMIT rule in full including BOTH selftest pins recomputed from landed bytes; O-3 local CI green on BOTH platforms with Linux under `--init` and the `nofile` lift and remote CI explicitly NOT evidence; O-4 fail-safe PROVEN via leg (g); O-5 class closure by POPULATION with the per-site mutants each REDding at their own leg; O-6 non-persistence WITNESSED across runs; O-7 byte-exactness asserted against the SEALED BYTES never against any relay
- FENCES none relaxable by you, by me, or by agreement between us: m-1 vetoes 1–8; m-3 V-A6-1..5 with the double-anchored envelope veto; m-4's triggers; A6-R1's one-commit rule. EXECUTION NOT AMENDMENT — execute where the sealed texts determine, STOP and route up through me where they defer or are silent, and A DISAGREEMENT WITH A SEALED BYTE IS A STOP, NOT AN EDIT
- VERIFY EACH CITED LOCUS AT THE BASE as you touch it: the sealed docs' CLI pin `b9bbdd8` is NOT an ancestor of `6ba01ef`, so do not resolve it and do not read its absence as drift; a locus that does not match at the base is a STOP, never a silent re-anchor
- NOT IN SCOPE: any sealed text, any surface A6 does not cut, PROMPT A/B/C, `bundle`/`local` classes, `.github/` (the R-4.38 count-gate repair is m-3's PARALLEL pre-merge gate), T1/T2/T3 bytes, the stage-5 report. No merge, push, PR mutation, remote CI, publication, deployment or release rides this token and no scope widening is authorized. On green under the fences AND both owners' byte reviews T4 FINAL releases; R-4.43 stays release-gating until m-4's sign-off; the merge remains the operator's knowing call. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; release hold ABSOLUTE
