#include <stdlib.h>
#include "qc.h"

void* emalloc(size_t size) {
    void *p;
    if ((p = malloc(size)) == NULL) {
        die("Out of memory");
    } else {
        return p;
    }
}
