#include <iostream>
#define N 3

void matrix_fill(int* matrix){
    for ( int i = 0, total=N*N; i < total; i++ ) {
        *( matrix + i ) =  1 + abs(
           ( ( ( i / N ) * N ) + i / N ) - i
        ) ;
    }
}

void matrix_print(int* matrix){
  for (int row = 0; row < N; row++){
    for (int col = 0; col < N; col++){
      std::cout
        << *( matrix + row*N + col )
        << (col+1 == N ? "":" ");
    }
    std::cout << std::endl;
  }
}

int main(){

    int *matrix = (int *) calloc( N * N,  sizeof( int ) );

    matrix_fill(matrix);
    matrix_print(matrix);

    return 0;
}
