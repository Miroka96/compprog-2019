#!/usr/bin/python3

import sys

lines = sys.stdin.readlines()
for l in lines:
    numbers = l.split(" ")
    operations = int(numbers[0]) * int(numbers[1]) - 1
    if operations < 0:
        operations = 0
    print(operations)
