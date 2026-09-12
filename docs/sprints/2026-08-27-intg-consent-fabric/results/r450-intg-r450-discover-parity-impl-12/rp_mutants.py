import sys
from pathlib import Path
sys.path.insert(0, str(Path.cwd()))          # harness/
from bivharness import scenario
from bivharness.report import Status
biv, out = Path(sys.argv[1]), Path(sys.argv[2])
spec = Path("scenarios/store-isolation-witness.json")
original = scenario._run_json
for locator in ("HOME", "CODEX_HOME", "CODEX_SQLITE_HOME", "CLAUDE_CONFIG_DIR"):
    def mutated(biv_, args, cwd, env_overrides=None, _locator=locator):
        overrides = dict(env_overrides or {}); overrides.pop(_locator, None)   # the FINAL env loses exactly one locator
        return original(biv_, args, cwd, overrides)
    scenario._run_json = mutated
    result = scenario.run_scenario(spec, biv, out / f"mutant-{locator}")
    scenario._run_json = original
    leaks = [line for line in result.detail.splitlines() if line.startswith("isolation-leak ")]
    tags = {line.split()[1].rstrip(":") for line in leaks}
    print(f"MUTANT {locator}: status={result.status.value} leak_tags={sorted(tags)}")
    print(result.detail)
    assert result.status is Status.FAIL and tags == {locator}, (locator, result.status, tags, result.detail)
    if locator == "CODEX_SQLITE_HOME":   # rev5 binding (3): ONE warning OBJECT whose kind AND path are both exact
        poison_db = out / f"mutant-{locator}" / "store-isolation-witness.poison" / "codex-sqlite" / "state_5.sqlite"
        warning_lines = [l for l in leaks if " warnings[" in l]
        assert len(warning_lines) == 1 and warning_lines[0].endswith(f" kind=CodexDbEnrichmentSkipped path={poison_db}"), (warning_lines, result.detail)
        positive_missing = [l for l in result.detail.splitlines() if l.startswith("isolation-positive missing")]
        assert not positive_missing, positive_missing   # the staged codex session at its store root is what PUBLISHES the warning
print("ALL FOUR MUTANTS RED ON EXACTLY THEIR OWN LOCATOR")
