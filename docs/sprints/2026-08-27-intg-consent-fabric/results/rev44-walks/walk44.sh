#!/usr/bin/env bash
# rev44 walk (MUST-2B-57): the Task 10 visibility read under an injected GH_HOST, rev44 vs rev43 lines; read-only (no gh write, no GH_DEBUG so no header is printed)
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r44; R43=$S/../r43/t10.sh; CAND=/Users/jack/Programming/bivpak-intg-substep2b-wiring
W=$S/w; rm -rf "$W"; mkdir -p "$W"
HDR='set -o pipefail; STOP() { printf "STOP-task-10 line=%s\n" "${BASH_LINENO[0]}" >&2; exit 1; }'
mk() { { printf '%s\n' "$HDR"; sed -n "${2}p" "$3"; sed -n "${4}p" "$3"; echo 'echo "VIS-OK $(cat "$EVID/visibility.txt") REPO=$REPO"'; } > "$W/$1.sh"; }
mk rev44 84 $S/t10.sh 90; mk rev43 84 $R43 90
printf 'rev44 lines: %s\n' "$(sed -n '2p' "$W/rev44.sh" | cut -d'#' -f1)"; printf 'rev43 lines: %s\n' "$(sed -n '2p' "$W/rev43.sh")"
run() { local c=$1 f=$2; shift 2; mkdir -p "$W/E-$c"; (cd "$CAND" && env "$@" GH_PROMPT_DISABLED=1 EVID=$W/E-$c bash "$W/$f.sh") > "$W/$c.out" 2>&1; echo "$c rc=$? | $(tr '\n' ' ' < "$W/$c.out" | cut -c1-220)"; }
run rev44-no-GH_HOST rev44 X=1
run rev44-GH_HOST-injected rev44 GH_HOST=gh-host-control.invalid
run rev43-GH_HOST-injected-CONTROL rev43 GH_HOST=gh-host-control.invalid
run rev44-GH_HOST-and-GH_REPO-injected rev44 GH_HOST=gh-host-control.invalid GH_REPO=gh-host-control.invalid/nosuch-owner/nosuch-repo
echo "static: gh calls in rev44 Task 10 not naming \"\$REPO\": $(grep -E 'gh (repo|pr|api)' $S/t10.sh | grep -v -c '"\$REPO"')"
echo "static: REPO assignments in rev44 Task 10: $(grep -c -E '(^|; )REPO=' $S/t10.sh); host-qualified: $(grep -c -E '(^|; )REPO=github\.com/iwnlcern/bivpak( |$)' $S/t10.sh)"
echo "gh $(gh --version | head -1 | cut -d' ' -f3): pr create --repo takes $(gh pr create --help | grep -o -E '\[HOST/\]OWNER/REPO' | head -1); gh pr create NOT run (no dry-run: its help says it may still push)"
