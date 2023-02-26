DATE=`date '+%Y%m%d%H%M%S'`
mkdir ../test_results/${DATE}
sleep 1
CORES=20
START=0
END=2999
for ((i=START; i<=END; i++)); do
    i4=$(printf "%04d" $i)
    cargo run --release --bin tester ../a.out < ../testcases/${i4}.txt 1> ../test_results/${DATE}/${i4}.txt 2>> ../test_results/${DATE}/${i4}_score.txt &
    echo ${i4}" done"

    if [[ $(jobs -r -p | wc -l) -ge ${CORES} ]]; then
        wait -n # 最も古いプロセスが終了するのを待機する
    fi
done
sleep 1

for ((i=START; i<=END; i++)); do
    i4=$(printf "%04d" $i)
    sed -n '$p' ../test_results/${DATE}/${i4}_score.txt | sed -e 's/.*= //; s/ //g' >> ../test_results/${DATE}/_${DATE}score_sum.txt
done