// Sample of Binary Tree implementation (using bidirectional nodes)

template <typename T>
class BinaryTree {

    // Constructor & Destructor
    public:
        BinaryTree();
        BinaryTree( std::vector<T> );
        ~BinaryTree();



    // Structures
    public:
        // Struct
        struct Node {                           // Our Node Structure
            T data;                             // Data Element
            Node *right  = nullptr;             // Right Node
            Node *left   = nullptr;             // Left Node

            // @unnessesary propery, but its allow us to
            // have a pointer to root node (relative to this node)
            // so we can sometimes do opperations only in nodes.
            Node *top    = nullptr;             // Parent Node

            // Height
            int height   = 0;

            Node(T item): data(item) {};
            // Constrcutor with parent node
            Node(T item, Node *node): data(item), top(node) {};
        };

    // Methods

    public:

        // Insert Element into tree
        Node* insert(T);

        void remove(Node*);

        // Push out node from Tree
        Node* shift(Node*);

        // Tree Traversals
        // Pre Order Traversal
        std::string preorder(Node* node=nullptr);

        // Ascending/In order
        std::string inorder(Node* node=nullptr);
 
        // Post Order Traversal
        std::string postorder(Node* node=nullptr);

        // Descending Order
        std::string descorder(Node* node=nullptr);
 

        // Return numeric value of Node item
        int value(Node*);

        // Search in Tree by Node numeric value in node (and its leavs)
        Node* find( int needle, Node* heystack=nullptr );

        // Root Getter.
        Node* root();

         // Return size of the tree.
        int size();

        // Debug Pointer
        void debug(Node* node);

        // View as Tree
        void tree(Node *node=nullptr);
        int _tree(Node *tree, int is_left, int offset, int depth, char *array);


        // General rotation functionality that used by rot_left and rot_right
        bool _rotate(std::string, Node*);

        // Bith of this use _rotate
        bool rotate_right(Node*);
        bool rotate_left(Node*);

        // Both of this uses rotate_right and rotate_right.
        bool rotate_left_right(Node*);
        bool rotate_right_left(Node*);

        // Duplicates using terminology as described in "instructions.pdf"
        bool rotate_left_left(Node*);
        bool rotate_right_right(Node*);

    private:

        // return whatever tree empty or not
        bool _empty();

        // destroy node.
        void _destroy(Node*);

        //  Insert Node to the tree.
        Node* _insert(T item, Node* tree);

        // Cut connection to 
        void _cut_top(Node*);

        // Return node height.
        int _height(Node*);

        // Update node height.
        void _update_node_height(Node*);

        // Tree Traversal 
        std::string _traversal(std::string order, Node* node=nullptr);
        
        // ...and Traversal bootstrap.
        std::string _traversal_bs(std::string order, Node* root);

    // Properties
    public:
        // none.
    private:
         // Tree Root
        Node *_root;

        // number of tree nodes.
        int  _size;

};
