## SITREP — the three nits triaged BY MEASUREMENT, not carried: all three confirmed at the bytes, nit (3)'s premise verified and its blast radius bounded smaller than feared, nit (4) is sharper than reported — the field is not merely unread, it is never written either

ROLE: Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t4-three-nits-triaged
PARENT_DISPATCH_ID: s4-matrix-wave-a-t4-panel-adjudicated
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T4-PANEL-ADJUDICATION-RECEIPTED-FURL1-HELD-NITS-CARRIED-20260823-005742.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-R438-INVENTORY-PLUS-COUNT-GATE-WOULD-RED-AT-MERGE-NOT-GREEN-ROUTED-UP-20260823-011248.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate and no code change requested. This discharges the triage the Implementer receipt handed to this seat and fixes the stage-5 record with measured severities. Nit (4)'s ownership question routes UP. No merge, push, PR mutation, remote CI, schema act, publication, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: authorized pre-edit T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: local T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` — unchanged by this relay
FROM: s4-matrix.planner
TO: s4.orchestrator-planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: Three nits triaged at the bytes — (2) confirmed low, mislabels without losing; (3) CONFIRMED with its discover premise verified, but it is the ONLY direct .git/ join in the engine and boundary has NO consumer, so it is a wrong RECORD not a broken restore, with ZERO gitlink test coverage; (4) CONFIRMED SHARPER — capture_env and its two fields appear ONLY as declarations in types.hpp and are neither written nor read anywhere in src/

## Why I measured rather than carried

Both upstream seats said plainly they did not deep-verify these: the Orchestrator marked them
"lens-reported, I did not deep-verify these", and the Implementer receipt "does not deep-verify,
fix, or assign them". That is correct conduct at both seats. It also means that until now nobody
had checked them, and a nit carried unexamined into a merge-readiness report becomes a claim the
operator reads as established. Triage is this seat's, so I measured all three.

## Nit (2) — `git_exec.cpp:222-224`, CONFIRMED, low

```cpp
const auto detail = git_bytes(result.stderr_bytes) + git_bytes(result.stdout_bytes);
return detail.find("missing object")  != npos || … ||
       detail.find("unable to read")  != npos ||   // :222
       detail.find("bad object")      != npos ||   // :223
       detail.find("invalid object")  != npos ||   // :224
```

Confirmed as described: unanchored `find()` over **concatenated stderr and stdout**, so any
occurrence anywhere in either stream flips the classification. Under `promisor`, a genuine
object-store corruption whose message contains one of those substrings is reclassified as
`promisor_objects_unavailable`.

**Severity LOW and I agree with the lens: it mislabels, it does not lose.** The failure is still a
failure; only its typed reason is wrong. No further action proposed.

## Nit (3) — `classify.cpp:344`, CONFIRMED, and its premise verified

The nit rests on a premise nobody had checked: that a gitlink `.git`-FILE checkout actually
reaches `classify`. **It does.** `discover.cpp` accepts either shape, in both of its acceptance
sites:

```text
discover.cpp:62-63   is_directory(marker_status) || is_regular_file(marker_status)
discover.cpp:90-91   is_directory(marker_status) || is_regular_file(marker_status)
```

And the read is exactly as reported — a direct path join, not `git rev-parse --git-path shallow`:

```cpp
const auto shallow_file = repo / ".git/shallow";   // classify.cpp:344
std::ifstream input{shallow_file};
```

For a linked worktree or submodule, `.git` is a file containing a `gitdir:` pointer, so
`repo/".git/shallow"` does not exist. `ifstream` on a missing path yields no lines **and no
error**, so the record becomes `shallow: true, boundary: {}` — wrong, plausible, and silent.

Two measurements that move this away from where the panel left it, one in each direction:

- **Smaller than "a class."** `classify.cpp:344` is the **ONLY** direct `".git/"` path join
  anywhere in the repo engine — I checked `classify`, `capture`, `restore`, `eligibility`,
  `discover`, `git`, and `git_exec`. One line, one fix surface. Framing it as a pervasive class
  would overstate it.
- **Bounded blast radius.** `Shallow::boundary` occurs only in `classify.cpp` (where it is
  written) and `types.hpp:145` (where it is declared). **No restore-side consumer reads it in
  this tree.** So today this is a wrong recorded value, NOT a restore that reconstructs the wrong
  shallow state. I would rather say that than let "the shallow boundary is wrong" imply a
  breakage it does not currently cause.

**But the reason it survived is the part worth carrying: ZERO test coverage.** No file under
`tests/` writes a `gitdir:` pointer at all, so no test ever exercises a gitlink checkout through
discovery. Same family as the T3 stage-4 gitlink `.git`-file finding, and they should carry
together as the Orchestrator said — the shared root is an untested repo shape, not two unlucky
lines.

**Severity: LOW today, on the strict condition that `boundary` stays unconsumed.** The moment any
restore path reads it, this becomes correctness. That conditional is the finding.

## Nit (4) — `restore.cpp`, CONFIRMED and SHARPER than reported

The nit says `capture_env` (`core.autocrlf`/`core.filemode`) is unused in restore-verify. Measured
across every `.cpp` and `.hpp` under `src/`, the three identifiers appear in exactly one file:

```text
types.hpp:163   std::optional<std::string> core_autocrlf;      declaration
types.hpp:164   std::optional<bool>        core_filemode;      declaration
types.hpp:173   CaptureEnvironment         capture_env;        declaration
```

No other occurrence anywhere in `src/`. **So it is not merely unread by restore-verify — it is
never written either.** The struct is unwired in both directions, which is a strictly stronger
statement than the lens made and worth correcting in the record.

Meanwhile `verify_restored` (`restore.cpp:310`) does require a clean tree via
`git status --porcelain=v2 -z` (`:340-342`) with no EOL or filemode compensation. So the exposure
the nit describes is real, and the data that could have compensated for it is not merely ignored,
it does not exist at runtime.

**Severity: LOW-to-MEDIUM and, more importantly, UNOWNED.** The Orchestrator flagged it as
"possibly the T5 payload layer's" and the Implementer left ownership unresolved. An unwired field
plus an uncompensated verify is a design question about where EOL/filemode normalization belongs,
which is above this pair. **I route the ownership question UP and prescribe nothing.**

## Disposition for stage-5

```text
(2) git_exec.cpp:222-224  LOW        mislabels, does not lose; no action proposed
(3) classify.cpp:344      LOW*       *conditional: LOW only while Shallow::boundary has no
                                     consumer; ONE line, the only direct .git/ join in the
                                     engine; ZERO gitlink test coverage; carry with the T3
                                     stage-4 gitlink finding as one untested-repo-shape item
(4) restore.cpp           LOW-MED    field unwired BOTH ways, not just unread; verify has no
                                     EOL/filemode compensation; OWNERSHIP ROUTED UP
```

All three are disclosed, none blocks T4, and none is a defect in the authorized NSDMI fix — that
delta remains exactly the three fenced files the panel cleared. I propose no code change and
touched no product byte.

T1 `00c06d9`, T2 `7688bbd`, T3 `70601fc` FINAL; T4 IMPLEMENTED at `6ba01ef`, panel-adjudicated,
FINAL held pending master's F-URL-1 disposition. My R-4.38 count-gate finding at `011248` remains
open above this seat. Merge is not push and neither is release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no product, test, workflow, branch, ref or worktree moved, and `6ba01ef` is untouched by this relay. Read-only at my seat: `git show` of `git_exec.cpp:214-230`, `classify.cpp:338-352`, `discover.cpp` acceptance sites, `restore.cpp:310-342` and `types.hpp:145/:163-173` at the candidate; a repo-engine-wide scan for direct `".git/"` path joins; a `src/`-wide scan for `capture_env`/`autocrlf`/`filemode` and for `Shallow::boundary` consumers; and a `tests/`-wide scan for any `gitdir:` pointer fixture. No merge, push, PR mutation, or remote CI. Docs lane: this relay and its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt`, `.github/` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: all three arms before commit — exact-file WITH freshness; `--index` error set path-normalized and diffed against the pre-append blob; `--relay-root` run with this relay present AND moved aside, requiring identical error sets. `substantive_actions_ref` and `implementation_work_claimed` measured False; `operational_token_text` carries no bare token. INDEX tail re-read for NEW INBOUND addressed to this seat, not only for monotonicity.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-THREE-NITS-TRIAGED-AT-BYTES-NIT3-CONFIRMED-NIT4-SHARPER-SEVERITIES-BOUNDED-20260823-032615.md` → TO `s4.orchestrator-planner`, `s4-matrix.implementer`
- WHY MEASURED RATHER THAN CARRIED: the Orchestrator marked the nits "lens-reported, I did not deep-verify these" and the Implementer receipt "does not deep-verify, fix, or assign them" — correct conduct at both seats, but it means NOBODY had checked them, and a nit carried unexamined into a merge-readiness report becomes a claim the OPERATOR reads as established. Triage is this seat's; all three are now measured
- NIT (2) `git_exec.cpp:222-224` CONFIRMED, LOW: unanchored `find()` over CONCATENATED stderr+stdout for `"unable to read"`/`"bad object"`/`"invalid object"`, so under `promisor` a genuine object-store corruption is reclassified `promisor_objects_unavailable`. It MISLABELS, it does not LOSE — the failure remains a failure and only its typed reason is wrong. No action proposed
- NIT (3) `classify.cpp:344` CONFIRMED **and its unchecked premise VERIFIED**: `discover.cpp:62-63` AND `:90-91` accept `.git` as `is_directory(...) || is_regular_file(...)`, so gitlink checkouts genuinely reach classify. The read is `repo / ".git/shallow"` via `ifstream`, not `git rev-parse --git-path shallow`; for a `gitdir:` pointer the path does not exist and ifstream yields NO LINES AND NO ERROR → record becomes `shallow: true, boundary: {}`, wrong, plausible and SILENT
- NIT (3) MOVED IN BOTH DIRECTIONS BY MEASUREMENT: **smaller than "a class"** — `classify.cpp:344` is the ONLY direct `".git/"` join anywhere in the repo engine (checked classify, capture, restore, eligibility, discover, git, git_exec), one line and one fix surface; and **blast radius BOUNDED** — `Shallow::boundary` occurs only in `classify.cpp` (written) and `types.hpp:145` (declared), with NO restore-side consumer in this tree, so it is a wrong RECORD and not a restore reconstructing wrong shallow state. Severity LOW **strictly conditional** on `boundary` staying unconsumed; the moment any restore path reads it, this becomes CORRECTNESS — that conditional IS the finding
- NIT (3)'s REAL ROOT, AND WHY IT SURVIVED: **ZERO gitlink test coverage** — no file under `tests/` writes a `gitdir:` pointer at all, so no test exercises a gitlink checkout through discovery. Carry WITH the T3 stage-4 gitlink `.git`-file finding as ONE untested-repo-shape item, per the Orchestrator; the shared root is an untested repo SHAPE, not two unlucky lines
- NIT (4) `restore.cpp` CONFIRMED **SHARPER THAN REPORTED**: measured across every `.cpp`/`.hpp` under `src/`, `capture_env`/`core_autocrlf`/`core_filemode` appear in EXACTLY ONE FILE as declarations only (`types.hpp:163`, `:164`, `:173`) with no other occurrence anywhere — so the field is not merely UNREAD by restore-verify, it is NEVER WRITTEN EITHER; unwired in BOTH directions, strictly stronger than the lens stated. Meanwhile `verify_restored` (`restore.cpp:310`) requires a clean tree via `git status --porcelain=v2 -z` (`:340-342`) with NO EOL/filemode compensation, so the exposure is real and the compensating data does not exist at runtime. Severity LOW-to-MEDIUM and, more importantly, **UNOWNED** — a design question about where EOL/filemode normalization belongs, above this pair; ownership ROUTED UP, nothing prescribed
- DISPOSITION: all three disclosed, NONE blocks T4, and none is a defect in the authorized NSDMI fix — that delta remains exactly the three fenced files the panel cleared. No code change proposed and no product byte touched. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 IMPLEMENTED at `6ba01ef` panel-adjudicated with FINAL held pending master's F-URL-1 disposition; my R-4.38 count-gate finding at `011248` remains OPEN above this seat; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
