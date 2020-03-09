#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define TAILLE 100000

void copie_file(char* path_src, char* path_dst)
{
  int fd = open(path_src, O_RDONLY);
  if (fd == -1)
  {
    perror("path_src pas ouvert");
    exit(EXIT_FAILURE);
  }
  int fd_dst = open(path_dst, O_CREAT | O_WRONLY | O_TRUNC , 0666);
  if (fd_dst == -1)
  {
    perror("erreur d'ouverture fichier de destination");
    exit(EXIT_FAILURE);
  }

  char buf[TAILLE];
  ssize_t rewrite;
  ssize_t length ;
  while((length = read(fd, buf, TAILLE-1)) >0)
  {
    buf[length] = '\0';
    rewrite = write(fd_dst, buf, length);
    if (rewrite == -1)
    {
      perror("erreur decriture");
      exit(EXIT_FAILURE);
    }
  }


  close(fd);
  if (fd == -1)
  {
    perror("path_src pas ferme");
    exit(EXIT_FAILURE);
  }
  close(fd_dst);
  if (fd == -1)
  {
    perror("path_dst pas ferme");
    exit(EXIT_FAILURE);
  }

}

int main(int argc, char** argv)
{

  if (argc != 3)
  {
    fprintf(stderr, " il faut exactement 2 parametres\n");
    exit(EXIT_FAILURE);
  }

  copie_file(argv[1], argv[2]);
  printf(" fichier copie\n");
  return 0;
}
