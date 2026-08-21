## SITREP — T2 option B ruling received and verified; mandatory one-line NSDMI scope ready, but the bounded pair PLAN is the next gate and no implementation token exists

ROLE: Implementer
PHASE: SITREP
AUTHORITY: report-only
DISPATCH_ID: s4-matrix-t2-fix-b-plan-await
PARENT_DISPATCH_ID: s4-matrix-wave-a-t2-fix-ruled-b-nsdmi
IN_REPLY_TO: PLAN-ORCHESTRATOR-PLANNER-T2-FIX-RULED-B-NSDMI-CAUSE-FIX-COUNT-GATE-SHAPE-ROUTED-UP-20260821-164516.md
RUN_ID: s4
CEREMONY_TIER: production-risk
EVIDENCE_TARGET: E2
HUMAN_GATE_REQUIRED: no new operator gate, but the mandated pair ceremony is not optional: bounded pair PLAN, Implementer PLAN-REVIEW approval, then pair-Planner bare DISPATCH-IMPL before any source edit
BASE: reconstructed T2 `e17234356a53ef14b997a4cf038bd72898961424`
FROM: s4-matrix.implementer
TO: s4-matrix.planner
CC: operator, s4.orchestrator-planner, s4.orchestrator-reviewer, master.orchestrator-planner, master.orchestrator-reviewer
SUBJECT: T2 B ruling received and verified at clean e172343; required correction is exactly src/core/repo/git.hpp empty_config_keys{} with optional cwd/stdout_file NSDMIs declined as unneeded scope; awaiting the pair's bounded PLAN for Implementer PLAN-REVIEW, no bare token or source authority yet; count-gate shape remains out-of-fence and routed up

The Orchestrator Planner's ruling is received as a choice of fix, not as a bare
implementation token. The ordered ceremony in `164516` is literal: the pair Planner
files a bounded PLAN naming B; this seat reviews that PLAN; only an approving review may
parent the pair Planner's `DISPATCH-IMPL`. No such bounded PLAN exists at live INDEX EOF,
so no source edit, test rerun, or T2 panel is authorized by this SITREP.

## Byte verification and scope position

The reconstructed worktree is clean at
`e17234356a53ef14b997a4cf038bd72898961424`. `src/core/repo/git.hpp` is
byte-identical between old T2 `92a70c9` and reconstructed T2 `e172343`; its relevant
members remain:

```text
cwd                                      no NSDMI, but designated at both enumerating sites
no_lazy_fetch{false}
isolate_global_config{false}
empty_config_keys                        no NSDMI and omitted at both sites: the fired member
stderr_mode{separate}
stdout_file                              no NSDMI, but designated at both enumerating sites
budget{30s}
```

Five `Git::Opts{` construction sites exist. Three use `{}` and cannot produce the fired
warning; two enumerate the other members and omit `empty_config_keys`. This confirms the
Orchestrator's corrected crux: B is a targeted cause-fix, not restoration of a universal
all-members-have-NSDMI invariant.

For the bounded PLAN, my scope position is the mandatory fix only:

```cpp
std::vector<std::string> empty_config_keys{};
```

I decline the optional `cwd{}` and `stdout_file{}` additions for this repair. Neither
member fired, both are explicitly designated at the only enumerating sites, and adding
them would expand the reviewed production delta without closing an observed or routed
defect. A later invariant-wide cleanup can be separately justified; it is not needed to
clear this STOP.

## Review bar for the forthcoming bounded PLAN

The Implementer PLAN-REVIEW will require all of these to be explicit and executable:

1. Exact base `e17234356a53ef14b997a4cf038bd72898961424` and exact one-path,
   one-line intended delta in `src/core/repo/git.hpp` only.
2. Retained pre-fix RED from the actual candidate under Ubuntu 24.04 GCC 13.3.0 with
   `-Werror=missing-field-initializers`, plus a post-fix rerun of the same actual-tree
   build to GREEN; no synthetic-only substitution.
3. Semantic no-op proof: default construction and `{}` value-initialization both
   produce an empty `std::vector<std::string>`, and the existing default/explicit `Opts`
   call paths retain their behavior.
4. No call-site edit and no other `Opts` site perturbed; `git diff --check`, exact scope,
   clean worktree, and fixed-head identity captured.
5. Fresh local Linux evidence before T2 Stage-3 panel. The already-green macOS selection
   remains prior evidence, but any plan that claims a complete fixed-head matrix must say
   exactly what is rerun at the fixed head rather than silently transcribing old bytes.
6. Count-gate shape remains a documented T1/T2 stage-4 visibility finding, not part of
   this one-line repair; `.github` stays outside s4's fence and no workflow edit appears.

T3 and T4 remain untouched at their old heads; `compare.py` remains held for T3's ordered
reconstruction. No remote CI, push, merge, PR mutation, publication, schema, deployment,
or release act is authorized or performed. The release hold is ABSOLUTE.

ACTIONS_GIT_REF: read-only verification only: exact relay lint; T2 head/status; old-versus-reconstructed `git.hpp` equality; member bytes and all five `Git::Opts{` sites; live INDEX EOF and absence of a bounded successor pair PLAN. No product, test, workflow, branch, ref, container, remote CI, push, merge, PR mutation, publication, schema, deployment, or release act. This relay plus one live-EOF INDEX row ride one explicit-path docs-lane commit.
RELAY_LINT: exact-file with freshness; live INDEX EOF re-read before append; `--index`; explicit-path add and commit. Inherited append-only INDEX reds remain disclosed and unmodified.
FINAL_GIT_STATUS_SHORT: T2 clean at `e172343`; shared main retains sibling-authored untracked relays and migration notes unchanged and unclaimed; only this relay and its one INDEX append are this seat's docs-lane delta.

CARRY LIST:
- `.relays/s4/s4-matrix-arm1-plan/SITREP-IMPLEMENTER-T2-B-RULING-RECEIVED-BOUNDED-PLAN-AWAITED-20260821-164833.md` -> `s4-matrix.planner`
- option B accepted as the future plan scope: exactly `empty_config_keys{}` in `src/core/repo/git.hpp`; optional `cwd{}`/`stdout_file{}` declined for this repair
- next required artifact is the bounded pair PLAN; this seat then PLAN-REVIEWs it; only an approve may parent the pair Planner's bare implementation token
- no source authority yet; T3/T4 and compare.py held; count-gate workflow repair out-of-fence and routed up; release hold ABSOLUTE
