START=0
END=1999
for ((i=START; i<=END; i++)); do
    i4=$(printf "%04d" $i)
    ./a.out < external_tools/in/${i4}.txt >> D.txt
done
