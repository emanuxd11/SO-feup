#include <stdio.h>
#include "list.h"

int main() {
    list *randlist = list_new_random(10, 500);
    printf("Random list we just created:\n");
    list_print(randlist);

    printf("\nList after removing the last element:\n");
    list_remove_last(randlist);
    list_print(randlist);

    printf("\nList after removing first and last:\n");
    list_remove_first(randlist);
    list_remove_last(randlist);
    list_print(randlist);

    printf("\nList after adding new element of value 69:\n");
    list_add_last(69, randlist);
    list_print(randlist);
}