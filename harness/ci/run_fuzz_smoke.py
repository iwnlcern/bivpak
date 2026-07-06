import argparse
import shutil
import subprocess
import tempfile
from pathlib import Path


def _run(target: str, corpus: Path, artifact_dir: Path, runs: int, seed: int):
    artifact_dir.mkdir(parents=True, exist_ok=True)
    return subprocess.run(
        [
            target,
            str(corpus),
            f"-runs={runs}",
            f"-seed={seed}",
            f"-artifact_prefix={artifact_dir.as_posix()}/",
        ],
        check=False,
        text=True,
        capture_output=True,
    )


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--runs", required=True, type=int)
    parser.add_argument("--seed", required=True, type=int)
    parser.add_argument("--manifest-corpus", required=True)
    parser.add_argument("--tar-corpus", required=True)
    parser.add_argument("--manifest-target", required=True)
    parser.add_argument("--tar-target", required=True)
    args = parser.parse_args()

    failures = []
    with tempfile.TemporaryDirectory(prefix="bivharness-fuzz-") as tmp:
        scratch = Path(tmp)
        manifest_corpus = shutil.copytree(args.manifest_corpus, scratch / "manifest-corpus")
        tar_corpus = shutil.copytree(args.tar_corpus, scratch / "tar-corpus")
        for name, target, corpus in (
            ("fuzz_manifest_json", args.manifest_target, manifest_corpus),
            ("fuzz_tar_member", args.tar_target, tar_corpus),
        ):
            run = _run(target, corpus, scratch / "artifacts" / name, args.runs, args.seed)
            if run.returncode != 0:
                failures.append(f"{name} exited {run.returncode}\n{run.stdout}\n{run.stderr}")
    if failures:
        print("\n".join(failures))
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
