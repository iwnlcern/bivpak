## PLAN rev1 — MR-1 accepted: the census is EIGHT, not five, and the three I missed are precisely the sites where the NSDMI actually changes which initialization path runs. I measured them directly on the real header, both arms, both platforms, rather than arguing they must be fine

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t2-nsdmi-fix-plan-r1
PARENT_DISPATCH_ID: s4-matrix-t2-nsdmi-fix-plan-review-r0
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-T2-NSDMI-MUST-REVISE-EIGHT-SITE-CENSUS-20260821-180908.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T2-FIX-RULED-B-NSDMI-CAUSE-FIX-COUNT-GATE-SHAPE-ROUTED-UP-20260821-164516.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate — bounded in-lane repair authorized as option B at `164516`. This relay carries NO token and authorizes NO keyboard; a successor Implementer PLAN-REVIEW approve is required, and the bare `DISPATCH IMPL` then parents to THAT approval. No merge, push, PR mutation, `.github` edit, schema act, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: accepted T1 `00c06d93146f13c0f8518b0893d2d944f0bd8231`; reconstructed T2 under repair `e17234356a53ef14b997a4cf038bd72898961424`
SUPERSEDES: PLAN `s4-matrix-t2-nsdmi-fix-plan` at SHA-256 `7bbd74994140cc6ad3c53bb428f6c27cad8d1216d60455f611b3d924188b6423`, blob `8d7f48fab5924595ee2172dd1ba20f4734f95135` (MUST REVISE)
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN rev1 — census corrected to eight sites; property (iii) rebound to all eight with a direct real-header A/B on the three plain default-init forms, identical on macOS and Linux GCC 13.3.0; fix and scope unchanged

## 1. MR-1 accepted, and the defect is mine in a shape I have a name for

My census searched the token `Opts{`. That pattern **cannot** match `biv::repo::Git::Opts opts;`
— a plain declaration has no brace. So I reported the pattern's hit count as the population:

```text
'Opts{'    hits at e172343: 5      <- what my grep could reach
'Git::Opts' hits            : 8      <- what actually exists
```

I printed the numerator and called it the denominator. That is the same defect I flagged
elsewhere in this lane as *measure the instrument's REACH, not its intent — always print the
denominator*, and I committed it while asserting a completeness property. The reviewer's
correction is exact and I am not qualifying it.

Small coda in the same key: the placeholder sweep I run over my own relays before filing
matched only the ASCII `...` and was blind to the Unicode ellipsis, so it passed this very
revision clean while two elisions sat in the census table. Widened, both replaced with exact
text. A checker with the defect it is checking for is worth one sentence, not a section.

## 2. The corrected census — eight sites, three kinds

```text
tests/test_repo_git.cpp @e172343
  :57   default argument, empty-brace   const Git::Opts& opts = Git::Opts{}
  :76   PLAIN default-init              Git::Opts opts;
  :124  empty-brace temporary           Git::Opts{}
  :147  PLAIN default-init              Git::Opts ordinary_opts;
  :228  PLAIN default-init              Git::Opts opts;
  :244  designated aggregate            Git::Opts{ six designators, empty_config_keys OMITTED }
  :265  empty-brace temporary           Git::Opts{}
  :293  designated aggregate            Git::Opts{ six designators, empty_config_keys OMITTED }
```

Three empty-brace, **three plain default-init**, two designated. The three I missed are not
incidental — as the review says, they are exactly the form where the NSDMI changes which
initialization path is selected: before B, `empty_config_keys` is default-initialized; after B,
the default member initializer is chosen. That relationship is what property (iii) has to
cover, so omitting those sites omitted the interesting half.

## 3. Property (iii), rebound to all eight

**Syntactic — all eight.** Every one of the eight lives in `tests/test_repo_git.cpp`, the single
translation unit of `biv_repo_git_tests`. That target compiled **clean** in both the patched
Linux arm (GCC 13.3.0, `Built target biv_repo_git_tests`) and the patched macOS arm. A clean
compile of that TU is therefore a proof across all eight forms, not five.

Worth stating because it is a real hazard the compile disposes of: adding an NSDMI does **not**
cost `Opts` its aggregate status in C++14-and-later, so designated initialization at `:244` and
`:293` remains valid. The patched builds compile those exact sites, so this is measured, not
assumed.

**Behavioral — the three plain sites, measured directly on the real header.** I did not argue
these are fine. I built a probe that includes the actual `core/repo/git.hpp` from each arm and
reports the observable state of both a plain default-initialized `Opts` and an empty-braced one:

```text
macOS (Apple clang, -std=c++23 -I src)
  unpatched  sizeof=112 | plain{sz=0 cap=0 empty=1} braced{sz=0 cap=0 empty=1} | cwd=0 lazy=0 iso=0 stderr=0 stdout=0 budget=30000
  patched    sizeof=112 | plain{sz=0 cap=0 empty=1} braced{sz=0 cap=0 empty=1} | cwd=0 lazy=0 iso=0 stderr=0 stdout=0 budget=30000

Linux (g++ 13.3.0, -std=c++23 -Wall -Wextra -Werror -I src)
  unpatched  sizeof=144 | plain{sz=0 cap=0 empty=1} braced{sz=0 cap=0 empty=1} | cwd=0 lazy=0 iso=0 stderr=0 stdout=0 budget=30000
  patched    sizeof=144 | plain{sz=0 cap=0 empty=1} braced{sz=0 cap=0 empty=1} | cwd=0 lazy=0 iso=0 stderr=0 stdout=0 budget=30000
```

Identical within each platform: same `sizeof`, both initialization forms empty with zero
capacity, and every other member bit-for-bit equal. (The 112-vs-144 difference is across
platforms, not across arms — the A/B is within-platform, which is the comparison that matters.)
The probe compiles in **both** arms because a standalone default-init never omits a designated
member, so unlike the suite build this comparison is available on Linux too.

**Runtime — the whole TU.** The same-platform macOS A/B of the actual target remains:
`179 assertions in 6 test cases`, identical in both arms; and the patched tree under Linux
non-root with the descriptor lift gives the same `179/6` with `ctest -R '^repo_git$'` rc=0. That
run exercises all eight sites, and I am now claiming it as an eight-site result rather than
mislabelling it.

## 4. Unchanged from rev0

The fix and its scope do not move: one line, `src/core/repo/git.hpp:21`,
`std::vector<std::string> empty_config_keys{};`.

Property (i) stands as filed — actual-tree GCC 13.3.0 A/B, unpatched `build_rc=2` reproducing
both `-Werror=missing-field-initializers` rows at `test_repo_git.cpp:250`, patched `build_rc=0`
`Built target biv_repo_git_tests`. Property (ii) stands as filed. The crux correction (`cwd:18`
and `stdout_file:23` also lack NSDMIs and never warn only because both enumerating sites
designate them, making B a targeted cause-fix on the one member both NSDMI-less **and** omitted)
stands. The optional latitude stays **declined**, with the residual registered: B does not close
the struct's susceptibility, and `cwd`/`stdout_file` would trip the identical check if a future
designated site omits either — a follow-up carrying its own evidence, not latitude consumed here.

I also accept the review's framing on evidence status: **these pre-token scratch measurements do
not substitute for the fixed-head retained run.** They are plan evidence. The implementation must
still retain the exact fixed-head canonical Linux build and `repo_git` results before T2's
Stage-3 panel.

## 5. Scope, and what follows your review

Recorded for grading, **not** a grant:

```text
- src/core/repo/git.hpp -> in
```

On your approve I issue the bare `DISPATCH IMPL` parented to **your PLAN-REVIEW**, TO exactly one
Implementer, with that `SCOPE_DIFF` row plus a `SCOPE_ROW_EVIDENCE` row and
`SCOPE_DIFF_RESULT: all-in`. Exit is the run, not the diff: canonical Linux build GREEN at the
fixed head with the results retained, then T2's Stage-3 panel on the fixed T2.
`harness-selftest` stays separately adjudicated under `201613` and the full Linux suite is never
labelled GREEN on it.

## 6. Carried

Linux `nonzero_exit` stays OWED in T1's stage-4. The count-gate SHAPE finding widens at T2's
fourth binary, rides both T1's and T2's stage-4 cells as a coverage-**visibility** gap rather
than a red, and its `.github` repair is outside s4's fence and routed UP — stage 5 will disclose
it explicitly. T3/T4 stay at their old heads; `compare.py` stays owed at T3 under its test
obligation. Schema F+G-fenced. Merge != push != release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only `git show e172343:tests/test_repo_git.cpp` for the broad `Git::Opts` census and `git show e172343:src/core/repo/git.hpp` for its include set; a probe TU compiled against the real header in both scratch arms locally under Apple clang and in one disposable `ubuntu:24.04 --platform linux/amd64` container under g++ 13.3.0. NO ref created or moved, NO product/test/workflow edit in any tracked worktree, NO merge, push, PR mutation, or remote CI; no unrelated Docker resource pruned or removed. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T2-NSDMI-R1-EIGHT-SITE-CENSUS-BOUND-20260821-183854.md` → TO `s4-matrix.implementer` for successor PLAN-REVIEW; SUPERSEDES rev0 at SHA-256 `7bbd74994140cc6ad3c53bb428f6c27cad8d1216d60455f611b3d924188b6423`
- THIS RELAY CARRIES NO TOKEN; the bare `DISPATCH IMPL` follows only after your approve and parents to THAT approval
- MR-1 ACCEPTED, defect owned in its own shape: my census grepped `Opts{`, which CANNOT match a plain `Git::Opts opts;` declaration — 5 pattern hits reported as the population where 8 exist. I printed the numerator and called it the denominator, while asserting a COMPLETENESS property. Same defect I have flagged elsewhere as measure the instrument's REACH and always print the denominator
- CORRECTED CENSUS, eight sites in three kinds: empty-brace `:57 :124 :265`; **PLAIN default-init `:76 :147 :228`**; designated `:244 :293`. The three I missed are exactly the form where the NSDMI changes which initialization path is selected, so omitting them omitted the interesting half
- PROPERTY (iii) REBOUND — SYNTACTIC: all eight live in the single TU of `biv_repo_git_tests`, which compiled CLEAN in both the patched Linux and patched macOS arms, so the compile proves all eight. Also measured rather than assumed: an NSDMI does NOT cost `Opts` its aggregate status in C++14-and-later, so the designated sites at `:244`/`:293` remain valid — the patched builds compile those exact sites
- PROPERTY (iii) REBOUND — BEHAVIORAL, measured on the REAL header not argued: a probe including the actual `git.hpp` from each arm reports IDENTICAL observable state within each platform for BOTH a plain default-init and an empty-braced `Opts` — macOS `sizeof=112`, Linux g++ 13.3.0 `sizeof=144`, both arms `plain{sz=0 cap=0 empty=1} braced{sz=0 cap=0 empty=1}` with every other member equal. Available on Linux too, because a standalone default-init never omits a designated member
- RUNTIME claimed correctly now as an EIGHT-site result: macOS A/B `179 assertions in 6 test cases` identical in both arms; patched Linux non-root with the descriptor lift the same `179/6`, `ctest -R '^repo_git$'` rc=0
- UNCHANGED: the one-line fix and its single-path scope; property (i) actual-tree GCC 13.3.0 A/B; property (ii); the crux correction; the optional latitude DECLINED with the residual registered (B does not close the struct's susceptibility for `cwd`/`stdout_file`)
- ACCEPTED FRAMING: these pre-token scratch measurements are PLAN evidence and do NOT substitute for the fixed-head retained run; the implementation must still retain the exact fixed-head canonical Linux build and `repo_git` results before T2's Stage-3 panel
- CARRIED: Linux `nonzero_exit` OWED in T1 stage-4; count-gate SHAPE rides both stage-4 cells as a visibility gap with its `.github` repair routed UP and disclosed in stage 5; T3/T4 at old heads; `compare.py` owed at T3; schema F+G-fenced; release hold ABSOLUTE
