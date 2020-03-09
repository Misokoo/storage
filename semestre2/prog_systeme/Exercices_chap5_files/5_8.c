#define CHECK(op) do { if (op == -1) raler(#op) ; } while (0)
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdnoreturn.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#define LENGTH 200

/*
OUBLIER STRCPY PCK RENVOIE PAS DERREUR SI ON COPIE UN CHAR* DANS UN CHAR*
PLUS PETIT
GO UTILISER SNPRINTF PCK RENVOIE LERREUR SI DEPASSEMENT OU AUTRE
STR CAT POUBELLE TOUT CE QUI YA STR DEDANS EN FAITE
*/
noreturn void raler(const char *msg, ...)
{
	va_list ap;

	va_start(ap, msg);
	vfprintf(stderr, msg, ap);
	fprintf(stderr, "\n");
	va_end(ap);

	perror("");
	exit(EXIT_FAILURE);
}


void print_permissions(int mode)
{
	int proprietaire = (mode >> 6) & 7;
	int groupe = (mode >> 3) & 7;
	int autre = mode & 7;
	char* perm[8]={"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
	write(1, perm[proprietaire], 3);
	write(1, perm[groupe], 3);
	write(1, perm[autre], 3);
}

int main(int argc, char** argv)
{


	struct stat stbuf;
	int stbuf_ret = lstat(argv[1], &stbuf);
	CHECK(stbuf_ret);
	//size_t permission = stbuf.st_mode & 0xf000;
	switch (stbuf.st_mode & S_IFMT) {
  case S_IFDIR:
	  write(1,"d", 1);
		break;

  case S_IFLNK:
	  write(1,"l", 1);
	  break;

  case S_IFREG:
	  write(1,"-", 1);
		break;

  default:
		write(1,"?", 1);
		break;
  }

	print_permissions(stbuf.st_mode & 0777);
	write(1, "\n", 1);
	return 0;
}
