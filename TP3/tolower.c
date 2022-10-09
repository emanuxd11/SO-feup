#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    printf("Original string: %s\n", argv[1]);
    
    for(int i = 0; i < strlen(argv[1]); i++) {
        if(isupper(argv[1][i])) {
            argv[1][i] = tolower(argv[1][i]);
        }
    }

    printf("String all in lowercase: %s", argv[1]);
}