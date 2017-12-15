#include "code.h"

// Компіляція
// ви может скомпілювати цю программу і і запустит наступним чином
// c++ problem_2_sort.cpp code.cpp -o sort -std=c++11 && ./sort

// довжина масиву
#define N 16

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

    // показуємо зміст масиву перед сортуванням.
    std::cout << "Before Sorting - " ;
    array_echo(array_length, array);

    // відсортуємомасив методом сортування вибіркою
    array_quick_sort(array_length, array);

    // показуємо зміст масиву після сортування.
    std::cout << "After Sorting - " ;
    array_echo(array_length, array);

    // звільнити ресурси
    free(array);
    return 0;
}
