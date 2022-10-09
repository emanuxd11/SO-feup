#include <stdio.h>

int strstrcnt(const char *haystack, const char *needle) {
    int count = 0;

    for(int i = 0; haystack[i] != '\0'; i++) {
        int j;
        for(j = 0; needle[j] != '\0' && needle[j] == haystack[i+j]; j++);
        if(needle[j] == '\0') count++;
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    printf("String \"%s\" shows up in \"%s\" %d times\n", argv[1], argv[2],
        strstrcnt(argv[2], argv[1]));
}