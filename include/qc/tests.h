#pragma once
#include <stdbool.h>

// If condition is false, terminates program and prints
// current filename and line. Has several advantages over
// std assert: prints custom error message and does not depend
// on NDEBUG macro definition

void qc_assert_impl(bool cond, char const* fmt, ...);
#define QC_ASSERT_IMPL(cond, fmt, ...)                                                                                \
    qc_assert_impl(cond, "Assertion failed:\n  %s:%d:\n  %s\nError message:\n  " fmt "%c", __FILE__, __LINE__, #cond, \
                   __VA_ARGS__)
#define qc_assert(cond, ...) QC_ASSERT_IMPL(cond, __VA_ARGS__, '\n')
