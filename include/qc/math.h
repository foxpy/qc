#pragma once
#include <stddef.h>

// Classic macros, type generic
#define MIN(a, b) ((a) > (b)) ? (b) : (a)
#define MAX(a, b) ((a) > (b)) ? (a) : (b)
// Greatest Common Divisor, a and b should be different from zero
size_t gcd(size_t a, size_t b);
// Least Common Multiple, a and b should be different from zero
size_t lcm(size_t a, size_t b);
