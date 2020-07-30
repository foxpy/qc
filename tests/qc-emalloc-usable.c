#include <stdlib.h>
#include "qc.h"

void iter(size_t n) {
    int *a = (int*) emalloc(sizeof(int) * n);
    for (size_t i = 0; i < n; ++i) {
        *a = (int) i * i;
        qc_assert(*a == (int)(i * i), "emalloc gives bad memory");
    }
    free(a);
}

int main() {
    iter(20);
    iter(40);
    iter(80);
}
