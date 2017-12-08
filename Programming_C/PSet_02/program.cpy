#include <iostream>

#define N $N

void matrix_fill($signature matrix$size){
    $filler
}

void matrix_print($signature matrix$size){
    for (int row = 0; row < N; row++){
        for (int col = 0; col < N; col++){
          std::cout
            << $elem[row][col]
            << (col+1 == N ? "":" ");
        }
        std::cout << std::endl;
      }
}


int main( int argc, char *argv[] ){

    $matrix_generate

    // заповнити матрицю
    matrix_fill(matrix);

    // роздрукувати матрицю до консолі
    matrix_print(matrix);

    return 0;
}
