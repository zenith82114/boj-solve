#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 [problem number]"
	exit 1
fi
if [ ! -f "./input.txt" ]; then
    echo "input.txt does not exist!"
    exit 1
fi

echo "Compiling $1.cpp..."
g++ -Wall -O3 $1.cpp -o solve

echo "Running Problem #$1..."
echo -e "================================"
./solve < input.txt
echo -e "\n================================"
rm solve
