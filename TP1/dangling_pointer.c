#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int) * 10);
    int arr[10];
    printf("Allocated %d bytes for pointer: %p\n", (int)sizeof(*p) * 10, p);
    printf("Allocated %d bytes for pointer: %p\n\n", (int)sizeof(arr), arr);

    /*free(p);
    *p = 5;
    printf("after free %d\n", *p);
    int *abc = p;

    printf("abc = %p\n", abc);*/
}