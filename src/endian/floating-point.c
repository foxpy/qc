#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "qc/endian.h"

void qc_fp64_to_be(uint8_t dst[static 8], double src) {
    assert(dst != NULL);
    uint64_t u;
    memmove(&u, &src, sizeof(src));
    qc_u64_to_be(dst, u);
}

void qc_fp64_to_le(uint8_t dst[static 8], double src) {
    assert(dst != NULL);
    uint64_t u;
    memmove(&u, &src, sizeof(src));
    qc_u64_to_le(dst, u);
}

void qc_fp32_to_be(uint8_t dst[static 4], float src) {
    assert(dst != NULL);
    uint32_t u;
    memmove(&u, &src, sizeof(src));
    qc_u32_to_be(dst, u);
}

void qc_fp32_to_le(uint8_t dst[static 4], float src) {
    assert(dst != NULL);
    uint32_t u;
    memmove(&u, &src, sizeof(src));
    qc_u32_to_le(dst, u);
}


double qc_fp64_from_be(uint8_t const src[static 8]) {
    assert(src != NULL);
    uint64_t u = qc_u64_from_be(src);
    double d = 0.0;
    memmove(&d, &u, 8);
    return d;
}

double qc_fp64_from_le(uint8_t const src[static 8]) {
    assert(src != NULL);
    uint64_t u = qc_u64_from_le(src);
    double d = 0.0;
    memmove(&d, &u, 8);
    return d;
}

float qc_fp32_from_be(uint8_t const src[static 4]) {
    assert(src != NULL);
    uint32_t u = qc_u32_from_be(src);
    float f = 0.0f;
    memmove(&f, &u, 4);
    return f;
}

float qc_fp32_from_le(uint8_t const src[static 4]) {
    assert(src != NULL);
    uint32_t u = qc_u32_from_le(src);
    float f = 0.0f;
    memmove(&f, &u, 4);
    return f;
}
