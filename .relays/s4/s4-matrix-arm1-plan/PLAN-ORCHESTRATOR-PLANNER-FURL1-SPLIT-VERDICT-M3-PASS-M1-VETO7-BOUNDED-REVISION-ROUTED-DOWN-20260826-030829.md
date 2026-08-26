## PLAN (the split owner verdict is IN and I routed it DOWN to your lane for ONE bounded revision commit — m-3 PASS on the absence bar, m-1 MUST-REVISE veto 7 on the comparator normalization family; I verified all three finding members at the candidate bytes myself before relaying them so you are not chasing a phantom; the design text does NOT move, the locks do NOT move, the fences do NOT move) — **THE TWO VERDICTS at master's owners' seats: m-3 (`023238`) discharged its SEPARATE R4 zero-m-3-surface absence bar + the complete `V-A6-1..6` gate GREEN at its own read of `bb06d7e` — the PascalCase engine-internal hook/memo types correctly classified as LOCKED M-R3 execution, not A6 bytes; that review is INDEPENDENT of the revision below and does not gate it. m-1 (`024819`) PASSES structure and vetoes 1–6/8/9 and every normative rule at its own execution (408/55 full + 56/14 focused reproduced as the THIRD independent measurement, two more separating mutants added, all twelve named mutants mapped to legs, fenced surfaces byte-identical, zero wiring) and FIRES VETO 7 on ONE bounded family in `url_endpoints_equivalent`'s normalization layer.** **I VERIFIED THE FINDING AT THE CANDIDATE BYTES (not carried from the report) — `git show bb06d7e:src/core/repo/git_exec.cpp`: F1 `one_trailing_slash` runs `while (value.size() > 1 && value.ends_with('/')) value.pop_back();` then re-adds exactly one, so it collapses ANY run of trailing slashes — `repo.git//` and `repo.git///` both normalize to `repo.git/`, equated with `repo.git/` across an unbounded slash-count difference; F2 the https authority parse takes `authority.rfind('@')`, so `https://@h.invalid/repo.git` parses to `user=""` and equals `https://h.invalid/repo.git` (also `user=""`) at `same_endpoint`, the empty-userinfo elision; F3 `ascii_lower` folds via locale-sensitive `std::tolower(byte)`. All three are real at the bytes. Veto 7 is sound.** **THE OWNER'S RULING, ON THE RECORD AND BINDING YOUR REVISION — rule 3's ambiguity was a STOP owed UP and the owning seat has now answered it: the DIFFERENCE reading GOVERNS. Two endpoints equate on the path IFF the paths are BYTE-IDENTICAL or differ by EXACTLY ONE trailing `/`, applied identically inside rule 5's "path byte-identical after rule 3" clause. NO unbounded canonicalization. Grounds are the sealed text's own machinery: the exhaustive-enumeration clause (an ambiguously-listed equivalence is not listed), the direction-of-error rule (under-determination resolves toward PROMPTING, and canonicalization is the silent-er reading), and the every-hop rule (multi-slash equivalence is UNPROVEN at any hop — for http(s) the path travels verbatim in the request and a server may distinguish `a` from `a//` — and unproven equivalence is divergence). THE SEALED DESIGN TEXT DOES NOT MOVE: rule 3 already decides under this ruling.** **YOUR REVISION — exactly m-1's §4 and NOTHING MORE: (1) PATH RULE (F1) — equate iff byte-identical or differing by EXACTLY ONE trailing `/`, the same rule inside rule 5's clause; no unbounded collapse. (2) USERINFO (F2) — present-but-empty userinfo is PRESENT; present-vs-absent diverges. (3) FOLD (F3) — explicit ASCII `A–Z` fold in `ascii_lower`, byte-deterministic under any host locale. (4) WITNESSES RIDE THE FIX (fixture-grammar discipline, above the sealed floor — FX-M-1's fifteen legs and twelve markers UNTOUCHED, nothing renumbers): comparator-table rows for `a` vs `a//` (divergent), the `a/` vs `a//` boundary, `://@h` vs `://h` (divergent), PLUS one real-git multi-slash divergence arm through the gate. (5) FORM — ONE new commit over `6ba01ef` REPLACING `bb06d7e` (the one-commit rule), the SAME six-path fence, ALL SIX package members still binding (m-1 vetoes 1–9 with v9 mechanical · complete `V-A6-1..6` · the SEPARATE R4 absence bar · m-4 triggers · the fourteen-unit reduced real-git E2 set · the `repos`-empty format fence), through YOUR pair's OWN gate first (Implementer plan-review approve → the pair Planner's bare dispatch-impl token; I issue no token here). No other engine byte moves.** **THE CORRECTED LOCK PIN, carried as locked bytes not a paraphrase and verified at MY bytes: master's `022605` dispatch cited `LOCKED_DESIGN_COMMIT 6aa64fe0894e5aa2b9e29b4df33c72cf99c81ecb`, which `git cat-file -t` PROVES nonexistent (a hand-expanded short-sha tail); the TRUE M rev8 commit is `6aa64fe280c40beec2c93063de1d38c830aac097` (subject "ADDENDUM M rev8 — the E2-timing deferral successor…", cat-file verified). Every SHA-256 pin was correct throughout — LOCKED_DESIGN_SHA256 `2966b839…`, POST_STAMP `57d89625…`, twin A6 `7ce2251d…`, m-4 SR-URL `a2f777c2…` — so no lock identity was ever wrong; the defect was the derived-at-git rule, and master re-banked it (R-4.43 records the owned defect). Use the true pin.** SEQUENCING: land the revision through your pair gate → BOTH owner reviews re-engage at the SUCCESSOR bytes (m-1 on the delta PLUS the Linux leg AT ITS OWN SEAT — charter parity recipe Ubuntu 24.04 `--platform linux/amd64`, `--init`, nofile raised to hard; m-3 re-verifies the R4 absence at the successor commit) → on green, back to me for the MERGE-GATE (a separate MERGE-GATE relay, unclaimed here) → the T4 FINAL question at the successor commit is the OPERATOR's alone → R-4.43 closes only on m-4's requirement-satisfied sign-off. The Linux leg stays DEFERRED-TO-SUCCESSOR and NOT-two-platform-confirmed until m-1 runs it at the successor bytes. Candidate `bb06d7e` is now superseded by the revision; T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; origin/main untouched; merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Orchestrator Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-furl1-split-verdict-bounded-revision
PARENT_DISPATCH_ID: s4-wave-a-furl1-engine-only-accepted-route-owner-reviews-up
IN_REPLY_TO: master/relays/s4-wave-a-furl1-engine-only-accepted-route-owner-reviews-up/PLAN-orchestrator-planner-20260826-025440.md
RELATED_CONTEXT: master/relays/s4-wave-a-furl1-engine-only-accepted-route-owner-reviews-up/DESIGN-REVIEW-planner-20260826-024819.md; master/relays/s4-wave-a-furl1-engine-only-accepted-route-owner-reviews-up/DESIGN-REVIEW-planner-20260826-023238.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — downstream after the revision lands and both owner reviews re-engage green: the MERGE-GATE before any merge claim; the operator's T4 FINAL re-weigh at the successor commit; m-4's sign-off closes R-4.43. No merge/push/PR-mutation/schema/remote-CI/release from this route. The release hold is ABSOLUTE.
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
DESIGN_DOC_ID: m1-addendum-M-20260823
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-M-2966b839-lock-20260825
LOCKED_DESIGN_SHA256: 2966b839a472df28a261890e1209d69d97a0bfe06c903c3f5029d2cd39a87df6
LOCKED_DESIGN_COMMIT: 6aa64fe280c40beec2c93063de1d38c830aac097
POST_STAMP_SHA256: 57d89625de4b47031cf2862065499ca1839fac7876f42deabe9d048d7de30082
COORDINATED_TWIN_POST_STAMP_SHA256: 7ce2251dd481161a457c029bf46e127522f1cc85cc5ab2fb2a92b7fc0c7fd771
CONSUMED_CONTRACT: m4-sr-url-family-20260823
CONSUMED_CONTRACT_SHA256: a2f777c2311ab04283992b24f5fba766c6ba8c66ef8bcf6bc88f7b48f88f7798
BASE: T4 `6ba01ef92ef5052b317f6210fa202d5577e1e6c1` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
CANDIDATE: the revision is a NEW commit over `6ba01ef` REPLACING `bb06d7ef801c5afa31a91155f45a520db6f4a64a` per the one-commit rule
FROM: s4.orchestrator-planner
TO: s4-matrix.planner, s4-matrix.implementer
CC: operator, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer, m-1.planner, m-3.planner
SUBJECT: PLAN — split owner verdict routed DOWN: m-3 PASS 023238 (absence bar + V-A6-1..6, independent), m-1 MUST-REVISE 024819 veto 7 on the comparator normalization family (F1 unbounded trailing-slash collapse / F2 empty-userinfo elision / F3 locale fold), all three verified at the candidate bytes at my seat; the owner's DIFFERENCE reading of rule 3 ruled on the record binds the fix; land m-1's §4 exactly — one new commit over 6ba01ef replacing bb06d7e, same six-path fence, six package members binding, through your pair gate then both owner reviews re-engage (m-1 delta + Linux leg at its seat; m-3 absence at successor); true lock pin 6aa64fe280c4 carried (master's cited tail nonexistent, all SHA-256 pins correct); MERGE-GATE/T4-operator/m-4-signoff sequence unchanged; release hold ABSOLUTE

## 1. The split verdict, verified at my bytes

```text
m-3  023238  PASS   R4 zero-m-3-surface absence bar + complete V-A6-1..6 at bb06d7e; independent, does not gate the fix
m-1  024819  MUST-REVISE  veto 7 on url_endpoints_equivalent normalization; vetoes 1-6/8/9 + all rules PASS at executed evidence
finding verified at git show bb06d7e:src/core/repo/git_exec.cpp at MY seat:
  F1  one_trailing_slash: while(size>1 && ends_with('/')) pop_back; then add one -> collapses ANY slash run to one
  F2  https parse authority.rfind('@') -> https://@h and https://h both user="" -> same_endpoint equal
  F3  ascii_lower via locale-sensitive std::tolower(byte)
```

## 2. The owner's ruling (on the record) and your bounded revision

```text
RULING  rule 3 DIFFERENCE reading GOVERNS: paths equate IFF byte-identical OR differ by EXACTLY ONE trailing '/'
        (same rule inside rule 5). No unbounded canonicalization. Sealed design text does NOT move.
REVISE  (1) path rule per the ruling  (2) present-but-empty userinfo is PRESENT (present-vs-absent diverges)
        (3) explicit ASCII A-Z fold  (4) witnesses ride the fix: a vs a// divergent, a/ vs a// boundary,
        ://@h vs ://h divergent, + one real-git multi-slash divergence arm; FX-M-1 15 legs/12 markers untouched
        (5) ONE new commit over 6ba01ef REPLACING bb06d7e, same six-path fence, six package members binding,
            through YOUR pair gate (Impl plan-review approve -> pair Planner token); I issue no token here
PIN     LOCKED_DESIGN_COMMIT = 6aa64fe280c40beec2c93063de1d38c830aac097 (true M rev8; master's cited tail
        6aa64fe0894e... is nonexistent per cat-file); all SHA-256 pins correct throughout
```

## 3. Sequencing and holds

```text
land revision via pair gate -> BOTH owner reviews re-engage at the successor:
  m-1  delta + Linux leg at ITS seat (Ubuntu 24.04 --platform linux/amd64, --init, nofile raised to hard)
  m-3  R4 absence at the successor commit
-> on green: back to me for the MERGE-GATE (separate relay, unclaimed) -> T4 FINAL to the OPERATOR alone
-> R-4.43 closes on m-4 sign-off
Linux leg DEFERRED-TO-SUCCESSOR; NOT-two-platform-confirmed stands until m-1 runs it at the successor bytes.
```

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product/branch/ref/merge/push/PR act at this seat — read-only verification against `../bivpak` odb: `git cat-file -t 6aa64fe0894e…` (nonexistent) and `6aa64fe280c4…` (commit, subject verified) in pdc; `git show bb06d7e:src/core/repo/git_exec.cpp` confirming F1 `one_trailing_slash`, F2 `authority.rfind('@')` empty-userinfo elision, F3 `ascii_lower` `std::tolower`. This PLAN routes master's bounded revision DOWN, carries the owner's ruling and the corrected lock pin, and issues NO token. This relay + its INDEX row ride ONE explicit-path docs-lane commit.
RELAY_LINT: per D-3.4 (v2.9.x) — per-file WITH freshness (clock read at 030829 immediately before writing); `.relays/s4/INDEX.md` tail re-read before appending; `--index` run and the inherited R-4.27 pre-existing chronology disorder disclosed NOT repaired (my appended tail row is monotone); add and commit path-scoped; status prose pipe-free.
FINAL_GIT_STATUS_SHORT: literal path-scoped status for this seat's two writes captured at commit; the shared checkout carries sibling-authored untracked state (incl. the 220111 stray completion), excluded and unclaimed.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-FURL1-SPLIT-VERDICT-M3-PASS-M1-VETO7-BOUNDED-REVISION-ROUTED-DOWN-20260826-030829.md` -> `s4-matrix.planner`, `s4-matrix.implementer`
- SPLIT VERDICT IN: m-3 023238 PASS (R4 absence bar + complete V-A6-1..6 at bb06d7e, independent of the fix); m-1 024819 MUST-REVISE veto 7 on the comparator normalization family, vetoes 1-6/8/9 + all rules PASS at its executed evidence (408/55 + 56/14 reproduced third independent, two more separating mutants, twelve named mutants mapped, fenced surfaces byte-identical, zero wiring)
- I VERIFIED THE FINDING AT THE CANDIDATE BYTES (not carried): F1 one_trailing_slash collapses ANY run of trailing slashes to one; F2 https authority.rfind('@') makes https://@h == https://h at user=""; F3 ascii_lower uses locale-sensitive std::tolower. Veto 7 SOUND
- OWNER'S RULING ON THE RECORD binds the fix: rule 3 DIFFERENCE reading GOVERNS — paths equate iff byte-identical OR differ by exactly one trailing '/', same rule inside rule 5; NO unbounded canonicalization; sealed design text does NOT move (grounds: exhaustive-enumeration, direction-of-error-toward-prompting, unproven-equivalence-is-divergence)
- YOUR REVISION = m-1 §4 exactly: (1) path rule per ruling (2) present-but-empty userinfo is PRESENT (3) explicit ASCII A-Z fold (4) witnesses ride the fix (a vs a// divergent, a/ vs a// boundary, ://@h vs ://h divergent, + one real-git multi-slash divergence arm; FX-M-1 fifteen legs/twelve markers untouched) (5) ONE new commit over 6ba01ef REPLACING bb06d7e, same six-path fence, six package members binding, through YOUR pair gate first — Impl plan-review approve then the pair Planner's bare token; I issue NO token here
- CORRECTED LOCK PIN carried as locked bytes: LOCKED_DESIGN_COMMIT = 6aa64fe280c40beec2c93063de1d38c830aac097 (true M rev8, cat-file verified at my bytes); master's cited 6aa64fe0894e... is NONEXISTENT (hand-expanded short-sha tail); every SHA-256 pin correct throughout (2966b839 lock / 57d89625 post-stamp / 7ce2251d twin / a2f777c2 m-4); R-4.43 records master's owned derived-at-git defect
- SEQ: land revision via pair gate -> BOTH owner reviews re-engage at successor (m-1 delta + Linux leg at ITS seat, charter parity recipe; m-3 absence at successor) -> on green back to me for the MERGE-GATE (separate relay, unclaimed) -> T4 FINAL at the successor to the OPERATOR alone -> R-4.43 closes on m-4 sign-off; Linux leg DEFERRED-TO-SUCCESSOR and NOT-two-platform-confirmed stands until m-1 runs it; bb06d7e superseded; T1 00c06d9 / T2 7688bbd / T3 70601fc FINAL; origin/main untouched; merge != push != release; release hold ABSOLUTE
