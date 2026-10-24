/* tee.c - TLPI Exercise 4-1: copy standard input to standard output AND a file.
 *
 *   ./tee file      erase the file first, then write to it
 *   ./tee -a file   append to the end of the file
 */
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    char buf[BUF_SIZE];
    ssize_t numRead;
    int fileFd, openFlags;
    char *filename;

    if (argc == 3 && strcmp(argv[1], "-a") == 0) {
        /* tee -a out.txt */
        openFlags = O_WRONLY | O_CREAT | O_APPEND;
        filename = argv[2];
    } else if (argc == 2) {
        /* tee out.txt */
        openFlags = O_WRONLY | O_CREAT | O_TRUNC;
        filename = argv[1];
    } else {
        fprintf(stderr, "Usage: %s [-a] file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fileFd = open(filename, openFlags, 0644);
    if (fileFd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, numRead) != numRead) {
            perror("write to stdout");
            exit(EXIT_FAILURE);
        }
        if (write(fileFd, buf, numRead) != numRead) {
            perror("write to file");
            exit(EXIT_FAILURE);
        }
    }

    if (numRead == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    if (close(fileFd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
