## IMPL STOP RETURN — Task 3 is frozen before staging or commit: rev10 requires writer refusal for empty `remotes[].remote`/`url`, but the retained parser accepts empty strings; enforcing the locked row narrows the writer below parser acceptance, omitting it violates the locked census, and changing the parser is expressly outside this token

ROLE: Pair Implementer
PHASE: IMPL
AUTHORITY: implementation
DISPATCH_ID: intg-substep2a-impl-2
PARENT_DISPATCH_ID: intg-substep2a-plan-review-10
IN_REPLY_TO: intg-substep2a/IMPL-pair-planner-20260902-055109.md
RELATED_CONTEXT: intg-substep2a/PLAN-pair-planner-20260902-053636.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-054431.md; ../../docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md; ../../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260830-151655.md; ../../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the locked rev10 plan and the retained parser describe different acceptance languages for empty remote name/url strings; m-1 must determine the schema truth and the pair Planner must issue an exact-hash successor plan, obtain fresh exact-byte review, and issue fresh implementation authority before any product edit, staging, replacement commit, Task 4, candidate submission, merge, push, publication, deployment, or release; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_SHA256: 63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577
LOCKED_DESIGN_COMMIT: 40b4f7a3dbfc60e5ab742678bc4e77198845c243
POST_STAMP_SHA256: 0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2
SECOND_CONSUMED_LOCK: m1-addendum-N-82293732-lock-20260827
THIRD_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 557904bee50dbf94a1f18154f9c174e23d1f475c8ef3f44bd06467ce2c464462
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996 (no rebase performed)
BRANCH: intg/format-act@9e6ebe8fca2454164051573323dd7adfa2901219 in /Users/jack/Programming/bivpak-intg-format-act; local tag retained-task3-9e6ebe8 resolves to the same sha; index CLEAN; exactly six Task-3 paths are unstaged and frozen; NOT a candidate
FROM: intg.pair-implementer
TO: intg.pair-planner
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: STOP UP — obtain an exact m-1 ruling on empty remotes strings, then a successor exact-hash plan/review/token; the current six-file patch remains uncommitted and is not byte-review-ready

## Authority consumed and stop point

The `055109` implementation grant was accepted only for Task 3 Steps 0 through 6 and Task 4 on a clean Task 3, under the exact rev10 plan digest `557904be…`. The retained head, tag, tranche-1 patch, plan digest, O lock and post-stamp, W-5 notice, and approval lineage were reverified before edits. Task 3 then proceeded test-first through the requested fallible writer, typed refusal tables, shared parser predicate, and the three bounded caller-propagation hunks.

Before staging or replacement commit, the locked plan's predicate census was compared again against the executable retained parser. That check found a schema-language contradiction. The dispatch's execution-not-amendment rule and S-FA-1 therefore fire. Work stopped immediately: no semantic choice, parser change, staging, reset, replacement commit, Task 4, candidate submission, merge, push, PR, remote CI, publication, deployment, seal, or release act followed.

## Blocking evidence — locked census and executable parser disagree

The exact rev10 plan at `docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md:115-123` says every typed-expressible parser acceptance predicate belongs in table A and specifically classifies `remotes[]` at lines 120-121 as requiring non-empty `remote`/`url`. Each table-A row must receive a writer-refusal arm.

The retained parser does not execute that predicate:

```text
src/core/manifest/manifest.cpp:41-47
required_string() checks only member presence and string type, then returns the string unchanged.

src/core/manifest/manifest.cpp:1807-1825
parse_remotes() calls required_string() for name and url and rejects only a failed expected;
it never checks either returned string for emptiness.
```

Therefore a typed JSON remote row with `name:""` or `url:""` is accepted by the retained parser.

The three available actions are mutually incompatible with the sealed execution boundary:

1. Keep `remotes-name-nonempty` and `remotes-url-nonempty` as writer refusal clauses. The writer then rejects carrier rows whose serialized image the parser accepts, narrowing the validated writer subset below the parser language and defeating the plan's O-R4 language-equality/symmetry claim.
2. Remove those two writer clauses and their negative witnesses. The implementation then omits two rows explicitly required by rev10's Step-0 census, changes the table/arm cardinality, and does not execute the reviewed plan.
3. Change `parse_remotes()` or `required_string()` to reject emptiness. That changes parser acceptance, which the `034802` correction and the implementation dispatch expressly prohibit; it would also affect other string fields if applied generically.

This is not a mechanical implementation decision. It is the S-FA-1 carrier-to-schema mismatch/defer class plus the dispatch's generic execution-not-amendment STOP. No option was selected locally.

## Frozen exact state

```text
retained HEAD: 9e6ebe8fca2454164051573323dd7adfa2901219
retention tag: retained-task3-9e6ebe8 -> 9e6ebe8fca2454164051573323dd7adfa2901219
index: empty
tranche-1 evidence patch: /tmp/bivpak-intg-substep2a.I7tq8s/tranche1-72fd3dc6.patch
tranche-1 patch sha256: 72fd3dc604957e14e944b9f7418a64f723125d8b138909e8e0bd5b045e4b22cf
frozen current patch: /tmp/bivpak-intg-substep2a.I7tq8s/task3-stop-remotes-nonempty.patch
frozen current patch sha256: fbf77f3d52b4a229d2309f45c39a62658351049db36276c6703688bd0dd88db7
candidate status: NONE — the current patch includes the unresolved non-empty clauses/tests and is not submitted
```

Exactly these six in-scope Task-3 paths are unstaged:

```text
 M src/core/manifest/manifest.cpp
 M src/core/manifest/manifest.hpp
 M src/core/pack/pack.cpp
 M tests/test_cli.cpp
 M tests/test_manifest.cpp
 M tests/test_open.cpp
```

The frozen patch contains the requested `expected<std::string>` writer surface, pre-emission validation, typed `RepoRowFacts`/violation machinery, the 42-row table A and 8-row table B, the shared parser post-build call, the three bounded caller adaptations, six FX-O leg tags, seven field tags, 50 `FX-O-INV` arms, one `FX-O-CTRL`, eight `O-MUTANT` markers, and the inherited nine named-mutant markers. Those bytes are evidence of the stopped execution only, not an approved resolution.

Focused receipts before the STOP:

```text
FX-O*: 459 assertions / 8 test cases — green
FX-N*: 134 assertions / 5 test cases — green
Manifest repos*: 269 assertions / 3 test cases — green
full dev build — green
C-3 per-file bounds at pack.cpp, test_cli.cpp, test_open.cpp — exact
```

The pre-tranche-2 baseline aggregate also completed before these edits. Product binaries were green; inherited/environment harness failures remained (`credential-env:ANTHROPIC_API_KEY`, the existing harness-e2 failure, and unavailable `readelf`). Those baseline failures are not claimed repaired and are not used to waive this product STOP.

SCOPE_DIFF (the ten-path grant; no byte outside it was changed by this seat):
- src/core/repo/classify.cpp -> in (landed predecessor; unchanged in this tranche)
- src/core/repo/types.hpp -> in (landed predecessor; unchanged in this tranche)
- src/core/repo/restore.cpp -> in (landed predecessor; unchanged in this tranche)
- src/core/manifest/manifest.hpp -> in (unstaged frozen Task-3 edit)
- src/core/manifest/manifest.cpp -> in (unstaged frozen Task-3 edit)
- tests/test_repo_engine.cpp -> in (landed predecessor; unchanged in this tranche)
- tests/test_manifest.cpp -> in (unstaged frozen Task-3 edit)
- src/core/pack/pack.cpp -> in (unstaged frozen bounded propagation edit)
- tests/test_cli.cpp -> in (unstaged frozen bounded propagation edit)
- tests/test_open.cpp -> in (unstaged frozen bounded propagation edit)
SCOPE_DIFF_RESULT: all-in

## Required ruling and resume conditions

Please route this finding to m-1 and return an exact ruling that answers one question: does the v1 parser/schema acceptance language permit empty `remotes[].remote` and `remotes[].url` strings?

- If yes, retire the two non-empty predicate rows and their refusal witnesses from a corrected plan, with the resulting exact table-A/cardinality statements.
- If no, authorize and specify the exact parser acceptance change and all affected fields/tests in a newly sealed scope; do not infer that `required_string()` should become globally non-empty.

After that ruling, resume only through a successor plan artifact with a new exact digest, fresh exact-byte Pair Implementer review, and a fresh addressed implementation token. State explicitly how O-R4 and the parser/writer language-equality proof are to be measured. The existing `055109` token is consumed at this STOP and is not authority to choose either branch.

## Escalation scan

ESCALATION_SCAN:
- authz/tenant/RLS/permissions/secrets: no — no credential value inspected or recorded
- migration/backfill/destructive-write/canonical-data-repair: no
- money/inventory/orders/planning/accounting/trust-critical-state: no
- AI-or-automation-acts-downstream: no — this remains parse/serialize reach only
- worker/scheduler/queue/retry/async-side-effect: no
- cross-repo/service-contract/generated-schema/shared-API-event: yes — sealed PDC Addendum O and the manifest parser/writer acceptance language are the disputed contract
- user-visible-control-with-materializer/downstream-consumer: yes — archive bytes and future restore behavior are user-visible, though 2b wiring remains absent
- test-runtime-role-mismatch: yes — Task 4 and Linux parity were correctly not run after the STOP
- broad-scope-expansion/ambiguous-product-semantics/residual-risk/live-verify-skip: yes — choosing empty-string validity changes the accepted schema language
ESCALATION_SCAN_RESULT: trigger-present
PRE_SCAN_PRESSURE: none
OPERATOR_WAIVER:
- status: none
- valid_waiver: no

ACTIONS_GIT_REF: no product commit; frozen unstaged evidence only on intg/format-act@9e6ebe8; this STOP report is the only docs-lane action; no Task 4, candidate, merge, push, PR, remote CI, publication, deployment, seal, or release
RELAY_LINT: to be engine-rendered; exact-file lint and root verification follow submission
FINAL_GIT_STATUS_SHORT:
 M src/core/manifest/manifest.cpp
 M src/core/manifest/manifest.hpp
 M src/core/pack/pack.cpp
 M tests/test_cli.cpp
 M tests/test_manifest.cpp
 M tests/test_open.cpp
Literal status in the isolated product worktree at freeze time; the index is empty. The primary docs checkout separately retains inherited S4 relay/docs state, untouched and not claimed clean.
