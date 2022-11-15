#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1

#define LINESIZE 256

int main(int argc, char *argv[]) {
    int nbytes, fd[2];
    pid_t pid;
    char line[LINESIZE];

    int fileDesc;
    if ((fileDesc = open(argv[1], O_RDONLY)) < 0) {
        perror("open error");
    }

    if (pipe(fd) < 0) {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        /* parent */
        close(fd[READ_END]);
        printf("Parent process with pid %d\n", getpid());
        printf("Messaging the child process (pid %d):\n", pid);

        int rd;
        while((rd = read(fileDesc, line, LINESIZE)) != 0) {
            if (rd < 0) {
                perror("read error");
                exit(EXIT_FAILURE);
            }

            if ((nbytes = write(fd[WRITE_END], line, rd)) < 0) {
                fprintf(stderr, "Unable to write to pipe: %s\n", strerror(errno));
            }

        }

        close(fd[WRITE_END]);

        /* wait for child and exit */
        if (waitpid(pid, NULL, 0) < 0) {
            fprintf(stderr, "Cannot wait for child: %s\n", strerror(errno));
        }
        exit(EXIT_SUCCESS);
    } else {
        /* child */
        close(fd[WRITE_END]);
        printf("Child process with pid %d\n", getpid());
        printf("Receiving message from parent (pid %d):\n", getppid());
        while ((nbytes = read(fd[READ_END], line, LINESIZE)) != 0) {
            if (nbytes < 0) {
                fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
            }

            /* write message from parent */
            write(STDOUT_FILENO, line, nbytes);
        }
        
        close(fd[READ_END]);
        /* exit gracefully */
        exit(EXIT_SUCCESS);
    }
}