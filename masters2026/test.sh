#!/bin/bash
# Usage: bash test.sh [problem] [max_seed]
# Example: bash test.sh A 9    (seeds 0-9, 10 cases)
# Example: bash test.sh A 99   (seeds 0-99, 100 cases)
# Example: bash test.sh A      (all 100 seeds)

PROBLEM=${1:-A}
MAX_SEED=${2:-99}
SCORER=./external_tools/target/release/score
IN_DIR=./external_tools/in${PROBLEM}

if [ ! -f "$SCORER" ]; then
    echo "Building scorer..."
    cd external_tools && cargo build --release --bin score 2>/dev/null && cd ..
fi

g++ -O2 -std=c++17 -o a.out ${PROBLEM}.cc
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

mkdir -p out${PROBLEM}

total=0
count=0
wa=0

for seed in $(seq -w 0 $MAX_SEED); do
    seed4=$(printf "%04d" $((10#$seed)))
    infile="${IN_DIR}/${seed4}.txt"
    outfile="out${PROBLEM}/${seed4}.txt"

    if [ ! -f "$infile" ]; then continue; fi

    ./a.out < "$infile" > "$outfile" 2>/dev/null
    result=$($SCORER "$infile" "$outfile" 2>/dev/null)
    score=$(echo "$result" | grep "Score" | awk '{print $NF}')

    if echo "$result" | grep -q "Not all\|Invalid\|error\|Out of range\|Parse error"; then
        echo "seed=$seed4 WA: $result"
        wa=$((wa + 1))
    else
        total=$((total + score))
        count=$((count + 1))
    fi
done

if [ $count -gt 0 ]; then
    avg=$((total / count))
    echo "Problem $PROBLEM: $count cases, WA=$wa, total=$total, avg=$avg"
else
    echo "Problem $PROBLEM: No valid results (WA=$wa)"
fi
