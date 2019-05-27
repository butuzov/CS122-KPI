#!/usr/bin/env python3.7
from collections import OrderedDict
from copy import copy

class Matrix(object):

    def __init__(self, sequence):

        """creating matix"""
        self.matrix = OrderedDict({
            letter: {
                letter:None for letter in sequence
            } for letter in sequence
        })

        "free cells lookups"
        self.allocs = {(row, col):0
            for key, row in enumerate(sequence)
                for col in sequence[key+1:]
        }

        # eye update
        [self.matrix[letter].update({letter: 0})
             for letter in sequence]


    def add(self, statment):
        assert len(statment) == 3

        a, expr, b = statment

        if expr not in ("=", "<", ">"):
            raise NotImplemented("Only =, <, > are implemented")

        ab, ba = 0, 0

        if expr == ">":
            ab, ba =  1, -1

        if expr == "<":
            ab, ba = -1, 1

        print("1", statment, a, b)
        if (self.matrix[a][b] and self.matrix[a][b] != ab) \
                or (self.matrix[b][a] and self.matrix[b][a] != ba) :
            raise ValueError("Cardinality error: value set")

        # print("changing", a, b, statment)
        self.matrix[a][b], self.matrix[b][a], = ab, ba


        for alloc_key in [key for key in ((a,b), (b,a)) if key in self.allocs]:
            del self.allocs[alloc_key]



        return self

    def at(self, a, b):
        return self.matrix[a][b]

    def done(self):

        while len(self.allocs) > 0:

            changed = False
            print("ALLOCS", self.allocs.keys())
            for key in list(self.allocs.keys()):
                print("")

                rows = [ k for k in [ (key[0], col) for col in self.matrix[key[0]]
                            if col != key[0]] if k not in self.allocs]

                # print("rows", rows)

                cols = [ k for k in [ (key[1], col) for col in self.matrix
                            if col != key[1]] if (k[1], k[0]) not in self.allocs]

                # print("cols", cols)
                # print()
                # print("NEW KEY", key)
                # print('rows', rows)
                # print('cols', cols)
                pairs = [ (r, c) for r in rows for c in cols if r[1] == c[1]]

                print('pairs', pairs)
                print('KEY', key)

                print(f"{self}")


                if len(pairs) == 0:
                    self.allocs[key] += self.allocs[key]+1
                    continue


                for pair in pairs:

                    comparison = self.at(*pair[0]), self.at(*pair[1])

                    # comparison impossible
                    if comparison in ((-1,-1), (1,1)):
                        continue

                    # default case include  (0,0)
                    do = "="

                    # values are equivalent
                    if comparison in ((0, 1), (-1, 1), (-1, 0)):
                        do = "<"

                    if comparison in ((1, 0), (1, -1), (0, -1)):
                        do = ">"

                    expr = "{1}{0}{2}".format(do, pair[0][0], pair[1][0])
                    changed = True
                    print( f"Matching {key}")
                    print(expr, pair)
                    print('P1', pair[0], self.at(*pair[0]))
                    print('P2', pair[1], self.at(*pair[1]))
                    self.add(expr)
                    break;
                    # print("NM\n", f"{self}")


            if not changed:
                break


    def _cell(self, x):
        if x is None:
            return self._cell(" ")
        return f"{x:^5}"

    def __repr__(self):
        string = self._cell("") + "|"
        string += "|".join( map(self._cell, list( self.matrix ) ))
        string += "\n"
        string += "_"*len(self.matrix)*7 + "\n"

        for row in self.matrix:
            string += self._cell(row) + "|"
            string += "|".join( map(self._cell, list( self.matrix[row].values() ) ))
            string += "\n"
            string += "-"* (len(self.matrix)*7) + "\n"

        return string

m=Matrix("abcd")
# for exp in ["a>b", "a<c", "d>c"]:
for exp in ["a>b", "a<c", "d>c"]:
    m.add(exp)



m.done()

print("finalform"),
print(m)
