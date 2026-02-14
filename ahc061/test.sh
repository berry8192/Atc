#!/bin/bash

cd external_tools

total=0
count=0
max_seed=99

if [ -n "$1" ]; then
    max_seed=$1
fi

for i in $(seq 0 $max_seed); do
    seed=$(printf "%04d" $i)
    cargo run -r --bin tester ../A < in/${seed}.txt > /dev/null 2> tmp_err.txt
    score=$(grep "Score" tmp_err.txt | awk '{print $3}')

    # 10件ごとに表示
    if [ $(($i % 10)) -eq 9 ] || [ $i -eq $max_seed ]; then
        echo "Seed $seed: $score"
    fi

    total=$((total + score))
    count=$((count + 1))
done

average=$((total / count))
echo "===================="
echo "Tested seeds: 0-$max_seed ($count cases)"
echo "Average: $average"
echo "Total: $total"

rm -f tmp_err.txt
