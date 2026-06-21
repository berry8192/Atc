#!/bin/bash
# Usage: bash test.sh [num_seeds] [src]
#   num_seeds: how many seeds (default 100)
#   src:       which source to build & test (default A.cc -> ./A)

NUM=${1:-100}
SRC=${2:-A.cc}
BIN="${SRC%.cc}"
OUTDIR=test_results/$(date +"%Y%m%d%H%M%S")
mkdir -p "$OUTDIR"

# compile (rebuild if source is newer than binary)
if [ ! -x "./$BIN" ] || [ "$SRC" -nt "./$BIN" ]; then
    echo "Compiling $SRC -> ./$BIN ..."
    g++ -O2 -std=c++17 -o "$BIN" "$SRC" || exit 1
fi

VIS=external_tools/target/release/vis
if [ ! -x "$VIS" ]; then
    echo "Building visualizer..."
    (cd external_tools && cargo build -r --bin vis) || exit 1
fi

echo "Binary:  ./$BIN"
echo "Seeds:   $NUM"
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
for c in $(seq 0 9); do printf " %8d" "$c"; done
echo

for i in $(seq 0 $((NUM - 1))); do
    IDX=$(printf "%04d" $i)
    FILE="external_tools/in/$IDX.txt"
    OUTFILE="$OUTDIR/$IDX.txt"
    ERRFILE="$OUTDIR/$IDX.err"
    ./"$BIN" < "$FILE" > "$OUTFILE" 2>"$ERRFILE"
    SCORE=$("$VIS" "$FILE" "$OUTFILE" 2>/dev/null | grep -oE "Score = [0-9]+" | awk '{print $3}')
    SCORE=${SCORE:-0}
    if grep -q "TIMEOUT" "$ERRFILE" 2>/dev/null; then
        TLES=$((TLES + 1))
        TLE_SEEDS="$TLE_SEEDS $i"
    fi

    # row label every 10 seeds
    if [ $((i % 10)) -eq 0 ]; then
        printf "%3d:" "$i"
    fi
    # red zeroes, dim normal
    if [ "$SCORE" -eq 0 ]; then
        printf " \033[31m%8d\033[0m" "$SCORE"
        FAILS=$((FAILS + 1))
        FAIL_SEEDS="$FAIL_SEEDS $i"
    else
        printf " %8d" "$SCORE"
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
printf "total:  %d   (150case換算: %d)\n" "$TOTAL" "$((AVG * 150))"
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
    echo "per150: $((AVG * 150))"
    echo "min:    $MIN"
    echo "max:    $MAX"
    echo "fails:  $FAILS"
    [ -n "$FAIL_SEEDS" ] && echo "fail_seeds:$FAIL_SEEDS"
    echo "tles:   $TLES"
    [ -n "$TLE_SEEDS" ] && echo "tle_seeds:$TLE_SEEDS"
} >> "$SCOREFILE"

exit 0
