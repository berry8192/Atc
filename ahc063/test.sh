#!/bin/bash
# Usage: bash test.sh [num_seeds]
# Runs c.out on seeds 0..(num_seeds-1), saves stdout to timestamped dir, prints scores + average

NUM=${1:-1000}
OUTDIR=$(date +"%Y%m%d%H%M%S")
mkdir -p "$OUTDIR"
echo "Output dir: $OUTDIR"

SCOREFILE="$OUTDIR/scores.txt"
TOTAL=0
for i in $(seq 0 $((NUM - 1))); do
    FILE=$(printf "external_tools/in/%04d.txt" $i)
    OUTFILE=$(printf "$OUTDIR/%04d.txt" $i)
    ./c.out < "$FILE" > "$OUTFILE" 2>/tmp/_ahc_score
    SCORE=$(cat /tmp/_ahc_score)
    echo "seed $i: $SCORE" | tee -a "$SCOREFILE"
    TOTAL=$((TOTAL + SCORE))
done
echo "---" | tee -a "$SCOREFILE"
echo "avg: $((TOTAL / NUM))" | tee -a "$SCOREFILE"
