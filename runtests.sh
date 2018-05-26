#!/usr/bin/env bash

dashes=-------------------------------------------------------
currentos=`uname`
passed_msg="SUCCESS. All tests passed."
failed_msg="ERROR. Test suite failed. See above output for details."

if [ ! -x ./bin/bugworld_test ]
then
    echo "Test suite not found."
    exit 1
fi

if [ "$currentos" == "Darwin" ]; then
    if ./bin/bugworld_test;
    then
        echo $dashes
        echo "$passed_msg"
        exit 0
    else
        echo $dashes
        echo "$failed_msg"
        exit 1
    fi
fi

if [ "$currentos" == "Linux" ]; then
    if valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./bin/bugworld_test;
    then
        echo $dashes
        echo "$passed_msg"
        exit 0
    else
        echo $dashes
        echo "$failed_msg"
        exit 1
    fi
fi

