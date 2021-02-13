#pragma once
#include <stdbool.h>

void qc_assert_impl(bool cond, char const* fmt, ...);
#define QC_ASSERT_IMPL(cond, fmt, ...)                                                                                \
    qc_assert_impl(cond, "Assertion failed:\n  %s:%d:\n  %s\nError message:\n  " fmt "%c", __FILE__, __LINE__, #cond, \
                   __VA_ARGS__)

