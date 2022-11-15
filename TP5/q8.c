#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h> 

int main(int argc, char* argv[]) {
    char buf[1024];
    char *command;
    char *historyFile = ".histfile";
    pid_t pid;

    /* do this until you get a ^C or a ^D */
    for ( ; ; ) {
        /* give prompt, read command and null terminate it */
        fprintf(stdout, "[crapshell] > ");
        if((command = fgets(buf, sizeof(buf), stdin)) == NULL)
            break;
        command[strlen(buf) - 1] = '\0';

        /* create array of options */
        char *option = strtok(command, " ");
        char **options = malloc(1 * sizeof(char*));
        int nOptions = 0;
        while (1) {
            options[nOptions] = option;
            if (option == NULL) break;

            nOptions++;
            options = realloc(options, (1 + nOptions) * sizeof(char*));
            option = strtok(NULL, " ");
        }

        if (strcmp(command, "exit") == 0) {
            free(options);
            exit(EXIT_SUCCESS);
        }

        /* call fork and check return value */
        if ((pid = fork()) == -1) {
            fprintf(stderr, "%s: can't fork command: %s\n",
            argv[0], strerror(errno));
            continue;
        } else if (pid == 0) {
            /* child */
            if (strcmp(command, "myhistory") == 0) {
                execlp("tail", "tail", historyFile, "-n", options[1], NULL);
            } 

            execvp(command, options);

            /* if I get here "execlp" failed */
            fprintf(stderr, "%s: couldn't exec %s: %s\n",
            argv[0], buf, strerror(errno));

            /* terminate with error to be caught by parent */
            free(options);
            exit(EXIT_FAILURE);
        }

        /* shell waits for command to finish before giving prompt again */
        if ((pid = waitpid(pid, NULL, 0)) < 0)
            fprintf(stderr, "%s: waitpid error: %s\n",
            argv[0], strerror(errno));
        
        /* concatenate all options into one string to go in history */
        char entry[1024];
        strcpy(entry, "");
        for (int i = 0; i < nOptions; i++) {
            if (options[i] == NULL) break;
            strcat(entry, options[i]);
            if (i + 1 < nOptions) {
                strcat(entry, " ");
            } else {
                strcat(entry, "\n");
            }
        }

        /* append this new entry to the .myhistory file */
        int fd = open(historyFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0) {
            fprintf(stderr, "error opening %s: %s\n", historyFile, strerror(errno));
            exit(EXIT_FAILURE);
        }
        if (write(fd, entry, strlen(entry)) == -1) {
            fprintf(stderr, "error writing to %s: %s\n", historyFile, strerror(errno));
            exit(EXIT_FAILURE);
        }
        if (close(fd) != 0) {
            fprintf(stderr, "error closing %s: %s\n", historyFile, strerror(errno));
            exit(EXIT_FAILURE);
        }

        /* free malloc-ed memory :D */
        free(options);
    }

    exit(EXIT_SUCCESS);
}
