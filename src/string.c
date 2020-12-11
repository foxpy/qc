#include <stdarg.h>
#include <limits.h>
#include "qc.h"

static ptrdiff_t qc_vasnprintf_impl(char** dst, size_t guess, size_t max, char const* format, va_list ap) {
    va_list args;
    int n;
    if (guess > max) {
        guess = max;
    }
    *dst = qc_malloc(guess);
    va_copy(args, ap);
    n = vsnprintf(*dst, guess, format, args);
    va_end(args);
    if (n < 0) {
        goto error;
    } else if ((size_t) n >= max) {
        return guess - 1;
    } else if ((size_t) n >= guess) {
        guess = n + 1;
        va_copy(args, ap);
        n = vsnprintf(*dst, guess, format, args);
        va_end(args);
        if (n < 0) {
            goto error;
        } else {
            return (ptrdiff_t) n;
        }
    } else {
        *dst = qc_realloc(*dst, n + 1);
        return (ptrdiff_t) n;
    }
    error:
    free(*dst);
    *dst = NULL;
    return -1;
}

ptrdiff_t qc_asprintf(char** dst, char const* format, ...) {
    va_list args;
    va_start(args, format);
    return qc_vasprintf(dst, format, args);
    va_end(args);
}

ptrdiff_t qc_asnprintf(char** dst, size_t mlimit, char const* format, ...) {
    va_list args;
    va_start(args, format);
    return qc_vasnprintf(dst, mlimit, format, args);
    va_end(args);
}

ptrdiff_t qc_vasprintf(char** dst, char const* format, va_list ap) {
    return qc_vasnprintf(dst, INT_MAX, format, ap);
}

ptrdiff_t qc_vasnprintf(char** dst, size_t mlimit, char const* format, va_list ap) {
    return qc_vasnprintf_impl(dst, 256, mlimit, format, ap);
}
