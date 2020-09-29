#pragma once

/*
 * Irrelevant: makes very little sense
 * to pollute main header
 */

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <stdnoreturn.h>

typedef union qc_rnd_state_t {
    uint64_t s64;
    double fp64;
} qc_rnd;

#define __qc_assert(cond, err_msg)                                        \
do {                                                                      \
    if (!(cond)) {                                                        \
        fprintf(stderr, "Assertion failed: %s:%d, ", __FILE__, __LINE__); \
        fprintf(stderr, "%s\n", err_msg);                                 \
        abort();                                                          \
    }                                                                     \
} while (0)                                                               \

#define __qc_assert_format(cond, format, ...)                             \
do {                                                                      \
    if (!(cond)) {                                                        \
        fprintf(stderr, "Assertion failed: %s:%d, ", __FILE__, __LINE__); \
        fprintf(stderr, format, __VA_ARGS__);                             \
        fputc('\n', stderr);                                              \
        abort();                                                          \
    }                                                                     \
} while (0)                                                               \

#define __qc_min(a, b) ((a) > (b)) ? (b) : (a)
#define __qc_max(a, b) ((a) > (b)) ? (a) : (b)
