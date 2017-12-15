#include <iostream>
#define N 3

void matrix_fill(int** matrix){
    for ( int i = 0, total=N*N; i < total; i++ ) {

        int row, index;
        row = i / N;
        index = i - ( ( i / N ) * N );

        *( *(matrix + row ) + index ) =  1 + abs(
           ( ( ( i / N ) * N ) + i / N ) - i
        ) ;
    }
}

void matrix_print(int** matrix){
  for (int row = 0; row < N; row++){
    for (int col = 0; col < N; col++){
      std::cout
        << *( *(matrix + row) + col )
        << (col+1 == N ? "":" ");
    }
    std::cout << std::endl;
  }
}

int main(){

    int** matrix = (int **) calloc( N,  sizeof( int * ) );
    for (int i = 0; i < N; i++ ){
      *(matrix+i) = (int *) calloc( N,  sizeof( int ) );
    }

    matrix_fill(matrix);
    matrix_print(matrix);

    return 0;
}
