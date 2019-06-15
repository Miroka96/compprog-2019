#!/usr/bin/python3

import sys

def decode(a, b):
    counts = [1, b+1]
    potencies = [b, b**2]

    potency = b**2
    i = 1

    while potency < a:
        counts.append(b * counts[i] + 1)
        i += 1
        potency *= b
        potencies.append(potency)

    count = 0
    na = a
    ni = i

    while ni >= 0: 
        while na - potencies[ni] >= 0:
            count += counts[ni]
            na -= potencies[ni]
        ni -= 1
    
    return count

lines = sys.stdin.readlines()

for l in lines:
    arr = l.split(' ')
    a = int(arr[0])
    b = int(arr[1])

factors = []
factor_counts = []
nb = b
sq = int(b**0.5)

if nb % 2 == 0:
    count = 0
    while nb % 2 == 0 and nb > 1:
        count += 1
        nb //= 2
    factors.append(2)
    factor_counts.append(count)

div = 3
while div <= sq and nb > 1:
    count = 0
    if nb % div != 0:
        div += 2
        continue
        
    while nb % div == 0 and nb > 1:
        count += 1
        nb //= div
    factors.append(div)
    factor_counts.append(count)
    div += 2
    
if nb > 1:
    factors.append(nb)
    factor_counts.append(1)

min_count = 100000000000000000000
for f, count in zip(factors, factor_counts):
    c = decode(a, f) // count
    if c < min_count:
        min_count = c

print(int(min_count))