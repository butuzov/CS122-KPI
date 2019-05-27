#!/usr/bin/env python3

def el(x):
    return 1.0 / ( ( 4.*x + 3. ) * 3. ** ( 4.*x + 3. ) )

summa = 0.0

for x in range(0,1):
    summa += el(float(x));
    print(el(float(x)))

print(summa)
