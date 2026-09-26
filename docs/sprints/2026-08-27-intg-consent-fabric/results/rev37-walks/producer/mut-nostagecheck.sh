# rev37 (m-4 151817 K3_TIE strict; master 154632): the corrected series reducer, produced beside Task 0's `series_verdict.py` (never overwritten) from THIS plan's block only when absent (staged in work/, digest-checked, then renamed into place), digest-pinned either way
V37=$EVID/series_verdict.rev37.py
if [ ! -e "$V37" ] && [ ! -L "$V37" ]; then
PLANP=$(cat "$RUNNERS/plan-path.txt") || STOP; [ -s "$PLANP" ] || STOP; V37S=$EVID/work/series_verdict.rev37.stage; x=0; python3 "$RUNNERS/plan_blocks.py" extract "$PLANP" series_verdict.py > "$V37S" || x=$?; [ "$x" -eq 0 ] && [ -s "$V37S" ] || STOP
[ ! -e "$V37" ] && [ ! -L "$V37" ] || STOP; v=0; mv "$V37S" "$V37" || v=$?; [ "$v" -eq 0 ] || STOP
fi
[ -f "$V37" ] && [ ! -L "$V37" ] || STOP
m=0; vs=$(shasum -a 256 "$V37" | cut -d' ' -f1) || m=$?; [ "$m" -eq 0 ] && [ "$vs" = 09b6cb7612907972bb9cf340a8ffcbf406a71da1194d034ce45c85de6127d452 ] || STOP
p=0; python3 -m py_compile "$V37" || p=$?; [ "$p" -eq 0 ] || STOP
