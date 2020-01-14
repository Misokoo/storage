#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int lireligne(int fd, char *buffer, int size) {
	// on essaie de lire size caractères dans fd
	// on place les caractères dans buffer
	// nbread est le nombre de caractères lus
	ssize_t nbread = read(fd, buffer, size);
	if (nbread == -1) {
		// si la lecture a échoué
		return -1;
	}

	int i; // indice de parcours de buffer
	// on parcourt les nbread premières cases de buffer
	// pour trouver un éventuel retour à la ligne
	for (i = 0; i < nbread; i++) {
		if (buffer[i] == '\n') {
			// si on trouve un retour à la ligne
			// on incrémente i et on arrète le parcours
			i++;
			break;
		}
	}
	// ici, i correspond au nombre de caractères retenus

	// il faut maintenant reculer le curseur de lecture
	// nb caractères lus = nbread
	// nb caractères conservés = i
	// -> il faut reculer de (nbread-i)
	lseek(fd, i - nbread, SEEK_CUR);
	return i;
}

int main(int argc, char **argv) {
	char buf[80];
	int nbread;
	
	int fdin = open(argv[1], O_RDONLY);
	if (fdin == -1) {
		perror(argv[1]);
		exit(1);
	}
	
	nbread = lireligne(fdin, buf, 80);
	write(1, buf, nbread);
	nbread = lireligne(fdin, buf, 80);
	write(1, buf, nbread);
	nbread = lireligne(fdin, buf, 80);
	write(1, buf, nbread);
}