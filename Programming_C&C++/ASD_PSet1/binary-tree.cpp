#include "binary-tree.hpp"

/****** Construction *******************************************************/
template <typename T>
BinaryTree<T>::BinaryTree() {
    _root        = nullptr;          // Pointer to the root of the tree
    _size        = 0;                // Total tree nodes number automatically?
}

template <typename T>
BinaryTree<T>::BinaryTree(std::vector<T> vec) {
    _root        = nullptr;          // Pointer to the root of the tree
    _size        = 0;                // Total tree nodes number automatically?

    if ( vec.empty() ) 
        return;

    // Quick Tree initiation using vector.
    for (T value : vec){
        insert(value);
    } 
}

/****** Destruction *******************************************************/
template <typename T>
BinaryTree<T>::~BinaryTree(){
    if ( ! _empty() ) {       // If Tree not empty
       _destroy(_root);     // We running destroy tree method for _root
    }
}

/**
 *  Destruction methon, accept pointer to node,
 *  if its not provided will destroy all tree.
 */
template <typename T>
void BinaryTree<T>::_destroy( BinaryTree<T>::Node *node ) {

    // No node - No Destruction.
    if ( ! node  ) {
        return;
    }

    //debug(node);

    if ( NULL != node->top ){
        Node *top = node->top;
        bool isRight = ( top->right == node );

        // NULLing pointer from THIS to TOP/ROOT node
        node->top = nullptr;

        // NULLing pointer to THIS node from TOP/ROOT node
        ( isRight ? top->right : top->left )=nullptr;
    }

    // If Left Node exists
    if ( NULL != node->left ) {
        _destroy(node->left);      // We going to destroy it
    }

    // If Right Node Exists
    if ( NULL != node->right ) {
        _destroy( node->right );
        // We going to destroy it as well!
    }

    // Decreasing Size.
    _size--;

   // debug(node);
    int val = value(node);
    // Finally destroy ActualRoot Node.
    // if ( _root == node ){
    //     _root = nullptr;
    // }
    delete node;

    // std::cout << val << std::endl;
}


/**
 * Return True  if Tree empty.
 *        False if not
 */
template <typename T>
bool BinaryTree<T>::_empty() {
    return _size == 0;
}



/**
 *   Insert data to particulare node or move item down to tree structure.
 */
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::_insert(T item, BinaryTree<T>::Node *root )  {

    // We trying to create node that points to left or right branch
    // of current node - depanding if value if item less or
    // ( greater or equal to node value)
    Node *iNode(item < root->data ? root->left : root->right);

    // In case if leaf node selected, but exists.
    // we going to insert it to right  node, depending if
    // item value greater then root node value , or to left if
    // its less then node value.

    if ( iNode ) {
        return _insert( item, iNode );
    }

    iNode = new Node(item, root); // Creating Node if Leaf not exists.

    // Comparison using overloaded operators
    // its important not to forget to overload comparison operators
    // if we deal with some custom structure.
    ( item < root->data ? root->left : root->right ) = iNode;

    // Increasing Size of the Tree.
    _size++;

    return iNode;
}


/**
 *  Inserts item into tree structure.
 */
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::insert(T item)  {

     // There is no root in this tree
    if ( _empty() ){
        _root = new Node( item );   // So let's create it.
        _size++;                    // and increase size to 1.
        return _root;
    }

    // Or insert item into tree structure.
    return _insert( item, _root );
}

template <>
int BinaryTree<int>::value(BinaryTree<int>::Node* node) {
    if (node) {
        return node->data;
    } else {
        return 0;
    }
}


template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::find( int needle, BinaryTree<T>::Node *heystack ) {

    if ( heystack == NULL ){
        heystack  = _root;
    }

    // match found.
    if ( value( heystack ) == needle) {
        return heystack;
    }

    // Checking node first.
    if ( heystack->left != NULL  && needle < value(heystack) ){
        return find(needle, heystack->left);
    } else if ( heystack->right != NULL && needle > value(heystack) ){
        return find(needle, heystack->right);
    }

    return nullptr;
}


template <typename T>
int BinaryTree<T>::_height(Node* node) {
    if ( node == NULL ){
        return -1;
    }
    return node->height;
}


template <typename T>
void BinaryTree<T>::_update_node_height( BinaryTree<T>::Node *node ) {

    if ( node == NULL ){
        return;
    }

    int height_l( _height( node->left ) ),
        height_r( _height( node->right ) );

    node->height = ( height_l > height_r ? height_l : height_r ) + 1;
}


/**
 * Root Getter.
 */
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::root() {
    return _root;
}


template <typename T>
int BinaryTree<T>::size() {
    return _size;
}


template <typename T>
void BinaryTree<T>::debug( BinaryTree<T>::Node *node  ){

    if ( node == NULL ){
        std::cout << "\nNODE IS NULL\n";
        return;
    }

    std::cout <<  std::string(80, '.') << std::endl;
    std::string s_top("NULL"), s_left("NULL"), s_right("NULL");
    std::string s_node("(" + std::to_string( value( node ) ) + ")");

    if ( node->top ) {
        s_top = "(" + std::to_string( value( node->top ) ) + ")";
    }
    if ( node->left ) {
        s_left = "(" + std::to_string( value( node->left ) ) + ")";
    }
    if ( node->right ) {
        s_right = "(" + std::to_string( value( node->right ) ) + ")";
    }

    int padding;


    padding = 9 +  s_left.size() + (s_top.size()/2);
    std::cout << std::string( padding, ' ' ) << s_top << std::endl;

    padding = s_left.size() + 3 + (s_node.size()/2);
    std::cout << "Debug: " << std::string( padding, ' ' ) << "^" << std::endl;


    std::cout << std::string( 7, ' ' ) << s_left << " < " << s_node << " > " << s_right << std::endl;
}




template <typename T>
bool BinaryTree<T>::_rotate( std::string dir, BinaryTree<T>::Node *node ) {

    //** Function body ********************************************************
    if ( dir != "right" && dir != "left" ) {
        return false;
    }

    bool isRightRotation = ( dir == "right" );

    Node *node_rotated   = node;      // This is node we rotating.
    Node *node_parent    = node->top; // This is parent node of node we rotating

    // Node Is NUll
    if ( node_rotated == NULL ){
        return false;
    }

    // There is nothing to take place of rotated node.

    if ( ( isRightRotation ? node->left : node->right ) == NULL ) {
        return false;
    }

    // Step 1: Left Child (in case of Right Rotation) node become new Root.
    //         Right Child (in case of Left Rotation) node become new Root.
    node =  isRightRotation ? node->left : node->right;


    // Step 2:
    // RightChild of new Root (RightRotation) -> LeftChild of old Root
    if ( true == isRightRotation && node->right != NULL ) {
        node_rotated->left = node->right;
        node->right->top = node_rotated;
    }

    // LeftChild of new Root (LeftRotation)  -> RightChild of old Root
    if ( false == isRightRotation && node->left != NULL ) {
        node_rotated->right = node->left;
        node->left->top = node_rotated;
    }


    // Step 3: Old Root becomes new root RightChild (RightRotation).
    //         Old Root becomes new root LeftChild  (LeftRotation).
   Node *tmp;
   tmp = ( isRightRotation ? node->right : node->left );
   ( isRightRotation ? node_rotated->left : node_rotated->right ) = nullptr;
   ( isRightRotation ? node->right : node->left ) = node_rotated;
   if ( tmp != NULL ) {
       ( isRightRotation ? node_rotated->left : node_rotated->right ) = tmp;
   }

    // Updating pointer to top/parent/root node.
    node_rotated->top = node;


    // Updating Top/Parent/Root node pointer to new Root.

    if ( _root == node_rotated) {
        _root = node;
        node->top = nullptr;
    } else  {
        ( node_parent->left == node_rotated
            ? node_parent->left : node_parent->right ) = node;
        node->top = node_parent;
    }

    // debug(node);
    // debug(node_rotated);

    _update_node_height(node_rotated);
    _update_node_height(node);

    return true;
}

template <typename T>
bool BinaryTree<T>::rotate_left_right( BinaryTree<T>::Node *node ){
    if ( rotate_right( node->right ) ){
        return rotate_left( node );
    }
    return false;
}

template <typename T>
bool BinaryTree<T>::rotate_left_left( BinaryTree<T>::Node *node ){
    return rotate_left_left(node);
}

template <typename T>
bool BinaryTree<T>::rotate_right_left( BinaryTree<T>::Node *node ){
    if ( rotate_left( node->left ) ){
        return rotate_right( node );
    }
    return false;
}

template <typename T>
bool BinaryTree<T>::rotate_right_right( BinaryTree<T>::Node *node ){
    return rotate_right_left(node);
}

template <typename T>
bool BinaryTree<T>::rotate_left( BinaryTree<T>::Node *node ){
    return _rotate( "left", node);
}

template <typename T>
bool BinaryTree<T>::rotate_right( BinaryTree<T>::Node *node ){
    return _rotate( "right", node);
}


template <typename T>
void BinaryTree<T>::remove(BinaryTree<T>::Node *node) {
    if ( node == NULL ){
        return;
    }

    delete shift(node);
}

template <typename T>
void BinaryTree<T>::_cut_top(BinaryTree<T>::Node *node){
    // fail fast.
    if ( ! node->top ){
        return;
    }
    // proceed to nulling.
    if ( node->top->left == node ) {
        node->top->left = nullptr;
    } else {
        node->top->right = nullptr;
    }
    node->top = nullptr;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::shift(BinaryTree<T>::Node *node){
    // Case 1. Node is NULL 
    if ( node == NULL ){
        return node;
    }

    // Case 2. This is Terminal Node.
    if ( node->left == NULL && node->right == NULL ) {
        // Cutting Connection betwean Parent and Child.
        Node *_ex_top = node->top;
        _cut_top(node);
        
        // nulling root in case if this is a root.
        if ( node == _root ){
            _root = nullptr;
        }

        _size--; // decreesing size 
        return node;
    }

    // Case 3. Scenario 1.
    // Removing non-terminal node that doesn't have right child.
    if ( node->left != NULL && node->right == NULL ) {

        Node *_ex_top  = node->top;
        Node *_ex_node = node;

        // Before cutting we need to get idea what branch it was.
        bool isRightNode = _ex_top && _ex_top->right == node;
       
        // Cutting...
        _cut_top(node);
        
        // updating pointer to right node 
        if ( _ex_top ) {
            (isRightNode ? _ex_top->right : _ex_top->left ) = node->left;
        }

        // new root taking palce.
        if ( _ex_node == _root ) {
            _root = node->left;
        }
        
        // new node taking place
        node = node->left;

        // setting pointer to previous parent.
        node->top = _ex_top;

        // nulling pointers or node before deletion.
        _ex_node->left = _ex_node->right = nullptr;

        // decrising size.
        _size--;

        return _ex_node;
    }

    // Case 3. Scenario 2. 
    // Removing non-terminal right node that has no left child.
    if ( node->right != NULL && node->right->left == NULL ) {
        
        Node *_ex_top = node->top;
        Node *_ex_node = node;
        
        // Before cutting we need to get idea what branch it was.
        bool isRightNode = _ex_top && _ex_top->right == node;

        _cut_top(node);
        
        // Now Left Node of Old Root is new Left Node of New Root.
        if (node->left) {
            node->right->left = node->left;
            node->left->top = node->right;
        }
        
        node->right->top = _ex_top;
        if ( _ex_top ) { 
            ( isRightNode ? _ex_top->right : _ex_top->left ) = node->right;
        }

        if ( _ex_node == _root ) {
            _root = node->right;
        }

        // resetting pointers of to be deleted node.
        _ex_node->left = _ex_node->right = nullptr;

        _size--;

        return _ex_node;
    }
    
    // Case 3. Scenario 3. 
    // // Node has right child that has left child.
    if ( node->right != NULL && node->right->left != NULL ) {
       
        _size++; 

        Node *child    = shift(node->right->left);
        Node *_ex_top  = node->top;
        Node *_ex_node = node;

        // Before cutting we need to get idea what branch it was.
        bool isRightNode = _ex_top && _ex_top->right == node;
      
        // New Left Child 
        child->left = node->left;
        child->left->top = child;

        // New Right Child.
        child->right = node->right;
        child->right->top = child;

        if (_ex_top){
            (isRightNode ? node->top->right : node->top->left ) = child;
        }

        if ( _ex_node == _root ) {
            _root = child;
        }

       // ( node == _root ? _root : node->top->right ) = child;

        node = child;

        // Top Pointers Reset. 
        _ex_node->left = _ex_node->right = nullptr;

        _size--; 
        return _ex_node;
    }

    return node;
}

/**
 * Tree Traversals 
 **/
template <typename T>
std::string BinaryTree<T>::preorder( BinaryTree<T>::Node *root )  {
    return _traversal_bs("preorder", root);    
}

template <typename T>
std::string BinaryTree<T>::inorder( BinaryTree<T>::Node *root )  {
    return _traversal_bs("inorder", root);    
}

template <typename T>
std::string BinaryTree<T>::postorder( BinaryTree<T>::Node *root )  {
    return _traversal_bs("postorder", root);    
}

template <typename T>
std::string BinaryTree<T>::descorder( BinaryTree<T>::Node *root )  {
    return _traversal_bs("descorder", root);    
}

template <typename T>
std::string BinaryTree<T>::_traversal_bs( std::string order, Node* root )  {
    // Early fall.
    if ( _empty() ){
        return "{}";
    }   

    if ( root == NULL ) {
        root = _root;
    }

    std::string output(_traversal( order, root ));

    if ( output.size() > 0 ){
        output = output.substr( 0, output.size() - 1 );
    }

    return "{" +  output +  "}";

}

template <typename T>
std::string BinaryTree<T>::_traversal(std::string order, Node* node){
    if ( _empty() || node == NULL ){
        return "";
    }

    // in order to avoid initializating map or maps here few times we 
    // simple implement 3 nested loops
    std::string output("");
    
    if ( order == "preorder") {
        
        output += std::to_string(value(node)) + ",";
        output += _traversal(order, node->left);
        output += _traversal(order, node->right);

    } else if (order == "postorder") {
        
        output += _traversal(order, node->left);
        output += _traversal(order, node->right);
        output += std::to_string(value(node)) + ",";

    } else if (order == "descorder") {
        
        output += _traversal(order, node->right);
        output += std::to_string(value(node)) + ",";
        output += _traversal(order, node->left);


    } else {
        output += _traversal(order, node->left);
        output += std::to_string(value(node)) + ",";
        output += _traversal(order, node->right);
    }   

    return output;
}
