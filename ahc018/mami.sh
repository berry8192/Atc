for i in {0000..2999}; do
    ./a.out < testcases/${i}.txt >> mami.csv
done