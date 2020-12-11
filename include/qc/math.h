#pragma once
#include <stddef.h>

#define QC_PI 3.14159265358979323846

// Classic macros, type generic
#define QC_MIN(a, b) ((a) > (b)) ? (b) : (a)
#define QC_MAX(a, b) ((a) > (b)) ? (a) : (b)
// Greatest Common Divisor, a and b should be different from zero
size_t qc_gcd(size_t a, size_t b);
// Least Common Multiple, a and b should be different from zero
size_t qc_lcm(size_t a, size_t b);
