# Per-file END-STATE byte baseline — B2 `e0d6c19` (for the combined post-(a) re-check)

Captured by `s4-floor.planner` per the orchestrator's required refinement (`214722`): at the combined
post-option-(a) SHA, a file whose end-state bytes hash-match its value below **carries mechanically**;
any file whose hash differs gets **fresh review**. Delta-range equality is NOT sufficient — this is the
re-stack-provenance rule (panels bind END-STATE bytes).

Baseline SHA: `e0d6c1994e286291cc7ab3439228edbb65f048a4` (one commit atop C `b8083be8529a97d1d3d5931a2c7b308335bbd09c`)
Scope: the full cumulative C→B2 path set, so any file can be adjudicated, not only the eight just folded.

| sha256 (end-state at e0d6c19) | path | in partial fold? |
|---|---|---|
| `21d348285d54d2d1cb1f17b8d9d9f388816de719258f5eac0d4fa5475ff49505` | `harness/CMakeLists.txt` | no (carried from C) |
| `2fb295a67ab2dd95388579e05513b1901b5db528e73faa4ad6e2ba097d3df6ec` | `harness/bivharness/e3.py` | yes |
| `1c96d3ac7b86b7836296475b2da3d6fd07b1806a70268a5a9981f237b713fcb4` | `src/adapters/adapter.hpp` | no (carried from C) |
| `cd1f8bc8f7ab87cf15251d84ad7e59c618a22f3c19b9633ff193350782800851` | `src/adapters/claude_code/claude_code.cpp` | no (carried from C) |
| `f8a5128c401832488b92ee4f10b5e34b9d8f8070acfff0721e4a91f4c5466669` | `src/adapters/claude_code/install.cpp` | yes |
| `2fd24c84bc7f114268b4e3d5f2d5fc98075130c61aa90c4df548f0fa13b5406d` | `src/adapters/codex/codex.cpp` | yes |
| `5e829ff7b391f8a06ff637f902a4a33cb1b7b56db3a363b31f12be7ba4b783b7` | `src/adapters/codex/install.cpp` | no (carried from C) |
| `cfcd49111ff9a4c9deabcd249d10ed9996d7c4adf597c86fb864309a41f60c96` | `src/adapters/rewrite_common.cpp` | yes |
| `4a0e77b7d7331f7419e87cf7746ce31428d17af3e1351500139a4d93a7ab48f3` | `src/adapters/rewrite_common.hpp` | no (carried from C) |
| `0f5cabfd755eea473e76c047c4ad47d1b0f7127de1da3f95d550731b85a1ea33` | `src/core/pack/pack.cpp` | no (carried from C) |
| `0b9fcffe2c6e2c417992c6737e5e99bda894672938330aebb1ad0c470fe5c616` | `tests/test_adapter_claude_collect.cpp` | yes |
| `17497caaca72f526eec1656f4256cfe414fc548e4dd44412903b487e724aaec2` | `tests/test_adapter_claude_install.cpp` | yes |
| `6b52a282387d12eff55d5718767d176e7c45b923faed4455f92609eff08b4d6e` | `tests/test_adapter_codex_collect.cpp` | yes |
| `35506db97b7af78b49b770301a3f027dc40a5a7b5463e15fad1dc3b01e1bd0f5` | `tests/test_adapter_codex_install.cpp` | no (carried from C) |
| `1c74fd06693577039d91d87c4a69dc42386888baa27ae3288dc7bb573453f8ae` | `tests/test_cli.cpp` | no (carried from C) |
| `2448bce775036f166a8d2a53fc871c89d936d28aaad31b14a4bb785820099c60` | `tests/test_pack.cpp` | yes |
| `0004f244738603df71dff62ec7209422c06817b38adb9f4ed6da354d0ea07799` | `tests/test_sessions.cpp` | no (carried from C) |

Verify at the combined SHA with:
```
git show "<combined-sha>:<path>" | shasum -a 256
```
