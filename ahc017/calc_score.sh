for i in {0000..0002}; do
    cat testcases/${i}.txt test_results/$1/${i}.txt > tmp.txt
    ./a.out < tmp.txt >> calc.txt
done