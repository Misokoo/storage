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
int cmp(char* path1, char* path2);
int check_if_changer(char* src, char* dst);

/*
Seuls les tests 1 et 2 marchent, les backups avec liens physiques
ont posés problèmes pour la recupération du nom du fichier de la version
précédente pour le comparer.
Les fonction cmp et checkifchanger n'ont donc pas été utilisés avec un
aboutissement mais je les ai laissés et mis en commentaire le code
essayant de mettre en palce les liens physiques pour montrer l'idée.
*/



/*
une variable globale qui contient .BACKUP_filename/versionbackup après la
premiere fonction, facilite grandement le code.
*/
char backup_repository[TAILLE];

/*
Deux fonctions pour se faciliter la vie
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



/*
fonction permettant la copie d'un fichier d'emplacement path_src
à l'emplacement path_dst
*/
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





/*
fonction permettant de savoir le nombre de abckups faite, cette est
specifiquement faite pour le dossier ./backup_file
(on ne test pas si les éléments sont des dossiers ou fichiers en parcourant
le dossier)
*/
size_t get_nb_backups(char* main_directory)
{
	DIR* dp = opendir(main_directory);
	size_t cpt = 0;
	if (dp == NULL)
	raler("open main directory");
	struct dirent* d;
	while  ((d= readdir (dp)) != NULL)
		cpt++;
	cpt = cpt -2;
	if (cpt == 10)
		return EXIT_FAILURE;
	return cpt;
}



/*
fonction qui créé une backup

entrée : repertory_origin est argv[1], soit le nom du dossier a backup
repertory dest est la varaible globale sous la forme de la chaine de
caractère ".BACKUP_filename/versionbackup"
*/
void create_backup(char* repertory_origin, char* repertory_dest)
{
	//size_t backups_nb = get_nb_backups(backup_repository);
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
			sprintf(path_dst + strlen(path_dst),"/%s", d->d_name);
			stat(path_src, &stbuf);
			printf("on est dans %s\n", path_src);
			if (S_ISREG(stbuf.st_mode))
			{
				// if ( (backups_nb > 0 ) && (check_if_changer(path_src,
				// path_dst) == 1))
				// {
				//		printf("creation du lien physique effectuée\n");
				// }
				// else
				// {
				//   copie_file(path_src, path_dst);
				//   printf(" on a copie le fichier dorigine %s en fichier
				// %s\n", path_src, path_dst);
				// }
				copie_file(path_src, path_dst);
			}
			else if(S_ISDIR(stbuf.st_mode))
			{
				sprintf(path_dst + strlen(path_dst),"%s", "/");
				sprintf(path_src + strlen(path_src),"%s", "/");
				int dd = mkdir(path_dst, 0777);
				open_error(dd);
				create_backup(path_src, path_dst);
			}
		}
	}
	if (closedir (d_origin) ==  -1)
	raler ("closedir");
}






/*
creation du répertoire des backups, et du dossier de la backup en cours, et
renvoie le nom du répertoire créé

valeur de retour :
.BACKUP_filename/versionbackup
*/
char* create_directory_backups(char** argv)
{
	sprintf(backup_repository ,"%s", ".BACKUP_");
	size_t j=strlen(backup_repository);
	for(size_t i = 0; i < strlen(argv[1]); i++)
	{
		if(argv[1][i] == '/')
			j=strlen(".BACKUP_");
		else
		{
			backup_repository[j] = argv[1][i];
			j++;
		}
	}
	backup_repository[strlen(".BACKUP_")+j -1] = '\0';
	if (access(backup_repository, F_OK) != 0)
	{
		int dd2 = mkdir(backup_repository, 0777);
		if (dd2 == -1)
		{
			fprintf(stderr, "erreur lors du mkdir de %s\n",backup_repository);
			exit (EXIT_FAILURE);
		}
	}
	int nb_backup = get_nb_backups(backup_repository);
	sprintf(backup_repository + strlen(backup_repository),"%s", "/");
	sprintf(backup_repository + strlen(backup_repository),"%i", nb_backup);
	int nb_backup_repository = mkdir(backup_repository, 0777);
	open_error(nb_backup_repository);
	return backup_repository;
}




/*
fonction qui a le même fonctionnement que la commande cmp en shell

valeur de sortie :
0 si les deux fichiers sont identiques
1 sinon
*/

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

/*
fonction permettant de voir si deux fichiers sont identiques, dans l'esprit
d'utiliser ls liens physique apres.
Cela n'a pas aboutie car je n'ai pas réussie à récuperer la version de la
backup précédente du fichier
*/
int check_if_changer(char* src, char* dst)
{
	char previous_file[TAILLE];
	size_t backups_nb = get_nb_backups(backup_repository);
	sprintf(previous_file, "%s", backup_repository);
	sprintf(previous_file + strlen(previous_file),"%s", "/");
	sprintf(previous_file + strlen(previous_file),"%li", (backups_nb-1));
	if (backups_nb > 0)
	{
		int rep = cmp(src, dst);
		if (rep == 0)
		{
			link(src, dst);
			return 1;
		}
	}
	return 0;
}



int main(int argc, char** argv)
{
	test1(argc, argv);
	char* name_backup_repository = create_directory_backups(argv);
	create_backup(argv[1], name_backup_repository);
	return 0;
}
