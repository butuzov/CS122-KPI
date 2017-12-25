// source stackoverflow
// https://stackoverflow.com/questions/801740

#define BT_HEIGHT 6
#define BT_WIDTH  170
#define DEBUG true


template <typename T>
auto BinaryTree<T>::_tree(BinaryTree<T>::Node *tree, int is_left, int offset, int depth, char *array) -> int {
     if ( !tree){
        return 0;
    }

    char b[10];

    #if DEBUG == true
        int width = 5;
        sprintf(b, "%02d|%02d", value(tree), tree->weight );
    #else
        int width = 3;
        sprintf(b, "%03d", value(tree));
    #endif

    int left  = _tree(tree->left,  1, offset,                depth + 1, array);
    int right = _tree(tree->right, 0, offset + left + width, depth + 1, array);

    for (int i = 0; i < width; i++) {
        array[ depth*BT_WIDTH + (offset + left + i) ] = b[i];
    }

    int row = (depth - 1) * BT_WIDTH;

    if ( depth && is_left ) {

        for (int i = 0; i < width + right; i++) {

            array[ row + (offset + left + width/2 + i) ] = '-';
        }
        array[ row + (offset + left + width/2) ] = '.';
    }

    if ( depth && !is_left ) {
        for (int i = 0; i < left + width; i++) {
            array[ row + (offset - width/2 + i) ] = '-';
        }
         array[ row + (offset + left + width/2) ] = '.';
    }
    return left + width + right;
}

template <typename T>
auto BinaryTree<T>::tree()  {
    tree(_root);
}

template <typename T>
auto BinaryTree<T>::tree(BinaryTree<T>::Node *node)  {
    if ( node == NULL ){
      return;
    }

    char* array( (char *) calloc( BT_HEIGHT * BT_WIDTH, sizeof(char)) );
    memset(array, ' ', BT_HEIGHT * BT_WIDTH);

    _tree(node, 0, 0, 0, array);

    std::cout << std::endl;

    for (int row = 0; row < BT_HEIGHT; row++ ){
        for (int col = 0; col < BT_WIDTH; col++)  {
            std::cout << array[ (row * BT_WIDTH + col) ];
        }
        std::cout << std::endl;
    }

    free(array);
}
