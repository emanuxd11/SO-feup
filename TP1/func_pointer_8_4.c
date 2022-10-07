#include <stdio.h>

int g(int (*h)(int), int y) {
    return h(y + 2);
}

int f(int x) {
    return x*x;
}

int z(int x) {
    return x*x*x*x*x*x*x*x*x*x;
}

int main() {
    printf("value: %d\n", g(f,2));
    printf("value: %d\n", g(z,2));
    return 0;
}