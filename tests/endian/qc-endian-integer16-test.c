#include <stdint.h>
#include <string.h>
#include "qc/endian.h"
#include "qc/tests.h"

static void check_u16_from_be(uint16_t expected, uint8_t const src[static 2]) {
    uint16_t actual = qc_u16_from_be(src);
    qc_assert(actual == expected, "qc_u16_from_be misbehaves");
}

static void check_u16_to_be(uint8_t const expected[static 2], uint16_t src) {
    uint8_t actual[2] = {0};
    qc_u16_to_be(actual, src);
    qc_assert(memcmp(actual, expected, sizeof(actual)) == 0, "qc_u16_to_be misbehaves");
    check_u16_from_be(src, actual);
}

static void check_u16_from_le(uint16_t expected, uint8_t const src[static 2]) {
    uint16_t actual = qc_u16_from_le(src);
    qc_assert(actual == expected, "qc_u16_from_le misbehaves");
}

static void check_u16_to_le(uint8_t const expected[static 2], uint16_t src) {
    uint8_t actual[2] = {0};
    qc_u16_to_le(actual, src);
    qc_assert(memcmp(actual, expected, sizeof(actual)) == 0, "qc_u16_to_le misbehaves");
    check_u16_from_le(src, actual);
}

static void check_i16(int16_t x) {
    uint8_t be[2];
    uint8_t le[2];
    qc_i16_to_be(be, x);
    qc_i16_to_le(le, x);
    {
        uint8_t tmp[2];
        for (size_t i = 0; i < 2; ++i) {
            tmp[i] = be[2-1-i];
        }
        qc_assert(memcmp(tmp, le, sizeof(le)) == 0, "qc_i16 endianness functions damage data");
    }
    {
        int16_t i_from_be = qc_i16_from_be(be);
        int16_t i_from_le = qc_i16_from_le(le);
        qc_assert(x == i_from_be, "qc_i16_from_be misbehaves");
        qc_assert(x == i_from_le, "qc_i16_from_le misbehaves");
    }
}

int main(void) {
    check_u16_to_be(((uint8_t[2]){0x01, 0x23}), UINT16_C(0x0123));
    check_u16_to_le(((uint8_t[2]){0x23, 0x01}), UINT16_C(0x0123));
    check_i16(INT16_C(512));
    check_i16(INT16_C(-9000));
}
