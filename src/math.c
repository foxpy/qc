#include <float.h>
#include <math.h>
#include "qc/math.h"

size_t qc_gcd(size_t a, size_t b) {
    if (a == 0 && b == 0) {
        return 0;
    } else if (a == b || b == 0) {
        return a;
    } else if (a == 0) {
        return b;
    } else if (a % 2 == 0 && b % 2 == 0) {
        return 2 * qc_gcd(a >> 1u, b >> 1u);
    } else if (a % 2 == 0 && b % 2 == 1) {
        return qc_gcd(a >> 1u, b);
    } else if (a % 2 == 1 && b % 2 == 0) {
        return qc_gcd(a, b >> 1u);
    } else {
        if (a > b) {
            return qc_gcd(a - b, b);
        } else {
            return qc_gcd(b - a, a);
        }
    }
}

size_t qc_lcm(size_t a, size_t b) {
    return a * b / qc_gcd(a, b);
}

bool qc_almost_equal_fp64(double a, double b, size_t precision) {
    return (fabs(a - b) <= DBL_EPSILON * fabs(a + b) * precision) ||
           (fabs(a - b) < DBL_MIN);
}

bool qc_almost_equal_fp32(float a, float b, size_t precision) {
    return (fabsf(a - b) <= FLT_EPSILON * fabsf(a + b) * precision) ||
           (fabsf(a - b) < FLT_MIN);
}

