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
#define NAME_SIZE 1000

void raler(char *msg)
{
    perror(msg);
    exit(1);
}
// memcpy
// strtol, strktor, open, close, opendirr, closedirr, snprintf, strcat

void concat_path(char *dst, const char *str1, const char *str2, const char *str3)
{
    int n;

    if ((n = snprintf(dst, NAME_SIZE, "%s%s%s", str1, str2, str3)) >= NAME_SIZE || n < 0)
        raler("snprintf error");

    return;
}

void test1(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: nb arg");
        exit(EXIT_FAILURE);
    }

    //test si argv[1] est un repertoire
    DIR *dp;
    dp = opendir(argv[1]);
    if (dp == NULL)
    {
        perror("usage: ");
        exit(EXIT_FAILURE);
    }

    struct stat stbuf;
    stat(argv[1], &stbuf);
    if (!S_ISDIR(stbuf.st_mode))
    {
        perror("usage: ");
        exit(EXIT_FAILURE);
    }
    // test si le dossier est accessible
    if (access(argv[1], R_OK | X_OK) == -1)
    {
        perror("usage: ");
        exit(EXIT_FAILURE);
    }
    closedir(dp);
    if (dp == NULL)
        raler("closedir");
}

void test2(char *dir)
{
    int status;
    pid_t pid;
    DIR *dp;
    dp = opendir(dir);
    if (dp == NULL)
    {
        perror("error when opening a dir");
        exit(EXIT_FAILURE);
    }
    struct dirent *dp_dirent;
    struct stat stbuf;
    struct stat stbuf_file;
    char file[NAME_SIZE];
    while ((dp_dirent = readdir(dp)) != NULL)
    {
        stat(dir, &stbuf);

        concat_path(file, dir, "/", dp_dirent->d_name);
        stat(file, &stbuf_file);
        if (S_ISREG(stbuf_file.st_mode))
        {
            unlink(file);
        }
    }


    while ((dp_dirent = readdir(dp)) != NULL)
    {
        stat(dir, &stbuf);

        concat_path(file, dir, "/", dp_dirent->d_name);
        stat(file, &stbuf_file);
        if (S_ISDIR(stbuf_file.st_mode))
        {
            pid = fork();
            switch (pid)
            {
            case -1:
                raler("fork");
                break;

            case 0:
                printf("fils %i\n", getpid());
                test2(file);
                exit(pid);
                break;

            default:
                if (wait(&status) == -1)
                    raler("wait");
                break;
            }
        }
    }

    rmdir(dir);
}

// gcc -g -Wall -Wextra -Werror -Wvla

int main(int argc, char **argv)
{
    test1(argc, argv);
    test2(argv[1]);
    return 0;
}
//unlink