#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int print_file(const char *filename) {
    /* check if file can be opened and is readable */
    int fd = open(filename, O_RDONLY);
    if(fd == -1) {
        printf("error: cannot open %s\n", filename);
        return EXIT_FAILURE;
    }

    /* print the contents in blocks */
    char buffer[BUFFER_SIZE];
    int bytesin;
    while((bytesin = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytesin);
    }

    /* close file */
    close(fd);
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    /* check if at least one argument is present */
    if (argc < 2) {
        printf("usage: cat filename\n");
        return EXIT_FAILURE;
    }

    /* iterate for all files */
    int err_val;
    for(int i = 1; i < argc; i++) {
        err_val = print_file(argv[i]);
        if(err_val == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
    }    
}