import hashlib, subprocess, sys
P = 'docs/sprints/2026-08-27-intg-consent-fabric/plans/PL-intg-substep2b-20260915.md'
src = subprocess.run(['git', 'show', 'e8b3ab2:' + P], capture_output=True, check=True).stdout.decode('utf-8')
assert hashlib.sha256(src.encode()).hexdigest() == '096e47b457d88e9e9163e0c7e76dfe8ad2fb6c4c212b77b33421ce816d2e3708'
t = src
def rep(a, b, n=1):
    global t
    c = t.count(a); assert c == n, (c, a[:100]); t = t.replace(a, b)
# ---- MUST-2B-57: the gh repository is host-qualified, so GH_HOST cannot re-route either gh call
rep('URL=https://github.com/iwnlcern/bivpak.git; REPO=iwnlcern/bivpak\n',
    'URL=https://github.com/iwnlcern/bivpak.git; REPO=github.com/iwnlcern/bivpak   # rev44 (MUST-2B-57): HOST/OWNER/REPO, so GH_HOST cannot send either gh call (the visibility read, the draft PR) to another host\n')
# ---- prose
rep("`URL=https://github.com/iwnlcern/bivpak.git`, `REPO=iwnlcern/bivpak`;",
    "`URL=https://github.com/iwnlcern/bivpak.git`, `REPO=github.com/iwnlcern/bivpak` (rev44, MUST-2B-57: host-qualified, so `GH_HOST` cannot re-route `gh repo view` or `gh pr create`);")
rep("MUST-2B-56: Step 0 also preserves the prior attempt's finalize bytecode, the syntax check writes none, and the Step 0 boundary is stated as the body's first receipt.",
    "MUST-2B-56: Step 0 also preserves the prior attempt's finalize bytecode, the syntax check writes none, and the Step 0 boundary is stated as the body's first receipt. rev44 folds the implementer's exact-hash MUST-REVISE of rev43 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-162852.md`, MUST-2B-57): the `gh` repository is host-qualified (`github.com/iwnlcern/bivpak`), so `GH_HOST` cannot send the visibility read or the draft PR to a host other than the one the literal git URL pushes to.")
rep("18. (rev42; rev43) Task 10:", "18. (rev42; rev43; rev44) Task 10:")
rep("every remote read and write naming that URL or `iwnlcern/bivpak`;", "every remote read and write naming that URL or the host-qualified `github.com/iwnlcern/bivpak` (rev44);")
H44 = ("- rev44 (2026-09-27): folds the implementer's exact-hash MUST-REVISE of rev43 (`intg-substep2b/PLAN-REVIEW-pair-implementer-20260927-162852.md`, MUST-2B-57), Task 10 only. "
       "rev43 pinned the git URL but gave `gh` only `OWNER/REPO`, and `GH_HOST` supplies the host when none is given: the implementer's read-only control sent the unqualified visibility read to the injected host. "
       "Now `REPO=github.com/iwnlcern/bivpak`, used by both `gh repo view` and `gh pr create --repo`; the git URL and rewrite gates are unchanged. "
       "The Task 0 / Task 9 `gh release download --repo iwnlcern/bivpak` lines are in completed tasks' sealed blocks and do not move.\n")
rep("- rev43 (2026-09-27): folds the implementer's exact-hash MUST-REVISE of rev42", H44 + "- rev43 (2026-09-27): folds the implementer's exact-hash MUST-REVISE of rev42")
sys.stdout.write(t)
