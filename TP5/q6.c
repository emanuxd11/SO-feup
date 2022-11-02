#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char buf[1024];
    char* command;
    pid_t pid;

    /* do this until you get a ^C or a ^D */
    for ( ; ; ) {
        /* give prompt, read command and null terminate it */
        fprintf(stdout, "$ ");
        if((command = fgets(buf, sizeof(buf), stdin)) == NULL)
            break;
        command[strlen(buf) - 1] = '\0';

        /* create array of options */
        char *option = strtok(command, " ");
        char **options = malloc(1 * sizeof(char*));
        int nOptions = 0;
        while (1) {
            options[nOptions++] = option;
            if (option == NULL) break;
            options = realloc(options, (1 + nOptions) * sizeof(char*));
            option = strtok(NULL, " ");
        }

        /* call fork and check return value */
        if ((pid = fork()) == -1) {
            fprintf(stderr, "%s: can't fork command: %s\n",
            argv[0], strerror(errno));
            continue;
        } else if (pid == 0) {
            /* child */
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
        
        free(options);
    }

    exit(EXIT_SUCCESS);
}

// execv takes a pointer to an array of arguments
// last element of this array needs to be a null
// pointer, just like in the main() arguments