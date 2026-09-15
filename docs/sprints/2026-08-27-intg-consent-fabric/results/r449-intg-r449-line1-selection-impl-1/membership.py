#!/usr/bin/env python3
# membership.py <image.bvpk> <out.json> — extracts manifest.json from a biv image (a zstd frame around a ustar/PAX tar) and writes the NORMALIZED
# selected set: per agent_sessions entry every membership-bearing field (agent, original_session_ids, original_path, normalized_path_key,
# normalization_scheme, path_flavor, artifacts, children, live_at_pack, agent_version_at_pack, provenance), sorted by (agent, ids) — LEG 3 compares
# WHOLE RECORDS, not only ids. Extraction: `tar --zstd -xOf` (GNU tar, Linux) first, then `tar -xOf` (macOS bsdtar reads zstd in-process).
import json, subprocess, sys
def extract(image):
    for cmd in (["tar", "--zstd", "-xOf", image, "manifest.json"], ["tar", "-xOf", image, "manifest.json"]):
        r = subprocess.run(cmd, capture_output=True)
        if r.returncode == 0 and r.stdout.strip():
            return r.stdout
    sys.exit(3)
def main(image, out):
    m = json.loads(extract(image))
    rows = sorted(m.get("agent_sessions", []), key=lambda e: (e.get("agent", ""), json.dumps(e.get("original_session_ids", {}), sort_keys=True)))
    keep = ("agent", "original_session_ids", "original_path", "normalized_path_key", "normalization_scheme", "path_flavor", "artifacts", "children", "live_at_pack", "agent_version_at_pack", "provenance")
    norm = [{k: e.get(k) for k in keep} for e in rows]
    with open(out, "w", encoding="utf-8") as f:
        json.dump({"count": len(norm), "sessions": norm}, f, indent=1, sort_keys=True)
    print("membership rows=%d" % len(norm))
if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
