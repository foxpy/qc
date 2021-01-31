#include <stdlib.h>
#include "qc/utils.h"
#include "qc/tests.h"

static void iter(unsigned n1, unsigned n2, unsigned n3) {
    unsigned* a = qc_malloc(sizeof(unsigned) * n1);
    for (unsigned i = 0; i < n1; ++i) {
        *a = i * i;
        qc_assert(*a == i * i, "qc_malloc gives bad memory");
    }
    a = qc_realloc(a, n2);
    for (unsigned i = 0; i < n2; ++i) {
        *a = i * i;
        qc_assert(*a == i * i, "qc_realloc gives bad memory");
    }
    a = qc_realloc(a, n3);
    for (unsigned i = 0; i < n3; ++i) {
        *a = i * i;
        qc_assert(*a == i * i, "qc_realloc gives bad memory");
    }
    free(a);
}

int main(void) {
    iter(20, 40, 80);
    iter(10, 11, 50);
    iter(200, 50, 150);
}
