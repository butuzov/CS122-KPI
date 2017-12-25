/**
 * This is header file of ProblemSet #3 - DataStructures
 * of Algorithmes and DataStructures course at KPI - IASA - CP122
 *
 * author: Oleg Butuzov
 *
 * created as a part of datastructures course
 * created as a part of Code Days
 */

/**
 * Binary Tree is tree like data structure optimized for search.
 *
 * this is default interface description
 * (no features) of binary tree.
 */

template <typename T>
class BinaryTree {
    public:
        BinaryTree(bool auto_balance=true);     // Constructor with balanceable
                                                // property
        ~BinaryTree();                          // Destructor

        // Struct
        struct Node {                           // Our Node Structure
            T data;                             // Data Element
            Node *right  = nullptr;             // Right Node
            Node *left   = nullptr;             // Left Node
            Node *top    = nullptr;             // Parent Node.

            // Weight
            int weight   = 0;

            // Struct Constrcutors.
            Node(T item): data(item) {};        // Struct Constructor
            // COnstrcutor with parent node
            Node(T item, Node *node): data(item), top(node) {
              //  std::cout << "new node created parent()";
            };
        };

        auto insert(T) -> void;                 // Insert Data Element.
        auto insert(T, Node*) -> void;          // Insert Element into node
        auto move(Node*, Node*) -> void;        // Move Node.

        // Destroy Node/Tree
        auto destroy(Node* ) -> void;

        // Traversal Info value of node.
        void values();

        // Return whatever or not tree is empty.
        auto empty() -> bool;

        // return size of the tree.
        auto size() -> int;

        // return weight on node...
        // auto weight(Node* node) -> int;

        // Return whatever or not node is OK (has two nodes)
        auto is_balanceable_horizontaly(Node* node) -> bool;

        // return whateve root/node is balanced.
        auto is_node_balanced(Node* node) -> bool;

        auto root_node_balance(Node* node) -> void;
        auto tree_rebalance(Node* node) -> void;

        auto node_weight(Node* node) -> int;
        auto node_weight_reset(Node* node) -> void;

        // Performe check and run balance procedure on 2nd topest
        // node (from the node we checking.)
        auto balance_node_upright(Node* node, std::string type = "") -> void;

        auto debug(Node* node);

        // Return pointer to Node that holds needle numeric value
        Node* find( int needle );

        // Search in Tree by Node numeric value in node (and its leavs)
        Node* find(Node* heystack, int needle);

        // deattach node from its top/root.
        auto deattach(Node* node) -> void;
        auto rotate_left(Node* node) -> void;
        auto rotate_right(Node* node) -> void;

        // Root
        auto root() -> Node*;
        // Show Tree
        auto tree();
        // Or Show just a branch
        auto tree(Node*);

        /*******************************************************
            This interface should be implemented
            for particular data type separatly.
        ********************************************************/
        // String representation of node value
        std::string view(T);

        // NUmber Value representation of node.
        int value(Node*);

        // is balanceable.
        bool _balanceable;

    private:

        // This is ROOT node pointer.
        Node *_root;

        // number of tree nodes.
        int  _size;

        // show level with some int.
        int _tree(Node*, int is_left, int off, int depth, char* array);

        // Traversal Info value of node.
        auto _value(Node*) -> std::string ;

};
