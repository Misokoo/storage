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
#define SIZE 1000

void raler(char *msg)
{
    perror(msg);
    exit(1);
}

// void test1(int argc, char **argv)
// {
//     if (argc != 2)
//     {
//         fprintf(stderr, "usage: nb arg");
//         exit(EXIT_FAILURE);
//     }

//     //test si argv[1] est un repertoire
//     DIR *dp;
//     dp = opendir(argv[1]);
//     if (dp == NULL)
//     {
//         perror("usage: ");
//         exit(EXIT_FAILURE);
//     }

//     struct stat stbuf;
//     stat(argv[1], &stbuf);
//     if (!S_ISDIR(stbuf.st_mode))
//     {
//         perror("usage: ");
//         exit(EXIT_FAILURE);
//     }
//     // test si le dossier est accessible
//     if (access(argv[1], R_OK | X_OK) == -1)
//     {
//         perror("usage: ");
//         exit(EXIT_FAILURE);
//     }
//     closedir(dp);
//     if (dp == NULL)
//         raler("closedir");

//     // test si argv[1] est bien un nombre
//     char *str = argv[1];
//     int base = 10;
//     char *endptr;
//     long val = strtol(str, &endptr, base);
//     if (endptr == str)
//     {
//         fprintf(stderr, "usage: maxchunksize nest pas un nombre\n");

//         exit(EXIT_FAILURE);
//     }
// }

int main(int argc, char **argv)
{
    // char request[SIZE];
    // fgets(request, SIZE, stdin);
    // request[strlen(request) - 1] = '\0';
    // ssize_t k = 0;
    // char *str = strtok(request, " ");
    // char request_splitted[SIZE][SIZE];
    // while (str != NULL)
    // {
    //     strcpy(request_splitted[k], str);
    //     k++;
    //     str = strtok(NULL, " ");
    // }

    // char buffer[SIZE];
    // strncpy(buffer, getenv("PATH"), SIZE);
    // char buffer_splitted[SIZE][SIZE];
    // int j = 0;
    // char *strbuf = strtok(buffer, ":");
    // while (strbuf != NULL)
    // {
    //     strcpy(buffer_splitted[j], strbuf);
    //     j++;
    //     strbuf = strtok(NULL, ":");
    // }

    printf("tout le buffer :\n");
    printf("%s\n", getenv("PATH"));
    printf("buffer splitted:\n");

    DIR *dp;
    for (ssize_t i = 0; i < j; i++)
    {
        dp = opendir(buffer_splitted[i]);
        if (dp == NULL)
        {
            perror("error when opening a dir");
            exit(EXIT_FAILURE);
        }
        struct dirent ⁎ dp_dirent;
        while ((dp_dirent = readdir (dp)) != -1 )
        {
            if(strcmp(dp_dirent.d_name, ".") && strcmp(dp_dirent.d_name, ".."))
            {
                if(!strcmp(request_splitted[0], dp_dirent.d_name))
                {
                    strcat(buffer_splitted[i], dp_dirent.d_name);
                    execv(/* a remplir*/)
                }
            }
        }

        closedir(dp);
    }

    // for(ssize_t i = 0; i< j ; i++)
    // {
    //     printf("%s\n", buffer_splitted[i]);
    // }

}