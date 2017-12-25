#include "application/application.cpp"
#include "time.h"

typedef BinaryTree<int> _ints_BinTree;

auto load_ints_rand(_ints_BinTree* tree, int limit) -> void;
auto load_fix_harryPotter(_ints_BinTree* tree) -> void;
auto load_ints_list(_ints_BinTree* tree) -> void;


int main(){
    _ints_BinTree T1( true );

    load_ints_rand(&T1, 32);
    //load_ints_list(&T1);

    T1.tree();
    T1.tree_rebalance(T1.root());
    // T1.tree();
    T1.values();
    return 0;
}


auto load_ints_rand(_ints_BinTree* tree, int limit = 32 ) -> void {

    srand( time( NULL ) );

    int *array = ((int*) calloc(limit, sizeof(int)));
    int i;
    while( tree->size() < limit ) {
        _ints_BinTree::Node *SNode;

        int nodeRandomValue( rand() % 99 +1 );
        if ( ! tree->find( nodeRandomValue ) ){
           // std::cout << nodeRandomValue << " ";
            array[i++] = nodeRandomValue;
            tree->insert( nodeRandomValue );
        }
    }

    std::string array_str("\nR {");
    for (int i; i < limit; i++){
        array_str += std::to_string( array[i] ) + ( i == (limit-1) ? "": "," );
    }
    std::cout << array_str + "}\n" ;

    free(array);
}

auto load_ints_list(_ints_BinTree* tree) -> void {

    // tree is perfectly balanced.
   int array[] = { 62,89,54,13,15,25,9,19,53,22,96,69,27,47,26,35,92,21,7,83,84,85,94,42,23,31,0,16,5,81,97,73 };

    // Unlabalanced.
   // int array[] = {5,24,66,17,33,3,62,37,81,99,30,42,51,93,97,71,60,64,87,47,83,35,19,73,90};
    int length  = sizeof(array) / sizeof(int);

    for (int i=0; i < length; i++){
        tree->insert( array[i] );
    }
}



auto load_fix_harryPotter(_ints_BinTree* tree) -> void {

    int array[] = {15,28,25,8,10,29,26,17,11,16,23,4,2,24};
    int length  = sizeof(array) / sizeof(int);

    for (int i=0; i < length; i++){
        tree->insert( array[i] );
    }

    // //tree->tree();
    tree->rotate_right( tree->find( 28 ) );

    // //tree->tree();
    // tree->rotate_right( tree->find( 11 ) );

    // //tree->tree();
    // tree->rotate_right( tree->find( 25 ) );
    // tree->rotate_left( tree->find( 17 ));
    // tree->rotate_right( tree->find( 23 ));

   // tree->rotate_right( tree->find( 23 ));

    // tree->debug(tree->find(16));
    // tree->debug(tree->find(17));
    // tree->debug(tree->find(23));

}
