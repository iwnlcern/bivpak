worktree HEAD 8509157c41c5ef66595d655f39eee5107081bd32
start 2026-09-11 13:36:40
ctest rc 8
end 2026-09-11 13:36:58
run1: this shell exported a name in e3.py CREDENTIAL_ENV_NAMES (ANTHROPIC_API_KEY; name only, value never read) -> 119 INVALID credential-env scenarios; NOT a product draw
run2: env -u ANTHROPIC_API_KEY -u OPENAI_API_KEY -u CODEX_ACCESS_TOKEN; start 2026-09-11 13:38:30
run2 ctest rc 0 end 2026-09-11 13:38:48
run3: run2 flags + --test-output-size-passed 50000000 --test-output-size-failed 50000000; rc 0 end 2026-09-11 13:40:11
finding: run2's JUnit <system-out> is head-truncated at CTest's default passed-output threshold (1024 bytes; the file says "[This part of the test output was removed since it exceeds the threshold of 1024 bytes.]"), so the pytest summary line is ABSENT and selftest_summary.py reports summary=absent -> a REAL green BASE would classify stop-invalid-base-draw under the rev18 runner. run3 (size flags 50000000) carries "1014 passed" -> summary=parsed failed=0 passed=1014 population=1014 names_count=0.
ctest: macOS 4.3.1 here; Ubuntu 24.04 parity image ctest 3.28.3 lists --test-output-size-passed/--test-output-size-failed/--test-output-truncation (checked in a disposable container).
key-shape scan of every log/junit (sk-ant-|sk-proj-|ghp_|eyJ…): 0 hits; only credential NAMES appear.
