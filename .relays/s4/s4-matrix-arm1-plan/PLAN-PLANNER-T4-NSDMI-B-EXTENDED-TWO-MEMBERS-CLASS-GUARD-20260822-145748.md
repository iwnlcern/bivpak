## PLAN — B, extended to TWO members, because the ruling and the guard it mandates cannot both hold as written. `budget_override` is NOT the only NSDMI-less member: `empty_config_keys` at `:25` lacks one too, and it is silent today only because all eight sites happen to name it. I measured all three arms on GCC 13: option B as literally ruled leaves the required canary RED

ROLE: Planner
PHASE: PLAN
AUTHORITY: plan-only
DISPATCH_ID: s4-matrix-t4-nsdmi-fix-plan
PARENT_DISPATCH_ID: s4-matrix-wave-a-t4-nsdmi-fix-ruled-b-class-guard
IN_REPLY_TO: .relays/s4/s4-matrix-arm1-plan/PLAN-ORCHESTRATOR-PLANNER-T4-NSDMI-FIX-RULED-B-PLUS-CLASS-GUARD-PATTERN-TO-M1-20260822-144729.md
RELATED_CONTEXT: .relays/s4/s4-matrix-arm1-plan/SITREP-PLANNER-T4-SCOUTED-SIX-RISK-PATHS-NSDMI-FIX-WOULD-DROP-20260822-141055.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: yes — ONE decision. `144729` rules B as the single line at `git_exec.hpp:24` AND mandates a class guard. I measured that those two cannot both hold: the canary stays RED under the one-line fix. This PLAN takes the resolution that satisfies BOTH of your own requirements (NSDMIs on both NSDMI-less members). If you would rather hold the literal one-line B, then the mandated guard must be withdrawn or redefined — I would rather you choose that explicitly than have me pick silently. This relay carries NO token; an Implementer PLAN-REVIEW approve is required and the bare token parents to THAT approval. No merge, push, PR mutation, schema act, deployment, or release. The release hold is ABSOLUTE
PLAN_LOCK_ID: s4-matrix-arm1-plan-20260806
BASE: reconstructed T4 `29120d09891bfc46e80635c2212befa22a0e2604` on FINAL T3 `70601fc201b3c41d2542d82399787b5febcbf03c`
FROM: s4-matrix.planner
TO: s4-matrix.implementer
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: PLAN — GitInvokeOptions has TWO NSDMI-less members not one; measured on GCC 13 that option B as literally ruled leaves the mandated canary RED and only NSDMIs on both members go green; B-extended plus the validated class canary, five proof obligations, scoped to git_exec.hpp and one test file

## 1. The ruling's premise is one line short, and I measured the consequence

`144729` states `budget_override` is "the ONLY member lacking" an NSDMI. Reading the struct at
the reconstructed head:

```text
struct GitInvokeOptions {                                    git_exec.hpp:19-26
  bool promisor{false};                                      NSDMI
  bool restore{false};                                       NSDMI
  bool allow_user_protocol{false};                           NSDMI
  GitCallClass call_class{GitCallClass::local};              NSDMI
  std::optional<std::chrono::milliseconds> budget_override;  NO NSDMI   :24
  std::span<const std::string> empty_config_keys;            NO NSDMI   :25   <- also
};
```

**Two** members lack an NSDMI, not one. The diagnosis of today's *symptom* is still exactly
right — only `budget_override` warns — and the reason is worth stating because it is the whole
trap: **all eight designated-init sites NAME `empty_config_keys`** (`classify.cpp:70`, `:113`;
`capture.cpp:38`, `:90`, `:111`, `:155`, `:292`, `:388`) and all eight OMIT `budget_override`.
So the second NSDMI-less member is invisible to the current build purely by coincidence of
call-site style.

**Measured on GCC 13.4.0 with `-Werror=missing-field-initializers`**, a standalone reproduction
of the struct plus the recommended canary shape (`GitInvokeOptions{.promisor = true}` — one
field named, all others omitted):

```text
ARM 1  struct as it is today          canary RED on BOTH budget_override and empty_config_keys   exit 1
ARM 2  budget_override{} ONLY         canary STILL RED on empty_config_keys                      exit 1
       (option B exactly as ruled)
ARM 3  BOTH members given NSDMIs      canary GREEN                                               exit 0
```

**So `144729`'s two requirements are mutually inconsistent as written.** It rules a one-line fix
and mandates a canary that the one-line fix cannot turn green. ARM 3 is the only configuration
that satisfies both, and it is forced rather than chosen — there is no discretionary widening
here, which is the difference between this and the oracle-C divergence where I did have a
choice and correctly had to route it.

I am flagging this the way I would want it flagged at me: the ruling is right about the cause,
right about B over C, and right to demand the guard. It stops one line short of the struct, and
a one-line-short premise is the same shape I have been caught on in this lane before.

## 2. The edit

Two NSDMIs in `src/core/repo/git_exec.hpp`, nothing else in production:

```cpp
  std::optional<std::chrono::milliseconds> budget_override{};
  std::span<const std::string> empty_config_keys{};
```

Both are provable behavioural no-ops, which is B's whole argument and it holds for both:
`std::optional<T>{}` is value-initialization, identical to the default constructor's empty
state; `std::span<const T>{}` is likewise the default-constructed empty span. Neither changes
what any of the eight sites already gets today.

I am NOT touching the eight call sites. Option C was rejected for eight production edits across
two files with member-order fragility, and that reasoning is unchanged and is now stronger:
under B-extended the sites need no edit at all.

## 3. The class guard

The canary shape `144729` recommends, and I adopt it because ARM 1/ARM 2 above already
demonstrate it discriminates:

```cpp
TEST_CASE("GitInvokeOptions members all carry default member initializers") {
  const biv::repo::GitInvokeOptions opts{.promisor = true};
  CHECK(opts.promisor);
  CHECK_FALSE(opts.restore);
  CHECK_FALSE(opts.allow_user_protocol);
  CHECK(opts.call_class == biv::repo::GitCallClass::local);
  CHECK_FALSE(opts.budget_override.has_value());
  CHECK(opts.empty_config_keys.empty());
}
```

Its guarding power is **not** in the assertions — it is in the *omission*. Naming one field and
omitting the rest means any future member added without an NSDMI makes this translation unit
fail `-Werror=missing-field-initializers` on Linux CI immediately, instead of silently on
someone's macOS Clang and then in CI weeks later. The assertions are a secondary check that the
defaults are what the NSDMIs say.

**Two things I want on the record about this guard.** First, it only fires where the warning
flag is on, so O-4 below requires the Implementer to confirm the test target actually carries
`-Werror=missing-field-initializers` — a canary compiled without the flag is a test that cannot
fail, and this lane has paid for unfalsifiable boxes before. Second, it guards
`GitInvokeOptions` alone. `Git::Opts` — T2's instance of this same class — is currently clean,
and a second canary there would guard both known instances. I have NOT put one in this plan
because the token `144729` describes is scoped to `git_exec.hpp` plus the guard's test file, and
`Git::Opts` lives in `git.hpp`. If the reviewer or the orchestrator wants it, it is one more
test function and no production byte, and I will file a rev1 — I would rather raise it than
quietly cover half the class I just named.

## 4. Proof obligations

```text
O-1  GCC MUST-BE-RED BASELINE, at the UNFIXED head 29120d0, under Docker --init and the
     chartered nofile lift: the focused Linux build fails on budget_override with
     -Werror=missing-field-initializers.  Record the exact diagnostic text and exit status.
     This validates the discriminator before anything is fixed.

O-2  LINUX GREEN at the fixed head: the same focused build succeeds, and its tests pass.
     Docker --init (035347/R-4.40) and nofile SOFT raised to the inherited HARD (R-4.31 arm (a)).
     Report any residual failures classified against the registered R-4.35 four-member family;
     anything outside it STOPS and routes.  Do not claim a whole-suite green.

O-3  MACOS INTERACTION SET GREEN at the fixed head (the T2/T3/T4 set the reconstruction used,
     14/14).  Record counts and exit status.

O-4  THE GUARD IS A REAL DISCRIMINATOR, proven in BOTH directions in a scratch copy:
       (a) confirm the guard's test target compiles WITH -Werror=missing-field-initializers --
           print the flag from the build command or the compile database.  A canary without
           the flag cannot fail and would be a ritual.
       (b) add a TEMPORARY NSDMI-less member to GitInvokeOptions -> the build MUST go RED,
           naming that member.
       (c) remove it -> GREEN.
     Restore-gate git_exec.hpp to its fixed digest after (b) and (c) before continuing.

O-5  SEMANTIC NO-OP AND SCOPE.  Exactly two changed files vs 29120d0: git_exec.hpp and the
     guard's test file.  No call site perturbed -- classify.cpp and capture.cpp must be
     byte-identical to 29120d0.  All eight GitInvokeOptions sites unchanged.
```

Any obligation that fails STOPS the cycle and routes; none may be reconciled into a pass.

## 5. Fence

In scope: `src/core/repo/git_exec.hpp` (two NSDMIs) and one test file for the canary.

**Not** in scope: `classify.cpp`, `capture.cpp` and every other call site; `git.hpp` and
`Git::Opts` (raised in §3, not planned); any other production byte; `.github/`; the schema; the
harness; the stage-5 report's contents.

No token here. Ceremony: this PLAN → Implementer PLAN-REVIEW → my bare `DISPATCH IMPL` parented
to that approval. Then T4 green on both platforms and Stage-3-panelable.

Merge ≠ push ≠ release; the release hold is ABSOLUTE.

ACTIONS_GIT_REF: none — no edits made at this seat; no branch, ref or worktree moved. Read-only `git show` of `src/core/repo/git_exec.hpp`, `classify.cpp`, `capture.cpp` and `git.hpp` at `29120d0`, `git cat-file -e` of `git_exec.hpp` at `70601fc` (absent, confirming T4-owned), and `git rev-parse` of the T4 branch; plus one disposable `gcc:13 --platform linux/amd64` container compiling a standalone 17-line reproduction of the struct in three arms to measure the canary's behaviour under `-Werror=missing-field-initializers`. No unrelated Docker resource pruned or removed. No merge, push, PR mutation, or remote CI. Docs lane: this relay + its INDEX row ride ONE explicit-path commit.
FINAL_GIT_STATUS_SHORT: this relay and its INDEX row are this seat's only working-tree delta at commit time; `git status --porcelain` over `harness/`, `src/`, `tests/`, `CMakeLists.txt` is empty; the shared checkout carries sibling-authored untracked paths, preserved and unclaimed
RELAY_LINT: exact-file WITH freshness immediately before commit; INDEX tail re-read before appending; `--index` diffed against the same lint on the pre-append blob; `--relay-root` run before commit required to name no error against this relay; `substantive_actions_ref` and `implementation_work_claimed` both measured FALSE on the finished bytes. Commit gated by logical AND.

CARRY LIST (D-8.5):
- `.relays/s4/s4-matrix-arm1-plan/PLAN-PLANNER-T4-NSDMI-B-EXTENDED-TWO-MEMBERS-CLASS-GUARD-20260822-145748.md` → TO `s4-matrix.implementer`
- THE RULING'S PREMISE IS ONE LINE SHORT: `144729` says `budget_override` is "the ONLY member lacking" an NSDMI, but `GitInvokeOptions` has TWO — `budget_override` at `:24` AND `std::span<const std::string> empty_config_keys` at `:25`. The SYMPTOM diagnosis is still exactly right (only `budget_override` warns) and the reason is the whole trap: all EIGHT designated-init sites NAME `empty_config_keys` (`classify.cpp:70`,`:113`; `capture.cpp:38`,`:90`,`:111`,`:155`,`:292`,`:388`) and all eight OMIT `budget_override`, so the second NSDMI-less member is invisible to the current build purely by coincidence of call-site style
- MEASURED ON GCC 13.4.0, three arms, standalone reproduction plus the recommended canary `GitInvokeOptions{.promisor = true}`: ARM 1 struct-as-today gives canary RED on BOTH members exit 1; ARM 2 `budget_override{}` ONLY, which is option B EXACTLY as ruled, leaves the canary STILL RED on `empty_config_keys` exit 1; ARM 3 BOTH members NSDMI'd gives canary GREEN exit 0
- SO `144729`'s TWO REQUIREMENTS ARE MUTUALLY INCONSISTENT AS WRITTEN — it rules a one-line fix and mandates a canary that the one-line fix cannot turn green. ARM 3 is the ONLY configuration satisfying both, so this is FORCED rather than chosen, which is the difference from the oracle-C divergence where I DID have a choice and correctly had to route it. ONE DECISION IS YOURS: if you prefer the literal one-line B, the mandated guard must be WITHDRAWN or REDEFINED, and I would rather you choose that explicitly than have me pick silently
- THE EDIT: two NSDMIs in `git_exec.hpp` and nothing else in production — `budget_override{}` and `empty_config_keys{}`. Both are provable behavioural no-ops, which is B's own argument holding for both: `std::optional<T>{}` is value-initialization identical to the default empty state, `std::span<const T>{}` is the default-constructed empty span. The EIGHT call sites are NOT touched — option C was rejected for eight production edits with member-order fragility and that reasoning is now stronger, since under B-extended the sites need no edit at all
- THE GUARD's power is in the OMISSION, not the assertions: naming one field and omitting the rest makes any future NSDMI-less member fail `-Werror=missing-field-initializers` on Linux CI immediately instead of silently on macOS Clang first. ARM 1 and ARM 2 already demonstrate it discriminates
- TWO THINGS ON THE RECORD ABOUT THE GUARD: (a) it only fires where the flag is on, so O-4 requires CONFIRMING the test target actually carries `-Werror=missing-field-initializers` — a canary compiled without the flag is a test that CANNOT FAIL and this lane has paid for unfalsifiable boxes before; (b) it guards `GitInvokeOptions` ALONE, and `Git::Opts` — T2's instance of this same class, currently clean — would need a second canary to cover both known instances. I did NOT put one in this plan because `144729` scopes the token to `git_exec.hpp` plus the guard's test file while `Git::Opts` lives in `git.hpp`; it is one more test function and no production byte, and I will file rev1 on request. Raised rather than quietly covering half the class I just named
- FIVE PROOF OBLIGATIONS: O-1 GCC MUST-BE-RED baseline at the UNFIXED `29120d0` recording the exact diagnostic and exit status, validating the discriminator before anything is fixed; O-2 Linux GREEN at the fixed head under Docker `--init` and the chartered `nofile` lift, with residuals classified against the registered R-4.35 four-member family and anything outside it STOPPING, and no whole-suite-green claim; O-3 macOS interaction set GREEN with counts and exit status; O-4 the guard proven a real discriminator in BOTH directions including confirming the flag is actually on the test target, a temporary NSDMI-less member turning the build RED and its removal GREEN, with a restore gate on `git_exec.hpp` after each; O-5 exactly TWO changed files versus `29120d0` with `classify.cpp` and `capture.cpp` byte-identical and all eight sites unchanged
- FENCE: `git_exec.hpp` and one test file only. NOT `classify.cpp`, NOT `capture.cpp`, NOT `git.hpp`/`Git::Opts`, no other production byte, no `.github/`, no schema, no harness, and not the stage-5 report's contents. NO TOKEN here: PLAN → Implementer PLAN-REVIEW → my bare token parented to THAT approval; then T4 green both platforms and Stage-3-panelable. T1 `00c06d9` / T2 `7688bbd` / T3 `70601fc` FINAL; T4 at `29120d0` NOT final and NOT panelable; all heads LOCAL and UNPUBLISHED; schema F+G-fenced; no remote CI, push, PR mutation, merge, publication, deployment or release; release hold ABSOLUTE
