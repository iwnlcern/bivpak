# Arm-1 schema act — R-4.8 pack-time packer-home carrier (design, rev0)

DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
AUTHOR: s4-matrix.planner
DATE: 2026-08-09
STATUS: rev0 — awaiting pair-Implementer DESIGN-REVIEW
TRACKER: R-4.8 (../../../pdc/master/RESIDUALS.md) — hard-gated before ANY release
UPSTREAM_DIRECTION: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-PACKER-HOME-CARRIER-INTO-ARM1-SCHEMA-ACT-SCOPE-20260809-024150.md

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

## 2. Operator ruling folded into this design

**Placement ruled by the operator (2026-08-09, inline to the pair Planner): option 1 —
one top-level field, written once.** The packer home is a pack-process fact: one process,
one `$HOME`, one value per image. A per-entry copy in `SessionProvenance` would duplicate
an identical string across every session entry and create the syntactic possibility of two
entries disagreeing about a fact that cannot differ — an impossible state the schema would
then have to police. Top-level makes the impossible state unrepresentable. This is an
OUTBOUND boundary contract: the floor's needle (unbuilt, deferred to this carrier) builds
against the shape below.

## 3. The field

```cpp
// src/core/manifest/manifest.hpp — struct Manifest
std::optional<std::string> packer_home;   // absolute packer $HOME at pack time; absent when unknown
```

- **Name:** `packer_home` (manifest JSON key `"packer_home"`).
- **Value:** the packer's absolute home directory path at PACK time, exactly as
  `Env.home` yields it (`generic_string()` — e.g. `/Users/jack`), unnormalized beyond
  that. It is the raw reference frame the needle matches against; the carrier does NOT
  derive a username, trim trailing separators beyond `generic_string()`'s behavior, or
  otherwise interpret the value. All prefix/username semantics belong to the consumer.
- **Flavor:** shares the existing top-level `source_path_flavor`. `$HOME` and the packed
  workspace are observed by the same process on the same host at pack time, so they are
  the same flavor by construction; no new flavor field. (If a future flavor-divergent
  packer appears, that is a schema revision, not this carrier.)

## 4. Capture (pack side)

At `pack.cpp`, from the existing `adapters::Env` (`process_env().home`):

- `$HOME` set and non-empty → `manifest.packer_home = env.home.generic_string()`.
- `$HOME` unset or empty (`Env.home` is the empty path) → field ABSENT (`nullopt`).
  Graceful degrade, never an error: an image without the carrier simply gets no
  home-prefix needle coverage, exactly like every pre-carrier image.

The writer NEVER emits an empty string: absent-or-empty at capture collapses to the field
not being written. There is no third state.

## 5. Serialization

`serialize(Manifest)` (`src/core/manifest/manifest.cpp`, top-level cluster at :481-484):
after `source_path_flavor`, emit

```
"packer_home": "<value>"        // only when packer_home.has_value()
```

Omit the key entirely when absent. Deterministic ordering preserved (fixed writer
sequence, as today).

## 6. Parse and compatibility (the F+G / enum-hardening posture)

Parse in the top-level cluster (`manifest.cpp:553-557` area) via the EXISTING helper:

```cpp
auto packer_home = optional_string(object, "packer_home");
```

`optional_string` (manifest.cpp:99) already implements exactly the tolerated-absent
contract, with prior art in the same schema (`SessionIds.parent` /
`parent_in_image`, manifest.cpp:271-272):

- key absent → `nullopt` (every pre-carrier image parses unchanged);
- JSON `null` → `nullopt`;
- present but non-string → `ParseError` (typed, fail-closed on malformed input);
- present string → value carried verbatim; **present-but-empty string → `ParseError`**
  (the writer never emits it — see §5 — so an empty value is malformed input by
  construction, and tolerating it would create the unfalsifiable third state §4 removes).

`format_version` stays 1 and NO `required_capabilities` entry is added: the field is
optional metadata in both directions (old reader + new image: unknown key is ignored by
the key-addressed dom parse; new reader + old image: absent → `nullopt`). This is the
compatibility shape the schema act's rules require; nothing here narrows what an existing
image or binary can do.

Round-trip invariant: `parse(serialize(m)).packer_home == m.packer_home` for both the
present and absent cases (empty-at-capture collapses to absent before serialize, so the
invariant is over the two legal states).

## 7. Consumer contract (bounded, outbound)

- The value is consumed ONLY by the floor's session-install home-prefix needle: read
  `manifest.packer_home` ONCE per image; `nullopt` → skip the home-prefix check for that
  image (no error, no warning path owned by the carrier).
- It is METADATA. It is NOT a rewrite target, NOT read by the core restore path, NOT an
  eligibility/classification input, and NOT rendered into any path operation. This keeps
  it inside the operator's binding line: the tool edits nothing but session-history
  artifacts; capturing pack-time metadata is not editing a restored payload.
- Contract fields for the floor (ratify or object at design-review): key `"packer_home"`,
  top-level, optional string, absolute pack-time home path in `source_path_flavor`'s
  flavor, absent ⇒ skip.

## 8. Error and edge cases (exhaustive)

| Case | Behavior |
| --- | --- |
| `$HOME` unset at pack | field absent; pack proceeds |
| `$HOME` empty string at pack | field absent; pack proceeds |
| pre-carrier image read by new binary | `nullopt`; restore + needle-skip proceed |
| new image read by pre-carrier binary | key ignored (key-addressed parse); unchanged behavior |
| `"packer_home": null` | `nullopt` (existing `optional_string` semantics) |
| `"packer_home": 42` (wrong type) | `ParseError{"packer_home"}` — fail closed |
| `"packer_home": ""` (empty string) | `ParseError{"packer_home"}` — writer never emits it; malformed by construction |
| home with non-ASCII / spaces | carried verbatim (string passthrough; no interpretation) |

No new `ErrKind` member: `ParseError` already covers the only failure mode. The D5
nine-member freeze is untouched.

## 9. Tests (schema-act test surface, `tests/test_manifest.cpp`)

1. RED/GREEN serialize: manifest with `packer_home` present → JSON contains the key with
   the exact value after `source_path_flavor`; absent → key not present in output.
2. Round-trip present: serialize→parse yields the same value.
3. Round-trip absent: serialize→parse yields `nullopt`.
4. Backward-compat fixture: a pre-carrier manifest JSON (no key) parses OK, `nullopt`.
5. `null` → `nullopt`; wrong-type (`42`) → `ParseError` naming `packer_home`;
   empty string (`""`) → `ParseError` naming `packer_home`.
6. Pack-side capture: pack with `HOME` set → manifest carries it; with `HOME`
   unset/empty → absent (via the existing pack test seam's env control).

## 10. Out of scope (hard lines)

- The home-prefix needle itself (floor-owned; lands together under R-4.8's gate, but its
  logic, needle-set mechanics, and refusal/consent lane are NOT this design's).
- Any username derivation, path normalization beyond `generic_string()`, or prefix logic.
- Any change to `SessionProvenance`, restore, eligibility, classification, or the repo
  engine. Both Step-3 fences (`scan.cpp:138`, `manifest.cpp:597`) unaffected.
- Any rewriting of restored payloads (the binding line).
- Release actions: R-4.8 is hard-gated before ANY release; the release hold is ABSOLUTE.

## 11. Landing

Authored in the Arm-1 schema-act wave on its head; integrates with the floor's needle
under the R-4.8 tracker (carrier + needle land together). Non-blocking to current Arm-1
Wave-A (panel-clean, with master) and to B2's union-scope resume.
