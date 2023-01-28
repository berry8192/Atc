echo "N, M, M/N, D, K, M/D, maxW" > input_agg.csv
sleep 1
for i in {0000..1999}; do
    ./a.out < testcases/${i}.txt >> input_agg.csv
done