import os
import stat
from pathlib import Path


def pin_env() -> int:
    previous = os.umask(0o022)
    os.environ["TZ"] = "UTC"
    os.environ["LC_ALL"] = "C"
    return previous


def _is_under_mnt(path: Path) -> bool:
    parts = path.resolve(strict=False).parts
    return len(parts) >= 2 and parts[0] == "/" and parts[1] == "mnt"


def probe(scratch: Path) -> list[str]:
    failures: list[str] = []
    if _is_under_mnt(scratch):
        failures.append("drvfs-guard")
        return failures

    try:
        scratch.mkdir(parents=True, exist_ok=True)
    except FileExistsError:
        pass

    mode_probe = scratch / ".bivharness-mode-probe"
    mode_probe.write_bytes(b"x")
    os.chmod(mode_probe, 0o751)
    if stat.S_IMODE(os.stat(mode_probe).st_mode) != 0o751:
        failures.append("mode-roundtrip")

    symlink_probe = scratch / ".bivharness-link-probe"
    try:
        symlink_probe.unlink()
    except FileNotFoundError:
        pass
    try:
        os.symlink(".bivharness-mode-probe", symlink_probe)
        if os.readlink(symlink_probe) != ".bivharness-mode-probe":
            failures.append("symlink")
    except OSError:
        failures.append("symlink")

    return failures
