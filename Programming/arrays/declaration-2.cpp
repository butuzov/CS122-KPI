#include <iostream>

int* array_create(int array_length) {
    return (int *) calloc(array_length, sizeof( int * ) );
}

void array_fill(int* array, int array_length){
    srand(time(0));
    for (int i = 0; i < array_length; i++) {
        array[i] = rand() % array_length + 1;
    }
}

void array_print(int* array, int array_length) {
    for (int i = 0; i < array_length; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main(){

  int array_length(10);

  // Creating array.
  int *array( array_create( array_length ) );

  // ...and poplute it with a random values.
  array_fill(array, array_length);

  array_print(array, array_length);

  return 0;
}
