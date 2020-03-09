#include <stdio.h>


int main() {
  int a[] = {1, 2, 3, 4, 5};
  int *a_ptr = a;


  printf("taille du pointeur %zu\n",sizeof(a_ptr));
  printf("taille du tableau %zu\n",sizeof(a));

  printf(" ladresse  de a_ptr %p\n", a_ptr);
  printf("ladresse du tableau %p\n", a);

}
