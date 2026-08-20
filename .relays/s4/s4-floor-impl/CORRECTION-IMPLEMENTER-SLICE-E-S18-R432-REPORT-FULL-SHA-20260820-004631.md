## CORRECTION — R-4.32 STOP report expanded the correct short commit prefix into the wrong full object ID; actual implementation commit is `66704714390fd45dafe43a7272262b763a91cddc`

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-floor-slice-e-r432-linux-harness-stop-sha-correction
PARENT_DISPATCH_ID: s4-floor-slice-e-r432-linux-harness-stop
IN_REPLY_TO: .relays/s4/s4-floor-impl/SITREP-IMPLEMENTER-SLICE-E-S18-R432-LANDED-MACOS-GREEN-LINUX-HARNESS-STOP-20260820-004333.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — the parent report's Linux test-failure STOP remains governing and still requires Planner disposition
FROM: s4-floor.implementer
TO: s4-floor.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: CORRECTION — preserve the 004333 report, replace only its two incorrect full-SHA expansions with the verified Git object ID; every test, scope, count, STOP, and authority statement stands

The `004333` report correctly names the implementation commit by its unique short prefix
`6670471`, but this seat then expanded that prefix without measuring the object and wrote
`66704716e819d5be3e52a1d031c62e0eb4dc25e8` twice. That 40-character value is wrong.

Fresh Git object resolution gives:

```text
git rev-parse 6670471
66704714390fd45dafe43a7272262b763a91cddc

git show -s --format='%H %s' 6670471
66704714390fd45dafe43a7272262b763a91cddc fix(schema): add EntrySchemaSkipped contracts (R-4.32)
```

Therefore the actual R-4.32 implementation commit is
`66704714390fd45dafe43a7272262b763a91cddc`. This successor corrects only the two full-SHA
expansions in the immutable parent report. Its correct short prefix `6670471`, exact
four-path scope, schema blob IDs, macOS receipt, Linux harness failure, A25/A27 STOP, and
requested Planner disposition all stand unchanged.

ACTIONS_GIT_REF: read-only Git object resolution plus this correction relay and one live-EOF INDEX row in one explicit-path coordination commit; no implementation byte, test, Docker, push, PR, GitHub Actions, merge, publication, deployment, or release
RELAY_LINT: exact correction freshness-linted before INDEX append; live INDEX EOF re-read before one append; exact correction re-linted with `--no-freshness`; inherited INDEX/root findings preserved and disclosed
FINAL_GIT_STATUS_SHORT: coordination checkout foreign untracked relay and migration history preserved and excluded; only this correction and its one INDEX append staged for this seat

CARRY LIST:
- actual R-4.32 implementation object -> `66704714390fd45dafe43a7272262b763a91cddc`
- incorrect full expansion in the immutable 004333 report -> SUPERSEDED by this correction
- every other 004333 report statement -> STANDS
- Linux harness STOP -> STANDS pending Planner disposition
