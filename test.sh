#!/bin/bash
echo > test-report

test() {
    files=($1)
    n=0
    passed=0

    for f in ${files[@]}; do
        let n++
        file=$(basename $f)


        echo -e "\nTesting $file..." >> test-report
        ./bin/tpcc < $f 2>> test-report
        feedback=$PIPESTATUS

        if [ "$feedback" = "$2" ]; then
            let passed++
			res="OK"
            printf "(%02d/%02d) - %-35s Expecting: %s | Got: %s | \033[0;32m%s\033[0;37m\n" $n ${#files[@]} "Testing $file..." $2 $feedback $res
        else
			res="NO"
            printf "(%02d/%02d) - %-35s Expecting: %s | Got: %s | \033[0;31m%s\033[0;37m\n" $n ${#files[@]} "Testing $file..." $2 $feedback $res
		fi
        echo "return : ${feedback}" >> test-report

    done

    if [ $passed -eq ${#files[@]} ]; then
        echo -e "\033[0;32m$passed tests out of ${#files[@]} passed! \033[0;37m"
    elif [ $passed = "0" ]; then
        echo -e "\033[0;31m$passed tests out of ${#files[@]} passed! \033[0;37m"
    else
        echo -e "\033[0;33m$passed tests out of ${#files[@]} passed! \033[0;37m"
    fi
}

make

echo "==================================GOOD====================================" | tee -a test-report
test "test/good/*.tpc" 0

echo "===============================SYNTAX-ERROR===============================" | tee -a test-report
test "test/syn-err/*.tpc" 1

echo "==============================SEMANTIC-ERROR==============================" | tee -a test-report
test "test/sem-err/*.tpc" 2

echo "=================================WARNING==================================" | tee -a test-report
test "test/warn/*.tpc" 0

echo "Done."