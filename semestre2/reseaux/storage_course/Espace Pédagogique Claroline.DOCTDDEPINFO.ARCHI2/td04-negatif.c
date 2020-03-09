#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int lireligne(int fd, char *buffer, int size) {
	ssize_t nbread = read(fd, buffer, size);
	if (nbread == -1) {
		return -1;
	}

	int i;
	for (i = 0; i < nbread; i++) {
		if (buffer[i] == '\n') {
			i++;
			break;
		}
	}
	lseek(fd, i - nbread, SEEK_CUR);
	return i;
}

int main(int argc, char **argv) {
	int fdin, fdout, i, nbread;
	char buffer[4096];
	
	// ouverture du premier fichier en lecture
	fdin = open(argv[1], O_RDONLY);
	if (fdin < 0) {
		perror(argv[1]);
		exit(1);
	}
	
	// ouverture du second fichier en écriture
	fdout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout < 0) {
		perror(argv[2]);
		exit(1);
	}
	
	// copie les trois premières lignes (en-tête)
	for (i = 0; i < 3; i++) {
		nbread = lireligne(fdin, buffer, 4096);
		write(fdout, buffer, nbread);
	}
	
	// lecture des pixels de l'image
	do {
		// lecture de pixels dans le buffer
		nbread = read(fdin, buffer, 4096);
		// inversion des pixels lus
		for (i = 0; i < nbread; i++) {
			buffer[i] = 255 - buffer[i];
		}
		// écriture des pixels inversés
		write(fdout, buffer, nbread);
	} while (nbread > 0);
	
	close(fdin);
	close(fdout);
}