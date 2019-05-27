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
  private:

      // Struct
      struct Node {                           // Our Node Structure
          T data;                             // Data Element
          Node *right = nullptr;              // Right Node
          Node *left  = nullptr;              // Left Node
          Node(T item): data(item) {};        // Struct Constructor
      };

      Node *root;                             // This is ROOT node pointer.

      void destroy(Node* );                   // Destroy node
      void insert(T, Node*);                  // Insert Element into node
      void showtree(Node*);                   // Traversal Show node.

  public:
      BinaryTree();                           // Constructor
      ~BinaryTree();                          // Destructor

      void insert(T);                         // Insert Data Element.
      void destroy();                         // Initial Destroy trigger
      void showtree();                        // Traversal Show tree start

      /*
        This interface should be implemented
        for particular data type separatly.
      */
      std::string view(T);                    // Display Node Content.
};
