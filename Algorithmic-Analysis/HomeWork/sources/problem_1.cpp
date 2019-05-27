#include <iostream>
#include <stdio.h>      /* printf */
#include <math.h>       /* sqrt */

// Цю программу можна скомпілювати наступним чином в середовищі unix/linux
// c++ problem_1.cpp -o ./in -std=c++11
//
// І запустити її насутпним чином
// ./in
// і далі слідувати інстуркціям.


#define MAX_ACCEPTED  3.5
#define MIN_ACCEPTED -1.5

/**
 * Функція валідації змінної x
 */
bool validate(float x){
    if ( x > MAX_ACCEPTED ){
        std::cerr << "Value of x bigger than one we can accpet. MAX_ALLOWED value is " << MAX_ACCEPTED << "." << std::endl;
        return false;
    }

    if ( x < MIN_ACCEPTED ){
        std::cerr << "Value of x bigger than one we can accpet. MIN_ALLOWED value is " << MIN_ACCEPTED << "." << std::endl;
        return false;
    }

    return true;
}


/******************************************************************
  Функція мейн
******************************************************************/

int main(int argc, char* argv[]){

  float x;

  while(true){

    // отримуємо відповідь з командної строки
    std::cout << "Please enter value of X (should be float) x=";
    if ( scanf("%f", &x) != 1) {
      std::cerr << "It doesn't looks like float at all. Please, try again..." << std::endl;
      continue;
    }



    // валідація розміру x
    if ( validate( x ) ){
      std::cout << "X is " << x << std::endl;
      break;
    }
  }

  // шуканий y
  float y;

  // кейс перший - x менше нуля
  if ( x < 1 ){
    // змінна extra буде слідкувати за x пря умові x != 0
    // за x == 0, буде використоуватись значення по замовчуванню 0.
    float extra(0.0);
    if (x != 0.0){
      extra = 1/x;
    }

    // власне вираз що ми шукаємо.
    y = ((x*x)+(5*x))*( extra + sqrt( x+4 ) );
    
  } else {

    // кейс другий
    for (float m = 1; m <= 7; m += 0.25) {
      y += (m-x)/sqrt(m+x);
    }

  }

  std::cout << "Y is " << y << std::endl;
  return 0;
}
