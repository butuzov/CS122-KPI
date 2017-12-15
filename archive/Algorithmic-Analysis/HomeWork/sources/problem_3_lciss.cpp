#include "code.h"

// Компіляція
// ви может скомпілювати цю программу і і запустит наступним чином
// c++ problem_3_lciss.cpp code.cpp -o bs -std=c++11 && ./bs

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

    // показуємо зміст масиву після сортування.
    array_echo(array_length, array);

    int longest(findLengthOfLCIS(array_length, array));
    std::cout << "Longest Continuous Increasing Subsequence is " << longest << std::endl;

    // звільнити ресурси
    free(array);
    return 0;
}
