#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_MAX 200

void print_bytec(FILE *f) {
    char *fileline = malloc(sizeof(char) * LINE_MAX);
    int bytec = 0;

    while(fgets(fileline, LINE_MAX, f)) {
        bytec += strlen(fileline);
    }
    free(fileline);

    printf("%d ", bytec);
}

void print_wordc(FILE *f) {
    char *fileline = malloc(sizeof(char) * LINE_MAX);
    int wordc = 0;

    while(fgets(fileline, LINE_MAX, f)) {
        for(int i = 0; i < strlen(fileline); i++) {
            if(fileline[i] == ' ' &&
               fileline[i+1] != ' ' &&
               fileline[i+1] != '\0' &&
               fileline[i+1] != '\n') {
                wordc++;
            }
        }
        if(fileline[0] != '\n' && fileline[0] != ' ') wordc++;
    }
    free(fileline);

    printf("%d ", wordc);
}

void print_linec(FILE *f) {
    char *fileline = malloc(sizeof(char) * LINE_MAX);
    int linec = 0;

    while(fgets(fileline, LINE_MAX, f)) {
        //if(fileline[strlen(fileline) - 1] == '$') linec++;
        //se não tiver uma linha vazia à frente, o wc não conta
        //??
        linec++;
    }
    free(fileline);

    printf("%d  ", linec);
}

void print_wc_opt(const char* filename, const char *opt) {
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    if(opt == NULL) {
        printf(" ");
        print_linec(f);
        rewind(f);
        print_wordc(f);
        rewind(f);
        print_bytec(f);
        printf("%s\n", filename);
        return;
    }

    switch(opt[1]) {
        case 'c':
            print_bytec(f);
            break;
        case 'w':
            print_wordc(f);
            break;
        case 'l':
            print_linec(f);
            break;
    }
    printf("%s\n", filename);

    if(fclose(f) != 0) {
        printf("Unable to close file properly\n");
    }
}

int main(int argc, char *argv[]) {
    if(strcmp(argv[1], "-c") == 0 || 
       strcmp(argv[1], "-w") == 0 ||
       strcmp(argv[1], "-l") == 0) {
        print_wc_opt(argv[2], argv[1]);
    } else if(argv[1][0] == '-') {
        printf("chcase: invalid option -- '%c'\n", argv[1][1]);
        printf("Valid options are \"-c\" and \"-w\" \"-l\" "
        "for byte count, word count and line count respectively\n");
        printf("Executing anyway...\n");
        print_wc_opt(argv[2], NULL);
    } else {
        print_wc_opt(argv[1], NULL);
    }
}