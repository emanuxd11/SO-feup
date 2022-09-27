#include <stdio.h>
    int main() {
    int i;
    char msg[] = "Hello World";
    
    for (i = 0; i < sizeof(msg); i++) {
        printf("%c <--> %c\n", msg[i], *(msg + i));
    }

    return 0;
}
//A variável msg comporta-se como se fosse de tipo char*
//Cada incremento de i corresponde a 1 byte