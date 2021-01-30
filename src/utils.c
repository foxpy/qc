#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "qc/utils.h"
#include "qc/noreturn.h"

qc_noreturn void qc_die_impl(char const* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    abort();
}

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
