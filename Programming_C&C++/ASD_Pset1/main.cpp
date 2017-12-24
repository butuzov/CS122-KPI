#include "application.cpp"
#include "time.h"

typedef BinaryTree<int> _ints_BinTree;

auto load_ints_rand(_ints_BinTree* tree, int limit) -> void;
auto load_fix_harryPotter(_ints_BinTree* tree) -> void;
auto load_ints_list(_ints_BinTree* tree) -> void;


int main(){
    _ints_BinTree T1;
    T1._balanceable = true;

    load_ints_rand(&T1, 26);
    // load_ints_list(&T1);
    // load_fix_harryPotter(&T1);
    std::cout << std::endl;

    // T1.is_node_balanced(T1.find(50));
    // T1.is_node_balanced(T1.root());


    T1.tree();
    T1.tree_rebalance(T1.root());
    T1.tree();
    T1.tree_rebalance(T1.root());
    T1.tree();
    T1.tree_rebalance(T1.root());
    T1.tree();
    T1.tree_rebalance(T1.root());
    T1.tree();

    // T1.rotate_right(T1.root());

    T1.values();


    std::cout << std::endl;



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
            array[i++] = nodeRandomValue;
            tree->insert( nodeRandomValue );
        }
    }

    std::string array_str("R {");
    for (int i; i < limit; i++){
        array_str += std::to_string( array[i] ) + ( i == (limit-1) ? "": "," );
    }
    std::cout << array_str + "}\n" ;

    free(array);
}

auto load_ints_list(_ints_BinTree* tree) -> void {

    // tree is perfectly balanced.
    int array[] = {23,40,56,34,13,55,6,91,46,99,12,86,81,33,59,76,95,21,25,39,20,52,37,96,63,22};

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

    //tree->tree();
    tree->rotate_left( tree->find( 10 ) );

    //tree->tree();
    tree->rotate_right( tree->find( 11 ) );

    //tree->tree();
    tree->rotate_right( tree->find( 25 ) );
    tree->rotate_left( tree->find( 17 ));
    tree->rotate_right( tree->find( 23 ));

   // tree->rotate_right( tree->find( 23 ));

    // tree->debug(tree->find(16));
    // tree->debug(tree->find(17));
    // tree->debug(tree->find(23));

}
