#include <stdbool.h>
#include <stddef.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include "qc/math.h"

bool qc_almost_equal_fp64(double a, double b, size_t precision) {
    assert(precision != 0);
    return (fabs(a - b) <= DBL_EPSILON * fabs(a + b) * precision) || (fabs(a - b) < DBL_MIN);
}

bool qc_almost_equal_fp32(float a, float b, size_t precision) {
    assert(precision != 0);
    return (fabsf(a - b) <= FLT_EPSILON * fabsf(a + b) * precision) || (fabsf(a - b) < FLT_MIN);
}
