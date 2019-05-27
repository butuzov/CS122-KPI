#!/usr/bin/env python3
n = float(6);
s = float(2);

result = 2 / (s**(2*n+1) * (2*n+1) * (1-(1/(s**2))) );
print(0.0001 > result, result);



def el(n):
    x = .5;
    return  ( x**(2.0 * n - 1.0) ) / (2.0 * n - 1.0)
sum_value = float(0.0);

for x in range(1,7):
    sum_value += el(x);
    #print(x, 'is', el(x)  );
    b = 2*x-1
    print( f" \dfrac{{1}}{{{b} \cdot 2^{b} }}   " )

#(0.43429448)
print((sum_value*2.0)*0.43429448);
