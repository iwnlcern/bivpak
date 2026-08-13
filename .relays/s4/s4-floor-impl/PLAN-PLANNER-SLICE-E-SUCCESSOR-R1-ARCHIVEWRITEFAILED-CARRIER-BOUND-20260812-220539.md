## PLAN (successor r1, slice E) — **R1 is answered without widening scope by one byte, and the measurement that settles it is that TEXT MODE PRINTS ONLY `kind` AND `detail`** (`cli/main.cpp:34-40`): `path`, `facts` and `errno` never reach an operator's terminal, so **both names must live in `detail` or J's calibration — "the operator can act rather than guess" — is not met by a JSON field they will never see.** Selected: existing `ErrKind::ArchiveWriteFailed` (the established pack-side producer-refusal kind, exit class **4**), both names in `detail`, structurally duplicated into `facts` for JSON. **No new kind, no `error.hpp`/`error.cpp`/`envelope.cpp`/`main.cpp`/`exit_map.hpp` change — the four-file production list is unchanged.** **R2: `1a` is struck from the combined-tree-first list; it was my contradiction between §2 and §3 and §3 was the correct one.** Pins re-derived at THIS act.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-plan-successor-r1
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
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-REVIEW-IMPLEMENTER-SLICE-E-SUCCESSOR-MUST-REVISE-CARRIER-CHECKPOINT-20260812-213906.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-29A5B3A3-CAP-OUTSIDE-A1241-BY-PREDICATE-20260812-212557.md (successor rev0, superseded by this relay); .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-BOTH-GATES-CLEAR-PIN-MOVED-SUCCESSOR-PLAN-29A5B3A3-20260812-211825.md (both gates clear, pin moved)
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: s4.orchestrator-planner, operator, s4.orchestrator-reviewer, master.orchestrator-planner, m-2.planner, m-1.planner
SUBJECT: PLAN (successor r1) — cap refusal bound to ArchiveWriteFailed/detail+facts/exit 4 with text and JSON oracles inside the existing scope; 1a struck from the combined-tree list

## 0. Pins re-derived AT THIS ACT (not carried from rev0's §0)

```text
addendum-12 @ 6eeeb157  29a5b3a3abb6777a…  == the lock's declared content              MATCH
addendum-12 @ pdc HEAD  d0e2c6eba6047c3b…  the lock POST-STAMP; exactly ONE commit
                        (6f2de0d) follows 6eeeb157 on this file, ONE hunk, head region
J           @ pdc HEAD  94b6440c6ea5342a…  UNMOVED                                     MATCH
origin/main             0db8fdd            unchanged -> the m-1 receipt is still ABSENT
```

## 1. R1 — the executable carrier, selected and bound

**The measurement that decides it** (at `0db8fdd`):

```text
support/error.hpp:37   BivError { ErrKind kind; string path; string detail; int err_no;
                                  map<string,string> facts; }
cli/main.cpp:34-40     TEXT:  "biv: " << to_string(kind) << (detail.empty() ? "" : ": " + detail)
                       -> path, facts and errno NEVER reach the terminal
report/envelope.cpp:360-378  JSON: kind, path, detail, errno, facts
report/envelope.cpp:386      ArchiveWriteFailed -> EXIT 4
pack.cpp                     the established producer-refusal idiom is already
                             cleanup_error(BivError{ErrKind::ArchiveWriteFailed, {}, "<hyphen-token>"})
```

**Selection:**

```text
ErrKind        ArchiveWriteFailed          EXISTING. The kind pack already uses for every
                                           producer-side refusal (adapter-session-invalid,
                                           adapter-session-id, adapter-member-invalid).
exit class     4                           inherited, unchanged
detail         "<cap-token>: entry=<original_session_id> cap=<cap-name> limit=<N> observed=<M>"
                                           BOTH NAMES LIVE HERE because text mode prints nothing else
path           <original_session_id>       consistent with existing use for the offending object
facts          {"cap","limit","observed","entry"}   structured duplicate; reaches JSON only
```

**Why `detail` and not `facts` alone:** J's calibration is that a producer refusal in the field means **the
cap is MIS-PRICED**, that the first occurrence routes to re-pricing rather than to a verdict about the
operator's data, and that the refusal must let the operator **act rather than guess**. An operator running
`biv pack` without `--json` sees `kind` and `detail` and nothing else. **A name that exists only in `facts`
is invisible to the person the calibration is written for.** `facts` is carried as well because it is free
and machine-readable, but the **text assertion is the load-bearing one.**

**Wording constraint, from the same calibration:** the message states FACTS — cap, limit, observed, entry —
and **never a verdict about the operator's sessions being too large.** The cap is ours and mis-pricing is
ours; the store is theirs.

**Scope consequence: NOTHING WIDENS.** No new `ErrKind`, so `support/error.hpp` and `support/error.cpp` are
untouched; no new rendered field, so `report/envelope.cpp`, `cli/main.cpp` and `report/exit_map.hpp` are
untouched. **The production list stays `adapter.hpp`, `codex/codex.cpp`, `codex/install.cpp`,
`core/pack/pack.cpp`.**

**The branch that ROUTES rather than proceeding:** if review concludes a **new typed kind** is required —
e.g. that `ArchiveWriteFailed` mis-describes a bounded refusal on well-formed data and deserves its own
kind and exit class — that reaches `error.hpp`, `error.cpp` and `exit_map`, which are **OUT of this list**.
**STOP and route; do not add a kind mid-build.** I am not pre-authorizing that branch, only naming it.

**The oracles — in-process AND actual-binary:**

```text
tests/test_pack.cpp   (in-process, per cap, on the cap+1 arm)
  - pack() returns an ERROR (not a report), kind == ArchiveWriteFailed
  - detail CONTAINS the entry's original_session_id AND the cap name
  - facts.at("entry") / facts.at("cap") / facts.at("limit") / facts.at("observed") present and correct
  - ZERO PARTIAL EMISSION: no agent_sessions entry for that session exists in the image, and no
    truncated children[] survives anywhere
  - the at-cap arm ACCEPTS and round-trips
tests/test_cli.cpp    (actual binary — this is the operator-visible proof)
  - `biv pack` EXIT CODE == 4
  - STDERR contains BOTH the entry id AND the cap name
  - `--json` error object carries kind/detail/facts with both names
```

**Killing arms, unchanged and all three still binding:** a refusal omitting **either** name FAILS; **any**
over-cap emission, truncated or whole, FAILS; and a genuine drop or alteration **within an emitted entry**
carrying no `§A12.4.1` `CollectReport.warnings` line FAILS — the arm that stops the cap ruling being
over-read into "warnings are optional."

## 2. R2 — the checkpoint stated ONCE, with `1a` where it belongs

**Struck from rev0 §2:** `1a` from the "first creditable at the combined tree" list. §3 was right and §2 was
my contradiction — **`1a` is the schema-independent collector-carriage failure and is one of the four
Stage-0 behavioral REDs.** The combined-tree checkpoint is the first creditable point for **`1b`, key 2's
second GREEN arm, `4a`, `5`, and the actual-binary E2E** — the schema-dependent set, and only those.

```text
STAGE 0 @ 0db8fdd      assertion-level REDs   1a, 3, 4, 6
                       GREEN controls          2 arm 1, 7, the three claude reference controls
   ↓ rebase onto the m-1 receipt SHA   (0db8fdd remains the AUDIT cut; both are named in the report)
POST-REBASE            GREEN control           2 arm 2   — a DEPENDENCY-INTEGRITY STOP if it is RED
                       assertion-level REDs    1b, 4a, 5 (atomic: both variants authored and run together)
   ↓
STAGE 1                the single coupled implementation, incl. the four caps and this carrier
   ↓
AFTER                  every key GREEN; controls still green; the actual-binary E2E
```

**A compile failure earns no behavioral-RED credit, and no implementation byte lands before every key it
greens has been observed failing on an assertion.**

## 3. Everything else carries from successor rev0 unchanged

The cap-carrier BASIS (outside `§A12.4.1` by its operative predicate — a whole-entry refusal emits no entry
for material to be omitted from; `§A12.4.2` + J carry it; **the "typed error discharges the clause" reasoning
is REJECTED and appears nowhere**); all four caps (1024 / 64 / 256 / 4096, per entry, whole-entry refusal,
never truncation, at-cap and cap+1 arms); the exhaustive six-path Stage 0 with **no production byte** and
`src/**` untouched; the coupled Stage 1 and why it cannot be split (transitive `child_ids` on the flat writer
emits C as a DIRECT CHILD of R under J's absence license — false data, not missing data); the m-1 stop gate
and the dependency-integrity stops; key 2 GREEN on both arms; key 5 atomic; A3's four checks on ONE
`codex.cpp` head carrying its ONE pin with the five read-side literal classes to be **re-located at the
head**, `codex/install.cpp` moving no pin, the claude pin frozen; the E2E and verification matrix, sandbox
guards and credential decoy, macOS plus **governing** local Ubuntu 24.04 `linux/amd64` Docker with Actions
NOT invoked and the three disclosed divergences, the base-container control, the inherited `.github` count-gate
disclosure; the branch cut from `origin/main` never local `main`, publication HELD, D-5.5(a) at hand-up;
R-4.20's mint sites (`:122`/`:430`/`:455`, **not** `:507-513`), MONO, M4-CG-0, R-4.24 not ours. The
stale-`STATUS` disclosure from rev0 §0a also stands: the locked document still says the VP `§A12.6`
re-verification and the operator re-waiver "have NOT run"; the former ran at `191415` and the latter is
superseded by the W-1 chain.

## 4. Token-time obligations

Unchanged: the **seven-element tuple** re-verified in the token relay, with **both design hashes re-derived
at that moment** — §0 above is a measurement with a timestamp, not a property of this plan — and the live
`d0e2c6eb` re-shown as the disclosed one-hunk status-only post-stamp. A miss makes W-1 INAPPLICABLE / NO
TOKEN.

## 5. What I am asking of you

**A plan review.** Is the carrier selection executable as written — `ArchiveWriteFailed`, exit 4, both names
in `detail` with `facts` as the structured duplicate, and the text assertion load-bearing because text mode
prints nothing else — and is the route-branch for a new kind drawn in the right place? Is the checkpoint now
stated once and consistently? Reply with `PLAN_REVIEW_VERDICT: approve` or `must-revise` (verdict line BARE
— no bold, no backticks; remarks via em-dash only, per the matcher's recorded grammar). **On approve, Stage 0
is dispatchable and Stage 1 still waits on m-1's receipt.** Merge ≠ push ≠ release; the release hold is
ABSOLUTE.

ACTIONS_GIT_REF: no product/test edits at this seat — at this filing act: re-hashed addendum-12 at `6eeeb157` (`29a5b3a3`) and pdc HEAD (`d0e2c6eb`, one commit `6f2de0d` after the target), re-hashed J (`94b6440c`), re-measured `origin/main` (`0db8fdd`, m-1 receipt absent); and read the error surface at `0db8fdd` — `support/error.hpp:37` `BivError` fields and the `ErrKind` enum, `cli/main.cpp:34-40` text rendering (kind + detail only), `report/envelope.cpp:360-378` JSON error object, `report/envelope.cpp:386` `ArchiveWriteFailed` → exit 4, and `pack.cpp`'s existing `cleanup_error(ArchiveWriteFailed, "<hyphen-token>")` producer-refusal idiom; this relay + its INDEX row ride one explicit-path docs-lane commit whose SHA lands after filing
RELAY_LINT: per D-3.4 — per-file WITH freshness before filing; INDEX tail re-read; `--index`; third arm at the active dispatch root. Disclosed reds: INDEX line 222 (pre-existing sibling class, not mine) and the cross-repo lineage class, cleared for this lineage by W-1 (concurred/effective) and still disclosed — no green claimed and no authority drawn from disclosure
FINAL_GIT_STATUS_SHORT: not claimed as a clean-tree proof — the shared checkout carries sibling state; this seat's writes are confined to this relay and `.relays/s4/INDEX.md`

CARRY LIST:
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-SUCCESSOR-R1-ARCHIVEWRITEFAILED-CARRIER-BOUND-20260812-220539.md` → `s4-floor.implementer` (plan review = slice E's plan gate); successor rev0 `212557` SUPERSEDED
- **R1 answered with ZERO scope widening.** The deciding measurement: `cli/main.cpp:34-40` prints ONLY `kind` and `detail`, so `path`/`facts`/`errno` never reach an operator's terminal and **a name that lives only in `facts` fails J's "act rather than guess" calibration.** Selected: existing `ErrKind::ArchiveWriteFailed` (pack's established producer-refusal kind), exit **4** inherited, BOTH names in `detail`, structured duplicate in `facts` for JSON, `path` = the entry id
- production list UNCHANGED (`adapter.hpp`, `codex.cpp`, `codex/install.cpp`, `pack.cpp`); `error.hpp`, `error.cpp`, `envelope.cpp`, `main.cpp`, `exit_map.hpp` all untouched. **ROUTE-BRANCH NAMED, not pre-authorized:** if a NEW typed kind is judged necessary it reaches three out-of-list files — STOP and route, never add a kind mid-build
- oracles: in-process per cap+1 (error kind, both names in `detail`, four `facts` keys, **ZERO PARTIAL EMISSION**, at-cap arm accepts) AND actual-binary (`biv pack` exit **4**, stderr carries BOTH names, `--json` error object carries them too). Three killing arms unchanged incl. the one preventing "warnings are optional"
- wording constraint from J's calibration: state FACTS (cap, limit, observed, entry), **never a verdict that the operator's sessions are too large** — the cap is ours and mis-pricing is ours
- **R2:** `1a` STRUCK from the combined-tree-first list — my §2/§3 contradiction, §3 correct; `1a` is a Stage-0 behavioral RED, and only `1b`, key 2 arm 2, `4a`, `5` and the E2E wait for the combined tree. Checkpoint now stated once
- pins re-derived AT THIS ACT; m-1 receipt still ABSENT so Stage 1 stays blocked; on approve Stage 0 is dispatchable; release hold ABSOLUTE
