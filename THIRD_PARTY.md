| dep | version | license | source URL | archive sha256 |
|---|---|---|---|---|
| simdjson | v3.10.1 | Apache-2.0 | https://github.com/simdjson/simdjson/archive/refs/tags/v3.10.1.tar.gz | 1e8f881cb2c0f626c56cd3665832f1e97b9d4ffc648ad9e1067c134862bba060 |
| zstd | v1.5.6 | BSD-3-Clause/GPLv2 dual | https://github.com/facebook/zstd/releases/download/v1.5.6/zstd-1.5.6.tar.gz | 8c29e06cf42aacc1eafc4077ae2ec6c6fcb96a626157e0593d5e82a34fd403c1 |
| Catch2 | v3.7.1 | BSL-1.0 | https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.1.tar.gz | c991b247a1a0d7bb9c39aa35faf0fe9e19764213f28ffba3109388e62ee0269c |

Fuzz builds copy clang 22.1.6's `libclang_rt.fuzzer-x86_64.a` into the build tree and localize 12 weak allocator symbols (`_ZdaPv`, `_ZdaPvm`, `_ZdaPvSt11align_val_t`, `_ZdaPvmSt11align_val_t`, `_ZdlPv`, `_ZdlPvm`, `_ZdlPvSt11align_val_t`, `_ZdlPvmSt11align_val_t`, `_Znam`, `_Znwm`, `_ZnamSt11align_val_t`, `_ZnwmSt11align_val_t`) before linking. This works around a distro libFuzzer packaging defect where the runtime's private C++ allocator overrides can mask ASan's allocator-family tracking. REMOVE-WHEN: re-test an unpatched libFuzzer archive at the next clang toolchain bump.
