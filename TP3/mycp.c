#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX 200

void print_file(const char *origin, const char* destiny) {
    FILE *forigin = fopen(origin, "r");
    FILE *fdestiny = fopen(destiny, "w");
    if(forigin == NULL || fdestiny == NULL) {
        printf("Unable to open files\n");
        return;
    }

    char *fileline = malloc(sizeof(char) * LINE_MAX);
    while(fgets(fileline, LINE_MAX, forigin)) {
        fprintf(fdestiny, "%s", fileline);
    }
    free(fileline);

    if(fclose(forigin) != 0 || fclose(fdestiny) != 0) {
        printf("Unable to close files properly\n");
    }
}

int main(int argc, char *argv[]) {
    for(int i = 1; i < argc; i += 2) {
        print_file(argv[i], argv[i+1]);
    }
}