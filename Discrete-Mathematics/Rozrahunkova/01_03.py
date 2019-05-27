#! /usr/bin/env python3


def undo( A, B ):
    return " ( ( " + B +"^\mathsf{c} \cap{"  + A + "} ) " + " \cup{" + " ( " + B + " \cap{" + A + "^\mathsf{c}} )} ) ";

def minus( A, B ):
    return "( " + A + " \cap " +B+ "\compl )"

def union( A, B ):
    return "( " + A + " \cup " + B + " )"

def simetric(A, B ):
    return union( intersect( f"{A}\compl", B ), intersect( A, f"{B}\compl" ) )

def intersect( A, B ):
    return "( " + A + " \cap " + B + " )"

#print( union( minus( "A", "X" ), intersect( "A", "B" ) ) )
#print( simetric( union( minus( "A", "X" ), intersect( "A", "B" ) ), "C") )

print( )

# print( minus( undo( "B", undo( "B",  "A" )), "B") )
