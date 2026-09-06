# The first push — publication receipt at `origin/main` = `bbf297e`, re-verified at the pair-planner's seat

Act: the ONE-TIME NAMED first publication of local `main` to `origin/main` under the operator's R-4.51 clause (1) (carrier `pdc:master/relays/publication-path-ruling/PLAN-operator-20260902-141706.md` @ b30cff98), routed by master `075759`, repaired `082012` @ 0fbd4fe6, and ruled to admit a second attempt within the same act `164704` @ ce0fb56c after the first attempt failed on the pair-planner's plan defect (`163348`, owned `164106`).
Executed by `intg.pair-implementer` under token `intg-firstpush-impl-2` (`intg-firstpush/IMPL-pair-planner-20260905-192430.md`) per plan `PL-intg-firstpush-20260905.md` rev7 @ `76bb7a548e916b3ed201ded92a331dcfd1dae6ae56a59107391f02f54cc6fdf1`; returned by `intg-firstpush/IMPL-pair-implementer-20260905-195647.md`.
This receipt records what the pair-planner re-derived on 2026-09-05 ~21:16 from the remote (read-only `ls-remote`), the local objects, and the implementer's external evidence home — not what the report says.

## 1. The three receipt lines master named (082012), re-derived

```text
(i)   git ls-remote origin refs/heads/main        bbf297e36a38a1fab8c2675f945098a0633f9f8b	refs/heads/main     (== the PIN)
(ii)  refs/remotes/origin/main                     bbf297e36a38a1fab8c2675f945098a0633f9f8b  (the implementer's one-ref --no-tags fetch)
      git rev-list --count main..origin/main       0                                          (the remote holds nothing local lacks)
(iii) git rev-list bbf297e..main                   11 commits, LISTED below — byte-equal to the report's receipt-iii.txt (cmp)
      64638fa9 ce95b9aa 036bd700 65ed8371 a041463a fd75f964 4c2b4b70 33565f0d e842e193 b7cf25e4 1fcc190e
      (every one a docs-lane commit of this cycle — relays, plans, receipts, sweep archives; R-4.52's first instance; NOT pushed; NOT a finding)
```

## 2. The publication

```text
published range        0db8fdd8424d27aad2c547614e9ebb95621a2794..bbf297e36a38a1fab8c2675f945098a0633f9f8b   814 commits
PIN tree               255e46d32eb6842507328cdac235bc85882f16f6
remote heads           25 (unchanged; only refs/heads/main moved)      remote tags 3 (no tag pushed; local tags 5)
local main             64638fa924d8118ddb83288ad9cbb723222456ae (unchanged by the act; 11 above the PIN)
```

## 3. The act, from the evidence home (read-only; 58 files)

```text
prepush-gate.txt   stop1_rc=0 stop2_remote=0db8fdd8… push_url_count=1 push_url=https://github.com/iwnlcern/bivpak.git fetch_url=(same) hook=…executable=no visibility=PRIVATE census=3/0/2/0 shell=zsh 5.9 act_line_count=1 act_span_bound=0 act_cmd_bound=0 dryrun_rc=0
act-span.txt == act-span-expected.txt   (cmp equal; the whole executable fragment of the approved plan's act line)
gate-dryrun.txt    To https://github.com/iwnlcern/bivpak.git / 0db8fdd..bbf297e  bbf297e… -> main
push-rc.txt        push_rc=0 · outcome_probe_rc=0 · remote_after=bbf297e… · class=a
push-stderr.txt    To https://github.com/iwnlcern/bivpak.git / 0db8fdd..bbf297e  bbf297e… -> main
boundary-proof.txt status_diff_rc=0 files=17842 inventory_diff_rc=0 symlinks=17 symlink_cmp_rc=0 findings=0
findings.txt       EMPTY (sha256 e3b0c442…)
verdict            class a AND empty findings → SUCCESS (computed, not narrated)
```

The execution shell was zsh 5.9 — the shell whose `:r` modifier defeated the rev4 attempt; the rev7 act line is a literal with no variable, and the gate bound its entire span before the push. No credential value appears in any evidence file.

## 4. What this receipt does NOT claim

No PR, no remote-CI run (green or red) cited, no tag, no merge, no deployment, no seal, no release. The release hold is ABSOLUTE. From this act onward R-4.51 clause (2) governs: every later work is a PULL REQUEST from a remote branch; the 11-commit docs-lane residue above the pin (12 with the commit carrying this receipt) is R-4.52, the operator's ruling, carried by master.
