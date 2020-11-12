#include <stdlib.h>
#include "qc.h"

static void iter(unsigned n) {
    unsigned *a = emalloc(sizeof(unsigned) * n);
    for (unsigned i = 0; i < n; ++i) {
        *a = i * i;
        qc_assert(*a == i * i, "emalloc gives bad memory");
    }
    free(a);
}

int main() {
    iter(20);
    iter(40);
    iter(80);
}
