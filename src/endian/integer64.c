#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "qc/endian.h"

void qc_u64_to_be(uint8_t dst[static 8], uint64_t src) {
    assert(dst != NULL);
    uint64_t extract_mask = UINT64_C(0xFF) << (64u - 8u);
    size_t fill_shift = 64u - 8u;
    for (size_t i = 0; i < 8; ++i) {
        dst[i] = (extract_mask & src) >> fill_shift;
        extract_mask >>= 8u;
        fill_shift -= 8u;
    }
}

void qc_u64_to_le(uint8_t dst[static 8], uint64_t src) {
    assert(dst != NULL);
    uint64_t extract_mask = UINT64_C(0xFF);
    size_t fill_shift = 0u;
    for (size_t i = 0; i < 8; ++i) {
        dst[i] = (extract_mask & src) >> fill_shift;
        extract_mask <<= 8u;
        fill_shift += 8u;
    }
}

void qc_i64_to_be(uint8_t dst[static 8], int64_t src) {
    assert(dst != NULL);
    uint64_t u;
    memmove(&u, &src, sizeof(src));
    qc_u64_to_be(dst, u);
}

void qc_i64_to_le(uint8_t dst[static 8], int64_t src) {
    assert(dst != NULL);
    uint64_t u;
    memmove(&u, &src, sizeof(src));
    qc_u64_to_le(dst, u);
}


uint64_t qc_u64_from_be(uint8_t const src[static 8]) {
    assert(src != NULL);
    uint64_t u = 0;
    for (size_t i = 0; i < 8; ++i) {
        u <<= 8;
        u |= src[i];
    }
    return u;
}

uint64_t qc_u64_from_le(uint8_t const src[static 8]) {
    assert(src != NULL);
    uint64_t u = 0;
    for (size_t i = 0; i < 8; ++i) {
        u <<= 8;
        u |= src[8 - 1 - i];
    }
    return u;
}

int64_t qc_i64_from_be(uint8_t const src[static 8]) {
    assert(src != NULL);
    uint64_t u = qc_u64_from_be(src);
    int64_t i = 0;
    memmove(&i, &u, 8);
    return i;
}

int64_t qc_i64_from_le(uint8_t const src[static 8]) {
    assert(src != NULL);
    uint64_t u = qc_u64_from_le(src);
    int64_t i = 0;
    memmove(&i, &u, 8);
    return i;
}
