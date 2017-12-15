int main(){
  int *ptr_int((int *) calloc(1, sizeof(int *)));
  printf("%p %i\n", ptr_int, (*ptr_int));
  *(ptr_int) = 3;
  printf("%p %i\n", ptr_int, (*ptr_int));
  free(ptr_int);
  printf("%p %i\n", ptr_int, (*ptr_int));
  return 0;
}
