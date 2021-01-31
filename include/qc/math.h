#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define QC_PI 3.14159265358979323846

uintmax_t qc_min_u(uintmax_t a, uintmax_t b);
intmax_t qc_min_s(intmax_t a, intmax_t b);
double qc_min_d(double a, double b);
#define qc_min(a, b)                        \
    _Generic((a) + (b), unsigned short      \
             : qc_min_u, unsigned int       \
             : qc_min_u, unsigned long      \
             : qc_min_u, unsigned long long \
             : qc_min_u, short              \
             : qc_min_s, int                \
             : qc_min_s, long               \
             : qc_min_s, long long          \
             : qc_min_s, double             \
             : qc_min_d, float              \
             : qc_min_d)((a), (b))

uintmax_t qc_max_u(uintmax_t a, uintmax_t b);
intmax_t qc_max_s(intmax_t a, intmax_t b);
double qc_max_d(double a, double b);
#define qc_max(a, b)                        \
    _Generic((a) + (b), unsigned short      \
             : qc_max_u, unsigned int       \
             : qc_max_u, unsigned long      \
             : qc_max_u, unsigned long long \
             : qc_max_u, short              \
             : qc_max_s, int                \
             : qc_max_s, long               \
             : qc_max_s, long long          \
             : qc_max_s, double             \
             : qc_max_d, float              \
             : qc_max_d)((a), (b))

// Greatest Common Divisor, a and b should be different from zero
uintmax_t qc_gcd(uintmax_t a, uintmax_t b);
// Least Common Multiple, a and b should be different from zero
uintmax_t qc_lcm(uintmax_t a, uintmax_t b);

bool qc_almost_equal_fp64(double a, double b, size_t precision);
bool qc_almost_equal_fp32(float a, float b, size_t precision);

uint16_t qc_rotr8(uint8_t a, size_t n);
uint16_t qc_rotr16(uint16_t a, size_t n);
uint32_t qc_rotr32(uint32_t a, size_t n);
uint64_t qc_rotr64(uint64_t a, size_t n);
size_t qc_rotr_usize(size_t a, size_t n);

uint16_t qc_rotl8(uint8_t a, size_t n);
uint16_t qc_rotl16(uint16_t a, size_t n);
uint32_t qc_rotl32(uint32_t a, size_t n);
uint64_t qc_rotl64(uint64_t a, size_t n);
size_t qc_rotl_usize(size_t a, size_t n);
