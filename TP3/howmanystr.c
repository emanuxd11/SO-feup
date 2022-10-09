#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Returns the number of characters that were skipped to
//find the needle or -1 in the case that it wasn't found
int my_strstr(const char *__haystack, const char *__needle) {
    for(int i = 0; i < strlen(__haystack); i++) {
        if(strncmp(i + __haystack, __needle, strlen(__needle)) == 0) {
            return i;
        } 
    }

    return -1;
}

int main(int argc, char *argv[]) {
    int appearance = 0, charcnt;
    char *cpy = strdup(argv[2]);

    while(1) {
        charcnt = my_strstr(cpy, argv[1]);
        if(charcnt == -1) break;
        
        cpy += charcnt + strlen(argv[1]);
        appearance++;
    }

    printf("String \"%s\" shows up in \"%s\" %d times\n", argv[1], argv[2], appearance);
}