#include <iostream>     /* std::cout */
#include <stdlib.h>     /* atoi      */ 

bool NaturalRootedNumber(int number);

int main(int argc, char *argv[]){

    // default number, in order to simplify development.
    int number_We_Looking_For(1000000);

    if (argc == 2) {
        number_We_Looking_For = atoi(argv[1]);
    }

    for (int i=1; i <= number_We_Looking_For; i++){
        if (NaturalRootedNumber(i)){
          std::cout << i << std::endl;
        }
    }
}

bool NaturalRootedNumber( int number ){

  // Алгоритм перевірки буде полягати в наступному

  // Піднесемо число до квадрату та видалемо його з нього.
  //   в такому разі нам буде відомо чи кратне воно 10
  //   (це число ми будемо перевіряти на етапі 2)

  int base = number * ( number - 1 );
  if (base % 10 != 0){
    return false;
  }

  // Знайдемо розряд числа з яким ми працюємо шукаємо
  int power = 1;
  while ( number % power != number) {
    power = power*10;
  }

  // і перевіримо остачу від ділення
  // різниці квадрату нашого числа і нашого числа
  if ( base % power != 0 ) {
    return false;
  }

  return true;
}
