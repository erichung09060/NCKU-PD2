if ! test -d ~/hw6/results ; then mkdir ~/hw6/results; fi
if ! test -d ~/hw6/answer ; then mkdir ~/hw6/answer; fi
cp -rf /home/share/hw6/* ~/hw6/answer
make -k clean all -C ~/hw6
for i in {1..5}; do
	for k in {1..3}; do
		if (( $i == 1 )) && (( $k <= 2 )); then
			continue;
		fi
		corpus=~/hw6/answer/testcase$i/corpus$i
		query=~/hw6/answer/testcase$i/query$i
		answer=~/hw6/answer/testcase${i}/result_corpus${i}_query${i}_${k}
		result=~/hw6/results/result${i}_${k}
		echo -n "testcase $i, k = $k : "
		duration=$( { /usr/bin/time -f "%E" ./hw6 $corpus $query $k > $result; } 2>&1) 
		diff $result $answer >> /dev/null
		if (( $? != 0 )); then
			echo "WA, time(real) : $duration"
			echo "diff ./results/result${i}_${k} ./answer/testcase${i}/result_corpus${i}_query${i}_${k}"
		else
			echo "AC, time(real) : $duration"
		fi

	done
done
