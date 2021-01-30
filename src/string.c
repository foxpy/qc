#include <stdarg.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "qc/string.h"
#include "qc/utils.h"

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
    va_list args;
    va_copy(args, ap);
    return qc_vasnprintf(dst, INT_MAX, format, args);
    va_end(args);
}

ptrdiff_t qc_vasnprintf(char** dst, size_t mlimit, char const* format, va_list ap) {
    va_list args;
    va_copy(args, ap);
    return qc_vasnprintf_impl(dst, 256, mlimit, format, args);
    va_end(args);
}

qc_result qc_str_to_unsigned(char const* str, size_t* dst, char const** tail) {
    assert(str != NULL);
    assert(dst != NULL);
    if (!isdigit(str[0])) {
        goto error;
    }
    char* endptr;
    errno = 0;
    unsigned long long u = strtoull(str, &endptr, 0);
    if (errno != 0) {
        goto error;
    } else {
        *dst = u % SIZE_MAX;
        if (tail != NULL) {
            *tail = endptr;
        }
        return QC_SUCCESS;
    }
error:
    if (tail != NULL) {
        *tail = NULL;
    }
    return QC_FAILURE;
}

qc_result qc_str_to_signed(char const* str, ptrdiff_t * dst, char const** tail) {
    assert(str != NULL);
    assert(dst != NULL);
    if (!isdigit(str[0]) && str[0] != '-') {
        goto error;
    }
    char* endptr;
    errno = 0;
    long long l = strtoll(str, &endptr, 0);
    if (errno != 0) {
        goto error;
    } else {
        *dst = l;
        if (tail != NULL) {
            *tail = endptr;
        }
        return QC_SUCCESS;
    }
error:
    if (tail != NULL) {
        *tail = NULL;
    }
    return QC_FAILURE;
}

qc_result qc_str_to_double(char const* str, double* dst, char const** tail) {
    assert(str != NULL);
    assert(dst != NULL);
    if (!isdigit(str[0]) && str[0] != '-' && str[1] != '+') {
        goto error;
    }
    char* endptr;
    errno = 0;
    double d = strtod(str, &endptr);
    if (errno != 0) {
        goto error;
    } else {
        *dst =d ;
        if (tail != NULL) {
            *tail = endptr;
        }
        return QC_SUCCESS;
    }
error:
    if (tail != NULL) {
        *tail = NULL;
    }
    return QC_FAILURE;
}

static int char_to_num(char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'a': case 'A': return 10;
        case 'b': case 'B': return 11;
        case 'c': case 'C': return 12;
        case 'd': case 'D': return 13;
        case 'e': case 'E': return 14;
        case 'f': case 'F': return 15;
        default: return -1;
    }
}

qc_result qc_hexstr_to_bytes(char const* str, uint8_t** dst) {
    if (strncmp(str, "0x", 2) == 0) {
        str += 2;
    }
    size_t len = strlen(str);
    if (len == 0) {
        *dst = NULL;
        return QC_SUCCESS;
    } else {
        *dst = qc_malloc(len + 1 / 2);
        size_t src_index = 0, dst_index = 0;
        if (len % 2 == 1) {
            int a = char_to_num(str[0]);
            if (a == -1) {
                goto error;
            } else {
                (*dst)[0] = a & 0xFFu;
                ++src_index;
                ++dst_index;
            }
        }
        while (src_index < len) {
            int a, b;
            if ((a = char_to_num(str[src_index])) == -1 || (b = char_to_num(str[src_index+1])) == -1) {
                goto error;
            }
            (*dst)[dst_index] = ((((unsigned) a) << 4u) | ((unsigned) b)) & 0xFFu;
            src_index += 2;
            dst_index += 1;
        }
    }
    return QC_SUCCESS;
error:
    free(*dst);
    *dst = NULL;
    return QC_FAILURE;
}
