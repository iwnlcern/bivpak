# GRILL_LOCK — R-4.8 packer-home carrier (rev0 → rev1)

GRILL_LOCK_ID: s4-matrix-arm1-r48-carrier-grill-20260809
DISPATCH_ID: s4-matrix-arm1-r48-carrier
DESIGN_DOC_ID: docs/sprints/2026-08-04-s4-step4/designs/2026-08-09-s4-matrix-arm1-r48-packer-home-carrier-design.md
TRIGGER: DESIGN-REVIEW rev0 must-revise B4 (`DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md`) — production-risk cross-domain seam
DATE: 2026-08-09

Durable record of the decisions closing rev0 blockers B1–B4: one operator-ruled cell,
four code-derived decisions (each with rejected alternatives), and the design-lock impact.
All byte references verified at review base `62dbf16` (blob hashes pinned in the rev0
review relay; unchanged from design commit `fc8f950`).

## Operator-ruled cell

### Q1 — non-absolute non-empty `$HOME` at pack

**RULED (operator, 2026-08-09, inline): treat as ABSENT** — same graceful degrade as
unset/empty. Rationale (operator's): a relative `$HOME` is a degenerate environment no
real system produces; it does not earn an error path. Consequence: pack never fails over
this metadata field; the emittable states remain exactly {absent, non-empty-absolute}.
Rejected: a typed pack error (louder, but fails a pack over metadata and invents an error
path for a near-empty domain).

## Code-derived decisions (from the bytes; no new authority)

### D1 — transport seam (closes B1)

`InstallTarget` (src/adapters/adapter.hpp:156-161) gains one bounded pass-through pair:

```cpp
std::optional<std::string> packer_home;          // image-level; opaque to core
manifest::PathFlavor packer_home_flavor{manifest::PathFlavor::posix};  // meaningful only when packer_home present
```

populated ONCE by `run_session_leg` (src/core/open/sessions.cpp:266-271) from
`manifest.packer_home` / `manifest.packer_home_flavor` at the single existing
`InstallTarget` construction site. Core performs NO interpretation, prefix logic, or path
operation on the value — it is transported opaquely; only the adapter session-install
verifiers (the floor's needle) read it. Both adapter legs receive the same image-level
value by construction (one construction site, proven at `tests/test_sessions.cpp` +
both `tests/test_adapter_{claude,codex}_install.cpp`).

Rejected alternatives:
- per-entry duplication in `AgentSessionEntry`/`SessionProvenance` — already rejected by
  the operator's placement ruling (impossible-disagreement state);
- a new `install()` parameter — churns the adapter API signature for every implementer
  and test double; a struct field is additive and default-benign;
- adapters re-reading the manifest — breaks layering (adapters have no manifest access;
  `run_session_leg` owns the `Manifest`, sessions.cpp:175-179).

### D2 — independent flavor (closes B2, flavor half)

New optional top-level `Manifest.packer_home_flavor` (JSON key `"packer_home_flavor"`,
values `posix|windows|wsl` via the existing `to_string`/`parse_path_flavor`), classified
from the HOME path's OWN spelling by the same `path_flavor()` classifier
(src/core/pack/pack.cpp:131-140). The rev0 claim "same host ⇒ same flavor" is false by
construction: on WSL a source under `/mnt/c/...` classifies `wsl` while the same
process's home `/home/user` classifies `posix`. The two keys co-occur or co-absent
(hardened pairing, see D4).

Rejected alternative: converting the home into the retained `source_path_flavor` — the
conversion is not total (`/home/user` has no `wsl`-flavor spelling); a partial conversion
would be lossy and unfalsifiable.

Still top-level, still written once — within the operator's placement ruling.

### D3 — absoluteness gate (closes B2, absolute half; applies Q1)

Capture rule: serialize only when `env.home.is_absolute()` and non-empty; otherwise the
field pair is ABSENT (Q1 ruling). `process_env()` (pack.cpp:231-245) performs no check
today; the gate lives at the capture site in pack, not in `process_env` (which other
consumers share).

### D4 — empty-string + pairing hardening (closes B3)

rev0 claimed `optional_string` yields `ParseError` on `""` — FALSE at the bytes
(manifest.cpp:99-115 returns every string verbatim, including empty). Corrected
mechanism, both sides:

- **Serializer/model rule:** emit the pair only when `packer_home.has_value() &&
  !packer_home->empty()`. An engaged-but-empty optional in the in-memory model serializes
  as ABSENT (collapse, stated honestly); the writer's emittable states are exactly
  {absent, non-empty}. The round-trip invariant is over emittable states.
- **Parse rule (local, this key only — no change to `optional_string` or its other
  callers):** after `optional_string(object, "packer_home")`, an engaged empty value ⇒
  `ParseError{"packer_home"}`. Pairing hardening: `packer_home` present requires
  `packer_home_flavor` present and valid, and vice versa — a lone key of either name ⇒
  `ParseError` naming the missing/lone key. Absent pair ⇒ both `nullopt` (every
  pre-carrier image).

### D5 — contract routing + proof surface (closes B4)

- The consumer contract is routed in its own relay addressed `TO: s4-floor.planner`
  (CC is not action authority; silence is NOT ratification). Rev1's re-review completes
  only with the floor Planner's affirmative response on record.
- Boundary restated in the 7-part form in rev1 §7 (Writes / Reads / Target entity /
  Downstream consumer / Contract / Proof / No-consumer action).
- Tests assigned to their real surfaces: `tests/test_manifest.cpp` (schema),
  `tests/test_pack.cpp` (capture incl. Q1/D3 cases and the WSL mixed-flavor case),
  `tests/test_sessions.cpp` (run_session_leg populates `InstallTarget` — present
  propagation and absent skip), `tests/test_adapter_claude_install.cpp` +
  `tests/test_adapter_codex_install.cpp` (both adapter legs receive the image-level
  value).

## Design-lock impact (rev1)

rev1 amends §§2-10 of the design doc: adds the flavor field (§3), the absoluteness gate
(§4), the emittable-states serializer rule (§5), the local parse validation + pairing
(§6), the D1 transport seam and 7-part boundary (§7), the new edge cases (§8), the
reassigned test matrix (§9), and reconciles §7/§10's "not read by core restore" to
"transported opaquely by core, interpreted only by adapter verifiers". The operator's
top-level-once placement ruling is UNCHANGED. `format_version` stays 1; no new `ErrKind`;
Step-3 fences untouched.

---

# Appendix — rev1 → rev2 decisions (re-review R1-R3, all code-derived)

TRIGGER: DESIGN-REVIEW rev1 must-revise R1-R3
(`DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md`). No operator cell this
round: every decision is forced at the bytes (layering, the model's own tests, helper
semantics). The floor's `050728` ratification is PRESERVED — the wire shape, own-flavor
meaning, and absence semantics are unchanged by rev2 (the re-review's own criterion for
not re-routing).

### D6 — single optional carrier struct (closes R3, model half)

```cpp
// manifest.hpp
struct PackerHome { std::string path; PathFlavor flavor{PathFlavor::posix}; };
// Manifest:
std::optional<PackerHome> packer_home;   // replaces the rev1 two-member pair
```

One optional. Co-absence is now BY CONSTRUCTION in memory (a lone flavor is
unrepresentable, matching the wire pairing rule), "both nullopt" tests become
`packer_home == std::nullopt`, and pair round-trip equality is a single `==`.
`InstallTarget` transport becomes one field: `std::optional<manifest::PackerHome>
packer_home;`. Rejected: making the flavor a second optional (two optionals recreate the
lone-flavor states the wire forbids); a canonical ignored flavor for absent home (an
unfalsifiable cell — a value that must never be read).

### D7 — core-local total classifier + parity pin (closes R1)

The rev1 classifier claim was false at the bytes: `pack.cpp::path_flavor()` has no
`windows` branch (pack.cpp:131-140). The re-review's suggested reuse of
`rewrite::path_flavor_for()` (rewrite_common.cpp:626-634) is TOTAL but lives in
`src/adapters/` — and the PARSER also needs the classifier (D8 wire validation), so
reuse is CIRCULAR: `rewrite_common` includes `manifest` for `PathFlavor`, so `manifest`
cannot include `rewrite_common`. Decision: a core-local classifier beside the manifest
schema, mirroring the rewrite grammar exactly:

```cpp
// manifest-side helper (single authority for the carrier)
std::optional<PathFlavor> classify_absolute(std::string_view path);
//   wsl:     size>=7 && starts_with("/mnt/") && ascii_alpha(path[5]) && path[6]=='/'
//   windows: (size>=3 && ascii_alpha(path[0]) && path[1]==':' && (path[2]=='\\' || path[2]=='/'))
//            || starts_with("\\\\?\\") || starts_with("//?/")
//   posix:   starts_with('/') and not wsl-form
//   nullopt: everything else (= not absolute in any supported flavor)
```

Precedence wsl-before-posix (a wsl mount is posix-lexical). Grammar parity with
`rewrite::path_flavor_for` is PINNED by a spelling-table test that includes both layers
(tests may depend on both; production layering stays acyclic). `pack.cpp::path_flavor()`
and every `source_path_flavor` caller are UNTOUCHED — no accidental behavior change.
Rejected: reusing `rewrite::path_flavor_for` (circular from manifest); extending pack's
`path_flavor` (changes source-path callers, and still unreachable from manifest); hoisting
rewrite internals into core (touches floor-adjacent adapter files — cross-pair collision;
noted as a possible future refactor, not this carrier's).

### D8 — wire validator, null rule, detail remap (closes R2 + R3 parse half)

- **Validity predicate (one authority, both boundaries):**
  `valid(PackerHome p) := !p.path.empty() && classify_absolute(p.path) == p.flavor`.
  This is host-INDEPENDENT and lexical — native `is_absolute()` cannot judge
  foreign-flavor images.
- **Capture (§4):** `classify_absolute(env.home.generic_string())` engaged ⇒ capture
  `{path, flavor}` (valid by construction); `nullopt` ⇒ ABSENT. This SUBSUMES Q1
  (relative ⇒ not absolute in any flavor ⇒ absent) and is total for Windows homes.
- **Serialize (§5):** emit the two keys iff `packer_home && valid(*packer_home)`;
  otherwise omit both. A manually constructed invalid engaged value (empty, relative,
  flavor-mismatched) COLLAPSES to absent — the same stated-collapse rule D4 established
  for empty, now covering the whole invalid class. Emittable states = {absent, valid}.
- **Parse (§6):** define `present := optional_string(...) engaged` — i.e. key present
  with a non-null string. JSON `null` ≡ missing key, for BOTH keys, by definition (the
  helper collapses them, manifest.cpp:99-115; no raw-key tracking needed — this resolves
  rev1's §6/§8 lone-null contradiction). Then: presence XOR ⇒ `ParseError` naming the
  lone key; both present ⇒ flavor via `parse_path_flavor` with a LOCAL detail remap (its
  hardcoded detail is `source_path_flavor`, manifest.cpp:462 — the carrier remaps its
  failure to `ParseError{"packer_home_flavor"}`; function and existing callers
  untouched), then `valid(pair)` else `ParseError{"packer_home"}` (subsumes `""`,
  relative, and mismatch). Both absent ⇒ `nullopt`.
- Round-trip invariant: over emittable states — absent↔absent, valid↔valid, single `==`.

## Design-lock impact (rev2)

rev2 amends §§3-9: the single-struct model (§3), classifier-driven capture (§4), the
valid-gated serializer (§5), the present/null definition + validator + remap (§6), the
one-field `InstallTarget` transport (§7 — wire contract to the floor UNCHANGED), the
windows/mismatch/lone-null edge rows (§8), and the extended matrix incl. the parity table
and validator falsifiers (§9). Placement ruling, Q1, `format_version` 1, no new
`ErrKind`, fences — all unchanged.
