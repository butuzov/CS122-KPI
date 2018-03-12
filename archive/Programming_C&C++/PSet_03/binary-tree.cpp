/****** DGeneral Creation *************************************************/
#include "binary-tree.hpp"

// Class Constructor
template <typename T>
BinaryTree<T>::BinaryTree(){
    root = nullptr;
}

/****** Destruction *******************************************************/

// Class Destructor
template <typename T>
BinaryTree<T>::~BinaryTree(){
  destroy();
}

// Destroys Tree Node.
template <typename T>
void BinaryTree<T>::destroy( BinaryTree<T>::Node *node ) {
    if ( node->left != NULL ){
        destroy(node->left);      // First Left Branch
    }

    if ( node->right != NULL ){
        destroy( node->right );   // Second Right Branch
    }

    delete node;                  // Finally destroy ActualRoot Node.
}

// Initiate tree destroy starting from root node.
template <typename T>
void BinaryTree<T>::destroy(){
  if ( root != NULL ){
      destroy(root);
  }
}


/****** Creating *********************************************************/

// Insert data bootstrap
template <typename T>
void BinaryTree<T>::insert(T item){

    if ( root ==  NULL ){
        // new node.
        root = new Node( item );
        return;
    }

    return insert(item, root);
}

// Insert data to particulare node.
template <typename T>
void BinaryTree<T>::insert(T item, BinaryTree<T>::Node *node ){

    Node *iNode;
    iNode = ( item < node->data ? node->left : node->right );

    if ( iNode != NULL ) {
        insert(item, iNode);
        return;
    }

     // comparison using overloaded operators
     // its important not to forget to overload comparison operators
     // if we deal with some custom structure.
    (
      item < node->data
        ? node->left
        : node->right
    ) = new Node(item);
}

/****** Show tree *******************************************************/

template <typename T>
void BinaryTree<T>::showtree(){
    if ( root != NULL ){
        showtree(root);
    }
}

template <typename T>
void BinaryTree<T>::showtree(BinaryTree<T>::Node *node){

    if ( node->left != NULL  ){
      showtree( node->left );
    }

    std::cout << view( node->data ) << std::endl;;

    if ( node->right != NULL  ){
        showtree( node->right );
    }
}
