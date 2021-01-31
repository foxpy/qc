#include <stdint.h>
#include <string.h>
#include "qc/endian.h"
#include "qc/tests.h"

static void check_u32_from_be(uint32_t expected, uint8_t const src[static 4]) {
    uint32_t actual = qc_u32_from_be(src);
    qc_assert(actual == expected, "qc_u32_from_be misbehaves");
}

static void check_u32_to_be(uint8_t const expected[static 4], uint32_t src) {
    uint8_t actual[4] = {0};
    qc_u32_to_be(actual, src);
    qc_assert(memcmp(actual, expected, sizeof(actual)) == 0, "qc_u32_to_be misbehaves");
    check_u32_from_be(src, actual);
}

static void check_u32_from_le(uint32_t expected, uint8_t const src[static 4]) {
    uint32_t actual = qc_u32_from_le(src);
    qc_assert(actual == expected, "qc_u32_from_le misbehaves");
}

static void check_u32_to_le(uint8_t const expected[static 4], uint32_t src) {
    uint8_t actual[4] = {0};
    qc_u32_to_le(actual, src);
    qc_assert(memcmp(actual, expected, sizeof(actual)) == 0, "qc_u32_to_le misbehaves");
    check_u32_from_le(src, actual);
}

static void check_i32(int32_t x) {
    uint8_t be[4];
    uint8_t le[4];
    qc_i32_to_be(be, x);
    qc_i32_to_le(le, x);
    {
        uint8_t tmp[4];
        for (size_t i = 0; i < 4; ++i) {
            tmp[i] = be[4 - 1 - i];
        }
        qc_assert(memcmp(tmp, le, sizeof(le)) == 0, "qc_i32 endianness functions damage data");
    }
    {
        int32_t i_from_be = qc_i32_from_be(be);
        int32_t i_from_le = qc_i32_from_le(le);
        qc_assert(x == i_from_be, "qc_i32_from_be misbehaves");
        qc_assert(x == i_from_le, "qc_i32_from_le misbehaves");
    }
}

int main(void) {
    check_u32_to_be(((uint8_t[4]){0x01, 0x23, 0x45, 0x67}), UINT32_C(0x01234567));
    check_u32_to_le(((uint8_t[4]){0x67, 0x45, 0x23, 0x01}), UINT32_C(0x01234567));
    check_i32(INT32_C(512));
    check_i32(INT32_C(-90000));
}
