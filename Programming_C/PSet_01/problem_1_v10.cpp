#include <iostream>     /* std::cout */
#include <stdlib.h>     /* atoi   */
#include <math.h>     /* atoi   */

bool NaturalRootedNumber(int number);

int main(int argc, char *argv[]){

    // default number, in order to simplify development.
    int number_We_Looking_For(40000);

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

  int base = pow(number, 2) - number;
  if (base % 10 != 0){
    return false;
  }

  // Знайдемо розряд числа з яким ми працюємо шукаємо
  int i = 0;
  while ( number % int(pow(10, i)) != number) {
    i++;
  }

  // і перевіримо остачу від ділення
  // різниці квадрату нашого числа і нашого числа
  if ( base % int(pow(10, i)) != 0 ) {
    return false;
  }

  return true;
}
