if ! test -d ~/hw7/results ; then mkdir ~/hw7/results; fi
if ! test -d ~/hw7/answer ; then mkdir ~/hw7/answer; fi
cp -r /home/share/hw7/* ~/hw7/answer
make -k clean all -C ~/hw7


for i in {1..4}; do
	for k in {1..3}; do
		if (( $i == 1 )) && (( $k <= 2 )); then
			continue;
		fi
		corpus=~/hw7/answer/testcase$i/corpus$i
		query=~/hw7/answer/testcase$i/query$i
		answer=~/hw7/answer/testcase${i}/result_${k}
		result=~/hw7/results/result${i}_${k}
		echo -n "testcase $i, k = $k : "
		duration=$( { /usr/bin/time -f "%E" ./hw7 $corpus $query $k > $result; } 2>&1) 
		diff $result $answer >> /dev/null
		if (( $? != 0 )); then
			echo "WA, time(real) : $duration"
			echo "diff ./results/result${i}_${k} ./answer/testcase${i}/result_${k}"
		else
			echo "AC, time(real) : $duration"
		fi

	done
done
