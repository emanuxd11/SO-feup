#define _GNU_SOURCE
//Para definir get_current_dir_name (ver man getcwd)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc != 1) {
        printf("./mypwd: too many arguments\n");
        return EXIT_FAILURE;
    }

    char *cwd_name = get_current_dir_name();
    if(cwd_name == NULL) return EXIT_FAILURE;
    
    printf("%s\n", cwd_name);
    free(cwd_name);
    return EXIT_SUCCESS;
}