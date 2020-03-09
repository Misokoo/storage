#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#define SIZE 10000

void cpy_buf(char* dst, char* src, size_t size)
{
  for(size_t i=0; i< size; i++)
  {
    dst[i] = src[i];
  }
}

char* first_occurence(char* buf, char* pattern, size_t length_buf, size_t length_pattern)
{
  size_t l_pattern=0, cpt=0;
  printf("debut ds la fonction\n");
  while((l_pattern < length_pattern) && (cpt < length_buf))
  {
    printf("%p\n", &buf[cpt]);
    if(pattern[l_pattern] == buf[cpt])
    {
      //printf("trouve %li\n", cpt);
      l_pattern++;
      if(l_pattern == length_pattern)
      {
        //printf("ici %p\n", (buf-1));
        printf("le cpt %li\n", cpt);
        printf("la taille  %li\n", length_pattern);
        buf = buf-l_pattern;
        return buf;
      }
    }
    else
    {
      l_pattern = 0;
    }
    cpt++;
    //printf("hello\n");
  }
  return NULL;
}


void remplace(char *buf, char *old_text, char*new_text, unsigned int size)
{
  //printf(" double test \n");
  char *first_occu ;
  char tmp[2*size];
  size_t new_curseur = 0, old_curseur=0, nb_occu=0, new_size = size;
  cpy_buf(tmp, buf, size);


  while((first_occu = first_occurence(tmp, old_text, size, strlen(old_text))) != NULL)
  {
    printf("%p\n", first_occu);
    nb_occu++;
    new_curseur = 0;
    printf("debut ds le main\n");
    while(&tmp[new_curseur] != tmp)
    {
      printf("%p\n",&tmp[new_curseur]);
      sleep(1);
      new_curseur++;
    }

    printf("trouve\n");
    for(size_t i=0; i<strlen(new_text); i++)
    {
        tmp[new_curseur] = new_text[i];
        printf("%c", tmp[new_curseur]);
        new_curseur++;
    }

    first_occu = strstr(&buf[old_curseur],old_text);
    //printf(" placement ancien cursuer:\n");
    while(&buf[old_curseur] != first_occu)
    {
      //printf("5 test\n");
      old_curseur++;
    }
    old_curseur+= strlen(old_text);
    //printf("%c%c%c\n\n", buf[old_curseur], buf[old_curseur+1], buf[old_curseur+2]);




    for(size_t k = old_curseur; k<size; k++)
    {
      tmp[new_curseur] = buf[k];
      //printf("%c", tmp[new_curseur]);
      new_curseur++;
    }

  }

  if(strlen(new_text)>strlen(old_text))
  {
    new_size = size + nb_occu*(strlen(new_text) - strlen(old_text));
  }
  else if (strlen(new_text)<strlen(old_text))
  {
    //printf("hello");
    new_size = size - nb_occu*(strlen(old_text) - strlen(new_text));
  }
  if(size == SIZE)
  {
    //printf("affichage1\n");
    write(1, tmp, new_size -(strlen(old_text)-1));
  }
  else
  {
    //printf("affichage2\n");
    write(1, tmp, new_size);
  }
}



int main(int argc, char** argv)
{
  if (argc != 4)
  {
    perror("usage: ./mysed old_text new_text file");
    exit(EXIT_FAILURE);
  }

  if (access(argv[3], F_OK) == -1)
  {
    perror("usage: ");
    exit(EXIT_FAILURE);
  }

  if (access(argv[3], R_OK) == -1)
  {
    perror("usage: ");
    exit(EXIT_FAILURE);
  }

  struct stat stbuf;
  stat (argv[3],&stbuf);
  if (!S_ISREG (stbuf.st_mode))
  {
    perror("usage: ");
    exit(EXIT_FAILURE);
  }

  if (strlen(argv[1]) >= 1025)
  {
    perror("usage: motif d'entrée trop long");
    exit(EXIT_FAILURE);
  }

  if (strlen(argv[2]) >= 1025)
  {
    perror("usage: motif d'entrée trop long");
    exit(EXIT_FAILURE);
  }

  size_t length_old = strlen(argv[1]);
  char* old_text = argv[1];
  char* new_text = argv[2];
  unsigned int nb_carac=0;
  int fd = open(argv[3], O_RDONLY);
  unsigned int buf[SIZE];
  //printf("hey\n");
  while ((nb_carac = read(fd, buf, SIZE))> 0)
 {
   //printf("read\n");
   //printf("hello");
   remplace((char*)buf, old_text, new_text, nb_carac);
   //printf("\n");
   if(nb_carac == SIZE)
   {
     lseek(fd,-(length_old-1),SEEK_CUR);
   }
 }
  return 0;
}



























///////////////////////////////////////////////////////////////////////////////////////////////////////////////:
