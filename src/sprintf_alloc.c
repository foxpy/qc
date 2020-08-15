#include "qc.h"
#include <limits.h>

char* sprintf_alloc(size_t size_hint, char const* format, ...) {
    va_list args;
    char* ret = emalloc(size_hint);
    va_start(args, format);
    int n = vsnprintf(ret, size_hint, format, args);
    va_end(args);
    if (n < 0) {
        die("vsnprintf has failed");
    } else if ((size_t) n >= size_hint) {
        size_t new_size = n + 1;
        ret = erealloc(ret, new_size);
        va_start(args, format);
        n = vsnprintf(ret, new_size, format, args);
        va_end(args);
    }
    ret = erealloc(ret, (size_t) n + 1);
    return ret;
}
