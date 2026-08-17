## RECONCILE — **FALSIFIER RUN: m-1's registered prediction CONFIRMED on BOTH variants, exit 3 / `UnmanifestedMember`, at `9729191`** — **VARIANT 1 (entry-level members) → exit 3, `UnmanifestedMember`, `path: "agents/codex/entry-level.jsonl"`. VARIANT 2 (child-level members ONLY) → exit 3, `UnmanifestedMember`, `path: "agents/codex/child-level.jsonl"`. The prediction was registered so the leg could falsify m-1; it did not — it confirmed them, and the `error.path` field discriminates the two variants, which is what makes variant 2 load-bearing rather than a restatement.** **ARM (a′)'s CHILD FOOTPRINT IS NOW WITNESSED, NOT ARGUED: variant 2's member is declared ONLY under `children[*].artifacts`, so an entry-artifacts-only widening — un-primed arm (a) — leaves this leg RED. The incompleteness of (a) is now a measurement rather than a sentence, exactly as the dispatch asked.** **AND A NEAR-MISS I AM DISCLOSING BECAUSE IT WOULD HAVE INVERTED THE RESULT: my FIRST invocation used `--into`, which is not a flag. It returned exit 5 / `UsageError` / `unknown-flag` — and the envelope even said `"verb": "pack"`. Had I read that as the falsifier's answer I would have reported a non-3 exit and "refuted" m-1 on a typo. I validated the instrument before reading anything: a deliberately corrupt image returns exit 3 / `NotABivpakImage`, proving the invocation reaches the open path rather than dying in argument parsing. THE CONTROL IS THE ONLY REASON THIS RESULT IS TRUSTWORTHY.** **The blocker I routed at `171847` is now confirmed by execution, not inference. Addendum L is unblocked on this leg; m-3's concurrence remains theirs.** No product byte, no fold, no token. `9729191` unchanged; branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE.

ROLE: Planner
PHASE: RECONCILE
AUTHORITY: review-only
DISPATCH_ID: s4-floor-slice-e-falsifier-confirmed
PARENT_DISPATCH_ID: s4-floor-slice-e-run-falsifier-a-prime
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-RUN-FALSIFIER-NOW-GATES-EVERYTHING-A-PRIME-CONVERGED-20260816-205607.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — this is the evidence act the dispatch assigned to this seat. It unblocks addendum L on the falsifier leg only; m-3's concurrence and m-1's authoring remain theirs. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-K-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-K-5da667fa-lock-20260816
SECOND_DESIGN_LOCK: m3-addendum-4-9049de44-lock-20260816, m3-addendum-5-b8686c75-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4.orchestrator-planner
CC: operator, s4.orchestrator-reviewer, s4-floor.implementer, master.orchestrator-planner, m-1.planner, m-3.planner
SUBJECT: RECONCILE — falsifier run at 9729191: BOTH variants exit 3 / UnmanifestedMember, confirming m-1's registered prediction; variant 2 witnesses arm (a)'s incompleteness; instrument validated by a corrupt-image control after a first invocation returned a false negative

## 1. Result — against m-1's registered prediction

```text
REGISTERED PREDICTION (m-1)   exit 3, UnmanifestedMember

VARIANT 1  entry-level agents/… member, present in tar AND checksums
           EXIT 3 · kind UnmanifestedMember · path "agents/codex/entry-level.jsonl"   CONFIRMED

VARIANT 2  child-level agents/… member ONLY (entry artifacts[] empty)
           EXIT 3 · kind UnmanifestedMember · path "agents/codex/child-level.jsonl"   CONFIRMED
```

**The prediction was registered so the leg could falsify m-1. It did not. Both variants land exactly on it**, and the `error.path` differs between them — the archive-integrity gate names the specific member it refused, which is what separates the two legs rather than leaving variant 2 a restatement of variant 1.

**What this settles.** The blocker routed at `171847` was E1 static reading; it is now **executed**. An archive carrying real transcript bytes for a schema-3 entry is refused wholesale at `open.cpp:280-282` before preview, skip, disclosure or exit 0. The locked A5/K forward-compat path is unreachable for any archive a real packer would produce.

**What variant 2 additionally settles — the reason it was worth building.** Its member is declared **only** under `children[*].artifacts`. Under un-primed arm (a) — widening the stub to carry entry-level `artifacts[]` alone — this leg **stays red**, because `required_agent_members` unions `child.artifacts` too (`open.cpp:180-181`). **Arm (a′)'s child footprint is therefore load-bearing as a measured fact, not an argued one.**

## 2. Instrument validation — and the near-miss that makes it necessary

**My first invocation was wrong and would have inverted the result.** I passed `--dest`'s job to a flag that does not exist:

```text
FIRST ATTEMPT   biv open <image> --json --into <dir>
                -> EXIT 5 · kind UsageError · detail "unknown-flag" · verb "pack"
```

**Exit 5, not 3.** Read naively that is a refutation of m-1 — reported, it would have sent a wrong finding up the chain on the strength of a typo, and the envelope's `"verb": "pack"` on an `open` command would have been the only tell. The accepted flag set is `--help --json --consent --dest --agent-bin --rename --abort-on-collision --verify` (`src/cli/args.cpp`).

**The control that makes the real result trustworthy:**

```text
CONTROL   a deliberately corrupt (non-archive) file, same invocation shape
          -> EXIT 3 · kind NotABivpakImage
```

That proves the invocation **reaches the open path** and dies on archive semantics rather than in argument parsing. A bare "exit 3" without this control is indistinguishable from exit 3 for an unrelated reason. **Same discipline as the blind `\s` pattern earlier in this review: a check that cannot return the other answer proves nothing.**

## 3. Reproduction — so m-1 and m-3 can re-run it rather than trust me

```text
binary    build/ci-macos/biv in the slice-E worktree at 9729191
          VALIDATED as built from these bytes: mtime 16:11:16 > newest src 15:57:14;
          `strings` contains both "EntrySchemaSkipped" and "entry_schema_unparsed_count"
image     hand-crafted (no packer emits schema-3; pack.cpp:504 maxes at 2):
          ustar tar, member order manifest.json, checksums.json, agents/codex/<member>.jsonl,
          zstd-framed. manifest carries ONE agent_sessions entry {agent:"codex", entry_schema:3}
          plus the artifacts declaration that distinguishes the variants; checksums.json lists
          the member with its real sha256 so the :272 membership check PASSES and the refusal
          is unambiguously the :280 allow-set gate
command   biv open <image>.bvpk --json --dest <out>
isolation HOME + CODEX_HOME + CODEX_SQLITE_HOME all redirected into the scratch tree.
          THE OPERATOR'S LIVE ~/.claude AND ~/.codex WERE NEVER READ OR WRITTEN.
artifacts scratch only; no repo file created, no product byte touched
```

**Evidence level: E2** — local command proof (fixture + shipped binary + process exit code). Not E3: this is not an integration/staging run, and I am not inflating it.

## 4. What this unblocks, and what it does not

```text
UNBLOCKED   the falsifier leg gating ADDENDUM L — confirmed on both variants
STILL OWED  m-3's (a′) concurrence + the list/info answer (theirs, addressed by master)
            m-1 authors L only after BOTH the falsifier confirms AND m-3 concurs
            — their pre-committed order, unchanged by this result
NOT TOUCHED M-b rides the a′ fold when L lands; leg (p)'s parity deferral stands;
            M-a (.github CI gates) held at master
```

**I have not folded anything and issued no token.** `9729191` stands implemented and unmerged under the m-1/m-3 byte reviews.

ACTIONS_GIT_REF: no product, test or fixture edit at this seat, and no repo file created — the falsifier images, isolated HOME and captured envelopes live entirely under the session scratchpad. Read-only in the repo: `src/cli/args.cpp` flag set, `open.cpp:176-185`/`:272-282`, manifest and checksums parse requirements, all at `9729191`. Binary validated as built from `9729191` before use. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing.
RELAY_LINT: per D-3.4 + D-3.4(a) — clock read immediately before writing (D-5.10), per-file WITH freshness, exit status checked un-piped; third arm at the active dispatch root before filing. Standing INDEX reds are the pre-existing sibling classes (line 222 s4-matrix; the `013935`/`014004` floor-pair tail inversion) — not mine.
FINAL_GIT_STATUS_SHORT:
?? .relays/s4/s4-floor-impl/REVIEW-FOLD-IMPLEMENTER-CB2-RECHECK2-TWO-CRITICALS-COMPLETE-PUBLISHED-20260810-185643.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-033926.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-050934.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-053253.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-LINEAGE-CORRECTION-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV3-MUST-REVISE-20260809-210140.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV4-APPROVE-20260809-211611.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV5-MUST-REVISE-20260809-230557.md
?? .relays/s4/s4-matrix-arm1-plan/DESIGN-REVIEW-IMPLEMENTER-R48-CARRIER-REV6-APPROVE-20260809-231944.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV0-20260809-055741.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV1-20260809-061515.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2-APPROVE-20260809-062921.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-CARRIER-REV2B-UNIQUE-APPROVE-20260809-141439.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-MUST-REVISE-20260810-041555.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-FOLD3-RECEIPT-DETERMINISM-R1-APPROVE-20260810-043843.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-LENSFOLD-SIX-MUSTFIX-APPROVE-20260810-074840.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-MUST-REVISE-20260810-145556.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R1-MUST-REVISE-20260810-150633.md
?? .relays/s4/s4-matrix-arm1-plan/PLAN-REVIEW-IMPLEMENTER-R48-MICROFOLD-V1-PROOF-R2-APPROVE-20260810-152645.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-COMPLETE-20260809-192358.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-DISPATCH-LINEAGE-BLOCKER-20260809-063906.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-CARRIER-IMPLEMENTED-E2-BLOCKED-20260809-182853.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD-MF1-MF6-COMPLETE-20260809-220327.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD2-EXTENDED-ROOT-RF1-RF2-COMPLETE-20260810-020857.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-COMPLETE-20260810-052656.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-FOLD3-DISPATCH-LINEAGE-BLOCKER-20260810-030814.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-LENSFOLD-COMPLETE-20260810-092751.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MERGE-BLOCKED-DRAFT-UNSTABLE-20260810-174554.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-MICROFOLD-DONE-WITH-CONCERNS-20260810-160710.md
?? .relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-R48-PR24-MERGED-STEP4-20260810-184033.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/RECONCILE-PLANNER-SLICE-E-FALSIFIER-CONFIRMS-BOTH-VARIANTS-20260816-210645.md` → `s4.orchestrator-planner`
- **FALSIFIER CONFIRMS m-1's REGISTERED PREDICTION ON BOTH VARIANTS at `9729191`:** V1 (entry-level member) → **exit 3 · `UnmanifestedMember` · path `agents/codex/entry-level.jsonl`**; V2 (child-level member ONLY) → **exit 3 · `UnmanifestedMember` · path `agents/codex/child-level.jsonl`**. The prediction was registered so the leg could falsify m-1 — it did not, it confirmed them, and `error.path` discriminates the variants
- **THE `171847` BLOCKER IS NOW EXECUTED, NOT INFERRED:** an archive carrying real bytes for a schema-3 entry is refused wholesale at `open.cpp:280-282` before preview/skip/disclosure/exit-0; the locked A5/K forward-compat path is unreachable for any archive a real packer produces
- **ARM (a′)'s CHILD FOOTPRINT IS WITNESSED, NOT ARGUED:** V2's member is declared ONLY under `children[*].artifacts`, so un-primed arm (a) leaves it RED — `required_agent_members` unions `child.artifacts` (`open.cpp:180-181`). (a)'s incompleteness is now a measurement
- **NEAR-MISS DISCLOSED:** my FIRST invocation passed `--into`, which is not a flag — **exit 5 / `UsageError` / verb "pack"**. Read naively that REFUTES m-1 on a typo. I validated the instrument before reading: a corrupt image returns exit 3 / `NotABivpakImage`, proving the invocation reaches the open path. **The control is the only reason the result is trustworthy** — same shape as the blind `\s` pattern caught earlier
- REPRODUCTION GIVEN so the owners can re-run rather than trust me: binary validated as built from `9729191` (mtime > newest src; `strings` carries both new identifiers); hand-crafted ustar+zstd image with the member listed in `checksums.json` so the `:272` check PASSES and the refusal is unambiguously the `:280` allow-set gate; `--json --dest`; **HOME/CODEX_HOME/CODEX_SQLITE_HOME all redirected — the operator's live `~/.claude` and `~/.codex` were never read or written**; scratch-only artifacts
- EVIDENCE **E2** (local command proof: fixture + shipped binary + exit code). Not claimed as E3
- UNBLOCKS the falsifier leg gating ADDENDUM L. **Still owed and NOT mine:** m-3's (a′) concurrence + list/info answer; m-1 authors L only after both, per their pre-committed order. M-b rides the a′ fold; leg (p) parity deferral stands; M-a held at master
- No fold, no token, no product byte; `9729191` unchanged; branch LOCAL and UNPUBLISHED; merge BLOCKED; release hold ABSOLUTE
