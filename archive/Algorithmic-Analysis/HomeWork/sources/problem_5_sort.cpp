#include "code.h"

// Компіляція
// ви может скомпілювати цю программу і і запустит наступним чином
// c++ problem_5_sort.cpp code.cpp -o sorter -std=c++11 && ./sorter bubble 8 9 7 6 5 4 3 2 1

#include <map>
#include <string>

/******************************************************************
  Функція мейн
******************************************************************/

int main(int argc, char* argv[]) {

  if (argc <= 2) {
      std::cout << "Not Enought arguments" << std::endl;
      return 1;
  }

  typedef void (*pfunc)(int, int *);

  std::map< std::string, pfunc > sorters;
  sorters["bubble"] = array_bubble_sort;
  sorters["selection"] = array_selection_sort;
  sorters["insertion"] = array_insertion_sort;
  sorters["insertion+"] = array_insertion_sort_inplace_swap;
  sorters["quick"] = array_quick_sort;
  sorters["merge"] = array_merge_sort;
  sorters["empty"] = array_empty_sort;


  if ( sorters.find( argv[1] ) == sorters.end() ) {
      std::cout << "Selected Sort Algorithm Not Exists" << std::endl;
      return 1;
  }



  int array_length( argc - 2 );
  int *array( array_make( array_length ) );
  for (int i = 0; i < array_length; i++){
    array[i] = atoi( argv[ 2 + i ] );
  }

  sorters[ argv[1] ]( array_length, array );

  free(array);
  return 0;
}
