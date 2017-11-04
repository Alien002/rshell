#!/bin/sh

echo "Multi-Command Tests for rshell:"

echo "Simple 2 command tests:"

echo "Testing echo A; echo B"
echo A; echo B

echo "Testing echo A || echo B"
echo A || echo B

echo "Testing echo A && echo B"
echo A && echo B

echo "Testing asdf || echo A"
asdf || echo A

echo "Testing asdf && echo A"
asdf && echo A

echo "More than 2 commands tests:"

echo "Test 1: echo A; echo B; echo C"
echo A; echo B; echo C

echo "Test 2: echo A && echo B && echo C"
echo A && echo B && echo C

echo "Test 3: echo A || echo B || echo C"
echo A || echo B || echo C

echo "Test 4: echo A; echo B || echo C"
echo A; echo B || echo C

echo "Test 5: echo A || echo B; echo C"
echo A || echo B; echo C

echo "Test 6: echo A; echo B && echo C"
echo A; echo B && echo C

echo "Test 7: echo A && echo B; echo C"
echo A && echo B; echo C

echo "Test 8: echo A; echo B || echo C"
echo A; echo B || echo C

echo "Test 9: echo A || echo B && echo C"
echo A || echo B && echo C

echo "Test 10: echo A && echo B || echo C"
echo A && echo B || echo C

echo "Other cases besides echo:"

echo "Test 11: echo \"||\" && echo \"&&\" && echo \";\""
echo "||" && echo "&&" && echo ";"

echo "Test 12: touch file.txt; ls -a; rm file.txt && ls -a"
touch file.txt; ls -a; rm file.txt && ls -a

echo "MAY BE MORE"

