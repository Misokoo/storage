#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#define TAILLE 1000
#define SIZE 1024


char name[TAILLE];
/*
Deux fonctions pour écrire plus rapidement les erreurs de write et de open
dans les autres fonctions.
*/
void raler(char* msg)
{
  perror(msg);
  exit(1);
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

  if (argc != 2)
  {
    fprintf(stderr, "usage: nb arg");
    exit(EXIT_FAILURE);
  }

  DIR* dp;
  dp = opendir(argv[1]);
  if (dp == NULL)
  {
    perror("usage: ");
    exit(EXIT_FAILURE);
  }

  struct stat stbuf;
  stat (argv[1],&stbuf);
  if (!S_ISDIR (stbuf.st_mode))
  {
    perror("usage: ");
    exit(EXIT_FAILURE);
  }

  if (access(argv[1], R_OK | X_OK ) == -1)
  {
    perror("usage: ");
    exit(EXIT_FAILURE);
  }
  closedir(dp);
  if (dp == NULL)
    raler("closedir");
}




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

size_t get_nb_backups(char* main_directory)
{
  DIR* dp = opendir(main_directory);
  size_t cpt = 0;
  if (dp == NULL)
    raler("open main directory");
  struct dirent* d;
  struct stat stbuf;
  while  ((d= readdir (dp)) != NULL)
  {
    if (strcmp (d->d_name , ".") != 0 &&strcmp (d->d_name , "..") != 0)
    {
      stat(d->d_name, &stbuf);
      if (S_ISDIR (stbuf.st_mode))
      {
        cpt++;
      }
    }
  }
  return cpt;
}


void create_backup(char* repertory_origin, char* repertory_dest)
{
  int nb_backup = get_nb_backups(repertory_origin);
  char path_backup[TAILLE];
  sprintf(path_backup + strlen(path_backup),"%s", repertory_origin);
  sprintf(path_backup + strlen(path_backup),"%s", "/");
  sprintf(path_backup + strlen(path_backup),"%i", nb_backup);
  int nb_backup_repository = mkdir(path_backup, 0777);
  open_error(dd);
  DIR* d_origin = opendir(repertory_origin);
  struct dirent* d;
  struct stat stbuf;
  printf("debut de boucle\n");
  int cpt = 1;
  while  ((d = readdir(d_origin)) != NULL)
  {
    printf(" %i eme tour de boucle\n", cpt);
    cpt++;
    if (strcmp (d->d_name , ".") != 0 && strcmp (d->d_name , "..") != 0)
    {
      char path_src[TAILLE];
      char path_dst[TAILLE];
      sprintf(path_src,"%s", repertory_origin);
      sprintf(path_dst, "%s", repertory_dest);
      sprintf(path_src + strlen(path_src),"/%s", d->d_name);
      sprintf(path_dst + strlen(path_dst),"/%i/%s", nb_backup, d->d_name);
      stat(path_src, &stbuf);
      printf("on est dans %s\n", path_src);
      if (S_ISREG(stbuf.st_mode))
      {
        copie_file(path_src, path_dst);
        printf(" on a copie le fichier dorigine %s en fichier %s\n", path_src, path_dst);
      }
      else if(S_ISDIR(stbuf.st_mode))
      {
        sprintf(path_dst + strlen(path_dst),"%s", "/");
        sprintf(path_src + strlen(path_src),"%s", "/");
        printf("\nON EST DANS UN DOSSIER %s\n", path_dst);
        int dd = mkdir(path_dst, 0777);
        open_error(dd);
        create_backup(path_src, path_dst);
        printf("\nheloooooooo\n");
      }
    }
  }

  if (closedir (d_origin) ==  -1)
    raler ("closedir");
}






int cmp(char* path1, char* path2)
{
  int fd1 = open(path1, O_RDONLY);
  if (fd1 == -1)
  {
    perror("path1 pas ouvert");
    exit(EXIT_FAILURE);
  }
  int fd2 = open(path2, O_RDONLY);
  if (fd2 == -1)
  {
    perror("path2 pas ouvert");
    exit(EXIT_FAILURE);
  }

  struct stat stbuf1, stbuf2;
  stat(path1, &stbuf1);
  stat(path2, &stbuf2);
  if (stbuf1.st_size != stbuf2.st_size)
  {
    close(fd1);
    close(fd2);
    return 1;
  }
  size_t buf1[SIZE];
  size_t buf2[SIZE];
  size_t n = 0, m=0;
  while ( (n = read(fd1, buf1, SIZE)) > 0 )
  {
    m = read(fd2, buf2, SIZE);
    for(unsigned int i = 0; i< m; i++)
    {
      if (buf1[i] != buf2[i])
      {
        close(fd1);
        close(fd2);
        return 1;
      }
    }
  }
  close(fd1);
  close(fd2);
  return 0;
}


int check_if_changer(char* path_src, char* main_directory)
{
  size_t backups_nb = get_nb_backups(main_directory);
  if (backups_nb > 0)
  {
    char path_previous[SIZE];
    sprintf(path_previous ,"%s", main_directory);
    sprintf(path_previous +strlen(path_previous),"%li/", (backups_nb-1));
    int rep = cmp(path_src, path_previous);
    printf("previous file : %s, current file %s\n", path_previous, path_src);
    if (rep == 0)
      return 1;
  }
  return 0;
}

char* create_directory(char** argv)
{
  sprintf(name ,"%s", ".BACKUP_");
  size_t j=strlen(name);
  for(size_t i = 0; i < strlen(argv[1]); i++)
  {
    if(argv[1][i] == '/')
    {
      j=strlen(".BACKUP_");
    }
    else
    {
      name[j] = argv[1][i];
      j++;
    }
  }
  name[strlen(".BACKUP_")+j -1] = '\0';

  // if(name[strlen(name) - 2] == '/')
  // {
  //   name[strlen(name) - 2] = '\0';
  // }
  printf("le chaine de caractere %s\n", name);

  if (access(name, F_OK) != 0)
  {
    int dd2 = mkdir(name, 0777);
    if (dd2 == -1)
    {
      fprintf(stderr, "erreur lors du mkdir de %s\n",name);
      exit (EXIT_FAILURE);
    }
  }
  return name;
}






int main(int argc, char** argv)
{
  test1(argc, argv);
  char* real_name = create_directory(argv);
  printf("%s\n", real_name);
  // char file[TAILLE];
  // sprintf(file ,"%s", ".BACKUP_");
  // sprintf(file + strlen(file),"%s", argv[1]);
  // printf("le chemin :%s:\n", file);
  //
  // if (access(file, F_OK) != 0)
  // {
  //   int dd = mkdir(file, 0777);
  //   open_error(dd);
  // }
  create_backup(argv[1], real_name);
  // printf(" valeur de cmp %i\n", cmp(argv[1], argv[2]));
  return 0;
}
