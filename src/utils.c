#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "qc.h"

#define FIRST_ATTEMPT_ALLOC_SIZE 256

void* emalloc(size_t size) {
    void *p;
    if ((p = malloc(size)) == NULL) {
        die("Out of memory");
    } else {
        return p;
    }
}

void* erealloc(void* ptr, size_t size) {
    void *p;
    if ((p = realloc(ptr, size)) == NULL) {
        die("Out of memory");
    } else {
        return p;
    }
}

char* sprintf_alloc(char const* format, ...) {
    va_list args;
    va_start(args, format);
    char* ret = vsprintf_alloc(format, args);
    va_end(args);
    return ret;
}

char* vsprintf_alloc(char const* format, va_list ap) {
    va_list args;
    char* ret = emalloc(FIRST_ATTEMPT_ALLOC_SIZE);
    va_copy(args, ap);
    int n = vsnprintf(ret, FIRST_ATTEMPT_ALLOC_SIZE, format, ap);
    if (n < 0) {
        die("vsnprintf has failed");
    } else if ((size_t) n >= FIRST_ATTEMPT_ALLOC_SIZE) {
        size_t new_size = n + 1;
        ret = erealloc(ret, new_size);
        va_copy(args, ap);
        vsnprintf(ret, new_size, format, args);
    } else {
        ret = erealloc(ret, (size_t) n + 1);
    }
    va_end(args);
    return ret;
}
