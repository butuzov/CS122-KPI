#include <iostream>

#define N 9

void matrix_fill(int matrix[][N]){
  for (int row = 0; row < N; row++){
    for (int col=0,stop=N-row; col < stop; col++){
      matrix[row][row+col] = col+1;
    }
    for (int col=0; col < row; col++){
      matrix[row][col] = matrix[col][row];
    }
  }
}

void matrix_print(int matrix[][N]){
  for (int row = 0; row < N; row++){
    for (int col = 0; col < N; col++){
      std::cout
        << matrix[row][col]
        << (col+1 == N ? "":" ");
    }
    std::cout << std::endl;
  }
}

int main(){
  int matrix[N][N];
  matrix_fill(matrix);
  matrix_print(matrix);
  return 0;
}
