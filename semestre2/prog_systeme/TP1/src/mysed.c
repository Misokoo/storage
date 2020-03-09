#include <stdio.h>
#include <stdlib.h>
#include "mysed.h"
#define SIZE 2015

 int main(int argc, char** argv)
 {
   if (argc != 3)
   {
     perror("wrongs numbers of arguments, use this usage :");
     perror("./mysed old_text new_text file")
     exit(EXIT_FAILURE);
   }

   if (!access(argv[2], F_OK | R_OK))
   {
     perror(" file doesnt exist or not readable");
     exit(EXIT_FAILURE);
   }

   if (!S_ISREG (stbuf.st_mode))
   {
     perror("this file isn't regular");
     exit(EXIT_FAILURE);
   }

   int fd = open(argv[2], O_RDONLY);
   if (fd == -1)
   {
     perror("error during opening file");
     exit(EXIT_FAILURE);
   }






   int size_old_text = strlen(argv[1]); // rechercher code erreur de strlen
   unsigned char* p;
   unsigned char buf[SIZE];
   int nb_carac, cpt = 0, i=0;
   while ((nb_carac = read(0, buf, SIZE))!= 0)
   {

     if(nb_carac == -1)
     {
       perror("error during a read ");
       exit(EXIT_FAILURE);
     }

     p = buf;
     while (i != nb_carac)
     {
       if (p[i] == old_text[cpt])
       {
         p[i] = old_text[cpt];
         cpt++;
       }
       else
       {
         cpt = 0;
       }
       i++;
     }


     i = 0;
   }



   return 0;
 }
