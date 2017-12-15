#include "code.h"

// Компіляція
// ви может скомпілювати цю программу і і запустит наступним чином
// c++ problem_4_binary_search.cpp code.cpp -o bs -std=c++11 && ./bs

// довжина масиву
#define N 20

/******************************************************************
  Функція мейн
******************************************************************/

int main(int argc, char* argv[]) {

  // Довжина масиву.
  int array_length(N);

  // Створення масиву.
  int *array( array_make( array_length ) );

  // заповнення його довільними значеннями.
  array_fill(array_length, array);

  // Обираємо значення що вже в масиві для подальшого пошуку.
  int value( array[ int( array_length / 2 ) ] );

  // відсортуємомасив методом сортування вибіркою
  array_insertion_sort(array_length, array);

  // що шукаємо?
  std::cout << "Searching for (" << value << ") in sorted array "<< std::endl;

  // показуємо зміст масиву після сортування.
  array_echo(array_length, array);

  // власне бінарний пошук
  int n = bisearch( value, array_length, array);
  if ( n == -1 ){
      std::cout << "Value not found " << std::endl;
  } else {
      std::cout << "Value found at index " << n << std::endl;
  }

  // звільнити ресурси
  free(array);
  return 0;
}
