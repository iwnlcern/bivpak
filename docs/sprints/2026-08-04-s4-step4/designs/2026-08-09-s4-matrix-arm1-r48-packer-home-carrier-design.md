# Arm-1 schema act — R-4.8 pack-time packer-home carrier (design, rev1)

DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
AUTHOR: s4-matrix.planner
DATE: 2026-08-09
STATUS: rev1 — B1-B4 folded; awaiting pair-Implementer re-review + floor Planner's affirmative contract response
GRILL_REQUIRED: yes
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809 (docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-carrier-grill-lock.md)
TRACKER: R-4.8 (../../../pdc/master/RESIDUALS.md) — hard-gated before ANY release
UPSTREAM_DIRECTION: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-PACKER-HOME-CARRIER-INTO-ARM1-SCHEMA-ACT-SCOPE-20260809-024150.md
REV0_REVIEW: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md (must-revise B1-B4; all four verified at the bytes by the pair Planner before this fold)

## 1. Context and problem

The operator's origin-invariant ruling (`215811`) puts the packer HOME/USERNAME in scope for
the floor's session-install verifier, needled path-context. The B2 floor fold proved
(byte-verified at `d6cceba`, re-verified at master `020816`) that the home-prefix needle
cannot be implemented honestly at the floor because nothing in the image carries the
packer's home:

- `SessionProvenance = {store_root, locator, discovery_tier, archived}` — no home
  (`src/core/manifest/manifest.hpp:24`).
- `AgentSessionEntry.original_path` is the session WORKSPACE, which may be outside HOME
  (`manifest.hpp:46`); `store_root` is `CLAUDE_CONFIG_DIR`/`CODEX_HOME`, not home.
- `Env.home` exists at pack (`src/core/pack/pack.cpp:239`, from `$HOME`) but is transient —
  never serialized.

Master ruled (operator-ratified, R-4.8) that the carrier is designed INTO the Arm-1 schema
act now, not bolted on later. The carrier and the floor's needle land TOGETHER on the
schema-act head, so no image ever carries the field without the needle that uses it, and
vice versa.

## 2. Operator rulings folded into this design

- **Placement (2026-08-09, inline): option 1 — one top-level field pair, written once.**
  The packer home is a pack-process fact: one process, one `$HOME`, one value per image.
  A per-entry copy in `SessionProvenance` would duplicate an identical string across every
  session entry and create the syntactic possibility of two entries disagreeing about a
  fact that cannot differ. Top-level makes the impossible state unrepresentable. This is
  an OUTBOUND boundary contract; the floor's needle builds against §7 and must ratify it
  AFFIRMATIVELY (grill D5 — CC silence is not ratification).
- **Q1 (2026-08-09, grill): non-absolute non-empty `$HOME` ⇒ field ABSENT** — a relative
  `$HOME` is a degenerate environment that does not earn an error path; same graceful
  degrade as unset/empty. Pack never fails over this metadata field.

## 3. The fields

```cpp
// src/core/manifest/manifest.hpp — struct Manifest
std::optional<std::string> packer_home;   // absolute packer $HOME at pack time; absent when unknown/degenerate
PathFlavor packer_home_flavor{PathFlavor::posix};  // meaningful only when packer_home is present
```

- **Names:** `packer_home` / `packer_home_flavor` (manifest JSON keys `"packer_home"`,
  `"packer_home_flavor"`), emitted together immediately after `source_path_flavor`.
- **Value:** the packer's absolute home directory path at PACK time, exactly as
  `Env.home` yields it (`generic_string()` — e.g. `/Users/jack`), unnormalized beyond
  that. The carrier does NOT derive a username, trim separators beyond `generic_string()`,
  or otherwise interpret the value. All prefix/username semantics belong to the consumer.
- **Flavor (grill D2):** `packer_home_flavor` is classified from the HOME path's OWN
  spelling by the same `path_flavor()` classifier (`pack.cpp:131-140`), values
  `posix|windows|wsl` via the existing `to_string`/`parse_path_flavor`. It is
  INDEPENDENT of `source_path_flavor` because same host does not imply same flavor: on
  WSL a source under `/mnt/c/...` is `wsl` while the same process's home `/home/user` is
  `posix`. (Rejected: converting the home into the retained source flavor — the
  conversion is not total and would be lossy/unfalsifiable.)

## 4. Capture (pack side)

At the capture site in `pack.cpp` (NOT inside `process_env()`, which other consumers
share), from the existing `adapters::Env`:

- `env.home` non-empty AND `env.home.is_absolute()` →
  `manifest.packer_home = env.home.generic_string()`;
  `manifest.packer_home_flavor = path_flavor(env.home)`.
- `$HOME` unset, empty, or set-but-relative (Q1) → BOTH fields ABSENT. Graceful degrade,
  never an error: an image without the carrier simply gets no home-prefix needle
  coverage, exactly like every pre-carrier image.

## 5. Serialization (emittable states)

`serialize(Manifest)` (`src/core/manifest/manifest.cpp`, top-level cluster :481-484):
after `source_path_flavor`, emit

```
"packer_home": "<value>",
"packer_home_flavor": "<posix|windows|wsl>"
```

ONLY when `packer_home.has_value() && !packer_home->empty()`; otherwise omit BOTH keys.
An engaged-but-empty optional in the in-memory model therefore serializes as ABSENT — a
deliberate, stated collapse (grill D4): the writer's emittable states are exactly
{absent, non-empty-absolute}, and there is no writer path that emits `""` or a lone key.
Deterministic ordering preserved (fixed writer sequence, as today).

## 6. Parse and compatibility (the F+G / enum-hardening posture)

Parse in the top-level cluster (`manifest.cpp:553-557` area):

```cpp
auto packer_home = optional_string(object, "packer_home");
auto packer_home_flavor = optional_string(object, "packer_home_flavor");
// local validation, this key pair only (no change to optional_string or its other callers):
//   packer_home engaged && empty            => ParseError{"packer_home"}
//   packer_home present XOR flavor present  => ParseError naming the lone/missing key
//   flavor present => parse_path_flavor(*)  => ParseError{"packer_home_flavor"} on unknown value
```

`optional_string` (manifest.cpp:99) supplies absent/`null` ⇒ `nullopt` and wrong-type ⇒
`ParseError` (prior art: `SessionIds.parent`/`parent_in_image`, manifest.cpp:271-272).
It returns `""` VERBATIM (it does not reject empties) — the empty-string hardening is the
LOCAL post-check above, not the helper (rev0 misstated this; corrected per B3). Pairing
is hardened: the two keys co-occur or co-absent; a lone key of either name is malformed
by construction because the writer always emits both together (§5).

`format_version` stays 1 and NO `required_capabilities` entry is added: the field pair is
optional metadata in both directions — old reader + new image: unknown keys are ignored
by the key-addressed dom parse (proven at `tests/test_manifest.cpp:113-132`); new reader
+ old image: absent pair ⇒ both `nullopt`. Nothing here narrows what an existing image or
binary can do.

Round-trip invariant (over the writer's emittable states, per §5): for absent and for
non-empty-absolute values, `parse(serialize(m))` yields the same
`packer_home`/`packer_home_flavor` pair.

## 7. Boundary contract and transport seam (grill D1/D5)

**The seam rev0 lacked (B1):** at the bytes, `run_session_leg` owns the whole `Manifest`
(`src/core/open/sessions.cpp:175-179`) but hands adapters only
`InstallTarget{workspace_root, target_store, member_read, capabilities}`
(`sessions.cpp:266-271`, `src/adapters/adapter.hpp:156-161`) — a top-level manifest field
cannot reach the adapter verifiers without transport. rev1 freezes it:

- `InstallTarget` gains one bounded pass-through pair:
  `std::optional<std::string> packer_home;` and
  `manifest::PathFlavor packer_home_flavor{manifest::PathFlavor::posix};`
  (meaningful only when `packer_home` is present).
- `run_session_leg` populates the pair ONCE, at its single existing `InstallTarget`
  construction site, from `manifest.packer_home` / `manifest.packer_home_flavor`. Both
  adapter legs receive the same image-level value by construction.
- Core (open/sessions and everything below it) performs NO interpretation: no prefix
  logic, no username derivation, no path operation on the value. Core TRANSPORTS the
  bytes opaquely; ONLY the adapter session-install verifiers (the floor's needle) read
  them. (This reconciles rev0 §7/§10: "not read by core restore" was imprecise — core
  transports, adapters interpret.)

**The 7-part boundary (B4):**

| Part | Statement |
| --- | --- |
| Writes | `pack.cpp` capture site writes `Manifest.packer_home` + `packer_home_flavor`; `serialize()` emits the key pair (§5) |
| Reads | `parse()` reads the pair (§6); `run_session_leg` copies it into `InstallTarget` (transport only); adapter session-install verifiers read `InstallTarget.packer_home`/`_flavor` |
| Target entity | the manifest (top-level), `InstallTarget` (transport), the per-session-install verify step (consumer) |
| Downstream consumer | the floor's home-prefix needle inside `claude`/`codex` adapter install verify (`install.cpp:651-656/689-693` lineage) — R-4.8 partner work |
| Contract | keys `"packer_home"`+`"packer_home_flavor"`, top-level, optional, co-occurring; absolute pack-time home in its OWN flavor; absent ⇒ needle skips (no error, no warning owed by the carrier) |
| Proof | one `InstallTarget` construction site (`tests/test_sessions.cpp`); both adapter legs receive the value (`tests/test_adapter_claude_install.cpp`, `tests/test_adapter_codex_install.cpp`); schema round-trip + hardening (`tests/test_manifest.cpp`); capture matrix (`tests/test_pack.cpp`) |
| No-consumer action | core restore takes NO action on the value (opaque transport); with no needle present the field is inert metadata |

**Ratification:** this contract is routed in its own relay addressed `TO:
s4-floor.planner`; the floor's AFFIRMATIVE response is required on record before this
design locks (CC silence is not ratification — grill D5).

## 8. Error and edge cases (exhaustive)

| Case | Behavior |
| --- | --- |
| `$HOME` unset at pack | pair absent; pack proceeds |
| `$HOME` empty at pack | pair absent; pack proceeds |
| `$HOME` set but relative (Q1) | pair absent; pack proceeds |
| WSL: source `/mnt/c/...`, home `/home/user` | `source_path_flavor=wsl`, `packer_home_flavor=posix` — independent by design (D2) |
| home with non-ASCII / spaces | carried verbatim (string passthrough; no interpretation) |
| in-memory engaged-but-empty `packer_home` at serialize | pair OMITTED (stated collapse; §5) |
| pre-carrier image read by new binary | both `nullopt`; restore + needle-skip proceed |
| new image read by pre-carrier binary | keys ignored (key-addressed parse; proven `tests/test_manifest.cpp:113-132`) |
| `"packer_home": null` | as absent — but flavor must then also be absent, else lone-key `ParseError` |
| `"packer_home": 42` (wrong type) | `ParseError{"packer_home"}` — fail closed |
| `"packer_home": ""` | `ParseError{"packer_home"}` — LOCAL post-check (§6); writer never emits it |
| lone `"packer_home"` without flavor (or vice versa) | `ParseError` naming the lone/missing key — pairing hardening (§6) |
| `"packer_home_flavor": "vms"` (unknown flavor) | `ParseError{"packer_home_flavor"}` via `parse_path_flavor` |
| manifest value present at restore, needle absent (pre-needle binary) | inert metadata; no action |

No new `ErrKind` member: `ParseError` covers every parse failure; capture failures do not
exist (Q1). The D5 nine-member freeze is untouched.

## 9. Tests (assigned to their real surfaces — grill D5)

`tests/test_manifest.cpp` (schema):
1. Serialize present → both keys after `source_path_flavor`, exact values; absent → neither key.
2. Serialize engaged-but-empty → neither key (collapse case).
3. Round-trip present and absent.
4. Backward-compat fixture: pre-carrier JSON (no keys) → both `nullopt`.
5. Hardening: `null`→absent-pair rule; wrong-type→`ParseError`; `""`→`ParseError`;
   lone key (each direction)→`ParseError`; unknown flavor→`ParseError`.

`tests/test_pack.cpp` (capture, env-controlled):
6. `HOME=/abs/path` → pair present, value exact, flavor classified from home spelling.
7. `HOME` unset → absent. 8. `HOME=` (empty) → absent. 9. `HOME=relative/home` → absent (Q1).
10. `HOME=/mnt/c/Users/x` with posix source → `packer_home_flavor=wsl`,
    `source_path_flavor=posix` (independence, mirror of §8's WSL row).

`tests/test_sessions.cpp` (transport):
11. Manifest with pair present → `run_session_leg` populates `InstallTarget.packer_home`/`_flavor`
    identically for every adapter leg invoked.
12. Manifest without pair → `InstallTarget.packer_home == nullopt` (absent-skip propagates).

`tests/test_adapter_claude_install.cpp` + `tests/test_adapter_codex_install.cpp` (both legs):
13. Each adapter's install path observes the transported value when present and the
    `nullopt` when absent (the needle's own assertions are floor-owned; these prove RECEIPT).

## 10. Out of scope (hard lines)

- The home-prefix needle itself (floor-owned; lands together under R-4.8's gate, but its
  logic, needle-set mechanics, and refusal/consent lane are NOT this design's). These
  tests prove transport/receipt, never needle semantics.
- Any username derivation, path normalization beyond `generic_string()`, prefix logic, or
  ANY core-side interpretation of the value (core transports opaquely — §7).
- Any change to `SessionProvenance`, eligibility, classification, or the repo engine.
  Both Step-3 fences (`scan.cpp:138`, `manifest.cpp:597`) unaffected.
- Any rewriting of restored payloads (the binding line): capturing and transporting
  pack-time metadata is not editing a restored payload.
- Release actions: R-4.8 is hard-gated before ANY release; the release hold is ABSOLUTE.

## 11. Landing

Authored in the Arm-1 schema-act wave on its head; integrates with the floor's needle
under the R-4.8 tracker (carrier + needle land together). Non-blocking to current Arm-1
Wave-A (panel-clean, with master) and to B2's union-scope resume. Design locks only on:
pair-Implementer re-review approve of THIS rev1 + the floor Planner's affirmative §7
contract response, both on record.
