## SITREP — the implementer's whole-plan review of rev4 (065734) closed MUST-2B-01..03 and 05..11 (MUST-2B-11 on their own official-selector reproduction at 631aae82 with the 1e987860 negative control) and MUST-REVISED three items; all three are ACCEPTED, verified at the pin, and folded into plan rev5 (artifact 5aabe373aa9c630151c1b0c60624567fb45759623fc5ef1c39235099b3f1a5d8 at docs 138a322), FILED as intg-substep2b-plan-5 (relay 070942) for the next exact-hash review: MUST-2B-04 reopened — T-STAGE's hold was narrated while apply_archive extracted every repos/ member, now ROUTED by an optional stage parameter (offline ⇒ drained + verified, never materialized, the stage path never touched) with a product discriminator, and Task 5's product STOP branch for a fenced classification is REMOVED (Task 5 does not start until m-1's Q11 word is in the gate file; the candidate holds at c4); MUST-2B-12 — one canonical root representation ("." and "" → the root), a root-claimed fast path in scan() and pack's canonicalization, with unit and product discriminators; MUST-2B-13 — Task 12 owns the POST-merge landing census after the operator's token (identity block + CEN row corrected; Task 11 pre-merge); the --offline claims scoped to the born non-shallow lane. The M edge fields on plan-5 are byte-identical to plan-4's (pinned 631aae82, PASS); the single re-sweep you asked for is archived and NOT re-run for rev5 — say the word if you want a second; one stale label disclosed; RECONCILE §R8; no product byte, no branch, no token; the release hold is ABSOLUTE

ROLE: Pair Planner
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: intg-substep2b
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2b/PLAN-REVIEW-pair-implementer-20260916-065734.md
RELATED_CONTEXT: intg-substep2b/PLAN-pair-planner-20260916-070942.md; intg-substep2b/PLAN-pair-planner-20260916-054308.md; intg-substep2b/SITREP-pair-planner-20260916-062910.md; ../../pdc/master/relays/intg-2b-wiring-act/PLAN-master-planner-20260916-051652.md; docs/sprints/2026-08-27-intg-consent-fabric/RECONCILE.md; docs/sprints/2026-08-27-intg-consent-fabric/results/lint-root-sweep-s2b-plan-edge-remeasure-20260916.txt
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E1
HUMAN_GATE_REQUIRED: no NEW gate — the next hop is the implementer's exact-hash review of rev5; Q11 (T-FENCE) and Q13 (T-STAGE) remain owner words gating Task 5's start and the offline full-image routing respectively; no product byte, no branch, no token; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
FROM: intg.pair-planner
TO: master.master-planner
CC: master.master-reviewer, intg.pair-implementer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer, m-4.planner, operator
SUBJECT: SITREP — rev4 review 065734: eight findings closed, three must-revised and folded into rev5 (070942, artifact 5aabe373…): T-STAGE routed (never materializes offline) + discriminator; T-FENCE product STOP branch removed (Task 5 waits on Q11, hold at c4); canonical root + fast path (MUST-2B-12); Task 12 owns the post-merge census (MUST-2B-13); M edge unchanged at 631aae82, re-sweep not re-run; §R8
REPO: `../bivpak` docs lane — plan rev5 (138a322), RECONCILE §R8 + roadmap (1b4e33a), the plan-5 relay + INDEX row (0a94f5c); no trailer; product bytes untouched at 186adf7d; `../pdc` READ-ONLY (no relay newer than 051652 under intg-2b-wiring-act at this filing); the pinned product bytes re-read for each finding: open.cpp:544-611 (apply_archive), :617-669 (execute_archive), scan.cpp:74-84 and :228 (the root relpath is ""), discover.cpp:88-91 (the root boundary is ".")
BRIDGE: intg.pair-planner → master.master-planner (report; one question inline: the plan-5 carrier's edge fields equal plan-4's byte-for-byte at the same pin — I read your "re-run the root sweep ONCE" as satisfied by the 2026-09-16 archive and did not spend another 45 minutes; if you want the sweep on the rev5 carrier itself, say so and it runs); implementer CC (rev5 at 5aabe373 is the object; review asks 7–8 name what changed; nothing outside the R8 rows moved); m-1 seats CC (Q11 now gates Task 5's START, not a branch inside it — the fence disposition per class is what the gate file wants; Q13 with m-3); m-3 seats CC (Q13: where a full-image artifact lands under open --offline — until then the offline arm drains and verifies, materializes nothing, prints no bundle line); m-4 CC (the MUST-2B-12 root-claimed fast path closes the "root repo children leak into payload" class with a product discriminator); operator CC (hold stands)

## The three folds (RECONCILE §R8 holds the rows with the bytes checked)

```text
MUST-2B-04  T-STAGE  apply_archive(image, plan, partial_dir, dirs, verify, stage) — stage: optional<path>; online ⇒ repos/ members extracted
                     into *stage/<full member path>; offline ⇒ drained + checksum-verified like agents/ members, never materialized; the stage
                     path never stat'ed/created/removed under --offline. DISCRIMINATOR: a regular FILE pre-created at the stage path → offline
                     exits 0 and leaves it unchanged; online control → OpenPartialPresent naming it; extract-regardless mutant ⇒ RED.
            T-FENCE  the InternalError "STOP-T-FENCE" branch and its wording REMOVED (grep 0); Task 5 Step 0 = hold-before-bytes: no Task 5
                     byte until /m1-fence-word.txt holds m-1's disposition per class; the candidate HOLDS at c4; the branch is
                     transcribed from the word in the revision that carries it.
MUST-2B-12           ScanExclusions::canonical ("." and "" → "", lexically_normal, no trailing slash); claims_root() ⇒ scan() returns an EMPTY
                     ScanResult before any read (the root repo is the single writer); pack canonicalizes discover's relpaths; unit test on the
                     PRODUCTION value "." + the "" twin + a nested arm (fast-path mutant named); Task 7: a workspace-root repo with tracked +
                     untracked + subdir ⇒ ZERO payload/ members, the repo restored with its untracked penumbra (mutant ⇒ payload/ appears).
MUST-2B-13           identity LANDING/CLOSURE + the CEN row → Task 12 (POST-merge, after the token; Task 11 = pre-merge rehearsal at H0 +
                     declaration; Task 10 = vehicle); Task 12 opens with the ORDER line and the landing census on the merge head with its
                     population re-produced there; the --offline "full + offline_declared" claims scoped to the born non-shallow lane.
```

## Disclosures

- The plan-5 relay's runner-proof note carries the label "(rev4: gates 3/13/4/2, omitted 0)"; the rev5 proofs are identical in every number (bytes=equal, gates 3/13/4/2, omitted 0, out_of_order 0, rc=0 ×4) — a stale label, not a stale measurement; the filed relay is immutable, so it is recorded here and in §R8.
- The re-sweep archived at 06:27 measured the plan-4 carrier; plan-5 declares the same seven edge fields at the same pin. Not re-run unless you ask.

Merge ≠ push ≠ publication ≠ release; the hold is ABSOLUTE.

ACTIONS_GIT_REF: docs-lane writes only — 138a322 (plan rev5), 1b4e33a (R8 + roadmap), 0a94f5c (plan-5 relay + INDEX), this relay (path-scoped commit follows), no trailer; product bytes untouched.
RELAY_LINT: engine-rendered submission; per-file 2.9.2 and 2.9.3 `relay-lint.py --no-freshness` on the draft; gates 0/0/0; the four commission-surface lines copied byte-for-byte from the filed r450 PLAN 194001.
FINAL_GIT_STATUS_SHORT:
 M .relays/intg/INDEX.md
Literal path-scoped status for this seat's own writes at write time; the shared bivpak tree carries the s4 lane's uncommitted rows, not claimed clean here.
