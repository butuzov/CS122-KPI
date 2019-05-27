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
 * Linked List is data structure that allow linear collection of data elements
 *
 * This abstraction allow us to:
 * - Use List on any Data Structure
 * - Data Elements Inserts
 *    - Prepand Elements to the Head
 *    - Append to the Tail
 *    - Insert after Current
 *
 */
template <typename T> class LinkedList {
  public:
      LinkedList();                       // Constructor
      ~LinkedList();                      // Destructor

      // data insert methods
      bool append(T);                     // Appending T value to the _tail
      bool prepend(T);                    // Appending T value to the _head
      bool insert(T);                     // Inserting T value to the _current

      // data retrive methods
      T head();                           // Return Item Value of _head
      T tail();                           // Return Item Value of _tail
      T current();                        // Return Item Value of _current

      // data remove methods
      bool pop();                         // remove element from the tail
      bool shift();                       // remove element from the head
      bool remove();                      // remove element from the _current

      // movement methods
      bool front();                       // Reset _current to head.
      bool next();                        // Move _current to the next element.

      // utility
      // typename Func
      void visualize();                   // show list entries
      std::string view(T);                // string replresentation on
                                          // data element.
      bool is_empty();                    // is this list empty?

      int  size();                        // return length of list,
                                          // interface to var length

  private:

    // Structs
    struct Node {
        T data;                         // Actual Stored data.
        Node *next = nullptr;           // Pointer to next node, nullptr
                                        // by default
        Node(T item): data(item) {};    // Casting constructor
                                        // use it as
                                        //
                                        // (LinkedList<Type>::Node) value;
    };

      // Variables
      int length;                         // Count variables that helps us track
                                          // linked list length.
                                          //

      Node  *_head = nullptr;             // Pointer to Node of Head
      Node  *_tail = nullptr;             // Pointer to Node of Current Element.
                                          // WARNING:
                                          // _current only updated on
                                          //  - LinkedList<Type>::next()
                                          //  - LinkedList<Type>::remove("current")


      Node  *_current;                    // Pointer to Node of Tail.

      // eNums
      enum position {
          eHead = 1,                      // 1 - points to "_head"
          eCurrent,                       // 2 - points to "_current"
          eTail,                          // 3 - points to "_tail"
      };

      // return int associated with string value (because of switch)
      int position(std::string);

      // Utility methods
      bool insert( T, std::string );      // Insert element to position
      bool remove( std::string );         // Remove element from position
      T retrive( std::string );           // Retrive node data at position 
};
