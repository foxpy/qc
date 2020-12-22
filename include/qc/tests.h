#pragma once
#include <stdio.h>
#include <stdlib.h>

// If condition is false, terminates program and prints
// current filename and line. Has several advantages over
// std assert: prints custom error message and does not depend
// on NDEBUG macro definition

#define QC_ASSERT_IMPL(fmt, ...) do {                      \
    fprintf(stderr, "Assertion failed: %s:%d, " fmt "%c",  \
            __FILE__, __LINE__, __VA_ARGS__);              \
    abort();                                               \
} while (0)

#define qc_assert(cond, ...)                               \
do {                                                       \
    if (!(cond)) {                                         \
        QC_ASSERT_IMPL(__VA_ARGS__, '\n');                 \
    }                                                      \
} while (0)
