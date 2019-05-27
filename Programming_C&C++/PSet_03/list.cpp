/**
 * This is header file of ProblemSet #3 - DataStructures
 * of Algorithmes and DataStructures course at KPI - IASA - CP122
 *
 * author: Oleg Butuzov
 *
 * created as a part of datastructures course
 * created as a part of Code Days
 */
#include <string>                 /* std:string           */
#include <iostream>               /* cout , cerr          */
#include <stdlib.h>               /* malloc, free, atoi   */
#include "list.hpp"

/**
 * Class Constructor
 *
 * only this it does, initiate zero length of list.
 */
template <typename T>
LinkedList<T>::LinkedList() {
    length = 0;
}

/**
 * Class Desctructor
 *
 * Destroy list, before last breath.
 */
template <typename T>
LinkedList<T>::~LinkedList() {
    while( ! is_empty() ){
        shift();
    }
}

/**
 * Utility (Private) Insert Method
 *
 * Do all dirty word of prepend/append/inset methods.
 *
 * @param item     Data Element
 * @param position head/current/tail position indicator.
 */
template <typename T>
bool LinkedList<T>::insert(T item, std::string position) {

    // Creating Node
    // LinkedList<T>::Node *iNode;

    // Memory allocation
    // iNode = ( LinkedList<T>::Node * ) calloc( 1, sizeof( LinkedList<T>::Node ) );

    // Casting item to Node value  (wraped with a struct)
    // (*iNode) = ( LinkedList<T>::Node ) item;

    Node *iNode = new Node(item);

    // printf( "\n%i - Adding link for %s\n", length, (item.Name).c_str() );

    // in case if there if list is empty we creating new value and assigning it
    // to head, tail and current =
    // which are all same and not exists at this point
    if ( is_empty() ) {
        // thay all same at this point.
        _head = _current = _tail = iNode;
        length++;
        return true;
    }

    // getting corresponding value
    switch( LinkedList<T>::position( position ) ) {
        case eHead:
          // while inseting element to the head
          // we adding pointet to exHead element to our Node
          // and then assigning our new node in place of head.

          (*iNode).next = _head;
          _head = iNode;

        break;

        case eCurrent:

            // Inserting our node AFTER current
            // and moving current pointer to new node.
            (*iNode).next = (*_current).next;
            (*_current).next = iNode;
            _current = iNode;

            if ( (*iNode).next == NULL ){
                // this is tail
                _tail = iNode;
            }

        break;

        case eTail:

          // we just inserting to the tail.
          // perhaps need some additional logic
          //
          // @todo - unittest inserts and removals.
          (*_tail).next = iNode;
          _tail = iNode;
        break;
    }

    length++;
    return true;
}

// Inserting T item into the head position
template <typename T>
bool LinkedList<T>::prepend(T item) {
    return insert(item, "head");
}

// Inserting T item into the current position
template <typename T>
bool LinkedList<T>::insert(T item) {
    return insert(item, "current");
}

// Inserting T item into the tail position
template <typename T>
bool LinkedList<T>::append(T item) {
    return insert(item, "tail");
}

//* Data Removal ***************************************************************

/**
 * Utility (Private) Remove Method
 *
 * @param position
 */
template <typename T>
bool LinkedList<T>::remove( std::string position ){

    // nothing to remove.
    if ( is_empty() ){
        return true;
    }

    // here we will hold data that we looking for.
    LinkedList<T>::Node *_look4;

    // We  getting pointer of element we looking for
    int pos_enum(LinkedList<T>::position( position ));

    switch( pos_enum ) {
        case eHead:
            _look4 = _head;
        break;

        case eCurrent:
            _look4 = _current;
        break;

        case eTail:
            _look4 = _tail;
        break;
    }


    // we setting _this to _head and start our search.
    Node *_this;
    Node *_previous;

    _this = _head ;
    _previous = nullptr;
    int n = 0;

    while( true ) {

        // we found element we looking for in next link of
        // our list.
        if ( _look4 == _this ){

            if ( _previous == NULL ) {
                // we currently deleting head
                if ( (*_this).next == NULL ) {
                    // this is only one element of our list.
                    _head = _current = _tail = nullptr;
                } else {
                    _head = (*_this).next;
                }

            } else {

                if ( (*_this).next == NULL ) {
                    // _current was same as _tail
                    if ( _tail == _current ) {
                        _current = _previous;
                    }
                    // new tail is previous
                    _tail = _previous;
                } else {
                    _current = _previous;
                }

                ( *_previous ).next = ( *_this ).next;

            }

            delete _this;
            length--;
            return true;
        }


        // next itteration...
        if ( ( *_this ).next ) {
            _previous = _this;
            _this = ( *( _this ) ).next;
        }

        // this isn't suppose to happen, but if it happend
        // returning fail state.
        if ( n++ > length ) {
            return false;
        }
    }

    // never happening...
    return false;
}

// Removes Item from _tail position
template <typename T>
bool LinkedList<T>::pop(){
    return remove( "tail" );
}

// Removes Item from _head position
template <typename T>
bool LinkedList<T>::shift(){
    return remove( "head" );
}

// Removes Item from _current position
template <typename T>
bool LinkedList<T>::remove(){
    return remove( "current" );
}

//* Data Retriving *************************************************************

/**
 * Utility (private) Retrive method
 *
 * return data from specified position.
 *
 * @param position
 */
template <typename T>
T LinkedList<T>::retrive(std::string position){
    if ( is_empty() ) {
        // we should check this in front.
        throw;
    }

    switch( LinkedList<T>::position( position ) ) {
        case eHead:
          return (*_head).data;
        break;

        case eCurrent:
          return (*_current).data;
        break;

        case eTail:
          return (*_tail).data;
        break;
    }

    throw;
}

// Return .data property of the Node from head position.
template <typename T>
T LinkedList<T>::head(){
    return retrive("head");
}

// Return .data property of the Node from tail position.
template <typename T>
T LinkedList<T>::tail(){
    return retrive("tail");
}

// Return .data property of the Node from current position.
template <typename T>
T LinkedList<T>::current(){
    return retrive("current");
}

//* Rewind *********************************************************************

// Rewind current pointer to head.
template <typename T>
bool LinkedList<T>::front(){
    if ( is_empty() ) {
        return false;
    }
    return (_current = _head);
}

// Move itterator to next item in list.
template <typename T>
bool LinkedList<T>::next(){
    if ( ( *_current ).next ){
        _current = ( *_current ).next;
        return true;
    }
    return false;
}

//* Helpers ********************************************************************

// Return list size
template <typename T>
int LinkedList<T>::size() {
    return length;
}

// Return List State
template <typename T>
bool LinkedList<T>::is_empty() {
    return size() == 0 ? true : false;
}

// Interface for internal class enum (position)
template <typename T>
int LinkedList<T>::position(std::string position) {

    if ( position == "head" ) {
        return eHead;
    }

    if ( position == "current" ) {
        return eCurrent;
    }

    // in all other cases - default place for adding item is tail.
    return eTail;
}



// int view
template <>
std::string LinkedList<int>::view(int item){
    return std::to_string(item);
}

template <typename T>
void LinkedList<T>::visualize() {
    if ( length == 0 ) {
        return;
    }

    LinkedList<T>::Node *_this;
    _this = _head;

    while( true ){

      std::cout << view( (*_this).data );

      // itterating to next available element.
      if ( ( *_this ).next ){
          _this = ( *( _this ) ).next;
          printf(" -> ");
      } else {
          // or stoping itteration is this is the end.
          break;
      }
    }
    printf("\n");
}
