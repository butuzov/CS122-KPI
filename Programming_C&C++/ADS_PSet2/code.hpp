#include <iostream>               /* io stream            */
#include <fstream>                /* files stream         */
#include <sstream>                /* strings stream       */
#include <stdio.h>                /* remove */
#include <time.h>
#include <math.h>
#include <assert.h>               /* assert */

// Numbers per sort / file
// 4 Gb memory for aprox 500 000 000 numbers
#define NUMBERS_PER_UNSORTED_ARRAY 50000000 

// Position of string where we going to store number of first source file.
#define POSITION 21

// base type
typedef unsigned long long uint64;

// should i use ram drive?
bool debug(false);

// count digits number - length of number.
int num_uint64_length(uint64);

std::string maybe_update_line(std::string, int);
uint64 line_to_number(std::string);

// Generate Random Numbers.
int get_random_index();
uint64 random(int);

// split our input file into unsorted chunks.
int split_big_file( std::string file );

// namings functions
std::string name(std::string name, int num);

bool sort_file( const char* );
void array_echo(int array_length, uint64* array);
void merge_files();

void swap(uint64 *a, uint64 *b);
uint64* array_make(int array_length);

void array_merge_sort(int array_length, uint64* array);
void array_heap_sort(int array_length, uint64* array);
