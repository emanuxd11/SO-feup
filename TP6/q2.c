#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

char* cmd1[] = {"ls", "-l", NULL};
char* cmd2[] = {"wc", "-l", NULL};

int main (int argc, char* argv[]) {
    int fd[2];
    pid_t pid;

    if (pipe(fd) < 0) {
        /* pipe error */
        perror("pipe error");
    }

    if ((pid = fork()) < 0) {
        /* fork error */
        perror("fork error");
    }

    if (pid > 0) {
        close(fd[READ_END]);
        dup2(fd[WRITE_END], STDOUT_FILENO); // stdout to pipe
        close(fd[WRITE_END]);

        // parent writes to the pipe
        if (execvp(cmd1[0], cmd1) < 0) {
            /* exec error */
            perror("exec error");
        }
    } else {
        close(fd[WRITE_END]);
        dup2(fd[READ_END], STDIN_FILENO); // stdin from pipe
        close(fd[READ_END]);

        if (execvp(cmd2[0], cmd2) < 0) {
            /* exec error */
            perror("exec error");
        }
    }
}