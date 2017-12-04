#include "code.h"

// Компіляція
// ви может скомпілювати цю программу і і запустит наступним чином
// c++ problem_5_generate.cpp code.cpp -o generate -std=c++11 && ./generate 16 > 16-$i.txt


/******************************************************************
  Функція мейн
******************************************************************/

int main(int argc, char* argv[]) {

  if (argc != 2) {
    std::cout << "You should provide a length or array" << std::endl;
    return 1;
  }

  // Довжина масиву.
  int array_length( atoi(argv[1]) );
  int array_end( atoi(argv[1]) - 1 );

  // Створення масиву.
  int *array( array_make( array_length ) );

  // заповнення його довільними значеннями.
  array_fill(array_length, array);

  for (int i=0; i < array_length; i++ ){
    std::cout << array[i] << (i == array_end ? "":" ");
  }

  std::cout << std::endl;

  // звільнити ресурси
  free(array);
  return 0;
}
