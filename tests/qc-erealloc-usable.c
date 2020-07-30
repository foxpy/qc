#include <stdlib.h>
#include "qc.h"

void iter(size_t n1, size_t n2, size_t n3) {
    int *a = (int*) emalloc(sizeof(int) * n1);
    for (size_t i = 0; i < n1; ++i) {
        *a = (int) i * i;
        qc_assert(*a == (int)(i * i), "emalloc gives bad memory");
    }
    a = erealloc(a, n2);
    for (size_t i = 0; i < n1; ++i) {
        *a = (int) i * i;
        qc_assert(*a == (int)(i * i), "erealloc gives bad memory");
    }
    a = erealloc(a, n3);
    for (size_t i = 0; i < n1; ++i) {
        *a = (int) i * i;
        qc_assert(*a == (int)(i * i), "erealloc gives bad memory");
    }
    free(a);
}

int main() {
    iter(20, 40, 80);
    iter(10, 11, 50);
    iter(200, 50, 150);
}
