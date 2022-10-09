#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX 200

void print_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char *fileline = malloc(sizeof(char) * LINE_MAX);
    while(fgets(fileline, LINE_MAX, f)) {
        printf("%s", fileline);
    }
    free(fileline);

    if(fclose(f) != 0) {
        printf("Unable to close file properly\n");
    }
}

int main(int argc, char *argv[]) {
    for(int i = 1; i < argc; i++) {
        print_file(argv[i]);
    }
}