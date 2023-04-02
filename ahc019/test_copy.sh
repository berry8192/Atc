DATE=`date '+%Y%m%d%H%M%S'`
mkdir ../test_results/${DATE}
sleep 1
CORES=20
START=0
END=19
for ((i=START; i<=END; i++)); do
    i4=$(printf "%04d" $i)
    ../a.out < in/${i4}.txt 1> ../test_results/${DATE}/${i4}.txt &
    echo ${i4}" out"

    if [[ $(jobs -r -p | wc -l) -ge ${CORES} ]]; then
        wait -n # 最も古いプロセスが終了するのを待機する
    fi
done
sleep 1

for ((i=START; i<=END; i++)); do
    i4=$(printf "%04d" $i)
    cargo run --release --bin vis in/${i4}.txt ../test_results/${DATE}/${i4}.txt 1>> ../test_results/${DATE}/${i4}_score.txt &
    echo ${i4}" vis"

    if [[ $(jobs -r -p | wc -l) -ge ${CORES} ]]; then
        wait -n # 最も古いプロセスが終了するのを待機する
    fi
done
sleep 1

for ((i=START; i<=END; i++)); do
    i4=$(printf "%04d" $i)
    sed -n '$p' ../test_results/${DATE}/${i4}_score.txt | sed -e 's/.*= //; s/ //g' >> ../test_results/${DATE}/_${DATE}score_sum.txt
done