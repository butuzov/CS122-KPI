// compile clang++ employees.cpp -o test -std=c++14


#include <iostream>
#include <stdio.h>                 /* printf, scanf, NULL  */
#include <stdlib.h>                /* malloc, free, atoi   */
#include <sstream>                 /* string stream        */
#include <string>
#include <vector>
#include "list.cpp"                /* linkedlist implementation  */
#include "app.cpp"                 /* app specific code          */

// спец дебагер
void debug(std::string message){
  std::cout << message <<std::endl;
}

// кастом вюшка
template<>
std::string LinkedList<Employee>::view(Employee item){
  return item.Name;
}


int main(int argc, char* argv[]){

  int error;

  LinkedList<Employee> employees;

  /**
   * Load Data from csv file
   */

  if ( argc == 2){
      error = load_csv( argv[1], &employees );
  } else {
      // debug settings
      std::string FName = "/Users/butuzov/Dropbox/CS122-AIS/Programming_C/PSet_03/employees.csv";
      error = load_csv( FName.c_str(), &employees );
  }

  if ( error != 0 ) {
      return error;
  }

  //employees.visualize();

  employees.front();
  std::cout << employees.view(employees.current()) << std::endl;

  while(employees.next()){
    std::cout << employees.view(employees.current()) << std::endl;
  }


}
