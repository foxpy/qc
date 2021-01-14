#include <stdlib.h>
#include "qc/utils.h"
#include "qc/tests.h"

static void iter(unsigned n) {
    unsigned *a = qc_malloc(sizeof(unsigned) * n);
    for (unsigned i = 0; i < n; ++i) {
        *a = i * i;
        qc_assert(*a == i * i, "qc_malloc gives bad memory");
    }
    free(a);
}

int main(void) {
    iter(20);
    iter(40);
    iter(80);
}
