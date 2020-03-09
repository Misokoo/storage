#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define SIZE 10000

/*
Ce programme valide en principe les 2 premiers tests , et bloque pour les tests
de fichiers binaires, il gère cependant lorsqu'un motif est entre 2 buffers,
et lorsque l'ancien motif n'est pas de même taille que le nouveau motif.
Le problème du 3eme test provient de l'utilisation de la fonction
strstr() que je n'ai pas réussi à recodder pour autre chose que des char à
temps.
Le test 4 n'a pas pu être tester car après le test3 mais il devrait marcher.
*/

//////////////////////////////////////////////////////////////////////////////
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
        printf("le buf retourne %p\n", buf);
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



/*
Deux fonctions pour écrire plus rapidement les erreurs de write et de open
dans les autres fonctions.
*/
void write_error(int fd)
{
  if (fd == -1)
  {
    perror("usage: le fichier n'a pas pu être écrit");
    exit (EXIT_FAILURE);
  }
}

void open_error(int fd)
{
  if (fd == -1)
  {
    perror("usage: le fichier n'a pas pu être ouvert");
    exit (EXIT_FAILURE);
  }
}


/*
Une seule fonction ( un peu longue) qui teste juste les  pre requis pour
faire le programme.
*/
void test1(int argc, char** argv)
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
}

/*
fonction qui modifie la taille d'écriture d'octets en fonction de la différence
du nombre de charactere de l'ancien et le nouveau texte, et ecrit le nombre
d'octets qu'il faut.
Tant que notre buffer initial est remplie entierement (size = SIZE), on n'écrira
pas tous les octets car on dplace le curseur en arriere de la taille du new_text
-1 pour gérer les chevauchements de mots entre 2 buffers.
*/

void write_with_updated_size(char* old_text, char* new_text, size_t size, char*
  tmp, size_t nb_occu)
{
  size_t new_size = size, write_return=0;
  if(strlen(new_text)>strlen(old_text))
  {
    new_size = size + nb_occu*(strlen(new_text) - strlen(old_text));
  }
  else if (strlen(new_text)<strlen(old_text))
  {
    new_size = size - nb_occu*(strlen(old_text) - strlen(new_text));
  }
  if(size == SIZE)
  {
    write_return=write(1, tmp, new_size -(strlen(old_text)-1));
    write_error(write_return);
  }
  else
  {
    write(1, tmp, new_size);
    write_error(write_return);
  }
}


void remplace(char *buf, char *old_text, char*new_text, unsigned int size)
{
  char *first_occu ;
  char tmp[2*size];
  size_t new_curseur = 0, old_curseur=0, nb_occu=0;
  memcpy(tmp, buf, size);


  while((first_occu = strstr(tmp, old_text)) != NULL)
  {
    nb_occu++;
    new_curseur = 0;
    while(&tmp[new_curseur] != first_occu)
    {
      new_curseur++;
    }

    for(size_t i=0; i<strlen(new_text); i++)
    {
        tmp[new_curseur] = new_text[i];
        new_curseur++;
    }

    first_occu = strstr(&buf[old_curseur],old_text);
    while(&buf[old_curseur] != first_occu)
    {
      old_curseur++;
    }
    old_curseur+= strlen(old_text);
    for(size_t k = old_curseur; k<size; k++)
    {
      tmp[new_curseur] = buf[k];
      new_curseur++;
    }
  }
  write_with_updated_size(old_text, new_text, size, tmp, nb_occu);
}



int main(int argc, char** argv)
{

  test1(argc, argv);
  size_t length_old = strlen(argv[1]);
  char* old_text = argv[1];
  char* new_text = argv[2];
  unsigned int nb_carac=0;
  int fd = open(argv[3], O_RDONLY);
  open_error(fd);
  char buf[SIZE];
  while ((nb_carac = read(fd, buf, SIZE))> 0)
 {
   remplace(buf, old_text, new_text, nb_carac);
   if(nb_carac == SIZE)
   {
     lseek(fd,-(length_old-1),SEEK_CUR);  //gère le chevauchement de motif
   }
 }
  return 0;
}



























///////////////////////////////////////////////////////////////////////////////////////////////////////////////:
