#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <errno.h>
#define LONG_MAX 4
#define LONG_MIN 0
#define SIZE 1024

void raler(char *msg)
{
	perror(msg);
	exit(1);
}

/*
Une seule fonction ( un peu longue) qui teste juste les  pre requis pour
faire le programme.
*/
void test1(int argc, char **argv)
{
	if (argc < 3)
	{
		fprintf(stderr, "usage: not enough arg\n");
		exit(EXIT_FAILURE);
	}
	if (argc > 1025)
	{
		fprintf(stderr, "usage: too much arg\n");
		exit(EXIT_FAILURE);
	}

	char *str = argv[1];
	int base = 10;
	char *endptr;
	long val = strtol(str, &endptr, base);
	errno = 0;
	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0))
	{
		perror("strtol");
		exit(EXIT_FAILURE);
	}
	if (endptr == str)
	{
		fprintf(stderr, "usage: maxchunksize nest pas un nombre\n");
		exit(EXIT_FAILURE);
	}

	if (atoi(argv[1]) < 1)
	{
		fprintf(stderr, "usage: max_chunck_size < 1\n");
		exit(EXIT_FAILURE);
	}

	if (atoi(argv[1]) > 1024)
	{
		fprintf(stderr, "usage: max_chunck_size  > 1024\n");
		exit(EXIT_FAILURE);
	}

	for (ssize_t i = 2; i < argc; i++)
	{
		str = argv[i];
		val = strtol(str, &endptr, base);
		errno = 0;
		if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0))
		{
			perror("strtol");
			exit(EXIT_FAILURE);
		}
		if (endptr == str)
		{
			fprintf(stderr, "usage: valeur nest pas un nombre\n");
			exit(EXIT_FAILURE);
		}
		else if (atoi(argv[i]) < 0)
		{
			fprintf(stderr, "usage: valeur negative\n");
			exit(EXIT_FAILURE);
		}
		else if (atoi(argv[i]) > 127)
		{
			fprintf(stderr, "usage: valeur > 127\n");
			exit(EXIT_FAILURE);
		}
	}
}

int look_for_max(int *chunk, int deb, int length, int chunk_size)
{
	int maxfinal = 0;
	pid_t pid, pid2;
	int size_first;
	int max1;
	int status;
	if (((length - deb) % 2) == 0)
		size_first = ((length - deb) / 2);
	else
		size_first = (length - deb - 1) / 2;

	if ((length - deb) > chunk_size)
	{
		pid = fork();
		switch (pid)
		{
		case -1:
			raler("fork");
			break;
		case 0:
			max1 = look_for_max(chunk, deb, length - size_first, chunk_size);
			printf("valeur de max1 : %i\n", max1);
			exit(max1);
			break;
		default:
			if(wait(&status) == -1)
				raler("wait");
			if (WIFEXITED(status))
				max1 = WEXITSTATUS(status);

			pid2 = fork();
			int max2;
			if (pid2 == -1)
				raler("fork");
			else if (pid2 == 0)
			{
				max2 = look_for_max(chunk, length - size_first, length, chunk_size);
				exit(max2);
			}
			else
			{
				if(wait(&status) == -1)
					raler("raler");
				if (WIFEXITED(status) > 0)
					max2 = WEXITSTATUS(status);

				if (max1 > max2)
					maxfinal = max1;
				else
					maxfinal = max2;
			}
			break;
		}
	}
	else 
	{
		for (ssize_t i = deb; i < length; i++)
		{
			if (chunk[i] > maxfinal)
				maxfinal = chunk[i];
		}
	}
	return maxfinal;
}

int main(int argc, char **argv)
{
	test1(argc, argv);
	int chunk[SIZE];
	int j = 0;
	for (ssize_t i = 2; i < argc; i++)
	{
		chunk[j] = atoi(argv[i]);
		j++;
	}
	int max = look_for_max(chunk, 0, argc - 2, atoi(argv[1]));
	exit(max);
}
