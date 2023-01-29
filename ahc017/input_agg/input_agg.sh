echo "N, M, M/N, D, K, M/D, dist_sum" > input_agg_log.csv
sleep 1
for i in {0000..0099}; do
    ./a.out < ../testcases/${i}.txt >> input_agg_log.csv
done