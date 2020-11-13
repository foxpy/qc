#pragma once
#include <stdio.h>
#include <stdlib.h>

// If condition is false, terminates program and prints
// current filename and line. Has several advantages over
// std assert: prints custom error message and does not depend
// on NDEBUG macro definition
// qc_assert_format also allows you to format error message if necessary

#define qc_assert(cond, err_msg)                                          \
do {                                                                      \
    if (!(cond)) {                                                        \
        fprintf(stderr, "Assertion failed: %s:%d, ", __FILE__, __LINE__); \
        fprintf(stderr, "%s\n", err_msg);                                 \
        abort();                                                          \
    }                                                                     \
} while (0)

#define qc_assert_format(cond, format, ...)                               \
do {                                                                      \
    if (!(cond)) {                                                        \
        fprintf(stderr, "Assertion failed: %s:%d, ", __FILE__, __LINE__); \
        fprintf(stderr, format, __VA_ARGS__);                             \
        fputc('\n', stderr);                                              \
        abort();                                                          \
    }                                                                     \
} while (0)
