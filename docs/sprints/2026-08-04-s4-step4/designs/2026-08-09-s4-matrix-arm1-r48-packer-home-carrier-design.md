# Arm-1 schema act — R-4.8 pack-time packer-home carrier (design, rev3)

DISPATCH_ID: s4-matrix-arm1-r48-carrier
PARENT_DISPATCH_ID: s4-build-standup-step4-opening-dispatch
AUTHOR: s4-matrix.planner
DATE: 2026-08-09
STATUS: rev3 — MF-1 Option A folded (panel-found degenerate-root tightening, ruled `204159`); awaiting pair-Implementer re-review on THIS doc hash; floor ratification `050728` stands as a ruled COMPATIBLE NARROWING (floor CC'd on the ruling to object)
GRILL_REQUIRED: yes
GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809 (docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-carrier-grill-lock.md — incl. the rev2 appendix D6-D8)
TRACKER: R-4.8 (../../../pdc/master/RESIDUALS.md) — hard-gated before ANY release
UPSTREAM_DIRECTION: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-PACKER-HOME-CARRIER-INTO-ARM1-SCHEMA-ACT-SCOPE-20260809-024150.md
REV0_REVIEW: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md (must-revise B1-B4)
REV1_REVIEW: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md (must-revise R1-R3; all three verified at the bytes by the pair Planner before this fold)
REV2_REVIEW: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md (approve, on rev2 hash `349ef6e1…`; lineage-corrected at `…061515`)
PANEL: docs/sprints/2026-08-04-s4-step4/reviews/2026-08-09-s4-matrix-r48-carrier-panel-29796bb.md (sealed `006144b2…`; MF-1 = the degenerate-root cell this rev folds)
MF1_RULING: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-R48-MF1-RULED-OPTION-A-TIGHTEN-NOW-FOLDS-ENDORSED-20260809-204159.md (Option A; floor-contract wording ruled a compatible narrowing, no re-ratification)
FLOOR_RATIFICATION: .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-FLOOR-PLANNER-R48-CONSUMER-CONTRACT-RATIFIED-20260809-050728.md (approve; wire shape preserved by rev2, so it stands per the rev1 re-review's own criterion)

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

- **Placement (2026-08-09, inline): option 1 — one top-level carrier, written once.**
  The packer home is a pack-process fact: one process, one `$HOME`, one value per image.
  A per-entry copy would duplicate an identical value across every session entry and make
  an impossible-disagreement state representable. Top-level makes it unrepresentable.
  The floor RATIFIED the resulting §7 contract affirmatively (`050728`), with the
  honest-packer limitation acknowledged on their record and two consumer-side duties
  taken.
- **Q1 (2026-08-09, grill): non-absolute non-empty `$HOME` ⇒ carrier ABSENT** — a
  relative `$HOME` is a degenerate environment that does not earn an error path; same
  graceful degrade as unset/empty. Pack never fails over this metadata. (rev2 subsumes
  Q1 under the classifier: not-absolute-in-any-flavor ⇒ absent, grill D8.)

## 3. The model and the wire (grill D6)

```cpp
// src/core/manifest/manifest.hpp
struct PackerHome {
  std::string path;                       // absolute packer $HOME at pack time, verbatim generic_string()
  PathFlavor flavor{PathFlavor::posix};   // classified from path's OWN spelling
};

// struct Manifest:
std::optional<PackerHome> packer_home;    // one optional; absent when unknown/degenerate
```

- **In memory:** ONE optional struct. Co-absence is by construction — a lone flavor is
  unrepresentable, mirroring the wire pairing rule. "Absent" is `std::nullopt`; pair
  equality and round-trip checks are a single `==`.
- **On the wire:** two JSON keys, emitted together immediately after
  `source_path_flavor`: `"packer_home"` (string) and `"packer_home_flavor"`
  (`posix|windows|wsl`). This is EXACTLY the shape the floor ratified — rev2 changes the
  producer-side model only, not the wire.
- **Value semantics:** the packer's absolute home at PACK time, verbatim
  (`generic_string()`), no username derivation, no normalization beyond that. All
  prefix/username semantics belong to the consumer (the floor's needle and its
  `origin_spellings`/`derive_pair_set` machinery).

**The classifier (grill D7 — core-local, total, single authority):**

```cpp
std::optional<PathFlavor> classify_absolute(std::string_view path);
//   wsl:     size>=7 && starts_with("/mnt/") && ascii_alpha(path[5]) && path[6]=='/'
//   windows: (size>=3 && ascii_alpha(path[0]) && path[1]==':' && (path[2]=='\\' || path[2]=='/'))
//            || starts_with("\\\\?\\") || starts_with("//?/")
//   posix:   starts_with('/') and not wsl-form        (precedence: wsl before posix)
//   nullopt: everything else = not absolute in any supported flavor
```

It lives beside the manifest schema (core), NOT in `src/adapters/rewrite_common.cpp`:
the parser needs it (§6) and `manifest` cannot include `rewrite_common` (which itself
includes `manifest` — circular). Its grammar MIRRORS `rewrite::path_flavor_for` +
`windows_drive_path`/`windows_extended_path`/`wsl_mount_path`
(rewrite_common.cpp:43-53,626-634) and the parity is PINNED by a spelling-table test that
includes both layers (§9 test 14). `pack.cpp::path_flavor()` and all `source_path_flavor`
callers are UNTOUCHED. This corrects rev1's false claim that the pack classifier could
emit `windows` (it has no such branch, pack.cpp:131-140).

**Validity predicate (grill D8 + MF-1 rev3 — one authority at every boundary):**

```cpp
valid(PackerHome p) := classify_absolute(p.path) == p.flavor
                       && non_degenerate(p.path, p.flavor)

// non_degenerate — a non-empty remainder after the flavor's root prefix (MF-1, ruled
// Option A at `204159`): a bare root is not a usable reference frame, and an untrusted
// image shipping one would make the future needle's home-prefix match EVERY absolute
// path of that flavor (fire-on-everything — a corrupted control, a worse class than the
// ratified absent⇒skip).
//   posix:            path.size() > 1               // "/" is degenerate
//   wsl:              path.size() > 7               // "/mnt/c/" is degenerate
//   windows drive:    path.size() > 3               // "C:/", "C:\" are degenerate
//   windows extended: path.size() > 4               // "//?/", "\\?\" are degenerate
```

The CLASSIFIER is untouched by rev3 — its grammar stays parity-pinned to
`rewrite_common` (§9 test 14); only the validity predicate above it tightens. The old
`!path.empty()` conjunct is subsumed: an empty path classifies `nullopt` and fails the
flavor match. Host-independent and lexical — native
`std::filesystem::path::is_absolute()` cannot judge foreign-flavor images and is not
used at any wire boundary.

## 4. Capture (pack side)

At the capture site in `pack.cpp` (NOT inside `process_env()`, which other consumers
share), from the existing `adapters::Env`:

- Capture gates on the FULL validity predicate (classify + non-degenerate): engaged ⇒
  `manifest.packer_home = PackerHome{env.home.generic_string(), *flavor}` — valid by
  construction.
- Everything else ⇒ carrier ABSENT: unset, empty, relative (Q1), any non-absolute
  spelling, and (rev3) a degenerate bare root — `HOME=/`, `HOME=/mnt/c/`, `HOME=C:\`
  degrade to the already-ratified skip path, strictly safer than shipping a root-only
  reference frame and nil-cost (none is a plausible home). Graceful degrade, never an
  error: an image without the carrier simply gets no home-prefix needle coverage,
  exactly like every pre-carrier image.

A native Windows home (`C:/Users/x`, `C:\Users\x`, extended `\\?\C:\Users\x`) classifies
`windows`; a WSL home under `/mnt/<drive>/` classifies `wsl`; an ordinary
`/home/user`/`/Users/jack` classifies `posix`. Total — no home spelling is unclassifiable
while still being serialized.

## 5. Serialization (emittable states)

`serialize(Manifest)` (`src/core/manifest/manifest.cpp`, top-level cluster :481-484):
after `source_path_flavor`, emit

```
"packer_home": "<path>",
"packer_home_flavor": "<posix|windows|wsl>"
```

iff `packer_home && valid(*packer_home)`; otherwise omit BOTH keys. A manually
constructed invalid engaged value (empty, relative, flavor-mismatched, or — rev3 — a
degenerate bare root) COLLAPSES to absent — the same stated-collapse rule rev1
established for empty, now covering the whole invalid class (grill D8 + MF-1). The writer's emittable states are exactly
{absent, valid (path,flavor)}; there is no writer path that emits `""`, a lone key, a
relative path, or a mismatched pair. Deterministic ordering preserved.

## 6. Parse and compatibility (the F+G / enum-hardening posture)

Parse in the top-level cluster (`manifest.cpp:553-557` area):

- **Presence definition:** `present := optional_string(object, key)` returns an ENGAGED
  value. JSON `null` ≡ missing key, for BOTH keys, by definition — `optional_string`
  collapses the two (manifest.cpp:99-115) and the carrier adopts that collapse as its
  rule, so no raw-key-presence tracking exists or is needed. (This resolves rev1's
  lone-null contradiction: `"packer_home": null` with no flavor key IS the absent pair.)
- **Pairing:** presence XOR ⇒ `ParseError` with detail ALWAYS `"packer_home_flavor"` —
  in BOTH directions, per §8's exhaustive table (rev3 wording fix: rev2's "naming the
  lone key" implied two possible details; the code and §8 have always resolved both to
  the flavor key, and this sentence now says so). Both absent ⇒
  `manifest.packer_home = std::nullopt`.
- **Both present:** flavor via `parse_path_flavor`, with a LOCAL detail remap — that
  helper's failure detail is hardcoded `source_path_flavor` (manifest.cpp:462), so the
  carrier maps its error to `ParseError{"packer_home_flavor"}` (helper and existing
  callers untouched). Then the validator: `valid({path, flavor})` else
  `ParseError{"packer_home"}` — this subsumes `""`, relative spellings, path/flavor
  mismatches (e.g. a posix path declared `windows`), and (rev3) degenerate bare roots
  (`/`, `/mnt/c/`, `C:/`, `//?/`, `\\?\`): a degenerate carrier is MALFORMED and
  fail-closes under §5/§6's existing rule for invalid values — not a new semantic. A
  hostile manifest cannot deliver a degenerate value past parse: present ⇒ non-empty,
  absolute, in its declared-and-verified flavor, with a non-empty remainder past the
  flavor's root.

`format_version` stays 1 and NO `required_capabilities` entry is added: the carrier is
optional metadata in both directions — old reader + new image: unknown keys are ignored
by the key-addressed dom parse (proven at `tests/test_manifest.cpp:113-132`); new reader
+ old image: absent ⇒ `nullopt`. Nothing here narrows what an existing image or binary
can do.

Round-trip invariant (over the writer's emittable states, §5):
`parse(serialize(m)).packer_home == m.packer_home` for absent and for every valid value.

## 7. Boundary contract and transport seam (grill D1/D5/D6)

**The seam:** at the bytes, `run_session_leg` owns the whole `Manifest`
(`src/core/open/sessions.cpp:175-179`) but hands adapters only
`InstallTarget{workspace_root, target_store, member_read, capabilities}`
(`sessions.cpp:266-271`, `src/adapters/adapter.hpp:156-161`). rev2 transport:

- `InstallTarget` gains ONE bounded pass-through field:
  `std::optional<manifest::PackerHome> packer_home;`
- `run_session_leg` populates it ONCE, at its single existing `InstallTarget`
  construction site, by copying `manifest.packer_home`. Both adapter legs receive the
  same image-level value by construction.
- Core (open/sessions and below) performs NO interpretation: no prefix logic, no
  username derivation, no path operation on the value. Core TRANSPORTS the struct
  opaquely; ONLY the adapter session-install verifiers (the floor's needle) read it.

**The 7-part boundary:**

| Part | Statement |
| --- | --- |
| Writes | `pack.cpp` capture site writes `Manifest.packer_home`; `serialize()` emits the valid-gated key pair (§5) |
| Reads | `parse()` reads + validates the pair (§6); `run_session_leg` copies the struct into `InstallTarget` (transport only); adapter session-install verifiers read `InstallTarget.packer_home` |
| Target entity | the manifest (top-level), `InstallTarget` (transport), the per-session-install verify step (consumer) |
| Downstream consumer | the floor's home-prefix needle inside `claude`/`codex` adapter install verify (`install.cpp:651-656/689-693` lineage) — R-4.8 partner work |
| Contract | wire keys `"packer_home"`+`"packer_home_flavor"`, top-level, optional, co-occurring; present ⇒ non-empty absolute in its own verified flavor with a non-empty remainder past the flavor's root (rev3 narrowing); absent ⇒ needle skips (no error, no warning owed by the carrier) — RATIFIED by the floor at `050728`, wire-identical; the rev3 validator change is a ruled COMPATIBLE NARROWING (`204159`: strictly safer for the consumer, no plausible home excluded; floor CC'd to object) |
| Proof | one `InstallTarget` construction site (`tests/test_sessions.cpp`, incl. the injectable `CountingAdapter` seam the re-review confirmed); both adapter legs receive the value (`tests/test_adapter_claude_install.cpp`, `tests/test_adapter_codex_install.cpp`); schema round-trip + hardening + classifier parity (`tests/test_manifest.cpp`); capture matrix (`tests/test_pack.cpp`) |
| No-consumer action | core restore takes NO action on the value (opaque transport); with no needle present the field is inert metadata |

**Ratification status:** the floor's affirmative approve (`050728`) covers exactly this
wire shape, own-flavor meaning, and absence semantics — all preserved by rev2 (only the
producer-side in-memory model changed), so per the rev1 re-review's own criterion the
ratification STANDS and no re-route is owed. Any future wire change re-routes to the
floor explicitly.

## 8. Error and edge cases (exhaustive)

| Case | Behavior |
| --- | --- |
| `$HOME` unset at pack | absent; pack proceeds |
| `$HOME` empty at pack | absent; pack proceeds |
| `$HOME` set but relative (Q1) | absent (classifier `nullopt`); pack proceeds |
| `$HOME` a degenerate bare root — `/`, `/mnt/c/`, `C:/`, `C:\`, `//?/`, `\\?\` (rev3) | absent (fails `non_degenerate`); pack proceeds |
| `$HOME=/Users/jack` | present, flavor `posix` |
| `$HOME=/mnt/c/Users/jack` (WSL) | present, flavor `wsl`; with a posix source, `source_path_flavor` independently `posix` — independence by design |
| `$HOME=C:/Users/x` or `C:\Users\x` | present, flavor `windows` (drive grammar, both separators) |
| `$HOME=\\?\C:\Users\x` (extended) | present, flavor `windows` (extended grammar) |
| home with non-ASCII / spaces | carried verbatim (string passthrough; no interpretation) |
| in-memory engaged-but-invalid at serialize (empty/relative/mismatch) | keys OMITTED (stated collapse; §5) |
| pre-carrier image read by new binary | `nullopt`; restore + needle-skip proceed |
| new image read by pre-carrier binary | keys ignored (key-addressed parse; proven `tests/test_manifest.cpp:113-132`) |
| `"packer_home": null`, no flavor key | absent pair (null ≡ missing; §6) |
| `"packer_home": null` + flavor present | lone-flavor `ParseError{"packer_home_flavor"}` (null ≡ missing, so the flavor is present without its partner) |
| lone `"packer_home"` (no flavor) | `ParseError{"packer_home_flavor"}` naming the missing partner per §6 pairing |
| `"packer_home": 42` (wrong type) | `ParseError{"packer_home"}` (existing `optional_string` behavior) |
| `"packer_home": ""` | `ParseError{"packer_home"}` via the validator |
| `"packer_home": "relative/home"` (any declared flavor) | `ParseError{"packer_home"}` via the validator |
| flavor mismatch (e.g. posix path declared `windows`; `/mnt/c/...` declared `posix`) | `ParseError{"packer_home"}` via the validator |
| degenerate bare root with its own (matching) flavor — `"/"` posix; `"/mnt/c/"` wsl; `"C:/"`/`"C:\"` windows; `"//?/"`/`"\\?\"` windows (rev3) | `ParseError{"packer_home"}` via the validator (malformed, fail-closed — §6) |
| `"\\?\C:\Users\x"` declared `windows` | present, valid (extended spelling with a non-empty remainder — the rev3 rule bans only the bare 4-byte prefix) |
| `"packer_home_flavor": "vms"` (unknown) | `ParseError{"packer_home_flavor"}` via the LOCAL remap (helper's own detail is `source_path_flavor`) |
| manifest value present at restore, needle absent (pre-needle binary) | inert metadata; no action |

Pairing errors name the key that is present-without-partner or the missing partner
consistently: the detail is always the FLAVOR key when the flavor is the lone/missing
side, and the HOME key when the home value itself is malformed. No new `ErrKind` member:
`ParseError` covers every parse failure; capture failures do not exist (Q1/D8). The D5
nine-member freeze is untouched.

## 9. Tests (assigned to their real surfaces)

`tests/test_manifest.cpp` (schema):
1. Serialize valid → both keys after `source_path_flavor`, exact values; absent → neither key.
2. Serialize engaged-but-invalid (empty; relative; posix-declared-windows) → neither key (collapse).
3. Round-trip valid per flavor: posix, wsl, windows drive `/`, windows drive `\`, windows extended.
4. Round-trip absent: `nullopt` → no keys → `nullopt`.
5. Backward-compat fixture: pre-carrier JSON (no keys) → `nullopt`.
6. Null rule: `"packer_home": null` alone → `nullopt`; null + flavor → `ParseError` detail `packer_home_flavor`.
7. Lone key each direction → `ParseError` naming the missing/lone partner per §8.
8. Wrong type → `ParseError{"packer_home"}`.
9. `""` → `ParseError{"packer_home"}`.
10. Relative value (each flavor declared) → `ParseError{"packer_home"}`.
11. Mismatch matrix: posix path declared `windows`/`wsl`; `/mnt/c/...` declared `posix`; `C:\...` declared `posix` → `ParseError{"packer_home"}`.
11b. Degenerate-root matrix (rev3, MF-1): `"/"` posix; `"/mnt/c/"` wsl; `"C:/"` and `"C:\"` windows; `"//?/"` and `"\\?\"` windows → `ParseError{"packer_home"}`; positive control `"\\?\C:\Users\x"` windows → valid. Serialize side: each degenerate value engaged-in-memory → both keys OMITTED (collapse, extends test 2).
12. Unknown flavor `"vms"` → `ParseError` with detail EXACTLY `packer_home_flavor` (remap falsifier).
13. `classify_absolute` unit rows: all §3 grammar branches + `nullopt` cases (relative, empty, `mnt/c/x` missing lead slash, `C:` two chars).
14. PARITY TABLE: `classify_absolute` agrees with `rewrite::path_flavor_for` on every absolute spelling in the table (both layers included by the test target; drift falsifier).

`tests/test_pack.cpp` (capture, env-controlled):
15. `HOME=/abs/posix` → present, posix. 16. `HOME` unset → absent. 17. `HOME=` → absent.
18. `HOME=relative/home` → absent (Q1). 18b. `HOME=/` → absent (degenerate root, rev3).
19. `HOME=/mnt/c/Users/x`, posix source → carrier `wsl` + `source_path_flavor` `posix`
    (independence). 20. `HOME=C:/Users/x` → present, windows (lexical capture is
    host-independent — settable on any CI host).

`tests/test_sessions.cpp` (transport):
21. Manifest with carrier → `run_session_leg` populates `InstallTarget.packer_home`
    identically for every adapter leg invoked (via the existing `CountingAdapter` seam).
22. Manifest without carrier → `InstallTarget.packer_home == nullopt` (absent-skip propagates).

`tests/test_adapter_claude_install.cpp` + `tests/test_adapter_codex_install.cpp` (both legs):
23. Each adapter's install path observes the transported value when present and the
    `nullopt` when absent (RECEIPT only; needle assertions are floor-owned).

## 10. Out of scope (hard lines)

- The home-prefix needle itself (floor-owned; lands together under R-4.8's gate). These
  tests prove transport/receipt, never needle semantics.
- Any username derivation, normalization beyond `generic_string()`, prefix logic, or ANY
  core-side interpretation of the value (core transports opaquely — §7).
- Any change to `SessionProvenance`, eligibility, classification, the repo engine,
  `pack.cpp::path_flavor()`/`source_path_flavor` semantics, or `rewrite_common.cpp`.
  Both Step-3 fences (`scan.cpp:138`, `manifest.cpp:597`) unaffected.
- Any rewriting of restored payloads (the binding line): capturing and transporting
  pack-time metadata is not editing a restored payload.
- Release actions: R-4.8 is hard-gated before ANY release; the release hold is ABSOLUTE.

## 11. Landing

Authored in the Arm-1 schema-act wave on its head; integrates with the floor's needle
under the R-4.8 tracker (carrier + needle land together). Non-blocking to current Arm-1
Wave-A (panel-clean, with master) and to B2's union-scope resume. Design locks on:
pair-Implementer re-review approve of THIS rev3 on its exact doc hash (the floor's
`050728` ratification on record; the rev3 validator tightening is a ruled compatible
narrowing per `204159`, floor CC'd there to object). rev3 implements inside the fold
directed by that ruling: ONE commit with the panel's MF-2..MF-6 test must-fixes, then
one targeted re-check at the new head.
