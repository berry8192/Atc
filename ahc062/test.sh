#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
cd "${SCRIPT_DIR}/external_tools" || exit 1

max_seed=9
if [ -n "$1" ]; then
    max_seed=$1
fi

solver="${SCRIPT_DIR}/a.out"
if [ ! -x "${solver}" ]; then
    echo "Solver binary not found or not executable: ${solver}" >&2
    echo "Build first: g++ -std=gnu++17 -O2 -I /home/berry/Atc/ac-library A.cc -o a.out" >&2
    exit 1
fi

cargo build -r --bin vis >/dev/null || exit 1
vis_bin="target/release/vis"

DATE=$(date '+%Y%m%d%H%M%S')
RESULT_DIR="${SCRIPT_DIR}/test_results/${DATE}"
mkdir -p "${RESULT_DIR}"

total=0
count=0
score_file="${RESULT_DIR}/scores.txt"

for i in $(seq 0 "$max_seed"); do
    seed=$(printf "%04d" "$i")
    in_file="in/${seed}.txt"
    out_file="${RESULT_DIR}/${seed}.txt"

    if [ ! -f "${in_file}" ]; then
        echo "Seed ${seed}: input not found (${in_file})"
        continue
    fi

    "${solver}" < "${in_file}" > "${out_file}"
    vis_output=$("${vis_bin}" "${in_file}" "${out_file}")
    score=$(echo "${vis_output}" | awk '/Score/ {print $3; exit}')

    if [ -z "${score}" ]; then
        echo "Seed ${seed}: score parse failed"
        continue
    fi

    echo "Seed ${seed}: ${score}"
    echo "${seed} ${score}" >> "${score_file}"
    total=$((total + score))
    count=$((count + 1))
done

if [ "${count}" -eq 0 ]; then
    echo "No valid cases were scored." | tee -a "${score_file}"
    echo "Results: ${RESULT_DIR}/"
    exit 1
fi

average=$((total / count))
echo "====================" | tee -a "${score_file}"
echo "Seeds: 0-${max_seed} (${count} cases)" | tee -a "${score_file}"
echo "Average: ${average}" | tee -a "${score_file}"
echo "Total: ${total}" | tee -a "${score_file}"
echo "Results: ${RESULT_DIR}/"
