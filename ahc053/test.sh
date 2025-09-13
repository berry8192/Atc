##### WDN用

START=0
END=99
for ((i=START; i<=END; i++)); do
    i4=$(printf "%04d" $i)
    ./a.out < external_tools/in/${i4}.txt >> log.csv
    echo ${i4}" out"
done