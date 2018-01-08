#include <iostream>               /* io stream            */ 
#include <string>                 /* string               */ 
#include <fstream>                /* files stream         */
#include <sstream>                /* strings stream       */
#include "binary-tree.cpp"
#define DEBUG false
#include "view.cpp"

// Type Definition.
typedef std::tuple<int, std::string> Mandragora;

// Overloading Compare Operator
bool operator < ( Mandragora a, Mandragora b );

void loadHarryPotterData(BinaryTree<Mandragora>* Tree);

int main(){
    
    BinaryTree<Mandragora> Tree;
    loadHarryPotterData(&Tree);
    
    std::cout << "Initial Tree\n";
    Tree.tree();

    std::cout << "Deleting Non-Terminal node (23) \n";
    Tree.remove(Tree.find(23));
    Tree.tree();


    std::cout << "Insert New node (23) witha different value. \n";
    Tree.insert(std::make_tuple(23, std::string("Rufus Scrimgeour") ));
    Tree.tree();

    
    std::cout << "Left Rotation of node 20 \n";
    Tree.rotate_left(Tree.find(20));
    Tree.tree();
    
    std::cout << "Right Rotation of node 25 \n";
    Tree.rotate_right(Tree.find(25));
    Tree.tree();


    std::cout << "Right Left (Double Right) Rotation of node 28 \n";
    Tree.rotate_right_left(Tree.find(28));
    Tree.tree();

    std::cout << "Left Right (Double Left) 8 \n";
    Tree.rotate_left_right(Tree.find(8));
    Tree.tree();

    std::cout << "Balancing tree manually \n";

    Tree.rotate_right(Tree.find(8));

    Tree.rotate_right(Tree.find(20));
    Tree.rotate_left_right(Tree.find(20));

    Tree.tree();

    return 0;
}

/**
 * Loads Data From File.
 */
void loadHarryPotterData(BinaryTree<Mandragora>* Tree){
    std::ifstream source( "binarytree.txt" );

    if ( !source.good() ){
        throw;
    }

    std::string line;

    while( std::getline( source, line ) ){
        int space_position( line.find(" ") );
        if ( space_position == -1 ) {
            continue;
        }
        // Inserting node to Tree
        Tree->insert(
            std::make_tuple(
                // Node Value
                std::stoi( line.substr( 0, space_position ) ),
                // Character Name
                line.substr(space_position+1)
            )
        );

    }
    source.close();
}

/**
 *  Operator Overload Implementation
 *  @used in Tree::insert
 */
bool operator < ( Mandragora a, Mandragora b ){
    if ( std::get<0>(a) != std::get<0>(b) ) {
        return std::get<0>(a) < std::get<0>(b);
    }
    return false;
}


/**
 * T value to Int convertor.
 */
template <>
int BinaryTree<Mandragora>::value(BinaryTree<Mandragora>::Node* node) {
    if (node) { 
        return std::get<0>(node->data);
    } else {
        return 0;
    }
}