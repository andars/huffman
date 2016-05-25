echo "running tests"
echo

VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log"

for test in build/test_*; do
    echo
    #1> >(sed 's/^/ /')
    if [ -f "$test" ]
    then
        echo "Running $test"
        if $VALGRIND ./$test 2>> tests/test.log
        then
            echo $test PASS
        else
            echo $test FAIL
            echo "---------"
            tail tests/test.log
        fi
    fi
done
echo

