# s4-floor AUDIT — planner seat — A7 floor + adapter legs at `main@8981bfd`

Author seat: `s4-floor.planner`.
Dispatch: `s4-floor-audit` (re-homed copy of record, `.relays/s4/s4-floor-audit/AUDIT-ORCHESTRATOR-PLANNER-20260804-231721.md`).
Independent artifact: the partner implementer's artifact was NOT read before filing this one.
Report of record: the accompanying relay under `.relays/s4/s4-floor-audit/` carries the status proofs; this artifact carries the audit body.

## 0. Method, baseline, instruments

- Baseline: this repo at `main@8981bfd` (`git rev-parse main` = `8981bfd0848039d533d9bb2a96301d4d81b564fa`, E2, this session).
  Every code read below is against the committed blob (`git show 8981bfd:<path>`, `git grep … 8981bfd -- <path>`), never the working tree.
- The LOCKED A7 consumed: `../pdc/master/domains/m-2-agent-adapters/design/2026-07-21-ADDENDUM-7-version-floor.md`.
  Lock VERIFIED before reliance (E2): `shasum -a 256` of the live file = `2e4020571d464b6a61d7d7eba3e7966987932494bb355b10bff4a8fb4b6624da`,
  identical to the blob at lock commit `c5ce327`, matching `DESIGN_SHA256` in the lock record
  (`../pdc/master/relays/s3-build-standup/DESIGN-PLANNER-M2-ADDENDUM7-LOCK-2E402057-20260728-110000.md`, `DESIGN_LOCK_ID: m2-addendum7-2e402057-lock-20260728`).
- The carrier consumed at the committed blob `ce9ef8c` (`git show ce9ef8c:…rclass2-fixture-evidence-map.md`); the working copy also hashes `c2bcdc12…` (the post-append SHA), so blob and file agree.
- Line numbers below are the blob's own; where a parent doc's cited line drifted, the site was re-found by criterion and the drift is recorded in §7.
- Absence claims: `git grep -F` (or `-c`) at `8981bfd` with the population stated per claim, run UNPIPED so the exit status is the instrument's own.
  One instrument correction made mid-audit and recorded: an early batch piped grep through `head`, which reports `head`'s exit, not grep's; every absence claim below was re-run unpiped before being written down.

## 1. R-W.1 / C1 both-legs head — VERIFIED STILL UNLANDED at `8981bfd`

The criterion (the three-step conjunction): literal membership AND full grammar AND total order ⇒ else typed REFUSE. What ships is the first step alone.

**Codex site (re-found by criterion, matches the package's cite):**
`src/adapters/codex/install.cpp:194-196` —

- `validated_codex_version(version)` = `version.starts_with("0.142.") || version.starts_with("0.144.")` — bare literal membership (E1).
- Full grammar: absent at admission. `semver_at`/`parse_codex_version` (`install.cpp:198+`) EXTRACT a version substring from probe output; nothing validates the grammar of the compared string as an admission conjunct.
- Total order: absent. Instrument: `git grep -n 'compare\|operator<\|std::strong_ordering' 8981bfd -- src/adapters/` — the only comparator is `compare_timestamp` (`codex/codex.cpp:231,267,338,343`), a discovery-recency order, not a version order. Population: every file under `src/adapters/`.
- Typed REFUSE: absent. A non-member version yields `Verdict::unvalidated`, and the refusal row is the generic `agent_not_validated_failed`/`"not-validated"` at `src/core/open/sessions.cpp:229-243` — no version-typed detail.

**Claude site:** `src/adapters/claude_code/install.cpp:331` —
`validated_claude_version(version)` = `version.starts_with("2.1.")` — same shape, one prefix (E1). Same grammar/order/typed-refuse absences, same instruments.

**Every call path reaching each site** (population instrument: `git grep -n 'validated_codex_version\|validated_claude_version' 8981bfd -- src/ tests/` = 6 hits, all enumerated; symmetric per leg):

1. **Host-verdict path:** `biv open` → `src/cli/main.cpp:258` `build_preview` → `src/core/open/sessions.cpp:129` `adapter->capabilities(host)` → `probe_capabilities` (codex `install.cpp:285-312`, claude `:420-447`) → `validated_*_version` on the HOST probe version (codex `:308`, claude `:443`). The verdict then gates install at `sessions.cpp:229-243` (`unvalidated`/`absent` ⇒ `agent_not_validated_failed` per session, exit 2 via `kind_for_row` + `envelope.cpp:391-394`).
2. **Image-version path:** `src/cli/main.cpp:352` `run_session_leg` → `sessions.cpp:262-265` `adapter->install(…)` → `codex_install`/`claude_code_install` → `host_version_unverified_for_install` (codex `:273-283`, called `:348`; claude `:408-418`, called `:486`) → `validated_*_version` on the IMAGE `agent_version_at_pack`. Reached only when the host verdict is `unvalidated_host`; controls the `host_version_unverified` flag, not admission.
3. **Display path (verdict consumer, not a gate):** `src/core/open/render.cpp:187-194` (consent prompt renders validated/unvalidated + `validated_range`), `:237-241`.

## 2. R-VF.1/2/3 implementing-head debt (fence F-2) — present behavior per site, all three CONFIRMED PRESENT as A7 names them

**(1) R-VF.1 — consent path is a bare skip, exit 0.**
`src/core/open/sessions.cpp:215-227`: the consent-denied branch emits one `sessions_consent_skipped` row per eligible entry (reason `"consent-denied"`) and `continue`s — zero adapter calls, no ids minted, no id map, no staging, no printed staging guidance. Exit class: `kind_for_row` (`sessions.cpp:52-79`) → `ErrKind::SessionsConsentSkipped` → exit 0 (`envelope.cpp:395-396`). Render suppresses the activation block under consent-no (`render.cpp:283`) and has no consent-no staging guidance surface. So the path is EXIT-compliant with sealed F57 and performs none of F57's required operation — exactly A7 §A7.7 defect (a). Both legs (the branch is agent-generic, upstream of the adapters).

**(2) R-VF.2 — `install(…, Consent::no)` writes metadata only, both legs.**
Codex: every member read, pair-set rewrite, verify scan, and write sits inside `consent == Consent::yes` (`src/adapters/codex/install.cpp:406-480`); the consent-no branch (`:499-509`, after the id-map push `:494-498`) emits `InstallSessionOutcome::staged` with empty `verify`, `content_rewrite = nullopt`, then `continue`s.
Claude: gate at `src/adapters/claude_code/install.cpp:533`; consent-no branch `:650-660`, same shape.
What the requirement needs and the tree lacks: install-ready staged BYTES (ids minted AND written, in-pair paths rewritten at stage time) and the A9 sidecar. Sidecar absence instrument: `git grep -F 'agents/manifest.json' 8981bfd -- src/` = 0 hits (population: all of `src/`). No staged-bytes writer exists on the consent-no path — the write plumbing exists only inside the consent-yes branch (promote-candidate, §6d).
Untested today: `git grep -ln 'Outcome::staged' 8981bfd -- tests/` = 0 hits — no test exercises the consent-no adapter branch.

**(3) R-VF.3 — the `staged`→`session_install_failed` mapper survives, still dead.**
`src/core/open/sessions.cpp:323-326`: `Outcome::staged` ⇒ `Row::session_install_failed`, reason `"error"` ⇒ exit 2 (`envelope.cpp:392`) — the latent F57 contradiction. Dead today: the sole product install call passes `adapters::Consent::yes` (`sessions.cpp:265`; population instrument: `git grep -n 'Consent::no\|Consent::yes' 8981bfd -- src/` = 7 hits, all enumerated in §0 notes — the only orchestration-side site is `:265`).

## 3. R-3.25(a) sites — VERIFIED, and the disposition's landing surfaces mapped (surfaces only)

**Codex assignment:** `src/adapters/codex/codex.cpp:391` — `.live_at_pack = false`, a hardcoded literal in the `SessionRecord` builder (`:374-392`).
ONLY-ness instrument: `git grep -n 'live' 8981bfd -- src/adapters/codex/` returns exactly one hit, `:391`. Scope: every line of every file under `src/adapters/codex/` at the blob — so it is the only `live_at_pack` assignment AND the only live-related token on the codex leg; no status/sidecar reader exists there.

**Claude computed path:** `src/adapters/claude_code/claude_code.cpp:152` `terminal_status` = `{completed, exited, stopped, failed}`; `live_facts_by_id` (`:156-188`) reads `<store>/sessions/*.json` sidecars keyed by `sessionId`; `.live_at_pack = live.live` at `:430`, with `agent_version_at_pack = facts.version.value_or(live.version.value_or("unknown"))` at `:429`.

**Pure-propagation claim for `pack.cpp`/`manifest.cpp`/`sessions.cpp`: CONFIRMED.**
Instrument: `git grep -n 'live_at_pack' 8981bfd -- src/` = 21 hits, all enumerated: `adapter.hpp:88` (struct member), the two adapter assignments above, `manifest.cpp:286,288,300` (`required_bool` read — the field is schema-REQUIRED), `:428-429` (write), `manifest.hpp:54`, `pack.cpp:403` (copy into entry), `:563` (warning trigger), `sessions.cpp:194,204,222,240,254,289` (entry→row copies), `:308` (adapter-row default `false`), `:314` (overwrite from manifest lookup), `sessions.hpp:57`, `render.cpp:278` (row suffix). None computes; only the claude adapter derives.
One plan-level observation: `sessions.cpp:308-314` default-initializes an adapter row's `live_at_pack` to `false` and only sets it when a matching manifest entry is found — a fail-OPEN default in the report layer if the lookup ever misses (§7.3).

**Where m-2's disposition (`170500` §4) lands — surfaces only, no design here:**
- The derivation: `src/adapters/codex/codex.cpp` collect — a rollout tail-record type read replacing the `:391` literal; TERMINAL set `{task_complete, turn_aborted, thread_rolled_back}`; any other tail (dangling tool call, truncated final line, empty file) ⇒ `true` (fail-closed).
- The mark: already transported — `manifest.cpp` field is required and round-trips; nothing new.
- The warning: already exists agent-agnostically — `pack.cpp:563-566` pushes `Warning{kind: "SessionLiveAtPack"}`; the open-side row suffix `[session was live at pack]` renders at `render.cpp:278`. The disposition's "exactly one default-visible warning" and MAY-wording (attestation-bound, R-3.36 class) land on the pack-warning text surface; the NEGATIVE CONTROL (terminal tail ⇒ warning ABSENT) is fixture-side.
- Ordering fence restated: (b) torn-tail is INOPERATIVE on the codex leg until this lands — `torn_tail` instrument: `git grep -c 'torn_tail' 8981bfd -- src/` = 0 hits (population `src/`), so A3.3's branch machinery is absent on BOTH legs and (b) is unimplemented everywhere, with the codex branch-3 reachability additionally blocked behind (a). A codex branch-3 test passing on the hardcoded flag fails review (dispatch law, restated).

## 4. A7 floor surface enumeration (fences F-1..F-6)

**The two constants (F-1 carriers; they are DIFFERENT things and this artifact never conflates them):**
- MIN — the pack FLOOR: codex `0.142`, claude `2.1`. Consumed by the PACK dispositions (admissible / omitted / archive-only) — a pack-side honest-packer bound, never an open-side invariant (M4-VF-N1).
- `surveyed_through` — the DISCLOSURE WATERMARK: codex `0.144`, claude `2.1`. Consumed ONLY by the §A7.9 loud-disclosure trigger (`readable_newer_than_survey`), never by pack or open admission.
- Tree state: `git grep -F 'surveyed_through' 8981bfd -- .` = 0 hits (population: whole tree) — neither constant exists; the only version literals are the allowlist prefixes (`codex/install.cpp:195`, display string `:290`; `claude_code/install.cpp:331`) and fixtures.
- §A7.10 same-commit mirror law (F-1): the constants + the adapter sites mirror to the harness pin mirror and RUNCARD in the SAME commit as any product change. Mirror sites in THIS repo at the blob: `harness/scenarios-e3/e3-dual-resume.json:24,42` (`validated_version_prefixes`) and `harness/selftest/test_e3_asserts.py:275,291,2355,2371` (+ the `version_in_validated_range` helper asserted at `:6273-6274`). The E3 RUNCARD is a pdc-side sealed artifact (the mirror commit spans repos; sequencing question for the plan, routed via the orchestrator if it needs an m-2/master answer).

**Every file the floor implementation must touch, with the floor work per file (`repos[]`-adjacent marks below):**

| # | file | floor work |
|---|---|---|
| 1 | `src/adapters/codex/install.cpp` | delete the allowlist admission gate (`:194-196`); direction gate `host ≥ basis` + grammar-before-ordering + typed details `basis_newer_than_host`/`basis_unorderable`; consent-no install-ready staging + A9 sidecar (R-VF.2); MIN/`surveyed_through` constants if homed per-leg |
| 2 | `src/adapters/claude_code/install.cpp` | same, claude leg (`:331` etc.) |
| 3 | `src/adapters/adapter.hpp` | `Capabilities::Verdict` restructure — shipped enum is `{validated, unvalidated_host, unvalidated, absent}` (`:108`); target vocabulary is readable / `readable_newer_than_survey` / unreadable / absent + the `newer_than_survey` boolean (§A7.7 cardinality). `version_refusal_detail` rides the existing optional `detail` (`:135`) |
| 4 | `src/core/open/sessions.cpp` | R-VF.1 end-to-end consent-no carrier (replace the `:215-227` bare skip with the `install(…, Consent::no)` path); mapper corrections (`:323-326` staged→chosen-outcome per F57; NEW `failed`-with-version-detail branch → `agent_not_validated_failed` + reason transport); agent-level unreadable gate (zero adapter calls); new-reader archive-only pre-consent filter + `archive_only_skipped` row |
| 5 | `src/core/open/sessions.hpp` | `Row` enum addition (`archive_only_skipped`); `kind_for_row` branch |
| 6 | `src/core/support/error.hpp` + `src/core/report/envelope.cpp` | one NEW 0-returning `ErrKind` for the clean archive-only skip + its `exit_for_error` entry (the shipped classifier is immutable for existing rows — `envelope.cpp:391-396`) |
| 7 | `src/core/open/render.cpp` | untested-newer loud line (watermark-driven); consent-no staging guidance; archive-only rendering in DEFAULT `list`/`info`; unreadable-host actionable recovery |
| 8 | `src/core/manifest/manifest.cpp` — **`repos[]`-ADJACENT** | schema-2 WRITER (`entry_schema: 2` + required `archive_only` object + the exact 7-char `"unknown"` sentinel) and schema-2-aware READER (full schema-1 set + marker) replacing the `>1` early-return at `:221-227` while preserving the `>known-max` skip for 3+; write path `:420-433` |
| 9 | `src/core/manifest/manifest.hpp` | `AgentSessionEntry` gains the `archive_only` object member |
| 10 | `src/core/pack/pack.cpp` | the three pack dispositions (known ≥ MIN admissible / known < MIN omitted-loud / unknown parseable archive-only); minimum-schema writer rule (today `entry_schema = 1` is hardcoded at `:405`); skip-loud pack report rows |
| 11 | `src/adapters/codex/codex.cpp` (+ claude `claude_code.cpp` untouched-or-light) | R-3.25(a) tail-record derivation (§3); `agent_version_at_pack` capture already exists both legs |
| 12 | `harness/scenarios-e3/e3-dual-resume.json`, `harness/selftest/test_e3_asserts.py` (+ pdc RUNCARD) | §A7.10 same-commit pin mirror |
| 13 | `tests/` | the FX-VF register build-out as arms land; PLUS the flip ledger — tests asserting current allowlist/not-validated behavior that the fold flips: `tests/test_adapter_claude_install.cpp`, `tests/test_adapter_codex_install.cpp`, `tests/test_envelope.cpp`, `tests/test_render.cpp`, `tests/test_sessions.cpp`, `tests/fixtures/probe-envelope-v1.json` (instrument: `git grep -ln 'not-validated\|not_validated\|unvalidated\|validated_range' 8981bfd -- tests/`). Flips must be LISTED decided-not-deleted (the DR-3 discipline, applied to the floor) |

**`repos[]`-adjacency / the named collision:** the floor's `manifest.cpp` work (rows 8-9 region `:206-330` parse, `:380-433` write) shares the FILE with Arm-1's schema act (`require_empty_array` at `:595-600`) and addendum F's closed flavor enums (`:167-177`, `:451-461`, `:565`). Charter fence 2 binds: floor work in `manifest.cpp` starts only after Arm-1's schema act lands (which itself waits on addendum F). Non-`manifest.cpp` floor surfaces (rows 1-7, 10-13) are NOT fence-2-blocked on their face — sequencing them ahead is a plan decision, not an audit finding.

**`entry_schema: 2` archive-only under pins P1–P5 — tree state of each pin's ground:** P1 minimum-schema writer (writer hardcodes 1 today, `pack.cpp:405` — the rule lands with the disposition logic); P2 marker object (absent — no `archive_only` token in src, instrument `git grep -c 'archive_only' 8981bfd -- src/` = 0); P3 no `format_version` bump / no `required_capabilities` (nothing to remove — neither exists on this path); P4 new-reader obligations (the `>1` early-return at `manifest.cpp:225` is the OLD-reader behavior to be superseded schema-aware while keeping the `>known-max` lever); P5 hostile-image (the M4-VF-2 `basis_unorderable` path is part of the direction-gate work, absent today).

**F-4 Step-3 non-perturbation:** everything in the table above outside A7's named clauses is fence-bound; the immutable legs verified here — old-reader skip rows (`sessions.cpp:194-206`), the exit classifier (`envelope.cpp:391-396`), `SessionsConsentSkipped` exit 0 — are exactly the surfaces FX-VF-P5 and the F57 rules pin as unchanged.

## 5. The EIGHTEEN-receipt inventory — per-receipt tree-state rows

Ground truth: six A7 receipts per m-2 `170500` §3; twelve A5 receipts per `224200` §4 (the discharged undertaking), population arithmetic per `222800` §3c and carrier §8 at `ce9ef8c`. Key-absence instruments, run repo-wide at `8981bfd`, unpiped: `git grep -rn 'FX-VF' -- .` exit 1; `git grep -rln 'FX-MG' -- .` exit 1 — ZERO receipt fixture keys exist anywhere in this tree. Arm states are the carrier's (all eighteen are `MUTATION REQUIRED AT SEAL` in their active generations: A7 234/228/6/0, A5 64/52/12/0). No receipt is executed here.

| # | receipt key | fixture keys in tree? | arm state | what execution needs that does not exist today (E1 instruments in §§1-4) |
|---|---|---|---|---|
| 1 | `FX-VF-O3/codex/disclosure-default-visible` | NO | MUTATION-required | `surveyed_through` constant (0 hits repo-wide); `readable_newer_than_survey` verdict (enum lacks it, `adapter.hpp:108`); the loud line (render surface absent); the FX-VF-O3 fixture |
| 2 | `FX-VF-O3/claude/disclosure-default-visible` | NO | MUTATION-required | same, claude leg |
| 3 | `FX-VF-O6/codex/no-image-field-in-derivation` | NO | MUTATION-required | the MIN/watermark/host-V derivation itself (constants absent); the CANON-4 five-input sweep fixture |
| 4 | `FX-VF-O6/claude/no-image-field-in-derivation` | NO | MUTATION-required | same, claude leg |
| 5 | `FX-VF-O4/codex/basis-nul-bearing/refuses-before-comparison` | NO | MUTATION-required | the grammar-before-ordering gate (no grammar conjunct, no order — §1); the NUL-bearing fixture with a REAL NUL byte (adversarial-payload carve-out; must never be normalized out by hygiene sweeps) |
| 6 | `FX-VF-O4/claude/basis-nul-bearing/refuses-before-comparison` | NO | MUTATION-required | same, claude leg |
| 7 | `FX-MG-1R/recovery-visibility` | NO | MUTATION-required | the §A5.10 migration backstop surface — `git grep -c -i 'migration' 8981bfd -- src/` = 0, `-i 'recovery'` = 0; `2.1.202` 0 hits in src; plus the fixture |
| 8 | `FX-MG-3a/recovery-visibility` | NO | MUTATION-required | same surface class + fixture |
| 9 | `FX-MG-6/default-visibility` | NO | MUTATION-required | its golden default-output line + fixture |
| 10 | `FX-MG-7/codex/full-grammar-red` | NO | MUTATION-required | the per-leg full-grammar basis check (absent — §1; the C1 head folds INTO the floor head, F-3); hostile-basis fixture; per-leg separation is load-bearing |
| 11 | `FX-MG-7/claude/full-grammar-red` | NO | MUTATION-required | same, claude leg |
| 12 | `FX-MG-9/evaluability-red` | NO | MUTATION-required | the evaluability-keyed abstention surface — `git grep -c 'evaluab' 8981bfd -- src/` = 0, `'abstain'` = 0; plus fixture |
| 13 | `A5.8/tier2-announcement/default-visibility` | NO | MUTATION-required | the loud-install path RE-ANCHORED post-A7 (fires on `readable_newer_than_survey`, which does not exist yet); the announcement surface — `git grep -c -i 'announcement' 8981bfd -- src/` = 0; fixture |
| 14 | `A5.8/tier2-createdpaths/default-visibility` | NO | MUTATION-required | the created-paths listing + its three separately-keyed content arms; sibling-stays-green is PART of the receipt |
| 15 | `A5.8/tier2-recovery/identify-visibility` | NO | MUTATION-required | the recovery block with three separately-rendered clauses (absent — 'recovery' 0 hits in src) |
| 16 | `A5.8/tier2-recovery/removes-ours-visibility` | NO | MUTATION-required | same block, its own clause; siblings stay green |
| 17 | `A5.8/tier2-recovery/vendor-warning-visibility` | NO | MUTATION-required | same block — `git grep -c -i 'vendor' 8981bfd -- src/` = 0 |
| 18 | `A5.8/silent-promotion` | NO | MUTATION-required (retained, §8-operative) | `surveyed_through` constant + the O7 boundary fixtures at FROZEN inputs (codex `0.145.0`, claude `2.2.0`); the mutation runs per the carrier's §8, NOT its byte-verbatim §1 row (the pre-A7 trap `224200` §3 flags); falsifier = both O7 above-survey loud-line keys |

Common to all eighteen: a build carrying the relevant implementation; every fixture GREEN before its mutation; one mutation per receipt, applied in isolation, reverted after; receipts produced AS ARMS LAND (charter §3), never in a terminal scramble.
Honesty bound: the twelve A5 rows' mutations/fixtures are consumed from `224200`/`222800`/carrier §8 (the design docs of record); addendum-5 itself was not re-read at this seat. The surface-absence instruments above are first-hand at `8981bfd`.

## 6. Duplicate/already-built gate — 4-bucket per surface

**(a) A7 floor core (constants, pack dispositions, direction gate, allowlist deletion)**
PRIMARY_BUCKET: still-open
still-open: no MIN/`surveyed_through` constant, no disposition logic, no `host ≥ basis` gate, no grammar/order conjuncts anywhere (§1, §4 instruments).
already-closed: none of the floor core; but the CLI probe oracle (§A7.6) is landed and SURVIVES as-is (`probe_capabilities` both legs), and `agent_version_at_pack` capture + `host_version_unverified` transport are landed — consume, do not rebuild.
product-overlapped: none (no sibling feature covers version admission).
recommended-next: implement per the locked A7 under fences F-1..F-6; `manifest.cpp` slices only after Arm-1's schema act (fence 2).

**(b) archive-only marker (`entry_schema: 2`)**
PRIMARY_BUCKET: still-open
still-open: writer + new reader + object + sentinel all absent (`archive_only` 0 hits in src).
already-closed: the OLD-reader leg is fully landed and IMMUTABLE — `manifest.cpp:221-227` early-return, `sessions.cpp:194-206` `entry-schema` skip rows, exit 2 via `UnknownAgentSkipped` — this is FX-VF-P5's ground and must not be altered.
product-overlapped: none.
recommended-next: implement P1–P5 exactly; new mechanisms only where A7 grants them (`archive_only_skipped` + the one new 0-returning kind).

**(c) R-W.1/C1 grammar + total-order head**
PRIMARY_BUCKET: still-open
still-open: both legs bare `starts_with` (§1).
already-closed: none.
product-overlapped: folds INTO the floor head by design (F-3) — not separate work, one head, one gate.
recommended-next: implement inside the floor fold with FX-MG-7 + FX-VF-O4 as the falsifiers.

**(d) R-VF.1/2/3 consent-no carrier**
PRIMARY_BUCKET: still-open
still-open: all three defects present exactly as A7 names them (§2).
already-closed: the exit CLASS is already correct (0 via `SessionsConsentSkipped`) — exit-compliant only; and the consent-yes branch already contains the full mint/rewrite/verify/write machinery (`codex/install.cpp:406-480`, `claude:533-613` region) — the fold PROMOTES that machinery into the consent-no path with staged targets + sidecar, it does not build staging from nothing.
product-overlapped: none.
recommended-next: one end-to-end carrier per §A7.7; correct the dead mapper toward F57; never cite it as precedent.

**(e) R-3.25(a) codex `live_at_pack`**
PRIMARY_BUCKET: still-open (codex leg only)
still-open: the codex derivation (hardcoded `false`, §3).
already-closed: the claude derivation, the manifest transport (required field, round-trips), the pack warning (`SessionLiveAtPack`), and the open-side render suffix are ALL landed — the codex fix is a collect-side derivation swap, nothing downstream.
product-overlapped: none.
recommended-next: implement the `170500` §4 disposition at `codex.cpp` collect; fixture the negative control (terminal tail ⇒ warning ABSENT).

**(f) R-3.25(b) torn-tail (A3.3)**
PRIMARY_BUCKET: still-open
still-open: `torn_tail` 0 hits in src — unimplemented on BOTH legs.
already-closed: none.
product-overlapped: none; sealed A3.3 defines it completely (no design needed).
recommended-next: implement four branches per leg with retained-prefix byte equality; on codex, only after (a) — branch 3 is unreachable before it, and a branch-3 test green on the hardcoded flag fails review.

**(g) receipts/fixtures substrate**
PRIMARY_BUCKET: still-open
still-open: zero FX-VF / FX-MG keys in tree (§5).
already-closed: none (the existing allowlist-asserting tests are the FLIP ledger, not receipt fixtures).
product-overlapped: none.
recommended-next: build fixtures with their arms as arms land; maintain the flip ledger decided-not-deleted.

## 7. Drift and observations for reconciliation (not defects in the dispatch's sense; routed, not absorbed)

1. **`SessionRowReport` now has NINE data members** — `detail` was appended (`sessions.hpp:46-62`; comment: "Appended last so existing designated initializers stay valid"; render consumes it at `render.cpp:272-274`). The locked A7's CANON closed-row rule closes exact rows over "ALL EIGHT members," and every CANON exact-row object omits `detail`. The lock is intact (the design bytes did not move — §0); the TREE moved after the design's ground-read. Receipt/fixture execution of every `…-exact` row key needs a ruling on the ninth member (close over it with `∅`, or an m-2 CANON amendment). This is an m-2 seam question — routed UP via `s4.orchestrator-planner`, never designed around at this seat.
2. **Parent-doc line drift, behavior identical** (re-found by criterion): consent short-circuit `sessions.cpp:211-222` → `:215-227`; the `Consent::yes` call `:259` → `:265`; the mapper `:297-307` → `:318-326`; codex consent-no `:482-497` → `:494-509`; claude consent-no `:615-634` → `:645-661`; `sessions.hpp:40-58` → `:46-62`. The two allowlist cites (`codex:195`, `claude:331`) are exact.
3. `sessions.cpp:308-314`: adapter-row `live_at_pack` defaults `false` when the manifest lookup misses — a fail-open default in the report layer; plan-level hardening note for the floor/adapter head.
4. No test asserts `Outcome::staged` (0 hits in `tests/`) — the consent-no adapter branch is untested at the baseline; the FX-VF-O1 staged keys will be its first coverage.
5. Boundary contract: not applicable — read-only audit, no writes produced for a downstream consumer.

## 8. Questions routed (none block the audit)

- Q1 → orchestrator (bridge to m-2): the nine-member closed-row ruling (§7.1).
- Q2 → plan/DESIGN phase (not for the bridge yet): the constants' home (per-adapter vs one shared header) and the cross-repo shape of the §A7.10 same-commit mirror (product + harness mirror in this repo; RUNCARD in pdc).
