#include <stdlib.h>
#include "qc.h"

void* erealloc(void *ptr, size_t size) {
    void *p;
    if ((p = erealloc(ptr, size)) == NULL) {
        die("Out of memory");
    } else {
        return p;
    }
}
