# rev40 walks — the records behind plan rev40 (impl-13's c10 mutant STOP folded)

Filed with rev40 (`682ceb885cf06f53270a6b3558f54a48f124ce3b36a63409c3ef9469db1aa607`) for the implementer's exact-hash review, after impl-13's STOP `intg-substep2b/IMPL-pair-implementer-20260926-211822.md`.
Every walk ran in the pair Planner's scratchpad on clones and mirrors; the real evidence home, the candidate worktree and every runners directory were read, never written. The scripts carry their scratch paths as they ran.
Every walked block is byte-equal to its BLOCK in the final rev40: `c10-mutants.sh` 2a9e1a30, `regate.sh` 675c839a, `resume.sh` c325718c. The task runners (task-0/9/10/11) are unchanged from rev39, and `plan_blocks.py check` is rc 0 for all four. The producer gate is rc 0 on the rev39 baseline (52 classified; no new read).
The `c10-mutants.sh` and `regate.sh` walks ran on an earlier rev40 draft whose only difference from the final is the `resume.sh` block (and the history line naming it); both blocks are byte-equal to the final.

## c10-mutants/ — the mutant arm, walked FOR REAL this time

rev39 disclosed its mutant arm as unwalked, and that is the arm that STOPped impl-13.
`yes-real.out`: rev40's block run once on a scratch clone of the candidate at c10 `2291a46`, with its own `.venv-harness` (from `harness/requirements.lock`) and a fresh `cmake --preset ci-macos` build, against a mirror of the Task 8c evidence (the rev39 record and work directory, `c10-red.txt` and the F4 patch). It took 7 min 12 s: `c10 mutants OK`, the receipt is `yes-real-receipt.txt`, the tree clean, the rev39 record untouched.
The receipt: M-H1-PRE `biv_tests=failed conforms=notrun failed_cases=1` ((w1) alone); M-H1-SCHEMA `case_rc=0 biv_tests=passed conforms=failed failed_cases=0`; M-H1-F4 `biv_tests=failed conforms=notrun failed_cases=2` ((w3)'s two cases); `verdict=ok`.
`wno.sh`: the same block with `cmake` and `ctest` stubbed on PATH and `build/ci-macos/biv_tests` a stub, each serving the REAL artifacts of that run. The stubbed YES passes.
The NO cases each STOP at their own guard, with no `verdict=ok` written and the tree clean: PRE served SCHEMA's or F4's artifacts; PRE's failing case renamed; SCHEMA served PRE's; F4 served PRE's; one of F4's two cases renamed; the conforms row absent from the CTest log; the rev39 record altered; the rev39 work directory absent; the rev40 record pre-existing.

## regate/ — Task 9b reads the verdict, never the file's presence

`w40regate.sh` is rev39's regate walk against the rev40 block. All rev39 cases keep their verdicts.
Three new cases STOP at `task8c-mutants-verdict`: `rev39-record-only` (exactly the real home's state today, which rev39's `[ -s ]` check would have admitted), `verdict-absent` and `verdict-twice`.

## step0prime/ — resume.sh bound by content for the SECOND successor

`w40wresume.sh` from a mirror of `s2b-runners-r9Akl6`, the directory impl-14 resumes from, whose token (impl-13) did not run Task 9. rev39's `resume.sh` STOPped here `task-9-record-mismatch-task-9.sh`; the rev40 block publishes with 31 carried lines, all byte-equal.
The NO cases each STOP with no new directory and the pointer unchanged: done-red, exit-mismatch, sh-altered, record-mismatch (now `task-9-record-owner-0`), owner-none, owner-two (a duplicate record set under another token: `owner-2`), receipt-absent, done-symlink.
`w40wresume-UG0.out` is the same walk from a mirror of `s2b-runners-UG0MP0` (the first-successor shape): it also publishes with 31 carried lines.
`w40wconsumer.sh`: `run-task.sh 10` from the carried directory reaches only the absent GO; without Task 9's receipts it STOPs at line 16.
