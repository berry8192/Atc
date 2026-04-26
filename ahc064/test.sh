#!/bin/bash
# Usage: bash test.sh [num_seeds] [binary]
#   num_seeds: how many seeds (default 100)
#   binary:    which executable to test (default b.out)

NUM=${1:-100}
BIN=${2:-b.out}
OUTDIR=$(date +"%Y%m%d%H%M%S")
mkdir -p "$OUTDIR"

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

# header for compact table
printf "    "
for c in $(seq 0 9); do printf " %5d" "$c"; done
echo

for i in $(seq 0 $((NUM - 1))); do
    IDX=$(printf "%04d" $i)
    FILE="external_tools/in/$IDX.txt"
    OUTFILE="$OUTDIR/$IDX.txt"
    ./"$BIN" < "$FILE" > "$OUTFILE" 2>/dev/null
    SCORE=$("$VIS" "$FILE" "$OUTFILE" 2>/dev/null | grep -oE "Score = [0-9]+" | awk '{print $3}')
    SCORE=${SCORE:-0}

    # row label every 10 seeds
    if [ $((i % 10)) -eq 0 ]; then
        printf "%3d:" "$i"
    fi
    # red zeroes, dim normal
    if [ "$SCORE" -eq 0 ]; then
        printf " \033[31m%5d\033[0m" "$SCORE"
        FAILS=$((FAILS + 1))
        FAIL_SEEDS="$FAIL_SEEDS $i"
    else
        printf " %5d" "$SCORE"
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

{
    echo "---"
    echo "avg:    $AVG"
    echo "total:  $TOTAL"
    echo "min:    $MIN"
    echo "max:    $MAX"
    echo "fails:  $FAILS"
    [ -n "$FAIL_SEEDS" ] && echo "fail_seeds:$FAIL_SEEDS"
} >> "$SCOREFILE"
