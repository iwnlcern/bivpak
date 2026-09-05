# Count-gate repair — landing receipt at `b065de1`, re-verified at the pair-planner's seat

Act: the R-4.38 count-gate repair (m-3 design `m3-countgate-repair-20260830` rev1 @ sha256 `0099d1cf4aeb39f3732e823657ec0b78434f6a638db70b69a3fd6bd4dd717875`; pair plan `PL-intg-countgate-20260830.md` rev9 @ `652f0d73f6784ddf38757371bc1c1755454a8402b4f64c9f8a6276002f0a1e55`), executed by `intg.pair-implementer` under token `intg-countgate-impl-2` (`intg-countgate/IMPL-pair-planner-20260905-055031.md`), returned by `intg-countgate/IMPL-pair-implementer-20260905-071231.md`.
This receipt records what the pair-planner re-derived from the repository objects and the external evidence home on 2026-09-05, not what the report says.
Acceptance is NOT claimed here: m-3.planner's seven-point byte review at the landed sha (CG-R6.3 (i)–(vii)) is the gate ahead, routed via master.

## 1. Topology (git objects)

```text
main                      b065de1107161bb5df9543c09b50091365338c1c
parents                   e14f15fc4f72e428e0750e05a435991d0c814b30   (exactly one; = the token-issuance commit = the captured run head)
ancestors of b065de1      81066ef yes · 29acc6c yes · e14f15f yes
diff-tree --name-only -r  .github/workflows/s2-harness.yml            (exactly one path)
git show --check          clean
workflow blob sha256      1af1d1cb543f70269a90d975d277305bccf70855e77d6b9603fc09e1d07b11f9   (= the report's)
origin/main               0db8fdd8424d27aad2c547614e9ebb95621a2794   (unchanged; nothing pushed)
branches                  no new branch; tags 5 (unchanged)
lane status               only the daemon INDEX projection and the 071231 relay itself uncommitted; workflow path clean
```

## 2. The landed workflow bytes (diff e14f15f → b065de1, read in full)

- macOS job: the `-R '^(biv_tests|harness-selftest|harness-e2|errno_table_gate|generated_envelope_conforms)$'` include is GONE; the selection is `ctest --preset ci-macos -E '^safety-hardening$' --output-on-failure` (one explicit exclusion, a platform-instrument absence: `readelf unavailable`, observed in the scout log).
- Both jobs: five `-r xml` executions each (ten total), one `checks` dict per job with five per-binary exact-equality tuples; the `expected_skips` gate reads `roots["biv_tests"]`.
- `expected_skips` literal block: sha256 `c2e7761fa1e3acbc512aeab5daaaff3c1a84f4048c79d2c3481b5364bd02bc09` in BOTH the parent and the landed blob (5 lines; extracted from `expected_skips = {` to its closing brace at the same indent) — byte-identical, membership unchanged.
- No `env:`, `secrets.`, or `env -u` byte added: the only `env:` and the only remaining `ctest … -R harness-selftest` line are the harness job's pre-existing lines, identical in the parent.
- The Linux `nofile` comment is retained above the `checks` dict.

## 3. The ten want cells vs the observed tuples

| binary | macOS want (landed) | macOS observed | Linux want (landed) | Linux observed |
|---|---|---|---|---|
| biv_subprocess_tests | 12/0/0/0 | 12/0/0/0 | 12/0/0/0 | 12/0/0/0 |
| biv_repo_git_tests | 6/0/0/0 | 6/0/0/0 | 6/0/0/0 | 6/0/0/0 |
| biv_repo_engine_tests | 60/0/0/0 | 60/0/0/0 | 60/0/0/0 | 60/0/0/0 |
| biv_tests | 418/0/0/3 | 418/0/0/3 | 420/0/0/1 | 420/0/0/1 |
| biv_probe_tests | 25/0/0/0 | 25/0/0/0 | 25/0/0/0 | 25/0/0/0 |

Observed = the tuples files in the evidence home (`tuples-macos.txt` sha256 `a91402bb…`, `tuples-linux.txt` `1e3b4224…`, both equal to the report's hashes); every want literal in the landed blob equals its observed cell.
The Linux `biv_tests` cell is the R-4.38 transcription: 420 observed vs the pinned 412 (the +8 the 2a Task-4 preview anticipated), now sourced from its own run at the run head, not from the preview.

## 4. Provenance in the commit message (71 lines, read)

Design pin, plan pin, `run_head=e14f15f… ancestor_81066ef_rc=0 ancestor_29acc6c_rc=0`, the five-binary preflight inventory, the ten observed cells with run ids and XML sha256s, the macOS run identity with the derived unset-name list and the host presence census (names only), `rc1=8 rc2=0 present_count=1 iff=PASS hygiene=PASS`, the token-scan line `cat_rc=0 hits=0`, `scout_rc=8` with the one platform exclusion, the `expected_skips` proof (`c2e7761f…`, byte_equal=yes), the Linux run identity (`ubuntu:24.04 linux/amd64 --init`, run head observed == expected, nofile soft == hard, name-free census) and the four-phase ledger. Every claimed fact traces to a recorded evidence file.

## 5. The external evidence home (read-only; 95 files; outside the checkout)

```text
run-head-ancestry.txt        run_head=e14f15f… ancestor_81066ef_rc=0 ancestor_29acc6c_rc=0
discriminator-predicate.txt  rc1=8 rc2=0 present_count=1 iff=PASS hygiene=PASS
precommit-guard.txt          s=0 s1=0 s2=0 d=1 removed=0 g=1 added=M  .github/workflows/s2-harness.yml
token-scan.txt               pattern=sk-[A-Za-z0-9]{8,}|-----BEGIN cat_rc=0 hits=0
landed-sha.txt               b065de1107161bb5df9543c09b50091365338c1c
status-initial.txt == status-post-observation.txt   (cmp equal; sha256 fbf10318…; 36 inherited rows — the shared tree's S4 state preserved)
discriminator-as-is.log      arm 1 (ambient host, one credential NAME present): harness-selftest ***Failed → rc1=8
discriminator-unset.log      arm 2 (the ruled environment): 100% tests passed → rc2=0
scout-macos.log              18/19 passed; the one red = safety-hardening "readelf unavailable" → the -E exclusion
```

The observer contract (m-3 ruling `012332`, R-OBS-1..6) is satisfied on the record: the unset set derived from `e3.py` at the run head; names only, no value read or recorded anywhere I looked; one environment; the discriminator executed and its predicate recorded; the exclusion set is exactly `{safety-hardening}`; the two-stage log scan zero-hit; the Linux container name-free.

## 6. Two things I checked that the report did not have to say

- The report's two REJECTED Docker transport probes left no repository effect (status snapshot equality) and no lingering container: the only container on the host is a three-week-old inherited S4 artifact, untouched.
- The first Linux job's selection remains unfiltered (no include list) and unchanged; the harness job (line 24) is outside the design's scope and was not touched.

## 7. Not claimed

m-3.planner's seven-point review (the veto's home); any push, PR, remote CI run, publication, merge gate, deployment, seal, or release. The FIRST PUSH remains master's routed one-time named act under R-4.51, never this lane's initiative. The release hold is ABSOLUTE.
