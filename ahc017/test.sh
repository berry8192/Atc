DATE=`date '+%Y%m%d%H%M%S'`
mkdir test_results/${DATE}
sleep 1
for i in {0000..1999}; do
    ./a.out < testcases/${i}.txt > test_results/${DATE}/${i}.txt
done