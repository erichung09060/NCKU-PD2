# Compile Command

```
mkdir results; g++ main.cpp -w && for i in {1..2}; do echo -e "\n[ Test case $i ] "; time ./a.out testcase/corpus_$i.txt testcase/query_$i.txt > results/result_$i.txt; diff testcase/result_$i.txt results/result_$i.txt;  done; rm -r results
```
