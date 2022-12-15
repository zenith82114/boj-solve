#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 {problem number}"
	exit 1
fi

SRC="src/$1.cpp"

if [ ! -f $SRC ]; then
    echo "$SRC does not exist!"
    exit 1
fi
if [ ! -f "./input.txt" ]; then
    echo "input.txt does not exist!"
    exit 1
fi

echo "Compiling $SRC..."
g++-11 -std=c++17 -Wall -O3 $SRC -o solve

echo "Running..."
echo -e "================================"
./solve < input.txt
echo -e "\n================================"
rm solve
