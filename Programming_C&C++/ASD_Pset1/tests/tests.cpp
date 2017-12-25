#include "../application/application.cpp"
#include "time.h"

typedef BinaryTree<int> _ints_BinTree;


int main( int argc, char* argv[] ){
    int array_length( argc - 1 );
    int *array((int *) calloc(array_length, sizeof(int)));
    for (int i = 0; i < array_length; i++){
        array[i] = atoi( argv[ 1 + i ] );
    }

    _ints_BinTree T1( true );
    for (int i = 0; i < array_length; i++){
        T1.insert(array[i]);
    }
    T1.tree();
    T1.tree_rebalance(T1.root());
    T1.tree();
//    T1.values();

    return 0;
}
