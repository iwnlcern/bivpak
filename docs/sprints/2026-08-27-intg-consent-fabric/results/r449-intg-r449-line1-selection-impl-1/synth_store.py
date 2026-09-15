#!/usr/bin/env python3
# synth_store.py <work> <seed> — builds the LARGE SYNTHETIC STORE pair S for LEG 1/2/3 (real-store SCALE, synthetic CONTENT), deterministic
# from <seed>, INSIDE <work> at locator values (m-3 C-2 rule 3): <work>/codex-home/sessions/2026/09/13/rollout-*.jsonl and
# <work>/claude-config/projects/<key>/<uuid>.jsonl. Exactly K of each agent carry cwd == <work>/ws/proj (the SELECTED set); every other file
# is out of the source root or carries no cwd. Ids are minted from the seed (never a POISON_SESSION_IDS value — proven by the runner, rule 1).
# CLASSES (per-file manifest row: path relative to <work>, agent, class, selected, size, head_end = byte offset just past the '\n' of the
# line that COMPLETES the head predicate — first cwd-bearing record (claude, A1 §A1) / first session_meta record (codex, c1 §4) — or null
# when no line completes it, i.e. the sealed whole-file case):
#   codex-bulk                 N_CODEX rollouts, line 1 = session_meta (+cwd); body BODY_CODEX bytes; K in root, the rest out of root
#   codex-garbage-line1        N_CODEX_GARBAGE out-of-root rollouts, line 1 unparseable, line 2 = session_meta        (head_end = end of line 2)
#   codex-no-meta              N_CODEX_NOMETA rollouts with NO session_meta anywhere                                   (head_end = null; not a candidate, silent — today's disposition)
#   claude-bulk                N_CLAUDE transcripts, lines 1-4 metadata without cwd, line 5 the first cwd-bearing record (the REAL shape,
#                              A1 FX-M06) with sessionId+version; body BODY_CLAUDE bytes; K in root, the rest out of root  (head_end = end of line 5)
#   claude-cwd-no-enrichment   N_CLAUDE_NOENRICH out-of-root transcripts whose FIRST cwd-bearing record (line 1) carries NO sessionId/version
#                              and whose body never carries them either — the implementer's O-1 counterexample: a reader that waits for the
#                              enrichment fields reads these to EOF; the first-cwd reader stops at line 1              (head_end = end of line 1)
#   claude-no-cwd              N_CLAUDE_NOCWD transcripts IN the source project directory with no cwd anywhere        (head_end = null; whole file, no_cwd_record — sealed)
# No credential-shaped string is ever written. S is NOT committed: it lives under $EVID/work, excluded from the evidence-of-record set.
import json, os, random, sys, uuid
N_CODEX, N_CODEX_GARBAGE, N_CODEX_NOMETA = 1500, 20, 10
N_CLAUDE, N_CLAUDE_NOENRICH, N_CLAUDE_NOCWD = 100, 10, 5
K = 3
BODY_CODEX, BODY_CLAUDE, BODY_NOCWD = 256 * 1024, 4 * 1024 * 1024, 1024 * 1024
def project_key(path):
    return "-" + path.strip("/").replace("/", "-")
def write_lines(path, head_lines, body_line, body_bytes, complete_index):
    """writes head_lines then body_line repeated to >= body_bytes; returns (size, head_end) where head_end is the offset just past head_lines[complete_index] (None if complete_index is None)"""
    os.makedirs(os.path.dirname(path), exist_ok=True)
    head_end = None
    with open(path, "w", encoding="utf-8") as f:
        off = 0
        for i, line in enumerate(head_lines):
            f.write(line); off += len(line.encode("utf-8"))
            if complete_index is not None and i == complete_index:
                head_end = off
        n = body_bytes // len(body_line.encode("utf-8")) + 1
        for _ in range(n):
            f.write(body_line)
    return os.path.getsize(path), head_end
def main(work, seed):
    rnd = random.Random(seed)
    def uid():
        return str(uuid.UUID(int=rnd.getrandbits(128), version=4))
    ws = os.path.join(work, "ws", "proj"); os.makedirs(ws, exist_ok=True)
    other = os.path.join(work, "elsewhere", "proj")
    rows = []; selected = {"codex": [], "claude": []}
    def row(path, agent, cls, sel, size, head_end):
        rows.append({"path": os.path.relpath(path, work), "agent": agent, "class": cls, "selected": sel, "size": size, "head_end": head_end})
    codex_dir = os.path.join(work, "codex-home", "sessions", "2026", "09", "13")
    def meta(sid, cwd, i):
        return json.dumps({"timestamp": "2026-09-13T00:%02d:%02dZ" % (i // 60 % 60, i % 60), "type": "session_meta",
                           "payload": {"id": sid, "session_id": sid, "cwd": cwd, "cli_version": "0.142.5"}}) + "\n"
    turn = json.dumps({"timestamp": "2026-09-13T00:00:00Z", "type": "response_item", "payload": {"type": "message", "role": "assistant", "content": [{"type": "output_text", "text": "x" * 1000}]}}) + "\n"
    for i in range(N_CODEX):
        sid = uid(); sel = i < K; cwd = ws if sel else other
        if sel: selected["codex"].append(sid)
        p = os.path.join(codex_dir, "rollout-2026-09-13T00-00-00-%s.jsonl" % sid)
        size, he = write_lines(p, [meta(sid, cwd, i)], turn, BODY_CODEX, 0); row(p, "codex", "codex-bulk", sel, size, he)
    for i in range(N_CODEX_GARBAGE):
        sid = uid(); p = os.path.join(codex_dir, "rollout-2026-09-13T00-01-00-%s.jsonl" % sid)
        size, he = write_lines(p, ["not json at all\n", meta(sid, other, i)], turn, BODY_CODEX, 1); row(p, "codex", "codex-garbage-line1", False, size, he)
    for i in range(N_CODEX_NOMETA):
        sid = uid(); p = os.path.join(codex_dir, "rollout-2026-09-13T00-02-00-%s.jsonl" % sid)
        size, he = write_lines(p, [], turn, BODY_CODEX, None); row(p, "codex", "codex-no-meta", False, size, he)
    proj = os.path.join(work, "claude-config", "projects", project_key(ws))
    oproj = os.path.join(work, "claude-config", "projects", project_key(other))
    def cl(obj):
        return json.dumps(obj) + "\n"
    body_full = cl({"type": "assistant", "cwd": other, "sessionId": "body", "uuid": "u", "parentUuid": "p", "message": {"role": "assistant", "content": [{"type": "text", "text": "y" * 1000}]}})
    body_bare = cl({"type": "assistant", "uuid": "u", "parentUuid": "p", "message": {"role": "assistant", "content": [{"type": "text", "text": "y" * 1000}]}})
    for i in range(N_CLAUDE):
        sid = uid(); sel = i < K; cwd = ws if sel else other; pdir = proj if sel else oproj
        if sel: selected["claude"].append(sid)
        head = [cl({"type": "last-prompt", "sessionId": sid, "lastPrompt": "p"}), cl({"type": "mode", "sessionId": sid, "mode": "default"}),
                cl({"type": "permission-mode", "sessionId": sid, "permissionMode": "default"}), cl({"type": "bridge-session", "sessionId": sid, "bridgeSessionId": uid()}),
                cl({"type": "user", "cwd": cwd, "sessionId": sid, "version": "2.1.202", "uuid": uid(), "parentUuid": None, "message": {"role": "user", "content": "hi"}})]
        body = cl({"type": "assistant", "cwd": cwd, "sessionId": sid, "uuid": "u", "parentUuid": "p", "message": {"role": "assistant", "content": [{"type": "text", "text": "y" * 1000}]}})
        p = os.path.join(pdir, sid + ".jsonl"); size, he = write_lines(p, head, body, BODY_CLAUDE, 4); row(p, "claude", "claude-bulk", sel, size, he)
    for i in range(N_CLAUDE_NOENRICH):
        sid = uid(); p = os.path.join(oproj, sid + ".jsonl")
        size, he = write_lines(p, [cl({"type": "user", "cwd": other, "uuid": uid(), "message": {"role": "user", "content": "hi"}})], body_bare, BODY_CLAUDE, 0)
        row(p, "claude", "claude-cwd-no-enrichment", False, size, he)
    for i in range(N_CLAUDE_NOCWD):
        sid = uid(); p = os.path.join(proj, sid + ".jsonl")
        size, he = write_lines(p, [cl({"type": "summary", "sessionId": sid, "version": "2.1.202", "summary": "s"})], body_bare, BODY_NOCWD, None)
        row(p, "claude", "claude-no-cwd", False, size, he)
    os.makedirs(os.path.join(work, "home"), exist_ok=True)
    counts = {}
    for r in rows: counts[r["class"]] = counts.get(r["class"], 0) + 1
    with open(os.path.join(work, "synth-manifest.json"), "w", encoding="utf-8") as f:
        json.dump({"seed": seed, "k": K, "counts": counts, "selected": selected, "ws": ws, "files": rows,
                   "total_bytes": sum(r["size"] for r in rows)}, f, indent=1, sort_keys=True)
    print("synth ok files=%d bytes=%d" % (len(rows), sum(r["size"] for r in rows)))
if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]))
