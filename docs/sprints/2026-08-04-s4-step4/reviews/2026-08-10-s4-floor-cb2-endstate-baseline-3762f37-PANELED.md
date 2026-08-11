# Per-file END-STATE baseline — PANELED pair C `b8083be` / B2 `3762f37`

Captured BEFORE the re-stack onto post-R-4.8 `origin/main` (`38a4702`) so the post-re-stack carry
adjudication is a LOOKUP, not a reconstruction.

**These bytes carry the COMBINED RE-CHECK PASS verdict** (record
`2026-08-10-s4-floor-cb2-combined-recheck-3762f37.md`). At the re-stacked head a file whose end-state
bytes hash-match below **carries that verdict**; any file that differs — every conflict-resolved file at
minimum — needs **FRESH review**. Delta-range equality is NOT sufficient (re-stack-provenance rule).

Scope = the UNION of C's delta (`721eeaefd168c917e4ee4cadf7cd0366baa43514`→C) and B2's delta (C→B2), hashed at the B2 end-state, because
B2 contains C. A C-only table would miss B2's edits; a C→B2-only table misses `sessions.cpp`, which is
C's file and IS a conflict — that omission is why this table was rebuilt.

C tree: `64d77cdeade243f7da001402a19212ef5d5d73d1` · B2 = one commit atop C

| sha256 @ 3762f37 | path | slice | R-4.8 collision? |
|---|---|---|---|
| `8ac47d21356824ca61783e6fce06699bd2c9a8666a2688a5942e43ab897a428c` | `harness/bivharness/compare.py` | C | no |
| `2fb295a67ab2dd95388579e05513b1901b5db528e73faa4ad6e2ba097d3df6ec` | `harness/bivharness/e3.py` | B2 | no |
| `2ee49d6e457a5bb618ad50d09fa75eb9e9c754085d35299c5672f921106879a9` | `harness/bivharness/scenario.py` | C | no |
| `21d348285d54d2d1cb1f17b8d9d9f388816de719258f5eac0d4fa5475ff49505` | `harness/CMakeLists.txt` | B2 | no |
| `73f438c4e492f6ee54ef9b4b1a57480f1fe1052409ff64a15a78230284e58100` | `harness/scenarios/open-consent-no.json` | C | no |
| `0fdaecb1c117b32d90f7d8b500c5134acbdc9f10403e89b09e2e9a3b29a9734f` | `harness/scenarios/open-consent-per-agent.json` | C | no |
| `3b1c659c838ab1ba820c44a1f842d862f777f20a87a8671c88034c543e80a602` | `harness/scenarios/open-deny-default.json` | C | no |
| `b2d66c81c5caf3b20d13e23b4e7f077deed72e629ae6f553e12e9ca7d72f2da5` | `harness/selftest/test_compare.py` | C | no |
| `2c864581b7b63e81b390ab0fbfec129288179871988fc275041c5b14ae0a734d` | `harness/selftest/test_e3_asserts.py` | C | no |
| `0291fb3e0b2ab43ebb14a97a3c5a1d5125312765110cbd97e660647c57ec92c3` | `harness/selftest/test_envelope.py` | C | no |
| `b3f3262a2362bb857fd0d8d50ad68ff73795f63eba5c88c574be350d0a69df0a` | `schemas/biv-exit-map.v1.json` | C | no |
| `4b4412c3dddca0cabbe9ed615af75cf05a388f1ec33f53811d0643e7cc7765dd` | `schemas/biv-json-envelope.v1.schema.json` | C | no |
| `1c96d3ac7b86b7836296475b2da3d6fd07b1806a70268a5a9981f237b713fcb4` | `src/adapters/adapter.hpp` | B2 | no |
| `cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851` | `src/adapters/claude_code/claude_code.cpp` | B2 | no |
| `5802406ee272ed496d005a8c8010fe08e21d336dd2e5e562c5177aedf27a2c11` | `src/adapters/claude_code/install.cpp` | B2 | no |
| `2fd24c84bc7f114268b4e3d5f2d5fc98075130c61aa90c4df548f0fa13b5406d` | `src/adapters/codex/codex.cpp` | B2 | no |
| `5e829ff7b391f8a06ff637f902a4a33cb1b7b56db3a363b31f12be7ba4b783b7` | `src/adapters/codex/install.cpp` | B2 | no |
| `cfcd49111ff9a4c9deabcd249d10ed9996d7c4adf597c86fb864309a41f60c96` | `src/adapters/rewrite_common.cpp` | B2 | no |
| `4a0e77b7d7331f7419e87cf7746ce31428d17af3e1351500139a4d93a7ab48f3` | `src/adapters/rewrite_common.hpp` | B2 | no |
| `af1045fc68cc8b3cc0272795f5ec8324733297c8fd9e3405046c9e6e660ffd82` | `src/core/open/render.cpp` | C | no |
| `bd64bb5b8229f204975e1477232715014a78b223042105917981116d432fd46f` | `src/core/open/sessions.cpp` | C | **YES → FRESH** |
| `deac5a31bb2e23121ab370665698a03b987f940a8f0a2ae3f83bb6e1528fbb9f` | `src/core/open/sessions.hpp` | C | no |
| `0f5cabfd755eea473e76c047c4ad47d1b0f7127de1da3f95d550731b85a1ea33` | `src/core/pack/pack.cpp` | B2 | no |
| `3d0830ceddbb9ea1faae30b1d6ccee728648fc915f8a8208424071ddb54eaef6` | `src/core/report/envelope.cpp` | C | no |
| `f3447560dd505542f10b26f46d5fb61942405f5928d9040161dad5dd57f5fd18` | `src/core/support/error.cpp` | C | no |
| `4f7172709ff497eff744e52dd09ab2db2e3854b11b1f3fffe5e423641f407514` | `src/core/support/error.hpp` | C | no |
| `2131cc80a628d8a2a6de67a8e10c29ba00389a08b42c32daa4bfa1eb473b3a64` | `tests/test_adapter_claude_collect.cpp` | B2 | no |
| `152b82df86da61e55c7410f94d55251c0080e60deb4025a9869c9b7fd8b45b2a` | `tests/test_adapter_claude_install.cpp` | B2 | **YES → FRESH** |
| `6b52a282387d12eff55d5718767d176e7c45b923faed4455f92609eff08b4d6e` | `tests/test_adapter_codex_collect.cpp` | B2 | no |
| `35506db97b7af78b49b770301a3f027dc40a5a7b5463e15fad1dc3b01e1bd0f5` | `tests/test_adapter_codex_install.cpp` | B2 | **YES → FRESH** |
| `1c74fd06693577039d91d87c4a69dc42386888baa27ae3288dc7bb573453f8ae` | `tests/test_cli.cpp` | B2 | no |
| `8326536990f366bf46b2ba3272a2858d5784af7f4b830cd85b4646b3f040cf3d` | `tests/test_envelope.cpp` | C | no |
| `38d790c1b185e7757d03d1b17e13592cebf46065b7c9ed84218d12a16c8b57ff` | `tests/test_pack.cpp` | B2 | **YES → FRESH** |
| `cbb4cdf17775fe8c51687d2a5c8efb26f0d51fdc8d523db21c930cb9c58e0883` | `tests/test_sessions.cpp` | B2 | **YES → FRESH** |

**C itself must move:** `sessions.cpp` is C's and conflicts, so C — byte-identical since its own panel —
gets a new SHA. A10.3 still binds (C never lands without B2).
