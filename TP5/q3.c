#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int value = 0;

    if((pid = fork()) == -1) {
        perror("fork");
        return EXIT_FAILURE;
    } else if(pid == 0) {
        /* child process */
        value = 1;
        printf("CHILD: value = %d, addr = %p\n", value, &value);
        return EXIT_SUCCESS;
    } else {
        /* parent process */
        if (waitpid(pid, NULL, 0) == -1) {
            perror("wait");
            return EXIT_FAILURE;
        }

        printf("PARENT: value = %d, addr = %p\n", value, &value);
        return EXIT_SUCCESS;
    }
}

// É executado o fork: 
// - o child process é executado primeiro
//   porque dentro do parent process existe
//   um wait() que obriga a que o parent
//   apenas execute após o seu child ter terminado
// - o pid do child process é sempre 0, logo
//   como este é executado primeiro, value = 1
//   e dá-se print a CHILD: value = 1, etc
// - o child process acaba
// - o parent process retoma a execução a partir 
//   do wait() e dá print ao PARENT = $value, etc,
//   lembrando sempre que value = 0 porque foi assim
//   declarado no início da função main, e este valor
//   apenas foi alterado dentro do child process
//   que já terminou :)
// - Os endereços são os mesmos porque a variável
//   foi declarada no início do programa e é sempre
//   a mesma :D