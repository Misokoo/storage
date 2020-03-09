#include <stdio.h>
void setint(int*, int);
int main()
{
   int a;
   setint(&a, 10);
   printf("%d\n", a);
   int* b;
   setint(b, 10);
   printf("%d\n", *b);
   return 0;
}
void setint(int* ip, int i)
{
   *ip = i;
}
