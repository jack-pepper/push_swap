#!/bin/bash

# Path to the program to be tested
PROGRAM="./push_swap"

# Array of valid test cases
valid_inputs=("0"\
		"123"\
		"0 9"\
		"-2 -5"\
		"3 -8"\
		"5 8 9 4 2 3 7"\
		"5 -8 -9 -4 -2 -3 -7"\
		"-5 8 -9 4 -2 -3 7"\
		"1 23 456"\
		"123 45 456 8"\
		"-123 456 -1147483647 1147483646"\
		"2147483647 -2147483648" \
		"-2147483648 2147483647" \
	)

# Array of invalid test cases (less than two arguments)
invalid_inputs=("" \
		" " \
		"m" \
		"-" \
		"abc" \
		"123 abc"\
		"123 1b3" \
		"123 12.34"\
		"123 456 - 789"\
		"123 -56.78"\
		"123 456 7*9"\
		"123 4-6 789"\
		"123 456 -2147483649"\
		"123 456 2147483648"\ 
	)

# Color codes for green (passed) and red (failed)
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No color (reset)

# Test for invalid inputs (less than two arguments)
for input in "${invalid_inputs[@]}"; do 
	$PROGRAM $input
    if [ $? -eq 0 ]; then
        echo -e "Test ${RED}FAILED${NC} for invalid input: $input (should not be accepted)"
    else
        echo -e "Test ${GREEN}PASSED${NC} for invalid input: $input (correctly rejected)"
    fi
    echo " "
done

# Test valid inputs (should pass with two arguments)
for input in "${valid_inputs[@]}"; do
	$PROGRAM $input
    if [ $? -ne 0 ]; then
        echo -e "Test ${RED}FAILED${NC} for valid input: $input"
    else
        echo -e "Test ${GREEN}PASSED${NC} for valid input: $input"
    fi
    echo " "
done

