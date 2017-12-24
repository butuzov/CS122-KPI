/****** DGeneral Creation *************************************************/
#include "binary-tree.hpp"


/****** Construction *******************************************************/
template <typename T>
BinaryTree<T>::BinaryTree() {
    _root        = nullptr;    // Pointer to the root of the tree
    _size        = 0;          // Total tree nodes number
    _balanceable = false;      // Should this tree be balanceable automatically?
}

/****** Destruction *******************************************************/
template <typename T>
BinaryTree<T>::~BinaryTree(){
    if ( ! empty() ) {       // If Tree not empty
        destroy(NULL);       // We running destroy tree method for NULL
                             // NULL means default node - root.
    }
}

/**
 *  Destruction methon, accept pointer to node,
 *  if its not provided will destroy all tree.
 */
template <typename T>
auto BinaryTree<T>::destroy( BinaryTree<T>::Node *node ) -> void {

    if ( ! node && _root ) {      // If provided NULL, we running
        destroy(_root);           // global tree destruction -
        return;                   // one node at time
    }

    deattach(node);               // Deataching top <=> this node
                                  // So no pointer left behind.

    if ( node->left ) {           // If Left Node exists
        destroy(node->left);      // We going to destroy it
    }

    if ( node->right ) {          // If Right Node Exists
        destroy( node->right );   // We going to destroy it as well!
    }

    _size--;                      // Decreasing Size.

    delete node;                  // Finally destroy ActualRoot Node.
}



/**
 * Drops Connection from TOP/PARENT/ROOT node to THIS node.
 * so... no pointer left behind.
 */
template <typename T>
auto BinaryTree<T>::deattach(BinaryTree<T>::Node *node) -> void {

    // Node isn't provided or this top already nulled (root node).
    if ( ! node || ! node->top ) {
        return;
    }

    // NULLing pointer to THIS node from TOP/ROOT node
    ( node->top->left == node ? node->top->left : node->top->right ) = nullptr;

    // NULLing pointer from THIS to TOP/ROOT node
    node->top = nullptr;
}

/**
 *   Insert data to particulare node or move item down to tree structure.
 */
template <typename T>
auto BinaryTree<T>::insert(T item, BinaryTree<T>::Node *parent ) -> void {

    // We trying to create node that points to left or right branch
    // of current node - depanding if value if item less or
    // ( greater or equal to node value)
    Node *iNode(item < parent->data ? parent->left : parent->right);

    // In case if leaf node selected, but...
    if ( iNode ) {                  // leaf (destination) node exists
        iNode->weight++;
        insert(item, iNode);        // we going to insert it to right or left
        return;                     // node, depends if item velue less then
    }                               // Node value.

    iNode = new Node(item, parent); // Creating Node if Leaf not exists.

    // Comparison using overloaded operators
    // its important not to forget to overload comparison operators
    // if we deal with some custom structure.
    ( item < parent->data ? parent->left : parent->right ) = iNode;

    _size++;                        // Increasing Size of the Tree.

    balance_node_upright( iNode, "inserted" );
    root_node_balance(_root);
}


/**
 *  Inserts item into tree structure.
 */
template <typename T>
auto BinaryTree<T>::insert(T item) -> void {

    if ( empty() ){                 // There is no root in this tree
        _root = new Node( item );   // So let's create it.
        _size++;                    // and increase size to 1.
        return;
    }

    _root->weight++;
    return insert(item, _root);      // Or insert item into tree structure.
}


/***************************************************************************/

template <typename T>
auto BinaryTree<T>::rotate_right(BinaryTree<T>::Node *node) -> void {

    if ( ! node || ! node->left ){
        return;
    }

    // preserving right node.
    Node *left   (node->left);
    Node *parent (node->top);

    if ( _root == node  ){

        // Deleting pointers to each other...
        _root->left = nullptr;
        left->top  = nullptr;

        // reseting weight.
        _root->weight = node_weight(_root->left) + node_weight(_root->right);

        // separated tree demo.
        // tree(_root);
        // tree(left);

        parent = _root;
        _root = left;

        // debug(parent);
        // debug(_root);


        // return;
        move(parent, _root);

    } else {
        // Logic of rotation

        // Top/Root will point to right Node.
        (  node == node->top->left
                 ? node->top->left
                 : node->top->right ) = left;

        // NULLing top and right pointers of separated node.
        node->left = node->top = nullptr;
        left->top = parent;

        // reseting weight.
        node->weight =  node_weight(node->left) + node_weight(node->right);

        // tree(node);
        // tree(left);

        move(node, left);
    }
}

template <typename T>
auto BinaryTree<T>::rotate_left(BinaryTree<T>::Node *node) -> void {

    if ( ! node || ! node->right ){
        return;
    }

    // preserving right node.
    Node *right  (node->right);
    Node *parent (node->top);

    if ( _root == node  ){

        // Deleting pointers to each other...
        _root->right = nullptr;
        right->top  = nullptr;


        // reseting weight.
        _root->weight = node_weight(_root->left) + node_weight(_root->right);

        parent = _root;
        _root = right;
        // debug(parent);
        // debug(_root);

        // return;
        move(parent, _root);

    } else {
        // Logic of rotation

        // Top/Root will point to right Node.
        (  node == node->top->left
                 ? node->top->left
                 : node->top->right ) = right;

        // NULLing top and right pointers of separated node.
        node->right = node->top = nullptr;

        // reseting weight.
        node->weight= node_weight(node->left) + node_weight(node->right);

        right->top = parent;

        move(node, right);
    }
}

template <typename T>
auto BinaryTree<T>::balance_node_upright(BinaryTree<T>::Node *node, std::string type) -> void {

    if ( ! _balanceable ) {
        return;
    }



    // Balance Node Upright work with 3 nodes, it accept bottom one as argument
    // and check to the top should this branch be balanced or not.

    if ( ! is_balanceable_horizontaly( node ) ){
        // actual node has two leavs
        return;
    } else if ( node->weight <= 3 && node->weight > 0 ) {
        balance_node_upright( node->left ? node->left : node->right );
        return;
    }




    if ( ! is_balanceable_horizontaly( node->top ) ){
        // parent node has two leavs
        return;
    }

    if ( ! is_balanceable_horizontaly( node->top->top ) ){
        // ok we can't do nothing here top one has both childrens.
        return;
    }


    if ( type == "inserted" ){
        char message[100] = "Inserted Node(%02d) -> Rebalance for Node(%02d) required";
         sprintf(message, message, value(node), value(node->top->top));
        //  std::cout << message << std::endl;
        //  tree();
    }

    if (type == "moved") {
        char message[100] = "Node(%02d) moved into Node(%02d) ->  Rebalance for Node(%02d) required";
        sprintf(message, message, value(node), value(node->top->top), value(node->top->top));
        // std::cout << message << std::endl;

        // tree();
    }


    // std::cout << "Before" << std::endl;
    // tree();

    if ( node->top->top->right ) {
        // Leaft Leaf available, rotating it to Left.
        rotate_left( node->top->top );
    } else {
        // Right Leaf available, rotating to Right.
        rotate_right( node->top->top );
    }

    // std::cout << "After" << std::endl;
    // tree();
}

template <typename T>
auto BinaryTree<T>::is_node_balanced(BinaryTree<T>::Node *node) -> bool {

    // to get an idea if node balanced we need to check if one of the leafs
    // of node, is bigger at least by 3 by a number of subnodes.

    int w_right(0), w_left(0);
    if ( node->right ){
        w_right = node->right->weight;
    }

    if ( node->left ){
        w_left = node->left->weight;
    }

    // std::cout << "left (" << w_left << ")"
    //           << "right (" << w_right << ")\n";

    int diff(w_left - w_right);

    // no need to include math.h for abs
    if ( diff > 2 || ( diff < 0 && (diff * (-1)) > 2 )) {
        return false;
    }

    return true;
}


template <typename T>
auto BinaryTree<T>::node_weight(Node* node) -> int {
    if (node){
        return node->weight + 1;
    }
    return 0;
}

template <typename T>
auto BinaryTree<T>::root_node_balance(Node* node) -> void{
    if ( ! _balanceable ) {
        return;
    }

    if ( ! node ){
        return;
    }

    if ( is_node_balanced( node ) ) {
        return;
    }

    // std::cout << value(node) << " Need Balance \n";
    // tree();

    // We already know that diff is enougth to balance tree
    if ( (node_weight(node->left) - node_weight(node->right)) > 0 ){
        // Left lear is heavier.
        // std::cout << "Tree need balance to right";
        // tree();
        rotate_right(node);

    } else {
        // std::cout << "Tree need balance to left";
        // tree();
        // Right leaf if havier.
        rotate_left(node);
    }

  //  std::cout << value(node) << " Balance Result \n";


}



template <typename T>
auto BinaryTree<T>::move(BinaryTree<T>::Node *from, BinaryTree<T>::Node *to) -> void {

    if ( value(from) < value(to) ) {
        if ( to->left ) {
            to->left->weight = 0;

            move(from, to->left);
            return;
        }
        to->left = from;
        from->top = to;
    }

    // moving to right of node.
    if ( value(from) >= value(to) ) {
        if ( to->right ) {
            to->right->weight = 0;
            move(from, to->right);
            return;
        }
        to->right = from;
        from->top = to;
    }


   // std::cout << "Noda(" << value(from) << ")" << "\n";

    node_weight_reset( to );

    balance_node_upright( from, "moved" );

    root_node_balance(from);
}


template <typename T>
auto BinaryTree<T>::tree_rebalance(BinaryTree<T>::Node *node) -> void{
    if ( ! _balanceable || ! node ) {
        return;
    }


    if (node->left) {
        tree_rebalance(node->left);
    }

    if (node->right) {
        tree_rebalance(node->right);
    }

    if ( ! is_node_balanced( node ) ) {
        std::cout << value(node) << " W " << node->weight << " need balance !\n";

        root_node_balance(node);

    }



    // if node weight less then 3
    // and this node has one chield...
    // balancing it up right.

   // std::cout << value(node) << " W " << node->weight << "!\n";

   // tree();
  //  root_node_balance(node);

   // std::cout << "After "  << value(node) << " W " << node->weight << "!\n";
   // tree();

    if (node->weight < 3 && is_balanceable_horizontaly(node)) {
    //    std::cout << "fuck?\n";
     //   balance_node_upright( node );
    }
  //  tree();

}

template <typename T>
auto BinaryTree<T>::node_weight_reset(BinaryTree<T>::Node *node) -> void{

    if ( ! node ) {
        return;
    }

    node->weight = node_weight(node->left) + node_weight(node->right);
    if ( node->top ) {
        node_weight_reset(node->top);
    }
}



/**
 * Check what ever node can be balanced.
 */
template <typename T>
bool BinaryTree<T>::is_balanceable_horizontaly(BinaryTree<T>::Node *node){
    if ( ! node ){
        return false;
    }

    // If both nodes has children - no declared OK!
    return ( node->left && node->right ) ? false : true ;
}

/** Utilities **************************************************************/

/**
 * Debug Info
 */

template <typename T>
auto BinaryTree<T>::size() -> int {
    return _size;
}

/**
 * Return True if tree empty.
 */
template <typename T>
auto BinaryTree<T>::empty() -> bool {
    return _size == 0;
}

template <typename T>
auto BinaryTree<T>::debug( BinaryTree<T>::Node *node  ){
    std::cout << "\n\nDebug for Node("<< value(node) << ") \n"
        << "Addr is " << node << "\n"
        << "Top is " << node->top << "\n"
        << "Left is " << node->left << "\n"
        << "Right is " << node->right << "\n"
    ;
}


/* Search ******************************************************************/
template <typename T>
auto BinaryTree<T>::find( int needle ) -> typename BinaryTree<T>::Node* {
    return find( _root, needle );
}

template <typename T>
auto BinaryTree<T>::find( BinaryTree<T>::Node *heystack, int needle ) -> typename BinaryTree<T>::Node* {

    if ( heystack == NULL ){
        return nullptr;
    }

    // Checking node first.
    if ( heystack->left  && value(heystack) > needle ){
        return find(heystack->left, needle);
    } else if ( heystack->right && value(heystack) < needle ){
        return find(heystack->right, needle);
    } else if (value(heystack) == needle) {
        return heystack;
    }

    return nullptr;
}

template <typename T>
auto BinaryTree<T>::root( ) -> typename BinaryTree<T>::Node*{
    return _root;
}


/*****/

/****** Show tree *******************************************************/
template <typename T>
void BinaryTree<T>::values(){
    if ( _root != NULL ){
        std::string values = _value(_root);
        std::cout << "V {" << values.substr(0, values.size()-1) << "}" ;
    }
}

template <typename T>
auto BinaryTree<T>::_value(BinaryTree<T>::Node *node) -> std::string {

    std::string exported;
    if ( node->left != NULL  ){
      exported  += _value( node->left );
    }

    exported  += view( node->data ) + ",";

    if ( node->right != NULL  ){
       exported += _value( node->right );
    }
    return exported;
}
