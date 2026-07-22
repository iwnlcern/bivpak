from dataclasses import dataclass, field
from enum import Enum
from typing import Any


class Status(str, Enum):
    PASS = "pass"
    FAIL = "fail"
    XFAIL_PENDING = "xfail-pending"
    INVALID = "invalid"


@dataclass
class ScenarioResult:
    id: str
    tier: str
    status: Status
    classes: list[str]
    held_asserts: list[str] = field(default_factory=list)
    detail: str = ""
    warnings: list[str] = field(default_factory=list)


@dataclass
class Report:
    results: list[ScenarioResult]

    def exit_code(self) -> int:
        bad = any(r.status in (Status.FAIL, Status.INVALID) for r in self.results)
        proven = any(r.status is Status.PASS for r in self.results)
        return 0 if (not bad and proven) else 1

    def to_json(self) -> dict[str, Any]:
        return {
            "runnable_passed": [r.id for r in self.results if r.status is Status.PASS],
            "failed": [r.id for r in self.results if r.status is Status.FAIL],
            "invalid": [r.id for r in self.results if r.status is Status.INVALID],
            "pending": [r.id for r in self.results if r.status is Status.XFAIL_PENDING],
            "held_asserts": {r.id: r.held_asserts for r in self.results if r.held_asserts},
            "rows": [
                {
                    "id": r.id,
                    "tier": r.tier,
                    "status": r.status.value,
                    "classes": r.classes,
                    "detail": r.detail,
                    "warnings": r.warnings,
                }
                for r in self.results
            ],
        }
