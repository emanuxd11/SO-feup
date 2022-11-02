#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /* fork a child process */
    fork();
    printf("%d\n", getpid());

    /* fork another child process */
    fork();
    printf("%d\n", getpid());

    /* and fork another */
    fork();
    printf("%d\n", getpid());

    return EXIT_SUCCESS;
}

// Palpite: 4 processos - main +
// os outros 3 child processes
// Processos = 2^n_forks = 8 ?