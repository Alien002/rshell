#!/bin/sh

echo "Tests for rshell:"

echo "Test 1: echo A"
echo A

echo "Test 2: ls -a"
ls -a

echo "Test 3: touch touch.cpp"
touch touch.cpp

echo "Test 3.5: ls -a"
ls -a

echo "Test 4: rm touch.cpp"
rm touch.cpp

echo "Test 4.5: ls -a"
ls -a

echo "Test 5: mkdir idk"
mkdir idk

echo "Test 5.5: ls -a"
ls -a

echo "Test 6: rm -f idk"
rmdir idk

echo "Test 6.5: ls -a"
ls -a



echo "so far..."
