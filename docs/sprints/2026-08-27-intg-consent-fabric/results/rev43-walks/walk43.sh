#!/usr/bin/env bash
S=/private/tmp/claude-501/-Users-jack-Programming-bivpak/6fecc389-d499-4128-a827-a4138f47bce6/scratchpad/r43; T=$S/t10.sh; CAND=/Users/jack/Programming/bivpak-intg-substep2b-wiring; RE=/Users/jack/Programming/bivpak-evidence/s2b-intg-substep2b-impl-1-y3iCLB
W=$S/w; rm -rf "$W"; mkdir -p "$W"
HDR='set -o pipefail; STOP() { printf "STOP-task-10 line=%s\n" "${BASH_LINENO[0]}" >&2; exit 1; }'
{ printf '%s\n' "$HDR"; echo 'B=186adf7d67171bd7afe621f39b657a1a113ce299; H=cb19326a5596bf30eab2ec2b9baeda0bc77be895'; sed -n '83,95p' "$T"; echo 'echo DEST-OK; cat "$EVID/fetch-url.txt" "$EVID/push-url.txt" "$EVID/visibility.txt"; wc -c < "$EVID/url-rewrite.txt"'; } > "$W/dest.sh"
echo "dest script map: block 83..95 -> lines 3..15 (85=fetch-url->5, 86=url-rewrite->6, 87/88=push-url->7/8, 89=remote-branch-before->9, 90=visibility->10)"
rd() { local c=$1 dir=$2; shift 2; mkdir -p "$W/E-$c/work"; (cd "$dir" && env "$@" EVID=$W/E-$c bash "$W/dest.sh") > "$W/$c.out" 2>&1; echo "$c rc=$? $(grep -m1 -E 'DEST-OK|STOP' "$W/$c.out")"; }
echo "== MUST-2B-55 destination binding"
rd yes-real "$CAND" X=1; sed -n '2,5p' "$W/yes-real.out"
rd yes-GH_REPO-elsewhere "$CAND" GH_REPO=nosuch-owner-zz9/nosuch-repo-zz9
(cd "$CAND" && GH_REPO=nosuch-owner-zz9/nosuch-repo-zz9 gh repo view --json visibility -q .visibility) > "$W/rev42-unqualified.out" 2>&1; echo "control: rev42's unqualified gh repo view under the same GH_REPO rc=$? $(head -c 80 "$W/rev42-unqualified.out" | tr '\n' ' ')"
git init -q --bare "$W/bare"
mkclone() { git clone -q --shared --no-checkout "$CAND" "$W/$1" && git -C "$W/$1" checkout -q --detach cb19326a5596bf30eab2ec2b9baeda0bc77be895; }
mkclone split; git -C "$W/split" remote set-url origin "$W/bare"; git -C "$W/split" remote set-url --push origin https://github.com/iwnlcern/bivpak.git; rd split-fetch-push "$W/split" X=1
mkclone ioff; git -C "$W/ioff" remote set-url origin https://github.com/iwnlcern/bivpak.git; git -C "$W/ioff" config "url.$W/bare.insteadOf" https://github.com/; rd insteadOf "$W/ioff" X=1
mkclone poff; git -C "$W/poff" remote set-url origin https://github.com/iwnlcern/bivpak.git; git -C "$W/poff" config "url.$W/bare.pushInsteadOf" https://github.com/; rd pushInsteadOf "$W/poff" X=1
rd env-injected-rewrite "$CAND" GIT_CONFIG_COUNT=1 "GIT_CONFIG_KEY_0=url.$W/bare.insteadOf" GIT_CONFIG_VALUE_0=https://github.com/
for c in split-fetch-push insteadOf pushInsteadOf env-injected-rewrite; do n=$(ls "$W/E-$c" | grep -c -E 'remote-branch|visibility|exposure|push-dry|push-rc'); echo "  $c: remote-read/push receipts written = $n"; done
echo "static: remote reads/writes in task-10 not naming \$URL/\$REPO: $(grep -n -E 'ls-remote|git push|gh (repo|pr)' "$T" | grep -v -E '"\$URL"|"\$REPO"' | grep -v 'ls-remote --get-url' | wc -l | tr -d ' ')"
echo "== MUST-2B-56 retention on the real prior-attempt byte set"
{ printf '%s\n' "$HDR"; sed -n '26,49p' "$T"; echo 'echo STEP0-COMPILE-OK "${AD-none}"'; } > "$W/s0.sh"
{ printf '%s\n' "$HDR"; sed -n '26,48p' "$T"; echo 'p=0; python3 -m py_compile "$F41" || p=$?; [ "$p" -eq 0 ] || STOP'; echo 'echo REV42-COMPILE-DONE'; } > "$W/s0-rev42compile.sh"
mkE() { cp -cRp "$RE" "$W/$1" || { echo "MIRROR-FAILED $1"; exit 9; }; }
mkE ret; F=$W/ret/finalize.rev41.py; fsb=$(shasum -a 256 "$F" | cut -d' ' -f1); fmb=$(stat -f %m "$F")
pb=$(ls "$W/ret/__pycache__" | sort | tr "\n" " "); (EVID=$W/ret RUNNERS=/nonexistent bash "$W/s0.sh") > "$W/ret.out" 2>&1; echo "retention rc=$? $(tail -1 "$W/ret.out")"
AD=$W/ret/attempts/task10-1; cmp -s "$RE/__pycache__/finalize.rev41.cpython-312.pyc" "$AD/__pycache__/finalize.rev41.cpython-312.pyc" && echo "  prior pyc preserved byte-equal in attempts/task10-1/__pycache__/"
pa=$(ls "$W/ret/__pycache__" | sort | tr "\n" " "); echo "  home __pycache__ before: $(echo $pb | wc -w | tr -d " ") entries; after: $(echo $pa | wc -w | tr -d " ") entries; finalize.rev41.* after: $(ls "$W/ret/__pycache__" | grep -c "^finalize\.rev41\.")"
echo "  finalize.rev41.py in place: sha=$( [ "$(shasum -a 256 "$F" | cut -d' ' -f1)" = "$fsb" ] && echo unchanged ) mtime=$( [ "$(stat -f %m "$F")" = "$fmb" ] && echo unchanged ) digest-is-a9eec925=$( [ "$fsb" = a9eec92599b4575b4c7b20a68a25da2ef645873fec75d4d7c8d5a30109f609c0 ] && echo yes )"
echo "  manifest: $(wc -l < "$AD/MANIFEST.pre" | tr -d ' ') rows; verify: $(grep -c ': OK$' "$AD/MANIFEST.verify") OK"
mkE neg; (EVID=$W/neg RUNNERS=/nonexistent bash "$W/s0-rev42compile.sh") > "$W/neg.out" 2>&1; echo "control (rev42 py_compile on the same shape) rc=$? $(tail -1 "$W/neg.out") -> finalize.rev41.* in the home __pycache__ after: $(ls "$W/neg/__pycache__" | grep -c "^finalize\.rev41\.")"; cmp -s "$RE/__pycache__/finalize.rev41.cpython-312.pyc" "$W/neg/attempts/task10-1/__pycache__/finalize.rev41.cpython-312.pyc" && echo "  (rev42-compile control: prior pyc also preserved first by rev43 Step 0, so the control isolates the compile line)"
mkE pyclink; rm "$W/pyclink/__pycache__/finalize.rev41.cpython-312.pyc"; ln -s "$RE/__pycache__/finalize.rev41.cpython-312.pyc" "$W/pyclink/__pycache__/finalize.rev41.cpython-312.pyc"; (EVID=$W/pyclink bash "$W/s0.sh") > "$W/pyclink.out" 2>&1; echo "pyc-symlink rc=$? $(tail -1 "$W/pyclink.out")"
mkE rcpt; echo push_rc=0 > "$W/rcpt/push-rc.txt"; (EVID=$W/rcpt bash "$W/s0.sh") > "$W/rcpt.out" 2>&1; echo "push-receipt rc=$? $(tail -1 "$W/rcpt.out")"
