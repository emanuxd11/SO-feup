#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>

int chaccessDate(const char *filename) {
    if(utimes(filename, NULL) == -1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int createFile(const char *filename) {
    mode_t newFile_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    return creat(filename, newFile_perms);
}

int openFile(const char *filename) {
    if(filename == NULL) return EXIT_FAILURE;

    int fd = open(filename, O_RDONLY); 
    if(fd == -1) {
        //Create new file with 644 permissions
        if(createFile(filename) == -1) {
            return EXIT_FAILURE;
        }

        close(fd);
        return EXIT_SUCCESS;
    }

    if(chaccessDate(filename) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    for(int i = 1; i < argc; i++) {
        if(openFile(argv[i]) == EXIT_FAILURE) {
            printf("mytouch: error accessing file %s\n", argv[i]);
        }
    }

    return EXIT_SUCCESS;
}