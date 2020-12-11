#pragma once
#include <stddef.h>
#include <stdbool.h>

#define QC_PI 3.14159265358979323846

// Classic macros, type generic
#define QC_MIN(a, b) ((a) > (b)) ? (b) : (a)
#define QC_MAX(a, b) ((a) > (b)) ? (a) : (b)
// Greatest Common Divisor, a and b should be different from zero
size_t qc_gcd(size_t a, size_t b);
// Least Common Multiple, a and b should be different from zero
size_t qc_lcm(size_t a, size_t b);

bool qc_almost_equal_fp64(double a, double b, size_t precision);
bool qc_almost_equal_fp32(float a, float b, size_t precision);
