#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 {problem number}.cpp"
	exit 1
fi
if [ ! -f "$1" ]; then
    echo "$1 does not exist!"
    exit 1
fi
if [ ! -f "./input.txt" ]; then
    echo "input.txt does not exist!"
    exit 1
fi

echo "Compiling $1..."
g++ -std=c++17 -Wall -O3 $1 -o solve

echo "Running..."
echo -e "================================"
./solve < input.txt
echo -e "\n================================"
rm solve
