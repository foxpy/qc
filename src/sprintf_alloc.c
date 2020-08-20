#include "qc.h"
#define FIRST_ATTEMPT_ALLOC_SIZE 256

char* sprintf_alloc(char const* format, ...) {
    va_list args;
    char* ret = emalloc(FIRST_ATTEMPT_ALLOC_SIZE);
    va_start(args, format);
    int n = vsnprintf(ret, FIRST_ATTEMPT_ALLOC_SIZE, format, args);
    va_end(args);
    if (n < 0) {
        die("vsnprintf has failed");
    } else if ((size_t) n >= FIRST_ATTEMPT_ALLOC_SIZE) {
        size_t new_size = n + 1;
        ret = erealloc(ret, new_size);
        va_start(args, format);
        vsnprintf(ret, new_size, format, args);
        va_end(args);
    } else {
        ret = erealloc(ret, (size_t) n + 1);
    }
    return ret;
}
