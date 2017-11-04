#!/bin/sh

echo "Commented Command Tests for rshell:"

echo "Test 1: echo test 1 # COMMENTSSSSSS"
echo test 1 # COMMENTSSSSSS

echo "Test 2: echo test 2 #COMMENTS NO SPACE AFTER #"
echo test 2 #COMMENTS NO SPACE AFTER #

echo "Test 3: echo hi; echo bye # comment again"
echo hi; echo bye # comment again

echo "Test 4: ls && echo hello #COMMENT HERE echo bye EVERYTHING AFTER # SHOULD NOT WORK"
ls && echo hello #COMMENT HERE echo bye EVERYTHING AFTER # SHOULD NOT WORK


echo "May be more tests"