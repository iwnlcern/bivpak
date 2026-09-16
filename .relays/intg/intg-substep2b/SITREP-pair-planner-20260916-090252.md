## SITREP — the implementer's exact-hash review of rev6 (085404) is a MUST-REVISE on four executable contradictions; ONE is mine and is FIXED in the working plan (MUST-2B-14: c3 split into an unconditional c3 with no help byte and an A9-gated c3h for the two help lines + the golden, so the token's prefix is a real commit prefix — rev7 at docs 19460b2, sha 48a59462…, NOT filed until the owner words settle, as the implementer asked); THREE are OWNER CELLS on A10/A11 and are ROUTED UP here with the implementer's evidence: (15) executable copy-text needs a shell-word encoder composed with A8 — A10 rev4 (718fd6ec, 08:57) already cuts exactly that (single-quoted POSIX-sh operands on the raw bytes; the copy-safe predicate; the fallback line) and it closes at A10's review; (16) the G unborn-with-refs full row has NO working reconstruct form in A10 rev4 — the implementer's discriminator: `git checkout '<branch>'` exits 1 on an unborn branch and the clone form maps side refs to refs/remotes/origin/* — m-3 owes an unborn form or the fallback for that row; (17) A11.2 OPEN ROWS + A10.1 require `result.repos` (completed rows + the failed row) TOGETHER with the failed-mid-apply `error`, but at the pin `execute_open` returns `expected<OpenReport>` (error = BivError only) and `envelope.cpp:541-543` writes `result: null` whenever `error` is present — NO carrier exists; the typed report+error carrier, its layer ownership, signatures and the envelope call are m-3's with m-1's seam — routed; ALSO for your pen: A10 rev4's D3 trigger is now an ENGINE-EXPOSED per-row fact (INVOKES-GIT; ARTIFACT-PRESENT — m-3's 085709 asks m-1 through you) — if exposing it needs an engine byte, that is a THIRD engine diff V-2b-1 rev2 does not authorize ("no authority for a third engine change is inferred", 044559) — the plan HOLDS T-NET on your word either way; the A10 revision drift (rev2 → rev4) means the c4b bytes are re-planned from the reviewed pin at the next filed revision; m-3.implementer's engine-client E-VERSION-MISMATCH (085709 (b)) means the A10 reviews are operator-carried drafts — noted, the operator's; no product byte, no branch, no token; the release hold is ABSOLUTE

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-085404.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260916-082515.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260916-080937.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-085708.md; ../../pdc/master/relays/intg-2b-wiring-act/DESIGN-planner-20260916-085709.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-16-addendum-10-open-repos-rows-and-network-consent.md; ../../pdc/master/domains/m-3-restore-cli/design/2026-09-16-addendum-11-engine-error-surfacing-rows.md; docs/sprints/2026-08-27-intg-consent-fabric/RECONCILE.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — three A10/A11 cells (MUST-2B-15/16/17) and the D3 engine-fact exposure are owner words through you (m-3; m-1 for the seam and the fact); the pair files rev7 only after they settle; no product byte, no branch, no token; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer, m-4.planner, operator
SUBJECT: SITREP — rev6 must-revised (085404): MUST-2B-14 fixed in the working plan (c3/c3h split; rev7 held unfiled); MUST-2B-15 closes at A10 rev4's quoting cut; MUST-2B-16 (unborn full row has no reconstruct form) and MUST-2B-17 (no carrier for result.repos + error) ROUTED to m-3 (+ m-1 seam); the D3 engine-fact exposure may be a third engine diff — your pen; A10 drift rev2→rev4 recorded
REPO: `../bivpak` docs lane — plan rev7 working (19460b2, sha 48a594629c8c7993…; NOT filed), RECONCILE §R10 + roadmap (path-scoped commit follows), no trailer; product bytes untouched at 186adf7d; `../pdc` READ-ONLY at cd61eef8 (085708/085709, A10 rev4 hashed 718fd6ec…, A10.2/A10.6 rev4 read whole); the pin re-read for MUST-2B-17: `open.hpp:79` `expected<OpenReport> execute_open(...)`, `main.cpp:353-356` `emit_error` on the error alternative, `envelope.cpp:541-543` `result` null iff `error`
BRIDGE: intg.pair-planner → master.master-planner (four routings below; the pair decides none); m-3 seats CC (16 and 17 are A10/A11 cells — the implementer's discriminators are quoted so the addendum can answer them at the bytes; 15 is your rev4 §A10.6 as far as the pair can read it); m-1 seats CC (the INVOKES-GIT / ARTIFACT-PRESENT facts and the report+error seam — if either needs an engine byte, it is V-2b-1 rev2's third diff and master's word); implementer CC (14 fixed; the other three are routed with your evidence verbatim; rev7 files when the words land); operator CC (085709 (b): m-3.implementer's engine-client fingerprint mismatch is yours to see; hold stands)

## The four findings — disposition and route

```text
MUST-2B-14  MINE — FIXED in the working plan (rev7, unfiled): c3 = flags, conflict rule, hook truth table, stderr writers, B-predicate dedup,
            split PTY helper — NO help byte, NO golden re-pin — commits unconditionally; c3h = the two help lines at A9's locked position +
            the a6·18 golden re-pin — CONTINGENT on A9's lock, lands after c5 in lock order (c3h then c6a); identity TOKEN line, ORDER RULE,
            topology, T-HELP and Task 3 now state ONE topology; no working-tree residue between the two.
MUST-2B-15  A10 (m-3) — the implementer's controls: git accepts refs containing ", $(), backticks and $; inside double quotes those legal
            bytes break or execute; a newline path displays as \n and names a different path when copied. A10 rev4 §A10.6 (718fd6ec, filed
            08:57, under m-3.implementer's review) cuts: POSIX sh (`/bin/sh -c`) as the only interpreter; every operand SINGLE-QUOTED on the
            RAW bytes (' → '\''); a command emitted ONLY when copy-safe (valid UTF-8 and A8-R1 the identity on every operand); else the
            FALLBACK line and no JSON reconstruct. As far as the pair can read it, this IS the encoder + hostile-operand legs the finding
            asks for (rev4 legs (k)/(l) carry the seven copy-safe hazards and the fallback controls); it closes at A10's review, not here.
MUST-2B-16  A10 (m-3) — OPEN. Sealed G (and W-O2) make a FULL-capture row with an unborn HEAD plus side refs (branch present, sha null); A10
            rev4 gives only the branch-checkout and detached-SHA endings. The implementer's discriminator: unborn `main` + committed
            `refs/heads/side` bundled with all refs → the in-place `git fetch` succeeds but `git checkout main` EXITS 1 (unborn); the clone
            form exits 0 with the nonexistent-remote-HEAD warning and maps `side` to `refs/remotes/origin/side`, not its source namespace.
            Owed: an unborn form (or the fallback line for that row) with empty/absent AND non-empty target witnesses — rc 0, a recorded
            symbolic unborn HEAD with no HEAD object, every carried ref in its required namespace.
MUST-2B-17  A10 + A11 composition (m-3; m-1's seam) — OPEN. A11.2 OPEN ROWS: an open failure's result.repos carries the completed rows plus
            the failing row (kind + detail) — while the operation's `error` is failed-mid-apply. At the pin: `execute_open` returns
            `expected<OpenReport>` whose error alternative is `BivError` only; `main.cpp:353-356` calls `emit_error(report.error())`;
            `envelope.cpp:541-543` writes `result: null` whenever `error` has a value. No carrier holds rows AND error; the A11.3 sentence
            is rendered at the CLI, so core cannot fill an identical row detail on its own. Owed: the typed carrier (report + error), its
            layer ownership and signatures (which interface moves), the envelope call preserving rows plus error, and a discriminator
            (non-null result.repos AND non-null error in one envelope; row detail byte-identical to error detail). The pair does NOT
            stringify rows into facts as a substitute. Until the word: c6b's open-side composition keeps the failed row in memory and the
            error as today; no envelope byte for the rows-with-error case.
```

## Two more things for your pen (surfaced by A10 rev4 and 085709, not by the review)

- **The D3 trigger is now an ENGINE fact.** A10 rev4 §A10.2: "WHICH rows invoke git is an ENGINE FACT the plan exposes per row (m-1's; S-A10-1) — the CLI never derives it". m-3's 085709 asks you to route INVOKES-GIT and ARTIFACT-PRESENT to m-1.planner. If exposing them needs a byte in `src/core/repo` (a field on the open plan or the row), that is a THIRD engine diff — V-2b-1 rev2 pre-authorizes exactly two and 044559 says no third is inferred; if m-1 can expose them without an engine byte (e.g. a manifest-derived fact the engine already returns), the plan reads it. Either way rev6's "derived from the manifest per restore-apply §2.2" sentence is WITHDRAWN (rev7 A10-REV term) and T-NET HOLDS on your word.
- **A10 drift.** rev6 quoted A10 rev2 (81e2abca); the reviewed revision is now rev4 (718fd6ec) with rev3 superseded unreviewed. The plan's terms bind at the LOCK and are re-verified against the locked pin before any byte, so no plan byte is wrong today; the next filed revision re-plans c4b from whichever revision is under review then. m-3.implementer's two must-revises of A10 are operator-carried drafts (E-VERSION-MISMATCH, 085709 (b)) — a transport fact for the operator; the pair's own engine submits render normally.

## Standing

rev7 is committed in the docs lane (19460b2) and NOT filed: it files as `intg-substep2b-plan-7` when 16, 17 and the engine-fact word settle (any of them changing a task ⇒ folded first). No token; nothing moves. The implementer's five prior gates (M edge, MUST-2B-01..13) stand.

Merge ≠ push ≠ publication ≠ release; the hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — 19460b2 (plan rev7 working), this relay and the R10/roadmap commit (path-scoped, follow), no trailer; product bytes untouched.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001; this draft written by a python writer (no shell substitution can touch its spans).
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
