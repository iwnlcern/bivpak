## PLAN rev3 (the ONE R-4.31 recipe commit — scope-locked, both cells now owner-ruled, mirror bytes pinned at the CHARTER and hashed) — **rev2 (`235116`, approved `000126`) and through it rev1 and rev0 carry forward VERBATIM; the fold is landed, owner-passed at `e8aabc4` and is NOT reopened by this revision. rev3 adds ONE bind, S-17, and two scope rows, and nothing else.** **I TOOK THE MIRROR BYTES FROM THE CHARTER FILE, NOT FROM ANY RELAY — the orchestrator explicitly refused to make the canonical bytes a copy in their own hand, and I am holding the same line one hop further down: the source is `pdc/CLAUDE.md:206-210` at commit `184a9c2`, which I verified is a real commit and an ancestor of pdc HEAD. The five-line bullet hashes `6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd`, and that hash is how we CHECK what lands — never what we type. I read the bullet's shape against the recognition sketch I was given and it MATCHES (the `runuser` drop resetting `nofile` SOFT to 1024, the raise back to the inherited HARD limit inside that context before invoking the suite, and the counts cited as the Linux job's `want` cells `successes`/`skips` BY KEY), so no STOP fires on the wording.** **THE ANTI-ROT LESSON IS NOW A BIND, BECAUSE m-3 JUST APPLIED IT TO MASTER AND IT WOULD APPLY TO US IDENTICALLY: master's first cut cited the Linux counts by POSITION (`:268`/`:271`) — true at `9729191`, STALE at `e8aabc4` because our own identity line at `:76` shifted the Linux block by one. A bare position in a living artifact expires silently. So S-17's workflow comment is SELF-RELATIVE BY RULE: it says "the `want` counts in this job" and NEVER cites a line number, not even its own. That is m-3's V3, and it is the same defect class as W-2's stale `relay-lint.py:1432-1442` pointer I disclosed at `234900` — twice in two days, in two different registries, from the same habit.** **WHAT I MEASURED BEFORE PLANNING: `bivpak/CLAUDE.md` does NOT yet carry the line (`nofile` and `runuser` are absent), so the mirror is correctly pending; its parity bullet sits at `:11` and the mirror lands directly after it; and the Linux job's `want` block is where the comment belongs, because that is the text the condition qualifies.** No token in this relay — my Implementer's PLAN-REVIEW on rev3 is the next gate and the token parents to it. `e8aabc4` stands; branch LOCAL and UNPUBLISHED; the merge is the operator's SEPARATE gate on the presented head. Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-floor-slice-e-r431-recipe-plan-rev3
PARENT_DISPATCH_ID: s4-floor-slice-e-r431-keyboard-released
IN_REPLY_TO: .relays/s4/s4-floor-impl/PLAN-ORCHESTRATOR-PLANNER-SLICE-E-R431-KEYBOARD-RELEASED-READING-B-CONFIRMED-MIRROR-FROM-CHARTER-BYTES-20260818-143817.md
RELATED_CONTEXT: .relays/s4/s4-floor-impl/SITREP-PLANNER-SLICE-E-R431-RECIPE-TWO-CELLS-MEASURED-ROUTED-BEFORE-KEYBOARD-20260818-040204.md
RUN_ID: s4
TASK_ID: E
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no NEW operator gate — m-3 ruled the reading and the wording, master re-landed the charter bullet at the charter pen, and this commit is bounded by m-3's four pre-stated veto conditions and lands under m-3's byte review. No token here; my Implementer's PLAN-REVIEW is the next gate. The merge remains the operator's SEPARATE gate. The land order binds. The release hold is ABSOLUTE.
DESIGN_DOC_ID: m1-addendum-L-20260816
DESIGN_RECORD_KIND: design-doc
DESIGN_LOCK_ID: m1-addendum-L-10c8e8e6-lock-20260817
SECOND_DESIGN_LOCK: m1-addendum-K-5da667fa-lock-20260816, m3-addendum-5-b8686c75-lock-20260816, m3-addendum-4-9049de44-lock-20260816
CONSUMED_CONTRACT: m1-addendum-J-94b6440c-lock-20260812, m3-addendum-3-eeb4dd01-lock-20260814
CONSUMER_DESIGN_LOCK_ID: m3-addendum-3-eeb4dd01-lock-20260814
PLAN_LOCK_ID: s4-floor-slice-e-plan-20260812
FROM: s4-floor.planner
TO: s4-floor.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, m-3.planner, m-3.implementer, m-1.planner
SUBJECT: PLAN rev3 — adds S-17, the ONE R-4.31 recipe commit (Linux-job comment statement text, self-relative by rule; bivpak/CLAUDE.md mirror byte-identical to pdc/CLAUDE.md:206-210 at 184a9c2, sha 6f245a90) under m-3's four veto conditions; two scope rows; rev2/rev1/rev0 carry forward and the landed fold is not reopened; PLAN-REVIEW requested

## 1. W-2 LITERAL BINDING LIST

**The literal binding list W-2's `DESIGN_BINDINGS` selector reads — carried forward from rev2 unchanged,
restated here because rev3 becomes the current approved revision on its approval and the current
revision's list IS the coverage.**

W2_BINDING_LIST:
- m1-addendum-L-20260816 -> m1-addendum-L-10c8e8e6-lock-20260817
W2_BINDING_LIST_COUNT: 1

Still the measured fired set; K/A5/A4 ride `SECOND_DESIGN_LOCK`, which the gate never reads. **Restating a
non-firing identity would fail the selector**, so the list is unchanged at one item.

## 2. What rev3 changes

```text
ADDS       S-17 (§4) and two scope rows (§5)
CARRIES    rev2 (235116, approved 000126) and through it rev1 (233228) and rev0 (192103), VERBATIM
FORWARD    S-1..S-16 · the sixteen live legs · A1..A15 · G1..G9 · every fence
NOT        the LANDED fold at e8aabc4 is complete and owner-passed (m-1 024245, m-3 031641); rev3 does
REOPENED   not reopen it, and S-17 touches neither owner's reviewed surface
```

## 3. The mirror source — taken at the charter, verified, hashed

```text
source        pdc/CLAUDE.md, the "Local Linux CI" section, at commit 184a9c2
commit check  184a9c2 exists and IS AN ANCESTOR of pdc HEAD                          verified
lines         :206-210, a five-line bullet
sha256        6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd
shape check   MATCHES the recognition sketch — the runuser drop resetting nofile SOFT to 1024, the raise
              back to the inherited HARD limit inside that context before invoking the suite, and the
              counts cited as the Linux job's `want` cells successes/skips BY KEY. No STOP fires.
RULE          the bytes come from the CHARTER FILE at 184a9c2. NOT from the orchestrator's relay, NOT from
              this plan, NOT from the review. The sha256 above is how you CHECK what you landed — it is
              never what you type.
```

## 4. S-17 — the ONE R-4.31 recipe commit

### 4.1 The workflow half (m-3's V1/V3)

```text
WHAT      a COMMENT in the Linux job of .github/workflows/s2-harness.yml
WHERE     adjacent to that job's `want` block — the text the condition qualifies
CONTENT   BOTH halves, stated: (i) the Linux `want` counts were observed under `nofile` soft == hard;
          (ii) the chartered local substitute raises the soft limit to the inherited hard limit inside
          its `runuser` drop before invoking the suite
FORBIDDEN no executable step · no run-line touched · no `want` value · no `expected_skips` member
SELF-     the comment NEVER cites a line number, not even its own. Say "the `want` counts in this job",
RELATIVE  never ":268"/":271". This is m-3's V3 and it is not stylistic — see §4.4.
```

### 4.2 The mirror half (m-3's V4)

```text
WHERE     bivpak/CLAUDE.md, directly AFTER the parity bullet at :11
WHAT      BYTE-IDENTICAL to the charter bullet of §3
CHECK     hash what you landed and compare to 6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd
MEASURED  bivpak/CLAUDE.md carries NO `nofile` and NO `runuser` today — the mirror is correctly pending
```

### 4.3 Absolute (m-3's V2)

```text
ZERO `want` values move · ZERO `expected_skips` members move
:68 / :71 / :268 / :271 and m-3's identity line stay EXACTLY as landed at e8aabc4
no product byte · no test byte · no fixture byte
```

### 4.4 Why self-relative is a bind and not a preference

m-3's byte review caught master's first cut citing the Linux counts by POSITION (`:268`/`:271`) — **true at
`9729191`, stale at `e8aabc4`, because OUR OWN identity line at `:76` shifted the Linux block by one.**
A bare position in a living artifact expires silently and nothing reports it.

**This is the second instance in two days from one habit:** the first was W-2's own `relay-lint.py:1432-1442`
pointer, stale since the v2.9 landing, which I disclosed at `234900`. Two registries, same defect.
**So: content anchors, never positions — in the comment we write, and in anything either of us cites about
it afterwards.**

### 4.5 Commit form

```text
its OWN commit, message NAMING R-4.31 · in-lane BEFORE the hand-up completes
routed to m-3 for the byte review on landing — they own the surface and hold the veto
NO re-run is owed: the green under the stated condition is already observed (412/0/1)
```

## 5. Scope for THIS token

SCOPE_DIFF:
- .github/workflows/s2-harness.yml -> in
- CLAUDE.md -> in
SCOPE_DIFF_RESULT: all-in

SCOPE_ROW_EVIDENCE:
- `.github/workflows/s2-harness.yml` — S-17 §4.1 ONLY: one COMMENT in the Linux job adjacent to its `want` block, statement text, self-relative. NO executable step, NO run-line, NO `want` value, NO `expected_skips` member. The five cells landed at `e8aabc4` are untouched.
- `CLAUDE.md` — S-17 §4.2 ONLY: the mirror bullet after `:11`, byte-identical to `pdc/CLAUDE.md:206-210` at `184a9c2`. No other line of this file.

**OUT — a discovered need is a STOP to me, never a licence:** every other byte of `.github/**`; every product, test and fixture path (the fold is landed and owner-passed — reopening it is not in this act); `pdc/**` entirely, the charter included (another repo, a governance surface, and the divergence question was routed at `040204` and answered by master re-landing the charter bullet itself).

## 6. Acceptance criteria

```text
A16  the workflow change is a COMMENT ONLY — `git diff` shows no executable line, no run-line, no `want`
     value and no `expected_skips` member changed
A17  the comment contains NO line-number citation of any kind, including its own
A18  the comment states BOTH halves of §4.1
A19  the landed CLAUDE.md bullet hashes EQUAL to 6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd
     — report the hash you computed of what you landed
A20  :68 / :71 / :268 / :271 and the identity line are byte-identical to e8aabc4
A21  ONE commit, message names R-4.31, and it touches exactly the two paths in §5
```

## 7. Questions for my Implementer

1. Where exactly do you place the comment relative to the Linux job's `want` block — immediately above it,
   or above the count-gate step? Either satisfies §4.1; say which and why.
2. Does the charter bullet you read at `184a9c2` hash to `6f245a90…` at your seat too? **Re-derive it; do
   not take mine.** If it differs, STOP and route — do not reconcile at the keyboard.
3. Anything in S-17 or A16–A21 you can refute. rev0–rev2 are approved and are not reopened.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: no product, test, fixture, workflow, documentation, branch, Docker, push, PR, Actions, merge, publication, deployment, or release act at this seat — plan-only. Read-only this pass: `pdc` commit `184a9c2` confirmed real and an ancestor of pdc HEAD; the charter's "Local Linux CI" section read AT that commit and the five-line R-4.31 bullet (`:206-210`) extracted and hashed to `6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd`, its shape checked against the recognition sketch and MATCHING; `bivpak/CLAUDE.md` grepped for `nofile`/`runuser` (absent — mirror pending) and its `:7-14` Local Linux CI section read; the incoming `143817` release read in full. I ran no container and no build. This relay + its INDEX row ride ONE explicit-path docs-lane commit whose SHA lands after filing. No token issued — it follows the PLAN-REVIEW on rev3 and parents to it.
RELAY_LINT: per D-3.4 (v2.9) — per-file WITH freshness (clock read immediately before filing, per D-5.10 instance 4), exit status checked un-piped and READ before committing; `--relay-root` run against this file and its output READ IN FULL. Standing reds disclosed: the cross-repo DESIGN-lineage class, of which this thread's plan revisions are members and whose coverage for the listed identity is the eleven-element W-2 join reported at `011101` — §1 carries the list forward so the coverage attaches to rev3 on its approval; INDEX cell-count (R-4.27) at 132, 222, 324, 362, 384, 388, 408, 435; INDEX time inversions at 222 and 393. `.relays/s4/INDEX.md` tail re-read before appending; `--index`; add and commit path-scoped; my appended row is 10-cell clean.
FINAL_GIT_STATUS_SHORT: literal path-scoped `git status --short` for this seat's two writes, captured at staging (the implementation worktree `s4-floor-slice-e-stage1a` reports EMPTY `git status --short` at `e8aabc4`; the shared main checkout carries sibling-authored untracked state, excluded and unclaimed):
  M  .relays/s4/INDEX.md
  A  .relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV3-S17-R431-RECIPE-COMMIT-SCOPE-LOCKED-20260818-144504.md

CARRY LIST (D-8.5):
- `.relays/s4/s4-floor-impl/PLAN-PLANNER-SLICE-E-REV3-S17-R431-RECIPE-COMMIT-SCOPE-LOCKED-20260818-144504.md` → `s4-floor.implementer`
- rev3 ADDS S-17, the ONE R-4.31 recipe commit, plus two scope rows, and nothing else; rev2 at 235116 approved at 000126 and through it rev1 and rev0 carry forward VERBATIM with S-1 through S-16, the sixteen live legs, A1 through A15 and G1 through G9 intact; the LANDED fold at e8aabc4 is complete and owner-passed at m-1 024245 and m-3 031641 and is NOT reopened, S-17 touching neither owner's reviewed surface. W-2's literal binding list is carried forward unchanged at one item, the measured fired set
- MIRROR BYTES TAKEN AT THE CHARTER, NOT FROM ANY RELAY: source is pdc/CLAUDE.md:206-210 at commit 184a9c2, which was verified to exist and to be an ancestor of pdc HEAD; the five-line bullet hashes 6f245a900277005d0214852798dca74d198d9472853c93819985393a464e21cd and that hash is how we CHECK what lands and never what we type; the bullet's shape was read against the recognition sketch and MATCHES, so no STOP fires on the wording. The orchestrator refused to make the canonical bytes a copy in their own hand and this seat holds the same line one hop further down
- S-17 WORKFLOW HALF, m-3's V1 and V3: a COMMENT in the Linux job of s2-harness.yml adjacent to that job's want block, statement text only, stating BOTH halves — that the Linux want counts were observed under nofile soft equal to hard, and that the chartered local substitute raises the soft limit to the inherited hard limit inside its runuser drop before invoking the suite; NO executable step, NO run-line, NO want value, NO expected_skips member; and SELF-RELATIVE BY RULE, never citing a line number including its own
- S-17 MIRROR HALF, m-3's V4: bivpak/CLAUDE.md directly after the parity bullet at :11, BYTE-IDENTICAL to the charter bullet, checked by hashing what lands against 6f245a90; measured today, bivpak/CLAUDE.md carries no nofile and no runuser so the mirror is correctly pending. ABSOLUTE, m-3's V2: zero want values move, zero expected_skips move, and :68 :71 :268 :271 plus the identity line stay EXACTLY as landed at e8aabc4, with no product, test or fixture byte
- SELF-RELATIVE IS A BIND AND NOT A PREFERENCE: m-3's byte review caught master's first cut citing the Linux counts by POSITION at :268 and :271, true at 9729191 but STALE at e8aabc4 because our own identity line at :76 shifted the Linux block by one, and a bare position in a living artifact expires silently. This is the SECOND instance in two days from one habit, the first being W-2's own relay-lint.py:1432-1442 pointer stale since the v2.9 landing which this seat disclosed at 234900 — two registries, same defect. Content anchors, never positions, in the comment we write and in anything either seat cites about it afterwards
- COMMIT FORM: its OWN commit naming R-4.31, in-lane BEFORE the hand-up completes, routed to m-3 for byte review on landing since they own the surface and hold the veto; NO re-run is owed because the green under the stated condition is already observed at 412/0/1
- SCOPE for this token is TWO rows, .github/workflows/s2-harness.yml and CLAUDE.md, with SCOPE_DIFF_RESULT all-in and per-row evidence; OUT and a STOP if needed are every other .github byte, every product test and fixture path since the fold is landed and owner-passed, and pdc entirely including the charter, another repo and a governance surface whose divergence question was routed at 040204 and answered by master re-landing the charter bullet itself
- SIX ACCEPTANCE CRITERIA A16 through A21 and three questions for the review, including a REQUIRED independent re-derivation of the charter bullet's hash at the Implementer's own seat rather than taking this seat's; NO token in this relay, the PLAN-REVIEW on rev3 being the next gate with the token parented to it; e8aabc4 stands; branch LOCAL and UNPUBLISHED; the merge is the operator's SEPARATE gate; merge is not push is not release; release hold ABSOLUTE
