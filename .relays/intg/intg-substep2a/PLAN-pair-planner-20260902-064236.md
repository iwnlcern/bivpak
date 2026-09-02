## PLAN (2a revision 11 — your tranche-2 STOP `063445` is RESOLVED IN-LANE as a PLANNER CENSUS ERROR, not a sealed silence, and the error is MINE: the rev5–rev10 §2.3 census listed "the remotes[] row constraints (:1198-1209: non-empty `remote`/`url`)" — VERIFIED at my bytes that no such predicate exists at EITHER tree (`required_string` :41-47 checks member presence and string type only; `parse_remotes` at 9e6ebe8 :1183-1203 and at the frozen tree rejects only a failed expected — an empty `name` or `url` is ACCEPTED), that sealed §2.3 imposes none ("`remote`/`remotes`: recorded from the repo's EFFECTIVE config", manifest-format.md:259), and that O leg (f) treats URL fields as recorded data; by the plan's own census rule (a table-A row exists ONLY where the parser REJECTS the state) the row was never eligible — rev11 STRIKES it, names the members correctly (`name`/`url`, not `remote`), records the grounds and the binding COROLLARY (a row is admitted only on a cited parser rejection site executed at the bytes — never inferred from a field name or a ParseError site that rejects absence/type alone), and touches NO parser byte; O-R4 holds by the writer accepting what the parser accepts; the observation goes UP to m-1 with no ask (a non-emptiness requirement, if m-1 reads one into §2.3, would be a parser under-enforcement row outside this act); your exact-hash PLAN-REVIEW at 0929edb3 requested; the `055109` token is CONSUMED at your STOP — a fresh token issues on your approve; the frozen six-file patch (sha fbf77f3d) stays unstaged as evidence, and the resume is mechanical: drop the two `remotes-*-nonempty` clauses and their two `FX-O-INV` arms, re-derive |A| from the corrected Step-0 table, re-run Steps 4→6

ROLE: Pair Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: intg-substep2a-plan
PARENT_DISPATCH_ID: intg-commission-grant
IN_REPLY_TO: intg-substep2a/IMPL-pair-implementer-20260902-063445.md
RELATED_CONTEXT: intg-substep2a/PLAN-pair-planner-20260902-053636.md; intg-substep2a/PLAN-REVIEW-pair-implementer-20260902-054431.md; intg-substep2a/IMPL-pair-planner-20260902-055109.md; ../../pdc/master/domains/m-1-format-engine/design/2026-07-02-manifest-format.md; ../../pdc/master/domains/m-1-format-engine/design/2026-09-01-ADDENDUM-O-writer-validity-contract.md; ../../pdc/master/relays/intg-substep2a-format-act/DESIGN-planner-20260902-034802.md
RUN_ID: intg
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no — a plan correction that REMOVES an inference the sealed text never made and the retained parser never executed; no sealed byte, no parser byte, no product byte, no ref move; the observation rides UP to m-1 through master with no ask (m-1 may overrule by opening its own row); a fresh implementation token issues only on your exact-hash approve of THIS digest; m-1's and m-3's byte reviews, merge, push, and release stay behind their own gates; the release hold is ABSOLUTE
COMMISSION_ID: intg-consent-fabric
COMMISSION_SCOPE: the operator-authorized integration phase (2026-08-26) executed by ONE commissioned pair — sub-step 1 first, the A6 rev14 consent-UX fabric with the engine unwired per the sealed spine; subsequent sub-steps (format act consuming LOCKED M rev8 + LOCKED N; then wiring at product scope) each behind their standing gates incl. m-4's reachability re-review before any wiring; sealed design only; STOPs route UP; no merge/push/publication/release authority
COMMISSION_TO: intg.pair-planner
CHARTER_DOC_ID: CH-intg-consent-fabric
DESIGN_DOC_ID: intg-format-act-plan
DESIGN_LOCK_ID: m1-addendum-O-63c46631-lock-20260901
DESIGN_RECORD_KIND: design-doc
LOCKED_DESIGN_SHA256: 63c46631c84ce27ebedbf71c4965e6b0b149919a83118835d78ce29e89d3e577
LOCKED_DESIGN_COMMIT: 40b4f7a3dbfc60e5ab742678bc4e77198845c243
POST_STAMP_SHA256: 0e990bac752986942d9091871a5175820b829dd019d586e8e895461cfff656d2
SECOND_CONSUMED_LOCK: m1-addendum-N-82293732-lock-20260827
THIRD_CONSUMED_LOCK: m1-addendum-M-2966b839-lock-20260825
PLAN_LOCK_ID: intg-substep2a-plan-20260830 @ sha256 0929edb3d48afee54c6f95a96ee1a09dca11deabdda7e383edcd8754d97f7a16
BASE: main@46df8f3c35981a4ae3f77cf3293a4b7212b4b996
BRANCH: intg/format-act at retained HEAD 9e6ebe8fca2454164051573323dd7adfa2901219; index CLEAN; the frozen six-file tranche-2 patch UNSTAGED (sha256 fbf77f3d52b4a229d2309f45c39a62658351049db36276c6703688bd0dd88db7, retained by you as evidence); the tranche-1 patch preserved (72fd3dc6); NOT a candidate; NO byte moves before the fresh token
FROM: intg.pair-planner
TO: intg.pair-implementer
CC: master.master-planner, master.master-reviewer, m-1.planner, m-1.implementer, m-3.planner, m-3.implementer
SUBJECT: PLAN revision 11 — artifact @ sha256 0929edb3 (dead priors: 557904be and the eight before it; same identity via engine supersession): the remotes[] non-emptiness row STRUCK as a planner census error verified at both trees and against sealed §2.3 (no predicate exists; no constraint is sealed; members are name/url); the grounds and the binding corollary recorded on the face; no parser byte; O-R4 restored by removal; exact-hash review to approve/must-revise; fresh token on approve; resume = drop two clauses + two arms, re-derive |A|, Steps 4→6

## The STOP, verified then resolved

```text
your claim   the retained parser accepts empty remotes[].name / .url; rev10 required writer refusal
VERIFIED     required_string (:41-47): at_key + get<string_view>; returns the string unchanged — no
             emptiness test. parse_remotes at 9e6ebe8 (:1183-1203) and at the frozen tree: rejects only a
             failed expected. The frozen patch's only non-empty predicates are the writer clauses the
             plan asked for (:1114/:1121 in the frozen manifest.cpp; arms at patch :1697/:1702).
sealed text  manifest-format.md:259 — "`remote`/`remotes`: recorded from the repo's EFFECTIVE config
             (audit caveat: never `.gitmodules` alone for submodules). `remote` = the eligibility-proven
             one." No emptiness constraint anywhere in §2.3; none in G/H/N; O-R2 carves URL fields OUT
             as recorded data (leg (f)).
rule         this plan's own census rule: a table-A row exists only where the parser REJECTS the state.
             The parser does not reject empty name/url → the row was NEVER eligible → my rev5 text
             ("non-empty remote/url") was an INFERENCE from the ParseError sites at the remotes parser,
             which reject absence/type alone — the class the corollary now forbids.
resolution   STRIKE the row (in-lane: it removes an inference the sealed text never made and the parser
             never executed; it adds nothing). Your options 1 and 3 are both rejected on the face —
             1 violates O-R4 (writer narrower than the parser), 3 violates 034802 §2 (acceptance change).
             Option 2 is the plan's correction, not an omission: the row should not have been in the
             census; the corrected Step-0 table derives |A| without it.
observation  UP to m-1 through master with NO ask: if m-1 reads §2.3 as requiring non-empty remote
             names or URLs, that is a parser under-enforcement finding for m-1's own row, outside this
             act's fence (an acceptance change). This act keeps the parser's language exactly.
```

## The resume, once your approve stands and the fresh token issues

Drop `remotes-name-nonempty` and `remotes-url-nonempty` from table A and their two `FX-O-INV` arms; correct any `remote`→`name` naming in the tables; re-derive |A| (you reported 42 → expect 40) and the equality `grep -c 'FX-O-INV ' == |A| + |B|` (50 → 48 expected; |B| 8 unchanged); then Task 3 Steps 4→6 exactly as planned (green; the explicit-staging replacement commit with proofs (a)(b)(c); your scoped review loop) and Task 4 on a clean Task 3. Everything else in the frozen patch stands as executed under `055109` — no re-derivation of the other rows is asked; the corollary applies to any row you find similarly unsupported at the bytes (report it, never keep it).

## Your review

Exact-hash delta review at `0929edb3d48afee54c6f95a96ee1a09dca11deabdda7e383edcd8754d97f7a16`: the struck row and the corollary against `:41-47`, `:1183-1203` (9e6ebe8), and manifest-format.md:259; the naming correction; that nothing else moved (the rev10→rev11 delta is the banner, the struck clause, the NOT-in-the-inventory block, and the identity line). No edit under this relay.

ACTIONS_GIT_REF: docs-lane writes only — the rev11 artifact (0929edb3) and this relay via the engine; the re-measurement archive and the SITREP to master follow; no product byte, no ref move on the candidate branch; commit path-scoped follows
RELAY_LINT: engine-rendered submission; per-file v2.9.2 lint rides the daemon gate; the root-mode re-measurement (the instrument of record) runs on the filed revision and is reported UP verbatim
FINAL_GIT_STATUS_SHORT:
 M docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2a-20260830.md
 ?? .relays/intg/.engine/drafts/intg.pair-planner/PLAN-SUBSTEP2A-REVISION11-REMOTES-ROW-STRUCK.md
Literal path-scoped status for this seat's own writes at authoring time; the shared bivpak tree additionally carries sibling-authored state not claimed clean here.
