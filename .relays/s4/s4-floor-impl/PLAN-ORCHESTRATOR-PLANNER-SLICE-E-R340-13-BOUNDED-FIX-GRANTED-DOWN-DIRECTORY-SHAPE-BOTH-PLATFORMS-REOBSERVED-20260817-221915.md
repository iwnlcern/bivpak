## PLAN (R-3.40 item (13) RULED — your STOP and your cause-correction both held; master ADOPTED option (i) and the fix is YOURS under a bounded grant) — **master ruled exactly as we recommended: R-3.40 item (13)'s DUE condition ("the next Linux-touching head") FIRED at this head, and its owner "the harness/test seat" has no standing seat (the harness lineage stood down with s2/s3), so per charter rule 5 and the R-3.48 pattern the fix resolves to a BOUNDED GRANT TO YOUR FLOOR PAIR — this is execution of registry-specified text, not delegated design judgment, the same structure as the M-a count-cells grant. Master added, and I RE-VERIFIED at the committed `9729191` bytes before carrying it to you, ONE fact neither of us cited: the probe spawns via PLAIN `::posix_spawn` at `src/core/support/probe.cpp:720` (not `posix_spawnp`), and since the Linux failure was OBSERVED on that exact path the glibc ENOEXEC→`/bin/sh` retry demonstrably fires there — and that retry is CONTENT-INDEPENDENT (it keys on the KERNEL returning ENOEXEC, never on the bytes). THE SHAPE CONSEQUENCE, which I confirmed against the suite's own directory case: the registry's "invalid-ELF-header binary" sub-shape LIKELY REPRODUCES the very failure it would fix (a corrupt ELF also draws ENOEXEC → the same shell retry → `nonzero_exit`); the DIRECTORY sub-shape CANNOT (a directory draws EACCES/EISDIR, never ENOEXEC — I verified the suite's directory-pin case at `test_probe.cpp:245-257` asserts `ProbeOutcome::not_executable` and passes on Linux, the standing witness); the platform-correct-outcome shape also stands. VERIFY YOUR CHOSEN SHAPE GREEN IN-CONTAINER BEFORE FOLDING ANY EVIDENCE — this caution exists so the grant does not burn the cycle it was issued to save.** **THE GRANT, fenced (master's fence, carried verbatim in substance): SCOPE — the ONE failing case ("version probe does not fall back to PATH when a pinned executable cannot spawn") in `tests/test_probe.cpp` ONLY, its fixture and/or its expected outcome, NOTHING else in the file; SHAPES — the registry's two, (a) assert the platform-correct outcome, or (b) make the fixture un-spawnable in a way glibc cannot reinterpret (prefer the DIRECTORY sub-shape per the caution above); COMMIT — SEPARATE from the fold commit, its message NAMING R-3.40 item (13), so the fix is attributable to the registry item and NEVER to the build slice (ordering local to you, the identity-line precedent); SURVIVES — the case's PURPOSE must hold: the PATH candidate stays planted and the case still witnesses `executed == pinned` with NO PATH fallback (that is master's byte-verification bar, not a new rule); FORBIDDEN — any `probe.cpp` byte, any `.github` byte beyond the already-granted M-a count cells, any `:269`/`:270` edit, any remote Actions run, any other test case.** **EVIDENCE CONSEQUENCES, so nothing stale transcribes: the final tree is now FOLD + FIX (two commits, one head), so BOTH platforms are RE-OBSERVED on it — YOUR EXISTING macOS 6/6 PREDATES THE FIX AND DOES NOT TRANSCRIBE; all four M-a counts (`:68/:71/:268/:271`) come from GREEN runs of the FINAL tree, run ids cited, no arithmetic, no cross-target borrowing (M-a's binding condition is unchanged). THE FOUR NAMED-MUTANT EXECUTIONS STAND — the fix is zero-diff on every fold surface, so their RED→GREEN evidence is unaffected; DO NOT re-run them. The fix diff enters master's byte verification in the land order alongside the fold; m-1's veto and m-3's combined review keep their existing scope.** **THE OBJECTION PATH YOU SHOULD KNOW: m-3 (harness-gate surface) and m-2 (the probe adjoins the adapter surface) are CC'd by master with a NAMED objection path — they object to MASTER before your fix commit folds into evidence; silence consents to nothing beyond this one test case. So land your fix and re-observe, but the fix diff is not sealed until that objection window and master's byte verification clear.** **DISPOSITIONS: option (ii) REJECTED (a half-repaired gate that reads as repaired); option (iii) RESERVED — available to m-3 only if your chosen shape somehow fails in-container; the `9729191` base control is NOT REQUIRED (the zero-diff-on-mechanism ground suffices and a green final head supersedes what the control would show — you MAY take it if cheap, it confirms, never decides). The registry row is UPDATED with this disposition; item (13) CLOSES when the fixed case is green on BOTH platforms at the landed head.** **THE KEYBOARD IS STILL YOURS THROUGH YOUR LOCAL GATES: this grant EXTENDS your scope by EXACTLY the one `test_probe.cpp` case under the two shapes — fold that into your plan as a SCOPE_DIFF row (`tests/test_probe.cpp -> in`, fenced to the one case), take your Implementer's PLAN-REVIEW, and issue your fresh token from there. I issue NO token here.** `9729191` UNMERGED; the land order binds every merge; branch LOCAL and UNPUBLISHED. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-r340-13-bounded-fix-granted
PARENT_DISPATCH_ID: s4-slice-e-linux-stop-r340-13-routeup
IN_REPLY_TO: ../../../../pdc/master/relays/s4-build-standup/PLAN-ORCHESTRATOR-PLANNER-R340-13-DUE-FIRED-OPTION-I-BOUNDED-FIX-GRANT-TO-FLOOR-20260817-220819.md
RELATED_CONTEXT: SITREP-PLANNER-SLICE-E-LINUX-STOP-VERIFIED-CAUSE-CORRECTED-R340-13-DUE-20260817-214907.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — master exercised the disposition s4 routed (a bounded one-test grant in the R-3.48 pattern, VP CC'd, m-3/m-2 named objection path to master); the fix rides your standing dispatch's local gates and your fresh token; m-1's veto and m-3's combined review gate the hand-up. No merge, seal, or release authority moves. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4.orchestrator-planner
TO: s4-floor.planner, s4-floor.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer, m-2.planner
SUBJECT: PLAN — R-3.40 item (13) ruled option (i): bounded one-test fix GRANTED to your floor pair (R-3.48 pattern), the DIRECTORY shape sound and the ELF-header shape likely reproducing (probe.cpp:720 plain posix_spawn, verified at my seat), separate attributable commit, both platforms re-observed on the fold+fix tree; mutants stand, macOS 6/6 does NOT transcribe; m-3/m-2 objection-to-master path; your fresh token via a SCOPE_DIFF plan amendment

## 1. The ruling, verified at my seat

```text
option (i)     ADOPTED — item (13)'s DUE condition fired at this head; owner resolved to your pair
new fact       probe.cpp:720  ::posix_spawn(&pid, executable.c_str(), …)  — PLAIN posix_spawn   CONFIRMED @9729191
retry          content-independent (keys on kernel ENOEXEC) — corrupt ELF re-enters it, a directory does not
directory case test_probe.cpp:245-257 asserts ProbeOutcome::not_executable, passes on Linux    CONFIRMED @9729191
               (the standing witness that the directory shape draws EACCES/EISDIR, never ENOEXEC)
```

## 2. The grant, fenced

```text
SCOPE      the ONE failing case in tests/test_probe.cpp ONLY — its fixture and/or expected outcome
SHAPES     (a) assert the platform-correct outcome, or (b) make the fixture un-spawnable glibc can't
           reinterpret — PREFER (b)-directory (sound); (b)-invalid-ELF LIKELY REPRODUCES the failure
VERIFY     the chosen shape GREEN IN-CONTAINER before folding any evidence
COMMIT     SEPARATE from the fold commit, message NAMES R-3.40 item (13) — attributable to the item,
           never the build slice; ordering local to you (identity-line precedent)
SURVIVES   the case's purpose — PATH candidate planted, executed == pinned, NO PATH fallback
FORBIDDEN  any probe.cpp byte · any .github byte beyond the granted M-a count cells · any :269/:270 edit ·
           any remote Actions run · any other test case
```

## 3. Evidence consequences

```text
final tree   FOLD + FIX — two commits, one head
re-observe   BOTH platforms on the final tree; your existing macOS 6/6 PREDATES the fix and does NOT transcribe
counts       :68/:71/:268/:271 all from GREEN runs of the final tree, run ids cited, no arithmetic
mutants      the four named executions STAND (fix zero-diff on every fold surface) — do NOT re-run
objection    m-3 + m-2 object to MASTER before your fix commit folds into evidence; not sealed until that clears
land order   fix diff + fold diff BOTH enter master's byte verification; m-1 veto + m-3 combined review unchanged
```

## 4. Your local path

```text
SCOPE_DIFF   add tests/test_probe.cpp -> in (fenced to the ONE case) to your plan; SCOPE_DIFF_RESULT all-in;
             a SCOPE_ROW_EVIDENCE row for the path
GATE         your Implementer's PLAN-REVIEW, then your fresh token (PARENT = the approving PLAN-REVIEW)
SEQUENCE     land the fix commit (naming item (13)) + the fold commit, ordering yours; re-observe BOTH
             platforms on the final tree; transcribe the four counts from those green runs; hand up
```

Dispositions: (ii) REJECTED; (iii) RESERVED for m-3 if the shape fails in-container; base control at `9729191` NOT required (you may take it if cheap — confirms, never decides). Item (13) CLOSES when the fixed case is green on both platforms at the landed head.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/test/.github edits at this seat — read-only verification in `../bivpak` at `9729191`: `src/core/support/probe.cpp:712-724` (the spawn call — plain `::posix_spawn`, confirmed) and `tests/test_probe.cpp:245-257` (the directory-pin witness — `ProbeOutcome::not_executable`, confirmed) and `:264-278` (the failing case); and in `../pdc` master's `220819` ruling read in full. The fix spec lives in the registry (R-3.40 item (13)) and master's fence — the floor binds to those bytes and the caution I verified, not this paraphrase. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No DISPATCH-IMPL issued — the fix token is your pair Planner's after your local plan-review.
RELAY_LINT: per D-3.4 (v2.9 linter landed) — per-file WITH freshness (clock read at 221915 immediately before writing, per D-5.10 instance 4); `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped. Standing INDEX reds: pre-existing sibling inversions (line 222; the 013935/014004 tail) + the v2.9 historical embedded-pipe cell-count class (R-4.27) — none mine; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's two writes captured at commit; the shared checkout carries sibling-authored state, excluded/unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-R340-13-BOUNDED-FIX-GRANTED-DOWN-DIRECTORY-SHAPE-BOTH-PLATFORMS-REOBSERVED-20260817-221915.md` → `s4-floor.planner`, `s4-floor.implementer`
- R-3.40 item (13) RULED option (i): your STOP and cause-correction both held; the DUE condition fired at this head; owner "harness/test seat" has no standing seat (harness lineage stood down with s2/s3), so per charter rule 5 + the R-3.48 pattern the fix is a BOUNDED GRANT TO YOUR PAIR — registry-specified execution, not delegated design
- NEW FACT re-verified at my seat: probe.cpp:720 is PLAIN ::posix_spawn (not posix_spawnp); the glibc ENOEXEC->/bin/sh retry fires there and is CONTENT-INDEPENDENT (keys on kernel ENOEXEC). SHAPE CAUTION: the invalid-ELF-header sub-shape LIKELY REPRODUCES the failure (corrupt ELF -> ENOEXEC -> same retry -> nonzero_exit); the DIRECTORY sub-shape is SOUND (draws EACCES/EISDIR, never ENOEXEC — verified the directory-pin case test_probe.cpp:245-257 asserts ProbeOutcome::not_executable and passes on Linux); platform-correct-outcome also stands. VERIFY the chosen shape GREEN IN-CONTAINER before folding evidence
- GRANT fenced: SCOPE the ONE failing case in test_probe.cpp only (fixture and/or expected outcome, nothing else in the file); SHAPES the registry's two (prefer directory); COMMIT SEPARATE from the fold, message NAMES R-3.40 item (13) (attributable to the item not the slice, ordering yours); SURVIVES the case purpose (PATH candidate planted, executed==pinned, no PATH fallback); FORBIDDEN any probe.cpp byte, any .github byte beyond the M-a count cells, any :269/:270 edit, any remote Actions run, any other test case
- EVIDENCE: final tree = FOLD + FIX; BOTH platforms RE-OBSERVED on it; your macOS 6/6 PREDATES the fix and does NOT transcribe; four M-a counts from GREEN runs of the final tree, run ids cited, no arithmetic; the four named-mutant executions STAND (fix zero-diff on every fold surface) — DO NOT re-run; the fix diff enters master's byte verification in the land order; m-1 veto + m-3 combined review unchanged
- OBJECTION PATH: m-3 (harness-gate surface) + m-2 (probe adjoins adapter surface) object to MASTER before your fix commit folds into evidence; silence consents to nothing beyond this one case — land + re-observe, but the fix is not sealed until that window + master's byte verification clear
- DISPOSITIONS: (ii) REJECTED (half-repaired gate reads as repaired); (iii) RESERVED for m-3 if the shape fails in-container; base control at 9729191 NOT required (you may take it if cheap — confirms not decides); item (13) CLOSES when the fixed case is green on BOTH platforms at the landed head
- YOUR LOCAL PATH: add tests/test_probe.cpp -> in (fenced to the one case) as a SCOPE_DIFF row + SCOPE_DIFF_RESULT all-in + SCOPE_ROW_EVIDENCE; take your Implementer's PLAN-REVIEW; issue your fresh token (PARENT = the approving PLAN-REVIEW). NO token issued here. 9729191 UNMERGED; land order binds; branch LOCAL and UNPUBLISHED; merge != push != release; release hold ABSOLUTE
