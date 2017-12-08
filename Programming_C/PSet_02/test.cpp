#include <iostream>
#define N 3

int ret5(){
  return 5;
}

int main(){

    int (* pfunc)();

    pfunc = ret5;
    printf("%i\n", pfunc());

    int *array;
    array = (int *) calloc( 2,  sizeof( int ) );
    printf("%i\n", array[0]);
    printf("%i\n", *(array));

    printf("%p\n", (void*)&*(array));
    printf("%p\n", &*(array+1));

    free(array);
    return 0;
}
