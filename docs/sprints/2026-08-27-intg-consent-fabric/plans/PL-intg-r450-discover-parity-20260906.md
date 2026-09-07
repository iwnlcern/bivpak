# R-4.50 claude-discover parity — Implementation Plan (revision 4)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task, IN DOCUMENT ORDER. Steps use checkbox (`- [ ]`) syntax for tracking. Nothing in this document is authority: implementation starts only on the pair Planner's addressed token after the exact-hash PLAN-REVIEW approve.

**Revision 4 (2026-09-06) — the implementer's Task 0 Step 5 STOP `175211` folded (PAIR-OWNED: the observer environment, no fence surface):** the isolated worktree had no `.venv-harness`, so `harness/CMakeLists.txt:12-20` fell through to Homebrew Python 3.14.6 without `pytest`'s `jsonschema`/`zstandard` and the exact-name-unset discriminator arm returned rc2=8 on ten collection errors before any harness assertion (root cause bounded read-only at the implementer's seat; the worktree retained clean at B; no P). rev4 adds Task 0 Step 3b — provision the worktree's harness venv EXACTLY as CI does (`s2-harness.yml:14-17`: Python 3.12 + `harness/requirements.lock`; the 2a lane's worktree carries the same venv; the Linux container's Phase S already provisions it) into the IGNORED path `.venv-harness/` (`.git/info/exclude:8`, shared by every worktree — `git check-ignore` proves it before any status gate) and proves the three modules import — and makes Task 0 Step 4 configure into a FRESH build directory, because `BIVHARNESS_PYTHON` is a CMake CACHE entry: re-configuring an existing `build/ci-macos` keeps the 3.14 fallback (MEASURED 2026-09-06 on a scratch harness configure: same build dir after the venv appears → still 3.14; a fresh build dir → the venv python) and the cache proof `grep -c` on `CMakeCache.txt` is the gate. The `175211` execution under `intg-r450-discover-parity-impl` is CONSUMED; the discriminator runs ONCE under rev4's token as a NEW execution, never a retry. A resume checkpoint lets Task 0 Step 2 VERIFY the retained worktree instead of re-creating it. Nothing else moved: helper bytes, the discover body, the witness, B/P/C, the vehicle, the landing rule. **Revision 3 (2026-09-06) — the `161925` must-revise of rev2 (`9b889d04`) folded across the WHOLE artifact:** F1 the six helpers are MATERIALIZED at Task 0 Step 0b, before any use (every invocation now follows its creation in document order — checked mechanically: each helper's first `python3 "$EVID/<name>.py"` line number > its fenced block's line number); F2 every helper invocation carries a CAPTURED status that is the gate (`cells.py` at B and C, `gate.py`, both `tuples.py` runs — a partial parse or an `equal=no` run exits nonzero with non-empty output, so `[ -s ]` alone was never a gate), and the two wc-to-tr line-count pipelines are replaced by a single-stage `awk 'END { print NR }'` count with its own status; the pipeline sweep is now MECHANICAL over executable spans (every backtick span containing a spaced pipe character; result 0 — prose cites no pipeline in backticks); F3 acceptance criterion 2 names its FIVE producing steps — `witness.py green` on the full-suite `biv_tests` XML at P/macOS, P/Linux, C/macOS, C/Linux plus the targeted run at P — each status-captured with a non-empty verdict file. Helper bytes and owner-ruled semantics unchanged from rev2. **Revision 2** folded `065859` (F1 RED fail-closed; F2 R-OBS before any suite run; F3 no tag; F4 producers materialized), CG-R7 rev5 B/P/C, and the R-4.52 landing rule.

**Goal:** execute sealed c1 §7 in the claude adapter's `discover` body so an existing `CLAUDE_CONFIG_DIR` store no longer suppresses an existing `$HOME/.claude` default store (both are searched, env first), with codex's `discover` as the reference shape; witness it with rows 1–5 + the codex parity row; land as ONE commit on a branch cut at the PUBLISHED base, carried to `origin` as a PR (the vehicle, never the evidence).

**Architecture:** the discover body becomes the codex shape (optional `env_root`; append the env store iff its value exists; append the default iff it exists AND `lexically_normal()` differs) — no other product byte. One NEW named Catch2 `TEST_CASE` in `tests/test_adapter_claude_collect.cpp` carries rows 1–5 + parity as `SECTION`s (the fence owner's shape, N = 1 exactly). The census change is transcribed into the two `successes` literals of `.github/workflows/s2-harness.yml` (`:85` macOS, `:326` Linux) in the SAME commit from the candidate's OWN observed `-r xml` runs under CG-R7 (rev5) and T-1..T-5 — observed, never derived. Two owners review one commit: m-2's fenced byte review (V-CP-1..6) over the product + test bytes; m-3's hunk review (CG-R7.5) over the two workflow lines.

**Tech stack:** C++20 (`std::filesystem`), Catch2 v3.7.1 (`TEST_CASE`/`SECTION`, `-r xml`, `-w UnmatchedTestSpec`), CMake presets `ci-macos` (host) and `ci` (Linux parity container: ubuntu-24.04 `linux/amd64` `--init`, `nofile` soft == hard), git worktrees, `gh` 2.97, python3 (XML parsing only).

**Spec (the law of this act, cited never retyped):** m-2 fence rev2 `pdc:master/relays/r437-pack-timeout-diagnosis/DESIGN-m2-planner-20260903-144700.md` @ sha256 `f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f` (pdc `dfb5b409`; Master Reviewer approve `151001`; design origin `intg-r450-discover-parity-act/DESIGN-m2-planner-20260906-002200.md` for `DESIGN_DOC_ID m2-r450-discover-fence-rev2-20260903`; peer approve `DESIGN-REVIEW-implementer-20260906-004520.md` at pdc `79fa1754`). Operator grant `r437-operator-scope-ruling/PLAN-operator-20260903-152117.md`. Master's route `intg-r450-discover-parity-act/PLAN-master-planner-20260905-212735.md`, composed ruling `PLAN-master-planner-20260906-004023.md`, and the R-4.52 landing carry `PLAN-master-planner-20260906-015102.md` (operator carrier `publication-path-ruling/PLAN-operator-20260906-015101.md`). m-3's Q2 ruling `DESIGN-planner-20260906-002436.md` (T-1..T-5) and the count-gate design `master/domains/m-3-restore-cli/design/2026-08-30-count-gate-repair-r438-rev1.md` at rev5 @ `9a0320b60e87819495ae1b11a9c4469455267af0275b9479dbf81376d1940f7d` (CG-R7.1–7.7 + V-CG-6; Master Reviewer approve `053521`; rev1 `0099d1cf` stays the landed repair's pin). Sealed c1 §7 in `master/domains/m-2-agent-adapters/design/2026-07-02-adapter-contract-and-session-semantics.md` @ `e4c19914…`.

## Global constraints (each line binds every task)

- DETERMINING TEXT (c1 §7): "Discovery returns ALL stores found (a set): env-set does not suppress the default if both exist and differ — both are searched."
- REFERENCE SHAPE: `src/adapters/codex/codex.cpp:1193-1206` for DISCOVER ONLY — append; `lexically_normal()` guard; env then defaults. Its trailing-slash property (`"/x/.claude/"` ≠ `"/x/.claude"` under `lexically_normal()`, probed 2026-09-05) is INHERITED by parity; any "tightening" is a V-CP-2 divergence (m-2, `004023`).
- TOUCHABLE: `src/adapters/claude_code/claude_code.cpp` discover body (:570-596 at the base) + `tests/test_adapter_claude_collect.cpp` + EXACTLY the two integer literals at `.github/workflows/s2-harness.yml:85` and `:326` (m-3's surface, CG-R7.2/7.4 (α); V-CP-1 read on the record to exclude them). NOTHING ELSE — no codex byte (V-CP-3), no collect byte (V-CP-4), no harness/stub/witness byte (V-CP-5), no other workflow byte (CG-R7.4 → STOP to m-3.planner), no CMake, no fixture file, no docs byte on the branch, NO TAG (local or remote), no ref other than the one branch. IGNORED, UNTRACKED environment paths in the worktree (`.venv-harness/` — ignored by `.git/info/exclude:8`, shared by all worktrees; `build/` — `.gitignore:1`) may be created, deleted and re-created: they are not repository bytes, and `git check-ignore -q <name>/` (trailing slash — the patterns are directory-only) proves each before any status gate reads the worktree.
- VETOES V-CP-1..6 (`144700` lines 64-71) and S-CP-1..5 (`142000` :55-71; S-CP-5 HELD, dedupe OUT) bind as written; sealed-text silence = STOP UP through the pair Planner → master; never a local reading.
- COUNT-GATE TERMS T-1..T-5 (`002436`) and CG-R7.1–7.7 (rev5): B/P/C predeclared below with binding points; the trigger is P's OBSERVATION against B's workflow values (a `TEST_CASE` diff is a PREDICTOR and consistency check only); cells transcribed from P's `-r xml` `OverallResultsCases` tuples on BOTH targets under CG-R2's topology and the R-OBS observer environment (`CREDENTIAL_ENV_NAMES` derived from `harness/bivharness/e3.py` at the head, unset by NAME, values never read); NO arithmetic anywhere in the evidence; an observed delta the predictor does not predict, or a predicted delta not observed, is a FINDING routed UP (a skip-set move touches `expected_skips` → V-CG-5 routed finding FIRST, never an edit); the ten per-binary tuples + XML sha256 + run identity + the old(B)/observed(P)/new(C) table in the commit message AND the tracked report.
- ONE commit `C` on branch `intg/r450-discover-parity` cut at `origin/main` = `bbf297e36a38a1fab8c2675f945098a0633f9f8b` (the PUBLISHED base; product bytes equal to local `main`; the PR's lineage exports zero unpublished commits — MEASURED at Task 0 Step 3 and Task 3 Step 4). Commit messages end with `Co-Authored-By: Claude Fable 5.1 <noreply@anthropic.com>`.
- SHELL DISCIPLINE (standing corrective `164704`; the F4 class): every status captured as `rc=0; <cmd> || rc=$?` and RECORDED; never `set +e`; NO pipelines in any evidence-producing span — every producer writes a FILE and its status is checked before the consumer reads the file; `grep -c`/`grep`/`git grep`/`diff` exit 1 is VALID DATA (zero matches / a difference) classified separately from 2+ (an error → STOP); every evidence file `[ -s file ] || STOP` before it is read (except files whose EXPECTED content is empty, which are checked with `[ ! -s file ]` after their producer's status is proven); refspecs and paths never spelled `"$VAR:…"` (zsh modifiers) — `"${VAR}"` braces everywhere a variable touches punctuation; the push line names the branch LITERALLY and is validated by `git push --dry-run` immediately before; no variable named `path`. `STOP` = stop the task, record the failing status and file, return to the pair Planner (never a retry, never a re-observation).
- The GitHub token never enters a container or any evidence; credential VALUES never read/printed; the host worktree byte-clean at product paths; inherited S4 state preserved, never cleaned.
- Merge ≠ push ≠ release. The branch push and the PR are authorized by R-4.51 clause (2) via the route; the local merge waits on the four-condition bar + both owner reviews + the operator's condition-4 token; under the R-4.52 LANDING RULE (operator option A, `015101`/`015102`) the landing = that merge PLUS ONE fast-forward push of local `main` to `origin/main` by this lane — that push is the MERGE PACKET's own step in the first-push shape, NOT this plan's token (this plan ends at the open PR); no docs-lane-only push; no tag/release/deploy/seal; red remote CI blocks nothing and is cited nowhere. The release hold is ABSOLUTE.

---

## B / P / C — roles, resolution, binding points (CG-R7.7, predeclared BEFORE any observation)

```text
B  the pre-act BASELINE = the declared base = origin/main = bbf297e36a38a1fab8c2675f945098a0633f9f8b (the published pin;
   the commit whose workflow bytes the candidate inherits). RESOLVED at Task 0 Step 1 (the remote re-read must equal it)
   and RECORDED with B's workflow values: the ten cells read from `git show bbf297e…:.github/workflows/s2-harness.yml`
   (biv_tests :85 = 418 / :326 = 420; the other eight cells; the macOS expected_skips names — the Linux job has
   no identity block, only its skips count cell) → $EVID/B-cells.txt.
P  the PROVISIONAL tree = product + test bytes over B's workflow bytes, workflow UNTOUCHED. P's identity is RECORDED at
   Task 1 Step 7 (after the provisional commit exists, BEFORE Task 2 observes it) → $EVID/P.txt. P is observed on both
   targets (Task 2) and is the SOURCE of every transcribed literal and of the skip identity set.
C  the CANDIDATE = P amended with EXACTLY the admitted (α) lines whose values P's observation supplied. C's identity is
   RECORDED at Task 3 Step 3 (after the amendment exists, BEFORE Task 4 observes it) → $EVID/C.txt. The diff P→C is
   exactly those lines (Task 3 Step 4). C is observed as the evidence of record (Task 4); C's observations == P's
   observations == C's literals (Task 4 Step 2).
ENTRY (CG-R7.1)  P's biv_tests tuple vs B's cells: a difference = census-changing act → transcription (Task 3);
   EQUAL = zero-delta — which CONTRADICTS the predictor (+1 TEST_CASE) → FINDING routed UP, no transcription, no commit.
TABLE  $EVID/bpc-table.txt: per binary per target one line `binary target old_B observed_P new_C` (values copied from the
   files that hold them, never typed); the identities B/P/C with their binding steps on top. Goes into the commit message
   (B, P; C's own sha cannot be in C's message — stated) and the tracked report (all three).
ANTI-RETROSPECTION  P.txt and C.txt are written at their binding steps and never rewritten; every later use re-reads them.
```

## File structure

- Modify: `src/adapters/claude_code/claude_code.cpp:570-596` — the `discover` body only.
- Modify: `tests/test_adapter_claude_collect.cpp` — one test-local `ScopedEnvVar` helper + two small helpers + ONE new `TEST_CASE` (rows 1–5 + parity as `SECTION`s), appended after the existing discover case at :97-116 (which is unchanged).
- Modify: `.github/workflows/s2-harness.yml:85` and `:326` — the two `biv_tests` `successes` integer literals, transcribed (Task 3), nothing else.
- Evidence (outside the repository): `$EVID` under `mktemp -d`; the tracked report `docs/sprints/2026-08-27-intg-consent-fabric/results/intg-r450-discover-parity-<C>.md` lands on lane-local `main` by the pair Planner (docs lane), never on the branch.

## The circularity, stated and resolved (CG-R7.7 is this shape, ruled)

A literal cannot be observed at the commit that contains it. Resolution, all three halves recorded: (1) P (product + test, workflow untouched) is observed on BOTH targets — the P run is the SOURCE of the two literals (copied from the XML by a script, Task 3); (2) P is amended into C (the two literals + the full message carrying the P tuples and `observed_head=P`); the tree delta P→C is PROVEN to be exactly the two workflow lines; P stays reachable by its recorded object id (the branch reflog holds it — `git reflog show intg/r450-discover-parity` lists it; `git cat-file -e` proves it before every use; no tag is created); (3) C is RE-OBSERVED on both targets — the C runs are the runs OF RECORD (ten tuples + XML sha256 + run identity in the tracked report and the IMPL return), and every C cell MUST equal the literal in C's workflow AND the P tuple; any inequality = FINDING, STOP UP. The two-commit alternative (product commit, then a workflow-only child as `b065de1` did) was rejected: the route and CG-R7.2 say ONE commit.

---

### Task 0 — worktree, branch at the published base, evidence home, B recorded, the harness venv provisioned, the observer environment derived (no product byte)

**Files:** none modified.

- [ ] **Step 0: evidence home + initial snapshot** (the inside-repo `case` guard VALIDATED 2026-09-06 in bash AND zsh: /tmp → ok, ./build → STOP) — `EVID=$(mktemp -d "${TMPDIR:-/tmp}/r450-evidence-XXXXXX")`; `case "$(cd "$EVID" && pwd -P)/" in "$(git rev-parse --show-toplevel)/"*) echo STOP-evid-inside-repo; exit 1;; esac`; `s0=0; git -C /Users/jack/Programming/bivpak status --porcelain > "$EVID/status-initial.txt" || s0=$?; [ "$s0" -eq 0 ] || STOP` (inherited S4 modifications are PRESERVED and DISCLOSED, never staged or cleaned; this file may legitimately be non-empty).

- [ ] **Step 0b: MATERIALIZE THE SIX HELPERS — before ANY use (F1 of `161925`)** — each block below is written to `$EVID/<name>.py` VERBATIM from this plan (copy the fenced bytes exactly; no edits), then proven present and syntactically valid with a CAPTURED status before the next helper is written: for each name in `cells witness hunks tuples transcribe gate`: `[ -s "$EVID/<name>.py" ] || STOP; k=0; python3 -m py_compile "$EVID/<name>.py" || k=$?; [ "$k" -eq 0 ] || STOP` (VALIDATED 2026-09-06 in bash AND zsh: the six extracted helpers compile with k=0; a helper with one byte corrupted → k=1 → STOP). Every later step INVOKES a helper only; no step writes one. Helper semantics are unchanged from rev2 (each carries its VALIDATED note, re-run at the pair Planner's seat on the rev3 bytes).

**`cells.py`**

```python
#!/usr/bin/env python3
# usage: cells.py <s2-harness.yml>   — prints the ten count-gate cells (+ the macOS expected_skips names), read from the bytes
import re, sys
text = open(sys.argv[1], encoding="utf-8").read()
starts = [m.start() for m in re.finditer(r"checks = \{", text)]
if len(starts) != 2:
    sys.exit(2)  # exactly one macOS block and one Linux block
bounds = starts + [len(text)]
for target, (lo, hi) in zip(("macos", "linux"), zip(starts, bounds[1:])):
    region = text[lo:hi]
    end = re.search(r"\n {10}\}\n", region)  # the block closer at the workflow's indentation
    if end is None:
        sys.exit(2)
    checks = region[:end.start()]
    cells = re.findall(r'"(biv_[a-z_]+)": \{\s*"successes": (\d+),\s*"failures": (\d+),\s*"expectedFailures": (\d+),\s*"skips": (\d+),', checks)
    if len(cells) != 5:
        sys.exit(3)
    for binary, s, f, e, k in cells:
        print(f"{binary} {target} successes={s} failures={f} expectedFailures={e} skips={k}")
    skips = re.search(r"expected_skips = \{(.*?)\}", region[end.end():], re.S)
    names = re.findall(r'"([^"]+)"', skips.group(1)) if skips else []
    print(f"expected_skips {target} {'n=' + str(len(names)) if skips else 'absent'} " + " | ".join(names))
```

Write this block to `$EVID/cells.py` VERBATIM from the plan (the pair Planner extracted and RAN it on the workflow at `bbf297e` 2026-09-06: ten cells with `biv_tests macos successes=418 … skips=3` and `biv_tests linux successes=420 … skips=1`; `expected_skips macos n=3` and `expected_skips linux absent` — the Linux job carries NO `expected_skips` identity block, only its count cell (`grep -c expected_skips` = 3 at `bbf297e`, all in the macOS job: the definition `:97` and its two uses `:119`/`:127`; none in the Linux job); on a copy with the Linux block removed → rc 2; with one binary removed → rc 3).

**`witness.py`**

```python
#!/usr/bin/env python3
# usage: witness.py <catch2-xml> red|green   — exit 0 iff the five ROW leaves have exactly the expected outcome
import sys, xml.etree.ElementTree as ET
xml_path, mode = sys.argv[1], sys.argv[2]
NAME = "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)"
RED_ROWS = {"ROW 1", "ROW 5"} if mode == "red" else set()
root = ET.parse(xml_path).getroot()
cases = [tc for tc in root.iter("TestCase") if tc.get("name") == NAME]
if len(cases) != 1:
    sys.exit(2)  # the named case must appear exactly once
seen = {}
for section in cases[0].findall("Section"):
    label = section.get("name", "").split(":")[0].strip()  # "ROW n"
    if not label.startswith("ROW "):
        continue
    results = section.find("OverallResults")
    if results is None or label in seen:
        sys.exit(3)  # every leaf carries one OverallResults; a leaf appears once
    seen[label] = int(results.get("failures", "-1"))
if set(seen) != {"ROW 1", "ROW 2", "ROW 3", "ROW 4", "ROW 5"}:
    sys.exit(4)  # all five leaves present
for label, failures in sorted(seen.items()):
    expected_red = label in RED_ROWS
    if failures < 0 or (failures > 0) != expected_red:
        sys.exit(5)  # a leaf's outcome differs from the mode's expectation
    print(f"{label} failures={failures} expected={'red' if expected_red else 'green'} ok")
overall = cases[0].find("OverallResult")
if overall is None or (overall.get("success") == "true") != (mode == "green"):
    sys.exit(6)  # the case verdict must agree with the mode
print(f"{mode} verdict ok")
```

Write this block to `$EVID/witness.py` VERBATIM from the plan (the pair Planner extracted and RAN it 2026-09-06 against synthetic Catch2 XML in the shape the binary emits: red-mode YES case ROW 1 + ROW 5 failing → 0; all-green in red mode → 5; ROW 2 failing in red mode → 5; a missing ROW 4 → 4; a duplicated leaf → 3; the wrong case name → 2; green-mode with the all-green XML → 0).

**`hunks.py`**

```python
#!/usr/bin/env python3
# usage: hunks.py <hunk-headers-file> <lo> <hi>  — exit 0 iff every @@ -a,b +c,d @@ old-range lies within [lo, hi]
import re, sys
lo, hi = int(sys.argv[2]), int(sys.argv[3])
headers = [line for line in open(sys.argv[1], encoding="utf-8").read().split("\n") if line.startswith("@@")]
if not headers:
    sys.exit(2)
for header in headers:
    m = re.match(r'@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@', header)
    if m is None:
        sys.exit(3)
    start = int(m.group(1)); count = int(m.group(2)) if m.group(2) is not None else 1
    end = start + count - 1 if count > 0 else start
    if start < lo or end > hi:
        print(f"OUTSIDE {header}")
        sys.exit(4)
    print(f"inside {header}")
```

Write this block to `$EVID/hunks.py` VERBATIM (the pair Planner RAN it 2026-09-06: a header `@@ -570,27 +570,29 @@` with bounds 570 596 → 0; `@@ -569,2 +569,2 @@` → 4; `@@ -590,10 +590,10 @@` → 4; an empty file → 2; a malformed header → 3).

**`tuples.py`**

```python
#!/usr/bin/env python3
# usage: tuples.py <target> <xml>...  — one line per XML: binary target successes failures expectedFailures skips xml_sha256; then the biv_tests skip set
import hashlib, os, sys, xml.etree.ElementTree as ET
target = sys.argv[1]
skips = None
for xml_path in sys.argv[2:]:
    binary = os.path.basename(xml_path).split("-")[0]
    data = open(xml_path, "rb").read()
    if not data:
        sys.exit(2)
    cases = ET.fromstring(data).find("OverallResultsCases")
    if cases is None:
        sys.exit(3)
    tuple_ = " ".join(f"{k}={cases.get(k, '0')}" for k in ("successes", "failures", "expectedFailures", "skips"))
    print(f"{binary} {target} {tuple_} xml_sha256={hashlib.sha256(data).hexdigest()}")
    if binary == "biv_tests":
        skips = sorted(tc.get("name") for tc in ET.fromstring(data).iter("TestCase") if tc.find("Skip") is not None)
if skips is None:
    sys.exit(4)
print(f"expected_skips_observed {target} n={len(skips)} " + " | ".join(skips))
```

Write this block to `$EVID/tuples.py` VERBATIM (the pair Planner RAN it 2026-09-06 on a synthetic five-XML set in the binary's shape: five tuple lines + the skip line with n=3; an empty XML → 2; an XML without `OverallResultsCases` → 3; a set without a `biv_tests` XML → 4).

**`transcribe.py`**

```python
#!/usr/bin/env python3
# usage: transcribe.py <workflow> <macos-biv_tests.xml> <linux-biv_tests.xml>
# Writes the observed biv_tests "successes" cells into lines 85 and 326 of the workflow.
# No arithmetic: the value written IS the XML's OverallResultsCases successes attribute.
import sys, re, xml.etree.ElementTree as ET
workflow, macos_xml, linux_xml = sys.argv[1], sys.argv[2], sys.argv[3]
def observed(path):
    cases = ET.parse(path).getroot().find("OverallResultsCases")
    if cases is None or cases.get("successes") is None:
        sys.exit(2)
    return cases.get("successes")
targets = {85: observed(macos_xml), 326: observed(linux_xml)}
lines = open(workflow, encoding="utf-8").read().split("\n")
for lineno in targets:
    if lines[lineno - 2].strip() != '"biv_tests": {':
        sys.exit(3)  # the anchor line above each cell must be the biv_tests block opener
    m = re.fullmatch(r'(\s+"successes": )(\d+)(,)', lines[lineno - 1])
    if m is None:
        sys.exit(3)
    lines[lineno - 1] = f"{m.group(1)}{targets[lineno]}{m.group(3)}"
open(workflow, "w", encoding="utf-8").write("\n".join(lines))
print("transcribed", targets)
```

**`gate.py`**

```python
#!/usr/bin/env python3
# usage: gate.py <C-cells.txt> <P-macos> <P-linux> <C-macos> <C-linux>  — exit 0 iff every cell agrees across literal(C), observed(P), observed(C)
import sys
def read(path):
    rows = {}
    for line in open(path, encoding="utf-8"):
        parts = line.split()
        if len(parts) >= 6 and parts[0].startswith("biv_") and parts[2].startswith("successes="):
            rows[(parts[0], parts[1])] = tuple(p.split("=", 1)[1] for p in parts[2:6])
    return rows
literals = read(sys.argv[1])
observed_p = {**read(sys.argv[2]), **read(sys.argv[3])}
observed_c = {**read(sys.argv[4]), **read(sys.argv[5])}
if len(literals) != 10 or set(literals) != set(observed_p) or set(literals) != set(observed_c):
    sys.exit(2)
bad = 0
for key in sorted(literals):
    ok = literals[key] == observed_p[key] == observed_c[key]
    bad += 0 if ok else 1
    print(f"{key[0]} {key[1]} literal_C={literals[key]} observed_P={observed_p[key]} observed_C={observed_c[key]} equal={'yes' if ok else 'no'}")
sys.exit(0 if bad == 0 else 5)
```

Write this block to `$EVID/gate.py` VERBATIM (the pair Planner RAN it 2026-09-06 on synthetic inputs: all ten agreeing → 0 with ten `equal=yes` lines; one C tuple altered → 5 with one `equal=no`; a missing cell → 2).

- [ ] **Step 1: the base is the published pin — B RESOLVED and RECORDED** — `f=0; git -C /Users/jack/Programming/bivpak fetch --no-tags origin refs/heads/main:refs/remotes/origin/main || f=$?; [ "$f" -eq 0 ] || STOP` (one ref, literal refspec); `BASE=$(git -C /Users/jack/Programming/bivpak rev-parse origin/main)`; REQUIRE `[ "$BASE" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP` (the remote moved — STOP UP, never re-base silently); `d=0; git -C /Users/jack/Programming/bivpak diff --quiet bbf297e36a38a1fab8c2675f945098a0633f9f8b main -- src tests CMakeLists.txt CMakePresets.json harness .github || d=$?; [ "$d" -eq 0 ] || STOP` (product bytes at the published pin == local main; measured 2026-09-05: 0 lines; `d` 1 = a real difference, 2+ = an error — both STOP, distinguished by the recorded value). B's workflow values: `w=0; git -C /Users/jack/Programming/bivpak show bbf297e36a38a1fab8c2675f945098a0633f9f8b:.github/workflows/s2-harness.yml > "$EVID/B-workflow.yml" || w=$?; [ "$w" -eq 0 ] && [ -s "$EVID/B-workflow.yml" ] || STOP`; `c=0; python3 "$EVID/cells.py" "$EVID/B-workflow.yml" > "$EVID/B-cells.txt" || c=$?; printf 'cells_B_rc=%s\n' "$c" > "$EVID/B-cells.rc"; [ "$c" -eq 0 ] && [ -s "$EVID/B-cells.txt" ] || STOP` (the helper materialized at Step 0b; a rejected PARTIAL parse exits 3 with six lines already printed — the STATUS is the gate, non-emptiness alone is not: VALIDATED 2026-09-06 in bash AND zsh: a mutant with one LINUX binary removed → the six macOS lines printed, then c=3 — output NON-EMPTY yet STOP reached on the status; a mutant with a macOS binary removed → c=3 with empty output) — the ten `binary target successes failures expectedFailures skips` lines + the macOS `expected_skips` name list (the Linux job carries no identity block; its skip identity is compared by COUNT only, the observed names recorded for the report), READ from B's bytes, never typed. Record `printf 'B=%s\n' "$BASE" > "$EVID/B.txt"`.

- [ ] **Step 2: worktree + branch — CREATE or VERIFY (resume checkpoint, rev4)** — if `/Users/jack/Programming/bivpak-intg-r450-discover-parity` does NOT exist: `git -C /Users/jack/Programming/bivpak worktree add -b intg/r450-discover-parity /Users/jack/Programming/bivpak-intg-r450-discover-parity bbf297e36a38a1fab8c2675f945098a0633f9f8b`; if it DOES exist (the `175211` STOP retained it clean at B): do NOT re-create — `cd` into it and VERIFY the same facts below (HEAD == the pin; status EMPTY; branch name `intg/r450-discover-parity`: `[ "$(git rev-parse --abbrev-ref HEAD)" = intg/r450-discover-parity ] || STOP`); any other state = STOP UP (never a reset, never a checkout). Then `cd /Users/jack/Programming/bivpak-intg-r450-discover-parity`; REQUIRE `[ "$(git rev-parse HEAD)" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP`; `s=0; git status --porcelain > "$EVID/status-worktree-0.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-worktree-0.txt" ] || STOP` (an EMPTY status is the expected content — checked as empty AFTER the producer's status is proven).
- [ ] **Step 3: the cut-point measurement (R-4.8 lesson)** — `c=0; n=$(git rev-list --count origin/main..HEAD) || c=$?; [ "$c" -eq 0 ] || STOP; [ "$n" -eq 0 ] || STOP; printf 'unpublished_commits_in_lineage=%s\n' "$n" > "$EVID/cutpoint.txt"`.
- [ ] **Step 3b: the harness venv in the worktree — CI's own recipe, into an IGNORED path (rev4; the `175211` cause)** — `g=0; git check-ignore -q .venv-harness/ || g=$?; [ "$g" -eq 0 ] || STOP` (the TRAILING SLASH is load-bearing: the exclude pattern `.venv-harness/` at `.git/info/exclude:8` is directory-only, so the query on an ABSENT path without the slash returns 1 even though the created directory will be ignored — MEASURED 2026-09-06 in bash AND zsh in a scratch repo carrying the same pattern: absent + no slash → 1; absent + slash → 0; existing dir → 0; and at the retained r450 worktree: absent + no slash → 1 while the main checkout and the 2a worktree, where the directory exists, → 0; rc 1 on the slash form = NOT ignored → STOP UP before anything is written); if `.venv-harness` already exists from a prior rev4 execution, delete it first (`rm -rf .venv-harness` — an ignored, untracked directory, never a repository byte); `v=0; /opt/homebrew/bin/python3.12 -m venv .venv-harness || v=$?; [ "$v" -eq 0 ] || STOP` (Python 3.12, the version CI pins at `s2-harness.yml:14`); `i=0; .venv-harness/bin/python -m pip install -q -r harness/requirements.lock > "$EVID/venv-pip.log" 2>&1 || i=$?; [ "$i" -eq 0 ] || STOP` (the pinned lock: `jsonschema==4.25.1`, `pytest==8.4.2`, `zstandard==0.25.0`); the module proof: `m=0; .venv-harness/bin/python -c 'import importlib.util as u, sys; missing = [m for m in ("pytest", "jsonschema", "zstandard") if u.find_spec(m) is None]; print("missing:", missing); sys.exit(1 if missing else 0)' > "$EVID/venv-modules.txt" 2>&1 || m=$?; [ "$m" -eq 0 ] || STOP`; record `.venv-harness/bin/python --version > "$EVID/venv-python.txt"`. (The whole form VALIDATED 2026-09-06 in a scratch directory: venv rc 0, pip rc 0, `missing: []`, Python 3.12.12.) The status gate stays valid: `s=0; git status --porcelain > "$EVID/status-post-venv.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-venv.txt" ] || STOP`.
- [ ] **Step 4: baseline build + baseline discover census — into a FRESH build directory (rev4)** — `BIVHARNESS_PYTHON` is a CMake CACHE entry (`harness/CMakeLists.txt:13-20`): a re-configure of an existing `build/ci-macos` KEEPS the interpreter it first chose (MEASURED 2026-09-06 on a scratch harness configure: same build dir after the venv appeared → still `python3.14`; a fresh build dir → `../.venv-harness/bin/python3`), so: `rm -rf build/ci-macos` (an ignored directory — `.gitignore:1`; the `175211` worktree's cache holds the 3.14 fallback); then `b=0; cmake --preset ci-macos > "$EVID/configure-0.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP`; THE INTERPRETER PROOF: `g=0; k=$(grep -c -E '^BIVHARNESS_PYTHON:FILEPATH=.*/\.venv-harness/bin/python3$' build/ci-macos/CMakeCache.txt) || g=$?; [ "$g" -le 1 ] || STOP; [ "$k" -eq 1 ] || STOP` (VALIDATED 2026-09-06 on the two scratch caches: the venv-selected cache → k=1; the 3.14 cache → k=0 with g=1 → STOP); then `b=0; cmake --build --preset ci-macos > "$EVID/build-0.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP`; `t=0; ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovers CLAUDE_CONFIG_DIR as an env-tier store" > "$EVID/existing-discover-0.log" 2>&1 || t=$?; [ "$t" -eq 0 ] || STOP` (the existing case, "env exists / default absent", unchanged by this act). Record the three fenced files' sha256 at the base: `shasum -a 256 src/adapters/claude_code/claude_code.cpp src/adapters/codex/codex.cpp tests/test_adapter_claude_collect.cpp > "$EVID/base-hashes.txt"; [ -s "$EVID/base-hashes.txt" ] || STOP` (codex's must be IDENTICAL at C, Task 5).
- [ ] **Step 5: the R-OBS observer environment — DERIVED NOW, before any suite run (F2); ONE execution under this revision's token** (the `175211` execution under `intg-r450-discover-parity-impl` — rc1=8 rc2=8 with the 3.14 fallback interpreter — is CONSUMED and cited, not re-run; a red arm 2 here again = FINDING UP with the logs, never a second run) — exactly the count-gate plan's Task 1 Step 3(a) and (c) (R-OBS-1..3, RULED `012332`): (a) `(cd harness && python3 -c 'from bivharness.e3 import CREDENTIAL_ENV_NAMES as n; print("\n".join(n))') > "$EVID/observer-unset-names.txt"; [ -s "$EVID/observer-unset-names.txt" ] || STOP` (derived from `e3.py` at this head, never typed; cross-check `e3.py:33-37` by eye and record the line range); host presence BY NAME ONLY: `while read -r n; do if printenv "$n" > /dev/null; then echo "$n present"; else echo "$n absent"; fi; done < "$EVID/observer-unset-names.txt" > "$EVID/observer-host-presence.txt"; [ -s "$EVID/observer-host-presence.txt" ] || STOP` (values never printed); the ONE environment: `OBS_ENV=(env); while read -r n; do OBS_ENV+=(-u "$n"); done < "$EVID/observer-unset-names.txt"` — every ctest and every `-r xml` run in Tasks 1, 2, 4 executes as `"${OBS_ENV[@]}" <command>`; (c) R-OBS-3 the discriminator EXECUTED at this head: arm 1 AS-IS (ambient, the control): `rc1=0; ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/discriminator-as-is.log" 2>&1 || rc1=$?`; arm 2 under the environment: `rc2=0; "${OBS_ENV[@]}" ctest --preset ci-macos -R '^harness-selftest$' > "$EVID/discriminator-unset.log" 2>&1 || rc2=$?`; `g=0; present_count=$(grep -c present "$EVID/observer-host-presence.txt") || g=$?; [ "$g" -le 1 ] || STOP`; the PREDICATE recorded as data: `rc2 == 0` (else FINDING, STOP UP — hygiene did not explain the red) AND (`rc1 != 0` iff `present_count > 0`) (else FINDING, STOP UP — the classification did not reproduce); `printf 'rc1=%s rc2=%s present_count=%s iff=%s hygiene=%s\n' … > "$EVID/discriminator-predicate.txt"`; both PASS is the gate to continue. (The reviewer's seat measured 2026-09-06: one name present, arm 1 rc 8 / 119 failures, arm 2 rc 0 / 1014 passed — the ambient run is NEVER the acceptance run.)

### Task 1 — the witness first (RED, fail-closed), then the discover body (GREEN under the observer environment)

**Files:** Modify `tests/test_adapter_claude_collect.cpp` (append after :116); Modify `src/adapters/claude_code/claude_code.cpp:570-596`.

**Interfaces:** consumes `biv::adapters::Env{getenv, home}`, `Store{root, locators, tier, archived}`, `DiscoveryTier{env, defaults, …}` (`src/adapters/adapter.hpp:23-49`); `biv::adapters::claude_code_adapter()` / `biv::adapters::codex_adapter()`; `biv::pack::pack(const fs::path&) -> expected<PackReport>` (`src/core/pack/pack.hpp:59`), `BivError{kind, path, detail}` (`src/core/support/error.hpp:40-46`, namespace `biv`), `ErrKind::ArchiveWriteFailed`.

- [ ] **Step 1: add the test-local helpers** (inside the existing anonymous namespace, after `write_file`):

```cpp
// Test-local environment scope for ROW 5's in-process pack call (mirrors tests/test_pack.cpp's ScopedEnv).
class ScopedEnvVar {
 public:
  ScopedEnvVar(std::string name, std::optional<std::string> value) : name_{std::move(name)} {
    if (const char* old = std::getenv(name_.c_str()); old != nullptr) {
      old_value_ = std::string{old};
    }
    if (value.has_value()) {
      setenv(name_.c_str(), value->c_str(), 1);
    } else {
      unsetenv(name_.c_str());
    }
  }
  ~ScopedEnvVar() {
    if (old_value_.has_value()) {
      setenv(name_.c_str(), old_value_->c_str(), 1);
    } else {
      unsetenv(name_.c_str());
    }
  }
  ScopedEnvVar(const ScopedEnvVar&) = delete;
  ScopedEnvVar& operator=(const ScopedEnvVar&) = delete;
  ScopedEnvVar(ScopedEnvVar&&) = delete;
  ScopedEnvVar& operator=(ScopedEnvVar&&) = delete;

 private:
  std::string name_;
  std::optional<std::string> old_value_;
};

biv::adapters::Env discovery_env(const fs::path& home,
                                 std::optional<std::string> claude_value,
                                 std::optional<std::string> codex_value) {
  return biv::adapters::Env{
      .getenv = [claude_value, codex_value](const std::string_view name) -> std::optional<std::string> {
        if (name == "CLAUDE_CONFIG_DIR") {
          return claude_value;
        }
        if (name == "CODEX_HOME") {
          return codex_value;
        }
        return std::nullopt;
      },
      .home = home};
}

std::vector<biv::adapters::DiscoveryTier> tiers(const std::vector<biv::adapters::Store>& stores) {
  std::vector<biv::adapters::DiscoveryTier> out;
  for (const auto& store : stores) {
    out.push_back(store.tier);
  }
  return out;
}
```

Add `#include "adapters/codex/codex.hpp"`, `#include "core/pack/pack.hpp"`, `#include "core/support/error.hpp"` beside the existing includes.

- [ ] **Step 2: write the ONE new TEST_CASE** (rows 1–5 + parity as SECTIONs; appended after the existing discover case; the name carries NO comma — a comma is a Catch2 spec separator):

```cpp
TEST_CASE("Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)") {
  const auto& claude = biv::adapters::claude_code_adapter();
  const auto& codex = biv::adapters::codex_adapter();
  const auto root = make_tmp("discover-parity");
  const auto home = root / "home";
  fs::create_directories(home);
  const auto claude_default = home / ".claude";
  const auto codex_default = home / ".codex";
  const auto claude_env = root / "claude-env";
  const auto codex_env = root / "codex-env";

  SECTION("ROW 1: env set, exists, differs; default exists -> TWO stores, env first") {
    fs::create_directories(claude_env / "projects");
    fs::create_directories(claude_default / "projects");
    fs::create_directories(codex_env);
    fs::create_directories(codex_default);
    const auto env = discovery_env(home, claude_env.string(), codex_env.string());

    const auto stores = claude.discover(env);

    REQUIRE(stores.has_value());
    REQUIRE(stores->size() == 2);
    CHECK(stores->at(0).root == claude_env);
    CHECK(stores->at(0).tier == biv::adapters::DiscoveryTier::env);
    CHECK(stores->at(1).root == claude_default);
    CHECK(stores->at(1).tier == biv::adapters::DiscoveryTier::defaults);
    for (const auto& store : *stores) {
      REQUIRE(store.locators.size() == 1);
      CHECK(store.locators.front().kind == "sessions_root");
      CHECK(store.locators.front().path == store.root / "projects");
      CHECK_FALSE(store.archived);
    }
    // PARITY: the same matrix against codex yields the same set shape (env first, then defaults).
    const auto codex_stores = codex.discover(env);
    REQUIRE(codex_stores.has_value());
    CHECK(tiers(*codex_stores) == tiers(*stores));
    REQUIRE(codex_stores->size() == 2);
    CHECK(codex_stores->at(0).root == codex_env);
    CHECK(codex_stores->at(1).root == codex_default);
  }

  SECTION("ROW 2: env set and lexically equal to the default -> ONE store (env)") {
    fs::create_directories(claude_default / "projects");
    fs::create_directories(codex_default);
    // A collapsing spelling: "<home>/./.claude" normalizes to the default (the reference shape's
    // lexically_normal() guard); a trailing-slash spelling would NOT collapse — inherited, not tested here.
    const auto claude_spelling = (home / "." / ".claude").string();
    const auto codex_spelling = (home / "." / ".codex").string();
    const auto env = discovery_env(home, claude_spelling, codex_spelling);

    const auto stores = claude.discover(env);

    REQUIRE(stores.has_value());
    REQUIRE(stores->size() == 1);
    CHECK(stores->front().tier == biv::adapters::DiscoveryTier::env);
    CHECK(stores->front().root == fs::path{claude_spelling});
    const auto codex_stores = codex.discover(env);
    REQUIRE(codex_stores.has_value());
    CHECK(tiers(*codex_stores) == tiers(*stores));
    REQUIRE(codex_stores->size() == 1);
    CHECK(codex_stores->front().root == fs::path{codex_spelling});
  }

  SECTION("ROW 3: env unset, default exists -> ONE store (defaults)") {
    fs::create_directories(claude_default / "projects");
    fs::create_directories(codex_default);
    const auto env = discovery_env(home, std::nullopt, std::nullopt);

    const auto stores = claude.discover(env);

    REQUIRE(stores.has_value());
    REQUIRE(stores->size() == 1);
    CHECK(stores->front().root == claude_default);
    CHECK(stores->front().tier == biv::adapters::DiscoveryTier::defaults);
    const auto codex_stores = codex.discover(env);
    REQUIRE(codex_stores.has_value());
    CHECK(tiers(*codex_stores) == tiers(*stores));
  }

  SECTION("ROW 4: neither -> ZERO stores") {
    const auto env = discovery_env(home, std::nullopt, std::nullopt);

    const auto stores = claude.discover(env);

    REQUIRE(stores.has_value());
    CHECK(stores->empty());
    const auto codex_stores = codex.discover(env);
    REQUIRE(codex_stores.has_value());
    CHECK(codex_stores->empty());
  }

  SECTION("ROW 5 (pinned interim, NOT c1 §7 dedupe/provenance compliance): one session id in both stores -> pack refuses") {
    const auto source = root / "proj";
    fs::create_directories(source);
    write_file(source / "work.txt", "workspace");
    const std::string session_id = "aaaaaaaa-1111-4000-8000-000000000055";
    const std::string transcript = "{\"type\":\"user\",\"cwd\":\"" + source.generic_string() +
                                   "\",\"sessionId\":\"" + session_id + "\",\"version\":\"2.1.202\"}\n";
    write_file(claude_env / "projects" / "project" / (session_id + ".jsonl"), transcript);
    write_file(claude_default / "projects" / "project" / (session_id + ".jsonl"), transcript);
    // version 2.1.202 is at/above the claude minimum: a BELOW-minimum copy is OMITTED with a
    // SessionBelowMinimumOmitted warning (tests/test_pack.cpp:684-720) and would never reach the
    // duplicate-id gate — the fixture must be collectable for ROW 5 to prove anything.
    const ScopedEnvVar scoped_home{"HOME", home.string()};
    const ScopedEnvVar scoped_claude{"CLAUDE_CONFIG_DIR", claude_env.string()};
    const ScopedEnvVar scoped_codex{"CODEX_HOME", (root / "absent-codex").string()};
    const ScopedEnvVar scoped_sqlite{"CODEX_SQLITE_HOME", (root / "absent-sqlite").string()};

    const auto refused = biv::pack::pack(source);

    REQUIRE_FALSE(refused.has_value());
    CHECK(refused.error().kind == biv::ErrKind::ArchiveWriteFailed);
    CHECK(refused.error().detail == "adapter-session-invalid");

    // The discriminator: the SAME id in ONE store only packs, with exactly one claude session —
    // so the refusal above is driven by BOTH stores being discovered, not by a broken fixture.
    fs::remove(claude_default / "projects" / "project" / (session_id + ".jsonl"));
    const auto packed = biv::pack::pack(source);
    REQUIRE(packed.has_value());
    CHECK(std::ranges::count_if(packed->agent_sessions,
                                [](const auto& entry) { return entry.agent == "claude-code"; }) == 1);
  }

  fs::remove_all(root);
}
```

- [ ] **Step 3: run it RED at the base bytes — FAIL-CLOSED (F1)** — three separately proven stages, none masked: (i) the build: `b=0; cmake --build --preset ci-macos > "$EVID/red-build.log" 2>&1 || b=$?; printf 'red_build_rc=%s\n' "$b" > "$EVID/red-build.rc"; [ "$b" -eq 0 ] || STOP`; (ii) the run, status CAPTURED and REQUIRED NONZERO, `-w UnmatchedTestSpec` so an unmatched name is an explicit nonzero exit (VALIDATED 2026-09-06 on the built Catch2 v3.7.1 binary: a non-matching name → rc 3 with the flag, rc 2 without it, both printing "No test cases matched"; the existing discover case with the flag → rc 0; `NoTests` is NOT a recognised warning in this Catch2 — rc 1 "Unrecognised warning option" — caught by executing the written form): `t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)" -r xml > "$EVID/witness-red.xml" 2> "$EVID/witness-red.stderr" || t=$?; printf 'red_test_rc=%s\n' "$t" > "$EVID/witness-red.rc"; [ "$t" -ne 0 ] || STOP; [ -s "$EVID/witness-red.xml" ] || STOP`; (iii) the PARSE of the retained XML — ROW 1 and ROW 5 the ONLY red leaves, ROWS 2–4 green, all five present exactly once, the TestCase name exact: `p=0; python3 "$EVID/witness.py" "$EVID/witness-red.xml" red > "$EVID/witness-red.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/witness-red.verdict" ] || STOP`. EXPECTED CAUSES: ROW 1 fails at `stores->size() == 2` (today's early return yields 1); ROW 5 fails at `REQUIRE_FALSE(refused.has_value())` (today only the env store is collected, so pack succeeds). Any OTHER red leaf, a green ROW 1 or ROW 5, a missing leaf, or a parser exit ≠ 0 = STOP: a fixture/model defect is fixed in the TEST and Step 3 re-runs from (i); a product-behaviour cause outside the discover body → STOP UP (S-CP-4).

- [ ] **Step 4: the discover body — the reference shape** (replace `claude_code.cpp:570-596` exactly; everything before :570 and after :596 byte-identical):

```cpp
  expected<std::vector<Store>> discover(const Env& env) const override {
    std::vector<Store> stores;
    auto append_store = [&](const fs::path& root, DiscoveryTier tier) {
      stores.push_back(Store{.root = root,
                             .locators = {StoreLocator{.kind = "sessions_root", .path = root / "projects"}},
                             .tier = tier,
                             .archived = false});
    };
    std::error_code ec;
    std::optional<fs::path> env_root;
    if (env.getenv) {
      auto configured = env.getenv("CLAUDE_CONFIG_DIR");
      if (configured.has_value() && fs::exists(*configured, ec)) {
        env_root = fs::path{*configured};
        append_store(*env_root, DiscoveryTier::env);
      }
    }

    const auto root = env.home / ".claude";
    if (fs::exists(root, ec) &&
        (!env_root.has_value() || root.lexically_normal() != env_root->lexically_normal())) {
      append_store(root, DiscoveryTier::defaults);
    }
    return stores;
  }
```

(`<optional>` is already included at :7. The shape is `codex.cpp:1193-1206` minus codex's sqlite/archived locators — the ONLY differences a side-by-side read may show are the locator kind/path (`projects`) and the absence of the archived twin; anything else is V-CP-2.)

- [ ] **Step 5: GREEN — under the observer environment (F2)** — (i) `b=0; cmake --build --preset ci-macos > "$EVID/green-build.log" 2>&1 || b=$?; [ "$b" -eq 0 ] || STOP`; (ii) the new case, status captured and REQUIRED ZERO, XML parsed in green mode: `t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovery returns every store found: env and default both searched with codex parity (c1 §7)" -r xml > "$EVID/witness-green.xml" 2> "$EVID/witness-green.stderr" || t=$?; printf 'green_test_rc=%s\n' "$t" > "$EVID/witness-green.rc"; [ "$t" -eq 0 ] && [ -s "$EVID/witness-green.xml" ] || STOP; p=0; python3 "$EVID/witness.py" "$EVID/witness-green.xml" green > "$EVID/witness-green.verdict" || p=$?; [ "$p" -eq 0 ] || STOP`; (iii) the existing discover case: `t=0; "${OBS_ENV[@]}" ./build/ci-macos/biv_tests -w UnmatchedTestSpec "Claude adapter discovers CLAUDE_CONFIG_DIR as an env-tier store" > "$EVID/existing-discover-1.log" 2>&1 || t=$?; [ "$t" -eq 0 ] || STOP`; (iv) the FULL macOS suite exactly as the workflow does, UNDER THE ENVIRONMENT (acceptance criterion 4's first half): `r=0; "${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/ctest-macos-P.log" 2>&1 || r=$?; printf 'ctest_macos_P_rc=%s\n' "$r" > "$EVID/ctest-macos-P.rc"; [ "$r" -eq 0 ] || STOP` (a red here is a FINDING routed UP with the log — never a further `env -u`, never an exclusion; the ambient arm-1 run of Task 0 Step 5 is the control, not the acceptance run).
- [ ] **Step 6: fence self-check before the provisional commit (materialized, statuses kept — F4)** — `s=0; git status --porcelain > "$EVID/status-pre-P.txt" || s=$?; [ "$s" -eq 0 ] && [ -s "$EVID/status-pre-P.txt" ] || STOP`; the file must name EXACTLY ` M src/adapters/claude_code/claude_code.cpp` and ` M tests/test_adapter_claude_collect.cpp` (two lines; `build/` is ignored): `printf ' M src/adapters/claude_code/claude_code.cpp\n M tests/test_adapter_claude_collect.cpp\n' > "$EVID/status-pre-P.expected"; d=0; diff "$EVID/status-pre-P.expected" "$EVID/status-pre-P.txt" > "$EVID/status-pre-P.delta" || d=$?; [ "$d" -eq 0 ] || STOP` (1 = an unexpected path → V-CP-1/3/5 STOP; 2+ = diff error STOP). The hunk range: `r=0; git diff -U0 -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-P.diff" ] || STOP; g=0; grep -E '^@@' "$EVID/claude-P.diff" > "$EVID/claude-P.hunks" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/claude-P.hunks" ] || STOP` (at least one hunk MUST exist → `g` must be 0); `h=0; python3 "$EVID/hunks.py" "$EVID/claude-P.hunks" 570 596 > "$EVID/claude-P.hunks.verdict" || h=$?; [ "$h" -eq 0 ] || STOP`. Codex untouched: `r=0; git diff --numstat -- src/adapters/codex/ > "$EVID/codex-P.numstat" || r=$?; [ "$r" -eq 0 ] && [ ! -s "$EVID/codex-P.numstat" ] || STOP` (empty is the expected content, checked after the status).

- [ ] **Step 7: the PROVISIONAL commit P — BOUND here (CG-R7.7), no tag (F3)** — `git add src/adapters/claude_code/claude_code.cpp tests/test_adapter_claude_collect.cpp && git commit -q -F "$EVID/message-P.txt"` where `message-P.txt` = `adapters(claude): discover returns every store found (env + default), codex parity — PROVISIONAL, cells not yet transcribed` + a body naming the design pin and plan pin + the trailer line. `P=$(git rev-parse HEAD)`; `printf '%s\n' "$P" > "$EVID/P.txt"; [ -s "$EVID/P.txt" ] || STOP`; `e=0; git cat-file -e "${P}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP`; `printf '%s\n' "$(git rev-parse "${P}^{tree}")" > "$EVID/P.tree"`. P is retained by this recorded object id: the branch reflog holds it after the amend (`git reflog show intg/r450-discover-parity` lists it); every later use re-reads `$EVID/P.txt` and re-proves `git cat-file -e "${P}^{commit}"` first. NO tag, NO extra ref (VALIDATED 2026-09-06 in bash AND zsh: `git cat-file -e "${sha}^{commit}"` → 0 for a real commit, 128 for a bogus sha (any nonzero STOPs); no `:` modifier can fire in `"${P}^{commit}"`).

### Task 2 — observation at P on BOTH targets (the SOURCE of the literals; CG-R7.3/7.7, T-1)

**Files:** none modified. Execute `PL-intg-countgate-20260830.md` Task 1 Steps 3(d)–(g) and 4 (the PROVEN instrument — the five `-r xml` runs per target under `"${OBS_ENV[@]}"` (derived in Task 0 Step 5; NOT re-derived), the inverted-selection scout (e), the R-OBS-5 token scan (f) over the concatenated logs (`cat` stage status-proved, then the zero-match-aware `grep -c`), the run identity (g); the four-phase Linux container: Phase H / R / T / S at `git show 990ba3b:docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep1-20260827.md` Task 5 Step 3 :757-763 with R-OBS-6's in-container name-free proof) VERBATIM with these retargets ONLY: (a) the run head is `P` (`$(cat "$EVID/P.txt")`, `git cat-file -e "${P}^{commit}"` re-proved first), the working tree is the r450 worktree, and Phase T clones the BRANCH `intg/r450-discover-parity` from `/repo-ro` with the receipt `rev-parse HEAD == P`; (b) XMLs land in `$EVID/P/<binary>-<target>.xml` and tuples in `$EVID/P/tuples-<target>.txt` (each XML `[ -s ]`-checked; each sha256 recorded); (c) the ancestry proofs are `a=0; git merge-base --is-ancestor bbf297e36a38a1fab8c2675f945098a0633f9f8b "$P" || a=$?` (REQUIRE 0) and `a2=0; git merge-base --is-ancestor b065de1107161bb5df9543c09b50091365338c1c "$P" || a2=$?` (REQUIRE 0 — the count-gate repair is in the lineage), both recorded.

- [ ] **Step 1: macOS observation at P** — the five `-r xml` runs under `"${OBS_ENV[@]}"` (each `x=0; "${OBS_ENV[@]}" ./build/ci-macos/<binary> -r xml > "$EVID/P/<binary>-macos.xml" 2> "$EVID/P/<binary>-macos.stderr" || x=$?; printf '%s\n' "$x" > "$EVID/P/<binary>-macos.rc"; [ -s "$EVID/P/<binary>-macos.xml" ] || STOP` — the rc is DATA here: a binary with failures exits nonzero and its tuple still transcribes; a MISSING or empty XML is the STOP), then `u=0; python3 "$EVID/tuples.py" macos "$EVID"/P/biv_subprocess_tests-macos.xml "$EVID"/P/biv_repo_git_tests-macos.xml "$EVID"/P/biv_repo_engine_tests-macos.xml "$EVID"/P/biv_tests-macos.xml "$EVID"/P/biv_probe_tests-macos.xml > "$EVID/P/tuples-macos.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/P/tuples-macos.txt" ] || STOP` → `$EVID/P/tuples-macos.txt` (five lines `binary target successes failures expectedFailures skips xml_sha256` + one `expected_skips_observed macos n=… <names>` line); the per-SECTION green proof on the full-suite XML (acceptance criterion 2): `p=0; python3 "$EVID/witness.py" "$EVID/P/biv_tests-macos.xml" green > "$EVID/P/witness-green-macos.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/P/witness-green-macos.verdict" ] || STOP` (the helper selects the named case inside the full run — VALIDATED 2026-09-06 on a synthetic full-suite XML with other cases present → 0); REQUIRE the `biv_tests` skipped-name set == B's `expected_skips` names for macOS from `$EVID/B-cells.txt` (a difference = the V-CG-5 routed FINDING, STOP UP — never an edit). The scout (e) and token scan (f) as in the countgate plan (both under `"${OBS_ENV[@]}"`, statuses captured, `hits=0` REQUIRED).

- [ ] **Step 2: Linux observation at P** — the four-phase container (ubuntu:24.04 `--platform linux/amd64` `--init`; `nofile` soft raised to hard inside the runuser drop; R-OBS-6 name-free proof by name inside the container before the measurement stage; `cmake --preset ci` + build + the five `-r xml` runs + the workflow-equivalent `ctest --preset ci` run, each stage's rc in the ledger), XMLs + per-stage rc ledger copied out to `$EVID/P/`, then the same `tuples.py linux` invocation over the five copied-out XMLs with `u=0; … || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/P/tuples-linux.txt" ] || STOP` → `$EVID/P/tuples-linux.txt`; the per-SECTION green proof on the copied-out Linux XML: `p=0; python3 "$EVID/witness.py" "$EVID/P/biv_tests-linux.xml" green > "$EVID/P/witness-green-linux.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/P/witness-green-linux.verdict" ] || STOP`; REQUIRE the Linux `biv_tests` observed skip COUNT == B's Linux `skips` cell (1) — the Linux job has no `expected_skips` identity block; the observed skipped NAME(s) are recorded in the tuples file and the report (a count difference = FINDING, STOP UP).
- [ ] **Step 3: ENTRY + the consistency CHECK (CG-R7.1/7.3, T-4) — observed trigger, syntactic predictor** — (i) ENTRY: compare P's `biv_tests` tuples (both targets) with B's cells from `$EVID/B-cells.txt`: a DIFFERENCE in `successes` on both targets = census-changing act → Task 3 transcribes; EQUAL on either target = zero-delta on that target, which contradicts the predictor → FINDING, STOP UP (no transcription, no commit); `failures` and `expectedFailures` MUST be 0 and `skips` MUST equal B's on both targets; the other four binaries' tuples MUST equal B's cells (any difference = FINDING, STOP UP). (ii) the PREDICTOR, materialized: `r=0; git diff bbf297e36a38a1fab8c2675f945098a0633f9f8b "$P" -- tests > "$EVID/tests-P.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/tests-P.diff" ] || STOP; g=0; added=$(grep -c '^+TEST_CASE(' "$EVID/tests-P.diff") || g=$?; [ "$g" -le 1 ] || STOP; g2=0; removed=$(grep -c '^-TEST_CASE(' "$EVID/tests-P.diff") || g2=$?; [ "$g2" -le 1 ] || STOP; printf 'added=%s removed=%s\n' "$added" "$removed" > "$EVID/predictor.txt"` (zero matches exit 1 = VALID; 2+ = STOP); REQUIRE `added=1 removed=0`; (iii) the check: `observed_P(successes) − old_B(successes)` per target must equal `added − removed` = 1 — a CHECK on the record, never a source (the literal written in Task 3 is the XML value); any mismatch in either direction = FINDING routed UP (never a quiet re-observation, never an exclusion). Write `$EVID/bpc-table.txt` NOW with the old(B)/observed(P) columns (new(C) filled at Task 3 Step 3), values copied from `B-cells.txt` and `tuples-*.txt`.
- [ ] **Step 4: no-mutation proof** — `s=0; git status --porcelain > "$EVID/status-post-P-obs.txt" || s=$?; [ "$s" -eq 0 ] && [ ! -s "$EVID/status-post-P-obs.txt" ] || STOP` (the worktree is EMPTY after observation; the evidence lives under `$EVID`; build dirs are ignored); main-repo status vs `status-initial.txt`: `s=0; git -C /Users/jack/Programming/bivpak status --porcelain > "$EVID/status-main-post-P.txt" || s=$?; [ "$s" -eq 0 ] || STOP; d=0; diff "$EVID/status-initial.txt" "$EVID/status-main-post-P.txt" > "$EVID/status-main-post-P.delta" || d=$?; [ "$d" -eq 0 ] || STOP`.

### Task 3 — transcribe the two literals FROM THE XML and amend P → C (one commit; C BOUND here)

**Files:** Modify `.github/workflows/s2-harness.yml:85` and `:326` (integer literals only).

- [ ] **Step 1: the transcription script — reads the XML, writes the literal, refuses anything else** (VALIDATED 2026-09-06 at the pair Planner's seat on a scratch copy of the workflow with two synthetic XMLs: correct block lines → the two literals replaced, all other bytes identical; a wrong anchor line → exit 3 with no write; a missing `OverallResultsCases` → exit 2 with no write):


Run: `x=0; python3 "$EVID/transcribe.py" .github/workflows/s2-harness.yml "$EVID/P/biv_tests-macos.xml" "$EVID/P/biv_tests-linux.xml" > "$EVID/transcribe.out" || x=$?; [ "$x" -eq 0 ] || STOP`.
- [ ] **Step 2: prove the workflow hunk is EXACTLY the two literals (CG-R7.4 (α); materialized — F4)** — `r=0; git diff --numstat -- .github/workflows/s2-harness.yml > "$EVID/workflow.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/workflow.numstat" ] || STOP; printf '2\t2\t.github/workflows/s2-harness.yml\n' > "$EVID/workflow.numstat.expected"; d=0; diff "$EVID/workflow.numstat.expected" "$EVID/workflow.numstat" > "$EVID/workflow.numstat.delta" || d=$?; [ "$d" -eq 0 ] || STOP`; `r=0; git diff -U0 -- .github/workflows/s2-harness.yml > "$EVID/workflow.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/workflow.diff" ] || STOP; g=0; grep -E '^[-+][^-+]' "$EVID/workflow.diff" > "$EVID/workflow-hunk.txt" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/workflow-hunk.txt" ] || STOP` (changed lines MUST exist → `g` 0); `a=0; n=$(awk 'END { print NR }' "$EVID/workflow-hunk.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 4 ] || STOP` (a single-stage line count with its own status — no pipeline; VALIDATED 2026-09-06 in bash AND zsh: 4-line file → n=4 a=0; missing file → a=2); `g=0; m=$(grep -c -E '^[-+][[:space:]]+"successes": [0-9]+,$' "$EVID/workflow-hunk.txt") || g=$?; [ "$g" -le 1 ] || STOP; [ "$m" -eq 4 ] || STOP` (all four changed lines are `successes` literals); the status names ONLY the workflow: `s=0; git status --porcelain > "$EVID/status-pre-C.txt" || s=$?; [ "$s" -eq 0 ] || STOP; printf ' M .github/workflows/s2-harness.yml\n' > "$EVID/status-pre-C.expected"; d=0; diff "$EVID/status-pre-C.expected" "$EVID/status-pre-C.txt" > "$EVID/status-pre-C.delta" || d=$?; [ "$d" -eq 0 ] || STOP`. Anything else = STOP to m-3.planner (through the pair Planner). (VALIDATED 2026-09-06 in bash AND zsh on the scratch transcription: numstat `2 2`, hunk 4 lines, `m=4`.)
- [ ] **Step 3: the ONE commit C = amend P; C BOUND here** — `git add .github/workflows/s2-harness.yml && git commit -q --amend -F "$EVID/message-C.txt"`. `message-C.txt`: subject `adapters(claude): discover returns every store found (env + default), codex parity; count-gate cells transcribed`; body: `Design pin: m2-r450-discover-fence-rev2-20260903 sha256 f2216ee606a03b0b5b0b7f4562fed52a7349219c28990e6ee3e89b0cc25e8c6f`; `Plan pin: intg-r450-discover-parity-plan-20260906 sha256 <this artifact's approved hash>`; `B=bbf297e36a38a1fab8c2675f945098a0633f9f8b (baseline; workflow values inherited) observed_head=P=<sha from P.txt> (provisional; source of the literals; reachable by object id / branch reflog; no tag) — C is this commit (its own sha cannot appear here; the tracked report binds it)`; `Observed cells at P (no arithmetic):` then the TEN `binary=… target=… run_id=… successes=… failures=… expectedFailures=… skips=… xml_sha256=…` lines from `$EVID/P/tuples-*.txt` exactly in `b065de1`'s form; the old(B)/observed(P) table from `bpc-table.txt`; the macOS and Linux run-identity + observer blocks (names only); the trailer `Co-Authored-By: Claude Fable 5.1 <noreply@anthropic.com>`. Then: `C=$(git rev-parse HEAD)`; `printf '%s\n' "$C" > "$EVID/C.txt"; [ -s "$EVID/C.txt" ] || STOP`; fill the new(C) column of `$EVID/bpc-table.txt` from the literals READ BACK from the committed workflow (`git show "${C}:.github/workflows/s2-harness.yml" > "$EVID/C-workflow.yml"` status-checked, then `c=0; python3 "$EVID/cells.py" "$EVID/C-workflow.yml" > "$EVID/C-cells.txt" || c=$?; [ "$c" -eq 0 ] && [ -s "$EVID/C-cells.txt" ] || STOP`).
- [ ] **Step 4: prove P → C (materialized; the `:(exclude)` pathspec VALIDATED 2026-09-06 in bash AND zsh on real commits: a workflow-only commit → rc 0; a product merge → rc 1)** — `P=$(cat "$EVID/P.txt"); C=$(cat "$EVID/C.txt"); e=0; git cat-file -e "${P}^{commit}" || e=$?; [ "$e" -eq 0 ] || STOP`; `r=0; git diff --numstat "$P" "$C" > "$EVID/p-to-c.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/p-to-c.numstat" ] || STOP; d=0; diff "$EVID/workflow.numstat.expected" "$EVID/p-to-c.numstat" > "$EVID/p-to-c.numstat.delta" || d=$?; [ "$d" -eq 0 ] || STOP`; `q=0; git diff --quiet "$P" "$C" -- . ':(exclude).github/workflows/s2-harness.yml' || q=$?; [ "$q" -eq 0 ] || STOP` (1 = a non-workflow byte moved between P and C; 2+ = error; both STOP); `[ "$(git rev-parse "${C}^")" = bbf297e36a38a1fab8c2675f945098a0633f9f8b ] || STOP`; `c=0; n=$(git rev-list --count "origin/main..${C}^") || c=$?; [ "$c" -eq 0 ] && [ "$n" -eq 0 ] || STOP` (the cut-point measure). Record all in `$EVID/p-to-c-proof.txt`.

### Task 4 — RE-OBSERVATION OF RECORD at C, both targets (the runs the tracked report and IMPL return carry)

- [ ] **Step 1:** repeat Task 2 Steps 1–2 with the run head `C` (`$(cat "$EVID/C.txt")`; `git cat-file -e "${C}^{commit}"` proved) → `$EVID/C/…` (ten tuples via the two status-captured `tuples.py` invocations exactly as Task 2, XML sha256, run identities, R-OBS discriminator arms re-run (R-OBS-3 at the resumed head) + token scan, in-container name-free proof, and the two per-SECTION green proofs `p=0; python3 "$EVID/witness.py" "$EVID/C/biv_tests-macos.xml" green > "$EVID/C/witness-green-macos.verdict" || p=$?; [ "$p" -eq 0 ] && [ -s "$EVID/C/witness-green-macos.verdict" ] || STOP` and the same for `$EVID/C/biv_tests-linux.xml` → `$EVID/C/witness-green-linux.verdict`) PLUS the workflow-equivalent full macOS suite under the environment at C (acceptance criterion 4's second half): `r=0; "${OBS_ENV[@]}" ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure > "$EVID/C/ctest-macos-C.log" 2>&1 || r=$?; printf 'ctest_macos_C_rc=%s\n' "$r" > "$EVID/C/ctest-macos-C.rc"; [ "$r" -eq 0 ] || STOP`; the Linux leg's `ctest --preset ci` stage rc 0 in the ledger.
- [ ] **Step 2: the gate's own semantics, locally (CG-R7.7: C's observations == P's observations == C's literals)** — `q=0; python3 "$EVID/gate.py" "$EVID/C-cells.txt" "$EVID/P/tuples-macos.txt" "$EVID/P/tuples-linux.txt" "$EVID/C/tuples-macos.txt" "$EVID/C/tuples-linux.txt" > "$EVID/C/gate-equality.txt" || q=$?; printf 'gate_rc=%s\n' "$q" > "$EVID/C/gate.rc"; [ "$q" -eq 0 ] && [ -s "$EVID/C/gate-equality.txt" ] || STOP` (the STATUS is the gate — an `equal=no` run prints ten lines and exits 5: VALIDATED 2026-09-06, the altered-C mutant → q=5, output non-empty, STOP reached): for each of the ten cells one line `binary target literal_C observed_P observed_C equal=yes|no`; ANY `no` = FINDING, STOP UP (no re-transcription, no amend — the plan returns to the pair Planner); the `biv_tests` skipped-name set at C == B's macOS `expected_skips` names, and the Linux skip count == B's Linux `skips` cell.

- [ ] **Step 3: no-mutation proof** as Task 2 Step 4 (files `status-post-C-obs.txt`, `status-main-post-C.*`).

### Task 5 — fence proofs at C, census of record at the branch head, IMPL return (no push yet)

- [ ] **Step 1: the touched set (materialized)** — `C=$(cat "$EVID/C.txt")`; `r=0; git diff --numstat bbf297e36a38a1fab8c2675f945098a0633f9f8b "$C" > "$EVID/touched.numstat" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/touched.numstat" ] || STOP`; the path column must be EXACTLY the three paths: `s=0; awk '{print $3}' "$EVID/touched.numstat" > "$EVID/touched.paths" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort "$EVID/touched.paths" > "$EVID/touched.paths.sorted" || o=$?; [ "$o" -eq 0 ] || STOP; printf '.github/workflows/s2-harness.yml\nsrc/adapters/claude_code/claude_code.cpp\ntests/test_adapter_claude_collect.cpp\n' > "$EVID/touched.expected"; d=0; diff "$EVID/touched.expected" "$EVID/touched.paths.sorted" > "$EVID/touched.delta" || d=$?; [ "$d" -eq 0 ] || STOP` (the workflow row must read `2 2`). Codex byte-identical (V-CP-3): `h=0; git show "${C}:src/adapters/codex/codex.cpp" > "$EVID/codex-C.cpp" || h=$?; [ "$h" -eq 0 ] && [ -s "$EVID/codex-C.cpp" ] || STOP`; its sha256 == the codex line of `$EVID/base-hashes.txt`. No `harness/` path in `touched.paths` (V-CP-5 — implied by the exact three-path equality). The claude hunk range at C: `r=0; git diff -U0 bbf297e36a38a1fab8c2675f945098a0633f9f8b "$C" -- src/adapters/claude_code/claude_code.cpp > "$EVID/claude-C.diff" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/claude-C.diff" ] || STOP; g=0; grep -E '^@@' "$EVID/claude-C.diff" > "$EVID/claude-C.hunks" || g=$?; [ "$g" -eq 0 ] && [ -s "$EVID/claude-C.hunks" ] || STOP; h=0; python3 "$EVID/hunks.py" "$EVID/claude-C.hunks" 570 596 > "$EVID/claude-C.hunks.verdict" || h=$?; [ "$h" -eq 0 ] || STOP` (V-CP-1). No collect byte (V-CP-4): `g=0; k=$(grep -c 'collect(' "$EVID/claude-C.diff") || g=$?; [ "$g" -le 1 ] || STOP; [ "$k" -eq 0 ] || STOP` (zero matches exits 1 = the EXPECTED state; 2+ = STOP).
- [ ] **Step 2: the census of record at the branch head, BOTH arms (082012 Answer (1) alternation; expectations WRITTEN FIRST; every producer materialized — F4)** — expectations: `printf '%s\n' 'tests/test_adapter_codex_collect.cpp:383' 'tests/test_adapter_codex_collect.cpp:385' 'tests/test_cli.cpp:1188' > "$EVID/census-expected-tree.txt"` (the three `sk-complete` fixture-filename false positives of the first-push receipt — line numbers RE-VERIFIED at `bbf297e` 2026-09-06) and `printf '%s\n' 'tests/test_adapter_codex_collect.cpp' 'tests/test_cli.cpp' > "$EVID/census-expected-history.txt"`. Tree arm: `r=0; git grep -n -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' "$C" -- . > "$EVID/census-tree-raw.txt" || r=$?; [ "$r" -le 1 ] || STOP` (`git grep` exits 1 on zero matches — data; 2+ = STOP); `s=0; sed -E 's/^[0-9a-f]{40}://; s/:.*$//' "$EVID/census-tree-raw.txt" > "$EVID/census-tree-paths-lines.tmp" || s=$?; [ "$s" -eq 0 ] || STOP` — NOTE: the FIRST substitution strips the sha prefix and the SECOND keeps `path:line` only by stripping from the line number's colon onward; the exact form is `sed -E 's/^[0-9a-f]{40}://' "$EVID/census-tree-raw.txt" > "$EVID/census-tree-stripped.txt"` then `sed -E 's/^([^:]+:[0-9]+):.*$/\1/' "$EVID/census-tree-stripped.txt" > "$EVID/census-tree.txt"`, each with its own `s=0; … || s=$?; [ "$s" -eq 0 ] || STOP` (paths + line numbers ONLY — no matched text is retained; NO value is printed or recorded at any step); `d=0; diff "$EVID/census-expected-tree.txt" "$EVID/census-tree.txt" > "$EVID/census-tree.delta" || d=$?; [ "$d" -eq 0 ] || STOP`. History arm: `r=0; git rev-list "$C" > "$EVID/rl.txt" || r=$?; [ "$r" -eq 0 ] && [ -s "$EVID/rl.txt" ] || STOP`; `x=0; xargs git grep -l -E 'sk-[A-Za-z0-9]{8,}|-----BEGIN [A-Z ]*PRIVATE KEY|AKIA[0-9A-Z]{16}|ghp_[A-Za-z0-9]{20,}|xox[abprs]-' < "$EVID/rl.txt" > "$EVID/census-history-raw.txt" || x=$?; [ "$x" -le 1 ] || STOP` (`/usr/bin/xargs` on macOS exits 0 when every batch matched and 1 when some batch had no match — both DATA, VALIDATED 2026-09-06 in bash AND zsh on a 3-commit range: matching alternation → 0, non-matching → 1; 2+ = STOP; `[ -s "$EVID/census-history-raw.txt" ] || STOP`); `s=0; sed -E 's/^[0-9a-f]{40}://' "$EVID/census-history-raw.txt" > "$EVID/census-history-paths.txt" || s=$?; [ "$s" -eq 0 ] || STOP; o=0; sort -u "$EVID/census-history-paths.txt" > "$EVID/census-history.txt" || o=$?; [ "$o" -eq 0 ] && [ -s "$EVID/census-history.txt" ] || STOP; d=0; diff "$EVID/census-expected-history.txt" "$EVID/census-history.txt" > "$EVID/census-history.delta" || d=$?; [ "$d" -eq 0 ] || STOP`. ANY new line or path (`d` 1) = STOP UP, never a judgement call; `d` 2+ = a diff error, STOP. (The whole two-arm form VALIDATED 2026-09-06 at the pair Planner's seat AT `bbf297e` — the must-be-YES case: tree arm = exactly the three expected lines; history arm = exactly the two expected paths; both deltas empty.)
- [ ] **Step 3: the IMPL return relay** (PHASE IMPL, report-only body, TO intg.pair-planner) carries: B, P (with `git cat-file -e "${P}^{commit}"` rc), C, the three-path numstat, the hunk-range verdicts, codex sha equality, the ten C tuples + ten P tuples (+ XML sha256 + run ids) and the old(B)/observed(P)/new(C) table, the two run-identity/observer blocks (names only), the discriminator predicates (Task 0 and Task 4), token-scan hits=0, gate-equality all `yes`, the RED parse verdict (ROW 1 + ROW 5 red, ROWS 2–4 green) and the GREEN parse verdict, the census deltas (both empty), `status-post-C-obs.txt` empty, the two `ctest-macos-*.rc` = 0, the Linux ledgers. NO push, NO PR yet — those are Task 6 after both owner reviews return through master.

### Task 6 — the vehicle (after the pair Planner's verification + m-2's fenced review + m-3's hunk review return through master with no red): push the branch, open the PR

- [ ] **Step 1: pre-push gate (the first-push discipline, retargeted to ONE remote BRANCH ref)** — `C=$(cat "$EVID/C.txt")`; `[ "$(git rev-parse HEAD)" = "$C" ] || STOP`; `u=0; git remote get-url --push --all origin > "$EVID/push-url.txt" || u=$?; [ "$u" -eq 0 ] && [ -s "$EVID/push-url.txt" ] || STOP; a=0; n=$(awk 'END { print NR }' "$EVID/push-url.txt") || a=$?; [ "$a" -eq 0 ] && [ "$n" -eq 1 ] || STOP`; `l=0; git ls-remote --heads origin intg/r450-discover-parity > "$EVID/remote-branch-before.txt" || l=$?; [ "$l" -eq 0 ] && [ ! -s "$EVID/remote-branch-before.txt" ] || STOP` (the ref must not pre-exist; non-empty = STOP UP); `v=0; gh repo view --json visibility -q .visibility > "$EVID/visibility.txt" || v=$?; [ "$v" -eq 0 ] && [ "$(cat "$EVID/visibility.txt")" = PRIVATE ] || STOP`; `[ ! -x "$(git rev-parse --git-path hooks/pre-push)" ] || STOP`; the census (Task 5 Step 2) re-asserted at C (the same files, both deltas empty); shell recorded (`printf '%s %s\n' "$0" "${ZSH_VERSION:-${BASH_VERSION:-unknown}}" > "$EVID/shell.txt"`).
- [ ] **Step 2: dry-run, then the push — LITERAL names, no refspec variable** — `y=0; git push --dry-run --no-tags origin intg/r450-discover-parity > "$EVID/push-dry.txt" 2>&1 || y=$?; [ "$y" -eq 0 ] || STOP`; the output must name `[new branch]      intg/r450-discover-parity -> intg/r450-discover-parity` (`g=0; k=$(grep -c -F 'intg/r450-discover-parity -> intg/r450-discover-parity' "$EVID/push-dry.txt") || g=$?; [ "$g" -eq 0 ] && [ "$k" -eq 1 ] || STOP`); then THE VERY NEXT COMMAND: `p=0; git push --no-tags origin intg/r450-discover-parity > "$EVID/push-stdout.txt" 2> "$EVID/push-stderr.txt" || p=$?; printf 'push_rc=%s\n' "$p" > "$EVID/push-rc.txt"`; outcome probe ALWAYS: `o=0; git ls-remote --heads origin intg/r450-discover-parity > "$EVID/remote-branch-after.txt" || o=$?; remote_after=$(cut -f1 "$EVID/remote-branch-after.txt")`; `if [ "$o" -ne 0 ]; then class=d; elif [ "$p" -eq 0 ] && [ "$remote_after" = "$C" ]; then class=a; elif [ "$p" -eq 0 ]; then class=e; elif [ "$remote_after" = "$C" ]; then class=c; elif [ -z "$remote_after" ]; then class=b; else class=e; fi; printf 'class=%s\n' "$class" > "$EVID/push-class.txt"`; ONE attempt per token, nothing retried in-lane; class ≠ a = STOP UP with the files.
- [ ] **Step 3: the PR** — `gh pr create --base main --head intg/r450-discover-parity --title "adapters(claude): discover returns every store found (env + default), codex parity; count-gate cells transcribed" --body-file "$EVID/pr-body.md" > "$EVID/pr.txt" 2>&1` (rc captured; REQUIRED 0; `[ -s "$EVID/pr.txt" ]`) where `pr-body.md` names: the design pin, the plan pin, B/P/C, the three-path numstat, the ten C tuples, the two owner-review relays, and the sentence "This PR is the vehicle under R-4.51 clause (2); the evidence of record is the local suites, the Docker parity leg, the owner byte reviews, and the operator's condition-4 token — a red remote CI is cited nowhere. Merge is local under the operator's token; the landing push of main follows the merge under the R-4.52 landing rule as the merge packet's own step." No label, no reviewer request, no auto-merge, no `gh pr ready`/draft toggling, no comment. (The route authorizes the PR as the vehicle; if `gh pr create` asks anything interactive → abort, STOP UP.)
- [ ] **Step 4: SITREP UP** with the push class, the PR URL, and the receipt files. This plan ENDS here. The MERGE-GATE packet (`results/intg-r450-discover-parity-merge-gate.md`, four conditions) follows from the pair Planner; the local merge (`git merge --no-ff` of C into lane-local `main`, §8-style receipt) happens ONLY under the operator's condition-4 token; the LANDING PUSH of `main` (R-4.52 rule: ONE fast-forward push, pinned sha, census at `main`'s head both arms against written expectations, dry-run, one attempt, class, receipt) is the merge packet's own step in the first-push shape — not this token's.

---

## Acceptance criteria (each measured, none inferred)

1. At C: `touched.paths.sorted` == the three expected paths; the workflow row `2 2` with the four changed lines all `"successes": <int>,`; `claude_code.cpp` hunks within :570-596 (`hunks.py` rc 0); codex.cpp sha unchanged; no harness/CMake/fixture/docs byte on the branch.
2. RED proven fail-closed at the base (build rc 0; test rc ≠ 0 under `-w UnmatchedTestSpec`; `witness.py red` rc 0: ROW 1 + ROW 5 red, ROWS 2–4 green; XML retained — Task 1 Step 3) and GREEN proven by `witness.py green` rc 0 with a non-empty verdict file at FIVE producing steps: the targeted macOS run at P (Task 1 Step 5), the full-suite `biv_tests` XML at P/macOS and P/Linux (Task 2 Steps 1–2), and at C/macOS and C/Linux (Task 4 Step 1); the existing discover case unchanged and green.
3. B/P/C bound in order with recorded identities (B before implementation; P before its observation; C before its observation); ten P tuples and ten C tuples observed under CG-R2 + R-OBS; ENTRY fired (P's `biv_tests` successes ≠ B's on both targets; every other cell equal; skips equal; the macOS skip set equal to B's names; the Linux skip count equal to B's cell); `gate.py` rc 0 (every cell: literal(C) == observed(P) == observed(C)); the P→C tree delta = the two literals; no arithmetic in any evidence.
4. The workflow-equivalent macOS ctest (`-E '^safety-hardening$'`) rc 0 under `"${OBS_ENV[@]}"` at P AND at C; the Linux parity leg reaches ctest with rc 0 at P and at C; the R-OBS discriminator predicate PASS/PASS at Task 0 and Task 4.
5. Census of record at C both arms == the written expectations (both deltas empty).
6. Cut-point `origin/main..C^` = 0; `C^` = `bbf297e…`; the branch pushed with class a; the PR open against `main`; at this plan's end `main` is NOT yet pushed (the landing push is the merge packet's step); no tag exists (local or remote); no release act.
7. m-2's fenced review (V-CP-1..6) and m-3's hunk review (CG-R7.5 a–f) both return through master with no red before the merge bar.

## Out of scope (an act here is a STOP, not a judgement)

Dedupe/provenance semantics (S-CP-5 HELD); any collect byte; any codex byte; any harness/stub/witness byte (S-CP-2 is m-3's at landing); any user-facing wording/warning/exit change (S-CP-3); any pack/open interaction beyond enumeration (S-CP-4); any workflow byte beyond the two (α) literals; `expected_skips`; CMake; fixtures under `tests/fixtures/`; the R-4.49 act; the merge, the landing push of `main` (the merge packet's step, not this token's); tags of any kind; release.

## Anti-half-fix guards

- The witness must have been RED first, fail-closed (Task 1 Step 3: build rc 0, test rc ≠ 0, `witness.py red` rc 0) — a green-only or unparsed witness is not a witness.
- ROW 5's discriminator (one store → pack succeeds with one session) must PASS in the same SECTION; a refusal without the passing control is not evidence of both-store discovery.
- The literals are written by the script from the XML; a hand-typed literal, or a literal equal to "old + 1" without an XML, is V-CG-2 red.
- B, P and C are bound at their steps and never rewritten (anti-retrospection); P and C both observed; equality proven by `gate.py`; P reachable by object id (no tag).
- No evidence-producing pipeline anywhere: every producer's status recorded, every input proven non-empty (or proven empty where empty is the claim).
- Every helper is written at Task 0 Step 0b and compiled before use; every helper INVOCATION captures its status — a helper's printed output is never the gate, its exit is.

## Revision history

- **rev1** `3931edab6a4b6f39c1d7fc60d4c29bbd8954f7ddc261a6dee9b76081a19f9bee` — FILED 2026-09-06 (`intg-r450-discover-parity-plan-1`, `010428`); MUST-REVISE by the implementer `065859` (F1 RED fail-open via `|| true`; F2 ambient macOS suite before the R-OBS correction; F3 ungranted local tag; F4 producer-masking pipelines). DEAD.
- **rev2** `9b889d045f46054c59fbe4502ede80e5d450fd4c83aee76fa8d2de7c65bd006f` — FILED 2026-09-06 (`intg-r450-discover-parity-plan-2`, `154309`); MUST-REVISE by the implementer `161925` (F1 five helpers invoked before creation; F2 `cells.py`/`gate.py` statuses uncaptured and two wc-to-tr line-count pipelines; F3 acceptance 2 promised green parses no step produced). DEAD.
- **rev3** `f1f95ee31c7b68e06a7acb38cc66b1f194a561164422a08df415dd22467b4054` — FILED 2026-09-06 (`intg-r450-discover-parity-plan-3`, `163706`); APPROVED `165625`; token `intg-r450-discover-parity-impl` `173252` CONSUMED at the implementer's Task 0 Step 5 STOP `175211` (rc2=8: the worktree's harness configured onto Homebrew Python 3.14.6 without jsonschema/zstandard — no `.venv-harness` in the isolated worktree). DEAD as the executing revision; its content stands.
- **rev4** — this artifact (`intg-r450-discover-parity-plan-4`): Task 0 Step 3b (the worktree's harness venv per CI's recipe into the ignored path, module proof, check-ignore proof), Step 4 into a fresh build dir with the CMakeCache interpreter proof, Step 2 resume checkpoint, Step 5 one-execution note; every new form executed from the WRITTEN bytes before filing.
- **rev3 (content)** — the three `161925` findings folded across the whole document (helpers materialized at Task 0 Step 0b; every helper status-captured; awk single-stage counts; five scheduled `witness.py green` proofs); helper bytes unchanged; every changed span executed from the WRITTEN bytes before filing.
