#!/bin/bash

dashes=-------------------------------------------------------

if [[ ! -f ./bin/bugworld_test ]]
then
	echo "Test suite not found."
	exit 1
fi

if valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./bin/bugworld_test;
then
	echo $dashes
	echo "ALL TESTS PASSED. VALGRIND OK."
	exit 0
else
	echo $dashes
	echo "SOME TESTS FAILED."
	exit 1
fi
