#include <stdlib.h>
#include "qc/utils.h"

void* qc_malloc(size_t size) {
    void *p;
    if ((p = malloc(size)) == NULL) {
        qc_die("Out of memory");
    } else {
        return p;
    }
}

void* qc_realloc(void* ptr, size_t size) {
    void *p;
    if ((p = realloc(ptr, size)) == NULL) {
        qc_die("Out of memory");
    } else {
        return p;
    }
}
