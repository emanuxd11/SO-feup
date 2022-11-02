#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for (int i = 0; i < 4; i++) {
        fork();
    }

    printf("[%d][%d]\n", getppid(), getpid());


    return EXIT_SUCCESS;
}

// Penso que novamente seja 2^4 = 16 processos (sim)