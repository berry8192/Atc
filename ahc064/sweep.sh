#!/bin/bash
# Usage: bash sweep.sh PARAM v1 v2 v3 ...
# Compiles D.cc with -DPARAM=value, runs 100 seeds, reports avg.
PARAM=$1
shift
echo "Sweeping $PARAM"
for v in "$@"; do
    g++ -O2 -std=c++17 -D${PARAM}=${v} -o d_sweep.out D.cc 2>/dev/null || {
        echo "  $PARAM=$v: compile fail"
        continue
    }
    TOTAL=0
    FAILS=0
    for i in $(seq 0 99); do
        IDX=$(printf "%04d" $i)
        ./d_sweep.out < external_tools/in/$IDX.txt > /tmp/sweep_out.txt 2>/dev/null
        S=$(./external_tools/target/release/vis external_tools/in/$IDX.txt /tmp/sweep_out.txt 2>/dev/null | grep -oE "Score = [0-9]+" | awk '{print $3}')
        S=${S:-0}
        [ "$S" -eq 0 ] && FAILS=$((FAILS+1))
        TOTAL=$((TOTAL+S))
    done
    AVG=$((TOTAL / 100))
    printf "  %s=%-8d avg=%d total=%d fails=%d\n" "$PARAM" "$v" "$AVG" "$TOTAL" "$FAILS"
done
rm -f d_sweep.out
