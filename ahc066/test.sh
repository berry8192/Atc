#!/bin/bash
# Usage: bash test.sh [num_seeds] [binary] [tle_limit_sec]
#   num_seeds:     how many seeds (default 100)
#   binary:        which executable to test (default a.out)
#   tle_limit_sec: wall-time threshold for TLE in seconds (default 2.0)
#
# 実時間ベースで TLE 検出する。/usr/bin/time -f "%e" で wall time を測り
# しきい値超過を TLE として記録する。元の "TIMEOUT" 文字列依存より厳密。

NUM=${1:-100}
BIN=${2:-a.out}
TLE_LIMIT=${3:-2.0}
OUTDIR=test_results/$(date +"%Y%m%d%H%M%S")
mkdir -p "$OUTDIR"

VIS=external_tools/target/release/vis
if [ ! -x "$VIS" ]; then
    echo "Building visualizer..."
    (cd external_tools && cargo build -r --bin vis) || exit 1
fi

echo "Binary:  ./$BIN"
echo "Seeds:   $NUM"
echo "TLE>:    ${TLE_LIMIT}s (wall time)"
echo "Outdir:  $OUTDIR/"
echo

SCOREFILE="$OUTDIR/scores.txt"
: > "$SCOREFILE"

TOTAL=0
MIN=99999999
MAX=0
FAILS=0
FAIL_SEEDS=""
TLES=0
TLE_SEEDS=""

# header for compact table
printf "    "
for c in $(seq 0 9); do printf " %7d" "$c"; done
echo

for i in $(seq 0 $((NUM - 1))); do
    IDX=$(printf "%04d" $i)
    FILE="external_tools/in/$IDX.txt"
    OUTFILE="$OUTDIR/$IDX.txt"
    ERRFILE="$OUTDIR/$IDX.err"
    TIMEFILE="$OUTDIR/$IDX.time"
    /usr/bin/time -f "%e" -o "$TIMEFILE" ./"$BIN" < "$FILE" > "$OUTFILE" 2>"$ERRFILE"
    WALL=$(cat "$TIMEFILE" 2>/dev/null || echo "0")
    SCORE=$("$VIS" "$FILE" "$OUTFILE" 2>/dev/null | grep -oE "Score = [0-9]+" | awk '{print $3}')
    SCORE=${SCORE:-0}
    # wall time > TLE_LIMIT → TLE
    if awk -v t="$WALL" -v lim="$TLE_LIMIT" 'BEGIN{exit !(t+0 > lim+0)}'; then
        TLES=$((TLES + 1))
        TLE_SEEDS="$TLE_SEEDS $i"
    fi

    # row label every 10 seeds
    if [ $((i % 10)) -eq 0 ]; then
        printf "%3d:" "$i"
    fi
    # red zeroes, dim normal
    if [ "$SCORE" -eq 0 ]; then
        printf " \033[31m%7d\033[0m" "$SCORE"
        FAILS=$((FAILS + 1))
        FAIL_SEEDS="$FAIL_SEEDS $i"
    else
        printf " %7d" "$SCORE"
    fi
    if [ $((i % 10)) -eq 9 ] || [ "$i" -eq $((NUM - 1)) ]; then
        echo
    fi

    echo "seed $i: $SCORE" >> "$SCOREFILE"
    TOTAL=$((TOTAL + SCORE))
    [ "$SCORE" -lt "$MIN" ] && MIN=$SCORE
    [ "$SCORE" -gt "$MAX" ] && MAX=$SCORE
done

AVG=$((TOTAL / NUM))

echo
echo "===== Summary ====="
printf "avg:    %d\n" "$AVG"
printf "total:  %d\n" "$TOTAL"
printf "min:    %d\n" "$MIN"
printf "max:    %d\n" "$MAX"
printf "fails:  %d / %d" "$FAILS" "$NUM"
[ -n "$FAIL_SEEDS" ] && printf " (seeds:%s)" "$FAIL_SEEDS"
echo
printf "tles:   %d / %d" "$TLES" "$NUM"
[ -n "$TLE_SEEDS" ] && printf " (seeds:%s)" "$TLE_SEEDS"
echo

{
    echo "---"
    echo "avg:    $AVG"
    echo "total:  $TOTAL"
    echo "min:    $MIN"
    echo "max:    $MAX"
    echo "fails:  $FAILS"
    [ -n "$FAIL_SEEDS" ] && echo "fail_seeds:$FAIL_SEEDS"
    echo "tles:   $TLES"
    [ -n "$TLE_SEEDS" ] && echo "tle_seeds:$TLE_SEEDS"
} >> "$SCOREFILE"
