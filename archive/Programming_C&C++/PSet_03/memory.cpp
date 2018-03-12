int main(){
  int *ptr_int((int *) calloc(1, sizeof(int *)));
  printf("%p %i\n", ptr_int, (*ptr_int));
  *(ptr_int) = 3;
  printf("%p %i\n", ptr_int, (*ptr_int));
  free(ptr_int);
  printf("%p %i\n", ptr_int, (*ptr_int));

  int *num = new int(4);
  printf("%p %i\n", num, (*num));

  *num = NULL;
  printf("%p %i\n", num, (*num));

  return 0;
}
