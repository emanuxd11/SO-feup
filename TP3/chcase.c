#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 

#define LINE_MAX 200

char *strlow(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if(isupper(str[i])) {
            str[i] = tolower(str[i]);
        }
    }
    return str;
}

char *strup(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if(islower(str[i])) {
            str[i] = toupper(str[i]);
        }
    }
    return str;
}

void chprint(char *fileline, char *opt) {
    if(opt == NULL) {
        printf("%s", fileline);
        return;
    }

    if(strcmp(opt, "-u") == 0) {
        printf("%s", strup(fileline));
    } else if(strcmp(opt, "-l") == 0) {
        printf("%s", strlow(fileline));
    }
}

void print_file_chcase(char *filename, char *opt) {
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char *fileline = malloc(sizeof(char) * LINE_MAX);
    while(fgets(fileline, LINE_MAX, f)) {
        chprint(fileline, opt);
    }
    free(fileline);

    if(fclose(f) != 0) {
        printf("Unable to close file properly\n");
    }
}

//Todo: allow multiple files and many option locations
int main(int argc, char *argv[]) {
    if(strcmp(argv[1], "-u") == 0 || 
       strcmp(argv[1], "-l") == 0) {
        print_file_chcase(argv[2], argv[1]);
    } else if(argv[1][0] == '-') {
        printf("chcase: invalid option -- '%c'\n", argv[1][1]);
        printf("Valid options are \"-u\" and \"-l\" for upper case and lower case respectively\n");
        printf("Executing anyway...\n");
        print_file_chcase(argv[2], NULL);
    } else {
        print_file_chcase(argv[1], NULL);
    }
}