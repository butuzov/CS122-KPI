#include <iostream>
#include <time.h>       /* time */
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <string>
#include <map>


#include "code.h"

/******************************************************************
  This header file describe functions used in home/practive work
  for a "Algorithmes Analysis and Design" subject at 1st semester
  of CS-122
******************************************************************/

// Create Array with length of array_length.
//
// This function will return preallocated memory pointers.
// for array filled with zero values.
int* array_make(int array_length) {
    return (int *) calloc(array_length, sizeof( int * ) );
}

// Fill Array `array` provided by pointer, by length of array_length
//
// Fill array with randomized int values.
// System time(NULL) used as seed.
void array_fill(int array_length, int* array) {
    srand(time(0));
    for (int i = 0; i < array_length; i++) {
        array[i] = rand() % (array_length*8) + 1;
    }
}

// Echo/Print Array `array` provided by pointer, by length of array_length
//
// Dump array to stdout
void array_echo(int array_length, int* array) {
    std::cout << "[";
    for (int i = 0; i < array_length; i++) {
        std::cout << array[i] << (i+1 != array_length ? ", ": "");
    }
    std::cout << "]" << std::endl;
}

// Swap operation for array elements.
// that doesn't require extra space.
void swap(int *a, int *b){
    if (a == b) {
        return;
    }
    // Maxim Myhailovich! 10nx!!!
    *a = *a + *b; // updating value of a y b
    *b = *a - *b; // updating value of b by (a minus b(b still holds value))
    *a = *a - *b; // updating value of a by decrementing b.
}

// Non Recursive Binary Search.
int bisearch(int value, int array_length, int* array){
    int index(-1); // this is a placeholder for element we looking for.
                   // by default -1 as fail state.
                   //
    int start(0);
    int end(array_length);



    while ( start != end ) {

        //  Middle of Searching range.
        int middle( start + ( ( end - start ) / 2 ) );

        // actuall compare values..
        if ( array[middle] == value ){
            // value found
            return middle;
        } else if ( value > array[middle] ){
            // value is more than current element
            start = middle + 1;
        } else if ( value < array[middle] ){
            // value is less then current element
            end = middle;
        }
    }

    return index; // fail.
}


// 674LC - Longest Continuous Increasing Subsequence
// because this task was an separate topic in my homework.
// its also commented in ukrainian.
//
// --------------------------------------------------------------------
// Для послідовності цілих чисел x[1], … , x[n]. Знайти
// максимальну довжину її зростаючої підпослідовності
// (число дій порядку nlog(n)).
// --------------------------------------------------------------------
// Вперше розв'язано як задачу 674 в LeetCode (https://leetcode.com)
// реалізацію мовами програмування Python і Go вперше опубліковано
// опубліковано в https://github.com/butuzov/leetcode-problems/
// в травні 2017 і переопубліковано в вересні.
//
// данний код являє собою копірку з попередніх реалізацій.
int findLengthOfLCIS(int array_length, int* array){

    if ( array_length <= 1){
        return array_length;
    }

    // найдовша і теперішня зростаюча послідовність це
    // наш елемент нашого масиву 0
    int longest(1);
    int current(1);

    // ітерація починається з елементу 1 (0 ми вже порахували)
    for (int i = 1; i < array_length; i++){
        // якщо новий елемент суворо більше
        // попереднього інкрементуємо теперішню зростаючу послідовність
        if ( array[i] > array[i-1] ) {
            ++current;
            // і якщо теперішя послідовність тає більшою за
            // вже найбільшу - то оновлюємо найбільшу
            longest = current > longest ? current : longest;
        } else {
            // переривання найбільшої послідовності і ініціація
            // теперішнього рахівника послідовності.
            current = 1;
        }
    }

    // повертаємо набільшу послідовність.
    return longest;
}


// Sorting Algorithmes.
// - Bubble (array_bubble_sort)
// - Selection (array_selection_sort)
// - Insertion (array_insertion_sort)
// - Insertion (alternative with inplace swap)  (array_insertion_sort_inplace_swap)
// - Merge Sort (array_merge_sort)
// - Quick Sort (array_quick_sort)

void array_selection_sort(int array_length, int* array) {
    if (array_length <= 1) {
        return;
    }

    int min(0);

    for (int current = 0; current < array_length; current++) {
        min = current;
        for (int index = current; index < array_length; index++) {
            if ( array[min] > array[index]) {
                min = index;
            }
        }
        swap( &array[current], &array[min] );
    }
}
void array_bubble_sort(int array_length, int* array){
    if (array_length <= 1) {
        return;
    }
    for (int i = 0; i < array_length; i++ ) {
        for (int j = i+1; j < array_length; j++ ) {
            if (array[i] > array[j]){
                swap( &array[i] , &array[j] );
            }
        }
    }
}
void array_insertion_sort(int array_length, int* array){
    if (array_length <= 1) {
        return;
    }

    for (int i = 1; i < array_length; i++){
        int value(array[i]);
        int reverse_itterator(i-1);

        while ( reverse_itterator >= 0 && value < array[ reverse_itterator ] ) {
          array[ reverse_itterator + 1 ] = array[ reverse_itterator ];
          reverse_itterator--;
        }

        if ( i != reverse_itterator+1 ){
            array[ ( reverse_itterator + 1 ) ] = value;
        }
    }
}

void array_insertion_sort_inplace_swap(int array_length, int* array){
    if (array_length <= 1) {
        return;
    }
    for (int i = 1; i < array_length; i++){
        int key(i);
        while ( key > 0 &&  array[key] < array[ key - 1 ] ) {
          swap( &array[key], &array[key-1] );
          key--;
        }
    }
}

void array_merge_sort(int array_length, int* array) {

    if ( array_length != 1 ) {

        // Size of Left array
        int left_length  = array_length / 2;

        // Size of the Right array
        int right_length = array_length - left_length;

        // Allocating memory for Left and Right arrays.
        int *left_array( array_make( left_length ) );
        int *right_array( array_make( right_length ) );

        // Initial Indexes.
        int left_index = 0, right_index = 0;

        // Dividing original array in two.
        for( int i = 0; i < array_length; i++ ) {
            if ( i < left_length ) {
                left_array[ left_index++ ] = array[ i ];
             } else {
                right_array[ right_index++ ] = array[ i ];
            }
        }

        /**
         * Actual Sort for both Sides
         */

        // recursive calls to sort left array...
        array_merge_sort( left_length, left_array );

        // array_echo(left_length, left_array);

        // ... and right arrays
        array_merge_sort( right_length, right_array );

        // array_echo( right_length, right_array );

        /**
         * Merging both sides!
         */

        // Reseting indexes for left and right array.
        left_index = 0, right_index = 0;

        // Original array index.
        int index = 0;

        // Merging values while sorting it.
        while( left_index < left_length && right_index < right_length ) {
            if ( left_array[ left_index ] < right_array[ right_index ] ) {
                array[ index++  ] = left_array[ left_index++ ];
            } else {
                array[ index++  ] = right_array[ right_index++ ];
            }
        }

        // If we have something left from left array, appending
        // it value to end of array.
        if ( left_index < left_length ) {
            for ( int j = left_index; j < left_length; j++){
                array[ index ++ ] = left_array[ j ];
            }
        }

        // If something left from right array, appending it value
        // to end of result array.
        if ( right_index < right_length ) {
            for ( int j = right_index; j < right_length; j++){
                array[ index ++ ] = right_array[ j ];
            }
        }

        free(left_array);
        free(right_array);
    }
}

void qsort_helper(int* array, int start, int end) {
    if (start > end){
        return;
    }

    // calculating partition index.
    int pivot = array[end];    // pivot
    int i = (start - 1);        // Index of smaller element
    for (int j = start; j <= end - 1; j++ ){
        if ( array[j] <= pivot ) {
          i++;    // increment index of smaller element
          swap(&array[i], &array[j]);
        }
    }

    swap( &array[i + 1], &array[end] );

    qsort_helper(array, start, i);
    qsort_helper(array, i+2, end);
};

void array_quick_sort(int array_length, int* array){
    qsort_helper(array, 0, array_length-1);
}

void array_empty_sort(int array_length, int* array){}
