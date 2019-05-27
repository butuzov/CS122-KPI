#include <iostream>
#include <time.h>       /* time */
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */



/******************************************************************
  This header file describe functions used in home/practive work
  for a "Algorithmes Analysis and Design" subject at 1st semester
  of CS-122
******************************************************************/

// Create Array with length of array_length.
int* array_make( int array_length);

// Fill Array `array` provided by pointer, by length of array_length
void array_fill( int array_length, int* array);

// Echo/Print Array `array` provided by pointer, by length of array_length
void array_echo( int array_length, int* array);

// Swap operation for array elements.
// doesn't require extra space.
void swap(int *a, int *b);

// Non Recursive Binary Search.
int bisearch(int value, int array_length, int* array);

// 674LC - Longest Continuous Increasing Subsequence
int findLengthOfLCIS(int array_length, int* array);


// Sorting Algorithmes.
// - Bubble (array_bubble_sort)
// - Selection (array_selection_sort)
// - Insertion (array_insertion_sort)
// - Insertion (alternative with inplace swap)  (array_insertion_sort_inplace_swap)
void array_bubble_sort(int array_length, int* array);
void array_selection_sort(int array_length, int* array);
void array_insertion_sort(int array_length, int* array);
void array_insertion_sort_inplace_swap(int array_length, int* array);
void array_quick_sort(int array_length, int* array);
void array_merge_sort(int array_length, int* array);

void array_empty_sort(int array_length, int* array);
