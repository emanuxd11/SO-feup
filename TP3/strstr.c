#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(strstr(argv[2], argv[1])) {
        printf("String %s is present in %s", argv[1], argv[2]);
    } else {
        printf("String %s is not present in %s", argv[1], argv[2]);
    }
}