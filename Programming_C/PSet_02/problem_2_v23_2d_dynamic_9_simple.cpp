#include <iostream>

#define N 9

void matrix_fill(int** matrix){
    for (int row = 0; row < N; row++){
        for (int col=0,stop=N-row; col < stop; col++){
            *( *( matrix + row ) + (row+col) ) = col+1;
        }
        for (int col=0; col < row; col++){
            *( *( matrix + row ) + (col) ) = *( *( matrix + col ) + (row) );
        }}
}

void matrix_print(int** matrix){
    for (int row = 0; row < N; row++){
        for (int col = 0; col < N; col++){
          std::cout
            << *( *( matrix + row ) + (col) )
            << (col+1 == N ? "":" ");
        }
        std::cout << std::endl;
      }
}


int main( int argc, char *argv[] ){

    int** matrix = (int **) calloc( N,  sizeof( int * ) );
    for (int i = 0; i < N; i++ ){
        *(matrix+i) = (int *) calloc( N,  sizeof( int ) );
    }

    // заповнити матрицю
    matrix_fill(matrix);

    // роздрукувати матрицю до консолі
    matrix_print(matrix);

    free(matrix);
    return 0;
}
