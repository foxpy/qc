#include <stddef.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include "qc/math.h"

uintmax_t qc_min_u(uintmax_t a, uintmax_t b) {
    return a < b ? a : b;
}

intmax_t qc_min_s(intmax_t a, intmax_t b) {
    return a < b ? a : b;
}

double qc_min_d(double a, double b) {
    return a < b ? a : b;
}

uintmax_t qc_max_u(uintmax_t a, uintmax_t b) {
    return a > b ? a : b;
}

intmax_t qc_max_s(intmax_t a, intmax_t b) {
    return a > b ? a : b;
}

double qc_max_d(double a, double b) {
    return a > b ? a : b;
}

uintmax_t qc_gcd(uintmax_t a, uintmax_t b) {
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

uintmax_t qc_lcm(uintmax_t a, uintmax_t b) {
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

uint16_t rotr8(uint8_t a, size_t n) {
    assert(n < 8);
    return a << (8 - n) | a >> n;
}

uint16_t rotr16(uint16_t a, size_t n) {
    assert(n < 16);
    return a << (16 - n) | a >> n;
}

uint32_t rotr32(uint32_t a, size_t n) {
    assert(n < 32);
    return a << (32 - n) | a >> n;
}

uint64_t rotr64(uint64_t a, size_t n) {
    assert(n < 64);
    return a << (64 - n) | a >> n;
}

uint16_t rotl8(uint8_t a, size_t n) {
    assert(n < 8);
    return a << n | a >> (8 - n);
}

uint16_t rotl16(uint16_t a, size_t n) {
    assert(n < 16);
    return a << n | a >> (16 - n);
}

uint32_t rotl32(uint32_t a, size_t n) {
    assert(n < 32);
    return a << n | a >> (32 - n);
}

uint64_t rotl64(uint64_t a, size_t n) {
    assert(n < 64);
    return a << n | a >> (64 - n);
}
