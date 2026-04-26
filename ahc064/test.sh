#!/bin/bash
# Usage: bash test.sh [num_seeds]
# Runs b.out on seeds 0..(num_seeds-1), uses external vis to score, prints + average.
# Diff from ahc063: ahc064 has no built-in score; we call external_tools/target/release/vis.

NUM=${1:-100}
OUTDIR=$(date +"%Y%m%d%H%M%S")
mkdir -p "$OUTDIR"
echo "Output dir: $OUTDIR"

VIS=external_tools/target/release/vis
if [ ! -x "$VIS" ]; then
    echo "Building visualizer..."
    (cd external_tools && cargo build -r --bin vis) || exit 1
fi

SCOREFILE="$OUTDIR/scores.txt"
TOTAL=0
for i in $(seq 0 $((NUM - 1))); do
    IDX=$(printf "%04d" $i)
    FILE="external_tools/in/$IDX.txt"
    OUTFILE="$OUTDIR/$IDX.txt"
    ./b.out < "$FILE" > "$OUTFILE" 2>/dev/null
    SCORE=$("$VIS" "$FILE" "$OUTFILE" 2>/dev/null | grep -oE "Score = [0-9]+" | awk '{print $3}')
    SCORE=${SCORE:-0}
    echo "seed $i: $SCORE" | tee -a "$SCOREFILE"
    TOTAL=$((TOTAL + SCORE))
done
echo "---" | tee -a "$SCOREFILE"
echo "avg: $((TOTAL / NUM))" | tee -a "$SCOREFILE"
echo "total: $TOTAL" | tee -a "$SCOREFILE"
