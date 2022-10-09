#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 200

void print_loc(const char *haystack, const char *needle) {
    FILE *f = fopen(haystack, "r");
    if(f == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char *fileline = malloc(sizeof(char) * LINE_MAX);
    int line = 0, j, column;
    while(fgets(fileline, LINE_MAX, f)) {
        line++;
        for(int i = 0; fileline[i] != '\0'; i++) {
            for(j = 0; needle[j] != '\0' && needle[j] == fileline[i+j]; j++);
            if(needle[j] == '\0') {
                column = i+1;
                printf("[%d:%d]\n", line, column);
            }
        }
    }
    free(fileline);

    if(fclose(f) != 0) {
        printf("Unable to close file properly\n");
    }
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Insufficient arguments\n");
    } else {
        print_loc(argv[2], argv[1]);
    }
}