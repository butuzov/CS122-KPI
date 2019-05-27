#! /usr/bin/env python3


A = [
    [1,0],
    [1,0],
    [0,1]
]

AR = [
    [1,1,0],
    [0,0,1],
]


print("AxAR = ")
for (row, items) in enumerate(A):
    for (col, item) in enumerate(items):
        print(row, col, item)
