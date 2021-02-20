#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "qc/tests.h"

void qc_assert_impl(bool cond, char const* fmt, ...) {
    assert(fmt != NULL);
    if (!cond) {
        va_list ap;
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        va_end(ap);
        abort();
    }
}
