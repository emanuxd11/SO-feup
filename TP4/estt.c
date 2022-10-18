#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *string = malloc(512);
    sprintf(string, "mystring.cringe");
    printf("%s\n", string);
    sprintf(string, "%s second %s part of string", string, string);
    printf("To check if it worked:\n");
    printf("%s", string);
}
