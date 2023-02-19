DATE=`date '+%Y%m%d%H%M%S'`
mkdir ../test_results/${DATE}
sleep 1
for i in {0000..2999}; do
    cargo run --release --bin tester ../a.out < ../testcases/${i}.txt 1> ../test_results/${DATE}/${i}.txt 2>> ../test_results/${DATE}/${DATE}.txt
done