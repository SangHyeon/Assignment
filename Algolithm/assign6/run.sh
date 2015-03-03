for((i=1; i<8; i++)); do
  echo testcase$i
  ./a.out testcase$i.txt
  echo ' '
done
