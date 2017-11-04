#!/bin/sh

echo "Exit Tests for rshell:"

echo "Test 1: -q"
-q

./a.out

echo "Test 2: echo hello; echo bye && -q"
echo hello; echo bye && -q

./a.out


echo "MAY BE MORE"

