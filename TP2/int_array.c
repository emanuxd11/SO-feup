#include <stdio.h>
    int main() {
    int i;
    int primes[] = {2, 3, 5, 7, 11};

    for (i = 0; i < sizeof(primes)/sizeof(int); i++) {
        printf("%d <--> %d\n", primes[i], *(primes + i));
    }

    return 0;
}

//primes comporta-se como um int*
//cada incremento de i corresponde
//a 4 bytes, que é o tamanho ocupado
//por variáveis de tipo int neste sistema