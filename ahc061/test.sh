#!/bin/bash

cd external_tools

max_seed=9
if [ -n "$1" ]; then
    max_seed=$1
fi

DATE=$(date '+%Y%m%d%H%M%S')
RESULT_DIR="../test_results/${DATE}"
mkdir -p "${RESULT_DIR}"

total=0
count=0
score_file="${RESULT_DIR}/scores.txt"

for i in $(seq 0 $max_seed); do
    seed=$(printf "%04d" $i)
    cargo run -r --bin tester ../a.out < in/${seed}.txt > "${RESULT_DIR}/${seed}.txt" 2> tmp_err.txt
    score=$(grep "Score" tmp_err.txt | awk '{print $3}')
    echo "Seed ${seed}: ${score}"
    echo "${seed} ${score}" >> "${score_file}"
    total=$((total + score))
    count=$((count + 1))
done

average=$((total / count))
echo "====================" | tee -a "${score_file}"
echo "Seeds: 0-${max_seed} (${count} cases)" | tee -a "${score_file}"
echo "Average: ${average}" | tee -a "${score_file}"
echo "Total: ${total}" | tee -a "${score_file}"
echo "Results: ${RESULT_DIR}/"

rm -f tmp_err.txt
