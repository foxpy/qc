#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "qc/endian.h"

void qc_u32_to_be(uint8_t dst[static 4], uint32_t src) {
    assert(dst != NULL);
    uint32_t extract_mask = UINT32_C(0xFF) << (32u - 8u);
    size_t fill_shift = 32u - 8u;
    for (size_t i = 0; i < 4; ++i) {
        dst[i] = (extract_mask & src) >> fill_shift;
        extract_mask >>= 8u;
        fill_shift -= 8u;
    }
}

void qc_u32_to_le(uint8_t dst[static 4], uint32_t src) {
    assert(dst != NULL);
    uint32_t extract_mask = UINT32_C(0xFF);
    size_t fill_shift = 0u;
    for (size_t i = 0; i < 4; ++i) {
        dst[i] = (extract_mask & src) >> fill_shift;
        extract_mask <<= 8u;
        fill_shift += 8u;
    }
}

void qc_i32_to_be(uint8_t dst[static 4], int32_t src) {
    assert(dst != NULL);
    uint32_t u;
    memmove(&u, &src, sizeof(src));
    qc_u32_to_be(dst, u);
}

void qc_i32_to_le(uint8_t dst[static 4], int32_t src) {
    assert(dst != NULL);
    uint32_t u;
    memmove(&u, &src, sizeof(src));
    qc_u32_to_le(dst, u);
}


uint32_t qc_u32_from_be(uint8_t const src[static 4]) {
    assert(src != NULL);
    uint32_t u = 0;
    for (size_t i = 0; i < 4; ++i) {
        u <<= 8;
        u |= src[i];
    }
    return u;
}

uint32_t qc_u32_from_le(uint8_t const src[static 4]) {
    assert(src != NULL);
    uint32_t u = 0;
    for (size_t i = 0; i < 4; ++i) {
        u <<= 8;
        u |= src[4 - 1 - i];
    }
    return u;
}

int32_t qc_i32_from_be(uint8_t const src[static 4]) {
    assert(src != NULL);
    uint32_t u = qc_u32_from_be(src);
    int32_t i = 0;
    memmove(&i, &u, 4);
    return i;
}

int32_t qc_i32_from_le(uint8_t const src[static 4]) {
    assert(src != NULL);
    uint32_t u = qc_u32_from_le(src);
    int32_t i = 0;
    memmove(&i, &u, 4);
    return i;
}
