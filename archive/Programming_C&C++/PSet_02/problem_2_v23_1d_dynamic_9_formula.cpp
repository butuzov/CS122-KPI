#include <iostream>

#define N 9

void matrix_fill(int* matrix){
    for ( int i = 0, total=N*N; i < total; i++ ) {
        int row   = i / N;
        int col   = i % N;
        int index = row * N + col ;
       *(matrix + (row*N) + (col) ) = 1 + abs( (row * N + row) - index );
    }
}

void matrix_print(int* matrix){
    for (int row = 0; row < N; row++){
        for (int col = 0; col < N; col++){
          std::cout
            << *(matrix + (row*N) + (col) )
            << (col+1 == N ? "":" ");
        }
        std::cout << std::endl;
      }
}


int main( int argc, char *argv[] ){

    int *matrix = (int *) calloc( N * N,  sizeof( int ) );

    // заповнити матрицю
    matrix_fill(matrix);

    // роздрукувати матрицю до консолі
    matrix_print(matrix);

    free(matrix);
    return 0;
}
