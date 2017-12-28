#!/usr/bin/env python3

def el(n):
    return 1.0/((n+1)+2)**(2.0*(n+1.0))

def el2(n):
    return 1.0/(n +2)**(2.0*n)

sum_value = float(0.0);

for x in range(1,3):
    _x = el(x);
    #print( _x <= 0.001, _x)
    sum_value+=el2(float(x));
    print( x, 'is', el2(float(x)))

print(sum_value)
