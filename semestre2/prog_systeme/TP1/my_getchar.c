#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define TAILLE 4096

int my_getchar(void)
{
  int c;
  ssize_t n = read(0, &c, 1);
  if (n == -1)
  {
    perror("probleme de read");
    exit(EXIT_FAILURE);
  }
  return n>0?c : EOF;
}
//le return depend de la condition, si n>0, on renvoie c sinon on renvoie myeof;
int my_getchar_buffered(void)
{
  static char buf[TAILLE];
  ssize_t n = read(0, &buf, TAILLE);
  if (n == -1)
  {
    perror("probleme de read");
    exit(EXIT_FAILURE);
  }
  ssize_t i = 0;
  int c = buf[i];
  while( (i < n) && (c != EOF) )
  {
     putchar(c);
     c = buf[i];
     i++;
  }
  return c;
}


int mygetchar_correction(void)
{
  static char* p;
  static unsigned char buf[TAILLE];
  static int ncar=0;
  if(ncar==0)
  {
    ncar=read(0, buf, TAILLE);
    p=buf;
  }
}
// main de my_getchar
// int main()
// {
//   int c = my_getchar();
//   while(c != EOF)
//   {
//      putchar(c);
//      c = my_getchar();
//    }
//   return 0;
// }

int main()
{
  printf("je commence");
  int c = my_getchar_buffered();
  // printf("hello");
  // while(c != EOF)
  // {
  //    c = my_getchar_buffered();
  //  }
  return 0;
}


/*

gcc -- version
dpkg librairie

gcc -Wall -Wextra -Werror my_getchar.c -o get


segment data pour les malloc, fonction globales, variable static

segment jesaispluslenom sagrandit en fct de la taille de la ple



static int mavariable =0; initialisation faite une seule fois, meme si plusieurs appels à la fonction
pour les fonction static dans une fonction, mais si apres on veut la modifier, on fit mavariable =machin
*/
