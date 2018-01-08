#include <iostream>               /* io stream            */
#include <time.h>                 /* time                 */
#include <string>                 /* string               */
#include <vector>                 /* vector               */


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
std::string array_str(int array_length, int* array) {
    std::string str("{");
    for (int i = 0; i < array_length; i++) {
        str += std::to_string(array[i]);

        str += ( i+1 != array_length ? ", ": "" );
    }
    str += "}";

    return str;
}
