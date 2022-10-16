#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_MAX 200
#define N_OPTIONS 3

char optlist[N_OPTIONS] = {'l', 'w', 'c'};

int count_byte(FILE *f) {
    char *fileline = malloc(sizeof(char) * LINE_MAX);
    int bytec = 0;

    while(fgets(fileline, LINE_MAX, f)) {
        bytec += strlen(fileline);
    }
    free(fileline);

    return bytec;
}

int count_word(FILE *f) {
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

    return wordc;
}

int count_line(FILE *f) {
    char *fileline = malloc(sizeof(char) * LINE_MAX);
    int linec = 0;

    while(fgets(fileline, LINE_MAX, f)) {
        if(fileline[strlen(fileline) - 1] == '\n') linec++;
    }
    free(fileline);

    return linec;
}

//has to be in format " line  word byte filename"
void print_wc_opt(const char* filename, const char *options, int optn) {
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    if(options == NULL && optn == 0) {
        printf(" %d ", count_line(f)); rewind(f);
        printf(" %d ", count_word(f)); rewind(f);
        printf("%d ", count_byte(f)); 
        printf("%s\n", filename); 

        if(fclose(f) != 0) {
            printf("Unable to close file properly\n");
        }
        
        return;
    }

    //spaces should make it lined up with the above
    for(int i = 0; i < N_OPTIONS; i++) {
        for(int j = 0; j < optn; j++) {
            if(options[j] != optlist[i]) continue;
                
            switch(options[j]) {
                case 'l':
                    if(optn > 1) printf(" ");
                    printf(" %d ", count_line(f));
                    break;
                case 'w':
                    if(optn > 1) printf(" ");
                    printf("%d ", count_word(f));
                    break;
                case 'c':
                    printf("%d ", count_byte(f));
                    break;
            }
        }
        rewind(f);
    }
    printf("%s\n", filename);

    if(fclose(f) != 0) {
        printf("Unable to close file properly\n");
    }
}

char *findopt(int n, char *args[], int *retn) {
    if(n == 1) return NULL;
    if(args == NULL) return NULL;

    char *options = malloc(sizeof(char));
    *retn = 0;

    for(int i = 1; i < n; i++) {
        if(args[i][0] != '-') continue;

        for(int j = 1; j < strlen(args[i]); j++) {
            for(int k = 0; k < N_OPTIONS; k++) {
                if(args[i][j] != optlist[k]) continue;
                
                int l;
                for(l = 0; l < *retn; l++) {
                    if(options[l] == optlist[k]) {
                        break;
                    }

                }
                if(l == *retn) {
                    options = realloc(options, ((*retn) + 1) * sizeof(char));
                    if(options == NULL) return NULL;
                    options[(*retn)++] = optlist[k];
                }
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

//add total count at the end -- 3
//make invalid option error and --help -- 2
//make prints line up between diff files -- 1
int main(int argc, char *argv[]) {
    int optn = 0, argn = 0; 
    char *options = findopt(argc, argv, &optn);
    char **arguments = findarguments(argc, argv, &argn);

    for(int i = 0; i < argn; i++) {
        print_wc_opt(arguments[i], options, optn);
    }
    if(arguments != NULL) free(arguments);
    if(options != NULL) free(options);
}