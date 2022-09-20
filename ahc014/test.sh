for i in `seq -f '%04g' 1 1`
do
  echo "$i.txt"
  ./a.out &
  cat "testcases/$i.txt"
done