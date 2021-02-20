#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "qc/endian.h"

void qc_u16_to_be(uint8_t dst[static 2], uint16_t src) {
    assert(dst != NULL);
    uint16_t extract_mask = UINT16_C(0xFF) << (16u - 8u);
    size_t fill_shift = 16u - 8u;
    for (size_t i = 0; i < 2; ++i) {
        dst[i] = (extract_mask & src) >> fill_shift;
        extract_mask >>= 8u;
        fill_shift -= 8u;
    }
}

void qc_u16_to_le(uint8_t dst[static 2], uint16_t src) {
    assert(dst != NULL);
    uint16_t extract_mask = UINT16_C(0xFF);
    size_t fill_shift = 0u;
    for (size_t i = 0; i < 2; ++i) {
        dst[i] = (extract_mask & src) >> fill_shift;
        extract_mask <<= 8u;
        fill_shift += 8u;
    }
}

void qc_i16_to_be(uint8_t dst[static 2], int16_t src) {
    assert(dst != NULL);
    uint16_t u;
    memmove(&u, &src, sizeof(src));
    qc_u16_to_be(dst, u);
}

void qc_i16_to_le(uint8_t dst[static 2], int16_t src) {
    assert(dst != NULL);
    uint16_t u;
    memmove(&u, &src, sizeof(src));
    qc_u16_to_le(dst, u);
}


uint16_t qc_u16_from_be(uint8_t const src[static 2]) {
    assert(src != NULL);
    uint16_t u = 0;
    for (size_t i = 0; i < 2; ++i) {
        u <<= 8;
        u |= src[i];
    }
    return u;
}

uint16_t qc_u16_from_le(uint8_t const src[static 2]) {
    assert(src != NULL);
    uint16_t u = 0;
    for (size_t i = 0; i < 2; ++i) {
        u <<= 8;
        u |= src[2 - 1 - i];
    }
    return u;
}

int16_t qc_i16_from_be(uint8_t const src[static 2]) {
    assert(src != NULL);
    uint16_t u = qc_u16_from_be(src);
    int16_t i = 0;
    memmove(&i, &u, 2);
    return i;
}

int16_t qc_i16_from_le(uint8_t const src[static 2]) {
    assert(src != NULL);
    uint16_t u = qc_u16_from_le(src);
    int16_t i = 0;
    memmove(&i, &u, 2);
    return i;
}
