#!/usr/bin/env python3
# usage: pack_run.py <biv> <work> <label B|H> <outdir>  — LEG 3's producer on one side: runs `biv pack <work>/ws/proj --json` THREE times with the
# locator environment pinned to S (HOME=<work>/home, CODEX_HOME=<work>/codex-home, CLAUDE_CONFIG_DIR=<work>/claude-config, TMPDIR=<work>/tmp; every
# other variable of the caller's environment passed through — the caller unsets the credential names), removing the previous image before each run;
# records each run's wall time and exit status, keeps the LAST run's stdout as <outdir>/pack-<label>.json (stderr beside it), renames the last image
# to <work>/ws/proj-<label>.bvpk and writes <outdir>/time-<label>.txt (three times, the median, the statuses). Exit 0 iff every run returned 0 or 2
# (2 = warned; biv's documented conflation) with `"ok": true` in its JSON and the image exists; the three statuses must be equal.
import json, os, shutil, subprocess, sys, time
biv, work, label, outdir = sys.argv[1:5]
src = os.path.join(work, "ws", "proj"); image = os.path.join(work, "ws", "proj.bvpk")
env = dict(os.environ); env.update({"HOME": os.path.join(work, "home"), "CODEX_HOME": os.path.join(work, "codex-home"),
                                    "CLAUDE_CONFIG_DIR": os.path.join(work, "claude-config"), "TMPDIR": os.path.join(work, "tmp")})
os.makedirs(env["TMPDIR"], exist_ok=True); os.makedirs(outdir, exist_ok=True)
times, rcs, oks = [], [], []
for i in range(3):
    for stale in (image, image + ".partial", image + ".spool"):
        if os.path.exists(stale): os.remove(stale)
    t0 = time.monotonic(); r = subprocess.run([biv, "pack", src, "--json"], env=env, capture_output=True, text=True); t1 = time.monotonic()
    times.append(t1 - t0); rcs.append(r.returncode)
    try: oks.append(bool(json.loads(r.stdout).get("ok")))
    except Exception: oks.append(False)
    open(os.path.join(outdir, "pack-%s.json" % label), "w").write(r.stdout); open(os.path.join(outdir, "pack-%s.stderr" % label), "w").write(r.stderr)
final = os.path.join(work, "ws", "proj-%s.bvpk" % label)
if os.path.exists(image): shutil.move(image, final)
med = sorted(times)[1]
with open(os.path.join(outdir, "time-%s.txt" % label), "w") as f:
    f.write("label=%s runs=3 times_s=%.3f,%.3f,%.3f median_s=%.3f rcs=%s oks=%s image=%s\n" % (label, times[0], times[1], times[2], med, ",".join(map(str, rcs)), ",".join(map(str, oks)), final))
print(open(os.path.join(outdir, "time-%s.txt" % label)).read().strip())
sys.exit(0 if (all(rc in (0, 2) for rc in rcs) and len(set(rcs)) == 1 and all(oks) and os.path.exists(final)) else 1)
