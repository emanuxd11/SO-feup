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
        if(fileline[strlen(fileline) - 1] == '\n') linec++;
    }
    free(fileline);

    printf("%d  ", linec);
}

void print_wc_opt(const char* filename, const char opt) {
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    if(opt == '\0') {
        printf(" ");
        print_linec(f);
        rewind(f);
        print_wordc(f);
        rewind(f);
        print_bytec(f);
        printf("%s\n", filename);
        return;
    }

    switch(opt) {
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

char *findopt(int n, char *args[], int *retn) {
    if(n == 1) return NULL;
    if(args == NULL) return NULL;

    char optlist[] = {'c', 'w', 'l'};
    int optn = 3;
    char *options = malloc(sizeof(char));
    *retn = 0;

    for(int i = 1; i < n; i++) {
        if(args[i][0] != '-') continue;

        for(int j = 1; j < strlen(args[i]); j++) {
            for(int k = 0; k < optn; k++) {
                if(args[i][j] != optlist[k]) continue;

                options = realloc(options, ((*retn) + 1) * sizeof(char));
                if(options == NULL) return NULL;
                
                options[(*retn)++] = optlist[k];
            }
        }
    }

    if(*retn == 0) {
        free(options);
        return NULL;
    }

    return options;
}

char **findarguments(int n, char *args[], int *retn) {
    if(n == 1) return NULL;
    if(args == NULL) return NULL;

    char **arguments = malloc(sizeof(char*));
    *retn = 0;

    for(int i = 1; i < n; i++) {
        if(args[i][0] == '-') continue;
        arguments = realloc(arguments, ((*retn) + 1) * sizeof(char*));
        if(arguments == NULL) return NULL;
        arguments[(*retn)++] = args[i];
    }

    if(*retn == 0) {
        free(arguments);
        return NULL;
    }

    return arguments;
}

int main(int argc, char *argv[]) {
    int optn = 0, argn = 0;
    char *options = findopt(argc, argv, &optn);
    char **arguments = findarguments(argc, argv, &argn);

    for(int i = 0; i < argn; i++) {
        if(options == NULL) {
            print_wc_opt(arguments[i], '\0');
            continue;
        }

        for(int j = 0; j < optn; j++) {
            print_wc_opt(arguments[i], options[j]);
        }
    }
    if(arguments != NULL) free(arguments);
    if(options != NULL) free(options);


    /*printf("Options:\n");
    for(int i = 0; i < optn; i++) {
        printf("%c\n", options[i]);
    }
    free(options);

    printf("Args:\n");
    for(int i = 0; i < argn; i++) {
        printf("%s\n", arguments[i]);
    }*/

    /*if(strcmp(argv[1], "-c") == 0 || 
       strcmp(argv[1], "-w") == 0 ||
       strcmp(argv[1], "-l") == 0) {
        print_wc_opt(argv[2], argv[1]);
    } else if(argv[1][0] == '-') {
        printf("mywc: invalid option -- '%c'\n", argv[1][1]);
        printf("Valid options are \"-c\" and \"-w\" \"-l\" "
        "for byte count, word count and line count respectively\n");
        printf("Executing anyway...\n");
        print_wc_opt(argv[2], NULL);
    } else {
        print_wc_opt(argv[1], NULL);
    }*/
}