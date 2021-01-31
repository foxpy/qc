#include <stdint.h>
#include <string.h>
#include "qc/endian.h"
#include "qc/tests.h"

static void check_u64_from_be(uint64_t expected, uint8_t const src[static 8]) {
    uint64_t actual = qc_u64_from_be(src);
    qc_assert(actual == expected, "qc_u64_from_be misbehaves");
}

static void check_u64_to_be(uint8_t const expected[static 8], uint64_t src) {
    uint8_t actual[8] = {0};
    qc_u64_to_be(actual, src);
    qc_assert(memcmp(actual, expected, sizeof(actual)) == 0, "qc_u64_to_be misbehaves");
    check_u64_from_be(src, actual);
}

static void check_u64_from_le(uint64_t expected, uint8_t const src[static 8]) {
    uint64_t actual = qc_u64_from_le(src);
    qc_assert(actual == expected, "qc_u64_from_le misbehaves");
}

static void check_u64_to_le(uint8_t const expected[static 8], uint64_t src) {
    uint8_t actual[8] = {0};
    qc_u64_to_le(actual, src);
    qc_assert(memcmp(actual, expected, sizeof(actual)) == 0, "qc_u64_to_le misbehaves");
    check_u64_from_le(src, actual);
}

static void u64_iteration(uint64_t x) {
    uint8_t be[8];
    uint8_t le[8];
    qc_u64_to_be(be, x);
    qc_u64_to_le(le, x);
    {
        uint8_t tmp[8];
        for (size_t i = 0; i < 8; ++i) {
            tmp[i] = be[8 - 1 - i];
        }
        qc_assert(memcmp(tmp, le, sizeof(le)) == 0, "qc_u64 endianness functions damage data");
    }
    {
        uint64_t u_from_be = qc_u64_from_be(be);
        uint64_t u_from_le = qc_u64_from_le(le);
        qc_assert(x == u_from_be, "qc_u64_from_be misbehaves");
        qc_assert(x == u_from_le, "qc_u64_from_le misbehaves");
    }
}

static void i64_iteration(int64_t x) {
    uint8_t be[8];
    uint8_t le[8];
    qc_i64_to_be(be, x);
    qc_i64_to_le(le, x);
    {
        uint8_t tmp[8];
        for (size_t i = 0; i < 8; ++i) {
            tmp[i] = be[8 - 1 - i];
        }
        qc_assert(memcmp(tmp, le, sizeof(le)) == 0, "qc_i64 endianness functions damage data");
    }
    {
        int64_t i_from_be = qc_i64_from_be(be);
        int64_t i_from_le = qc_i64_from_le(le);
        qc_assert(x == i_from_be, "qc_i64_from_be misbehaves");
        qc_assert(x == i_from_le, "qc_i64_from_le misbehaves");
    }
}

int main(void) {
    check_u64_to_be(((uint8_t[8]){0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF}), UINT64_C(0x0123456789ABCDEF));
    check_u64_to_be(((uint8_t[8]){0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10}), UINT64_C(0xFEDCBA9876543210));
    check_u64_to_le(((uint8_t[8]){0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01}), UINT64_C(0x0123456789ABCDEF));
    check_u64_to_le(((uint8_t[8]){0x10, 0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE}), UINT64_C(0xFEDCBA9876543210));
    check_u64_to_be(((uint8_t[8]){0x67, 0x58, 0x26, 0x47, 0xCE, 0xB3, 0xFE, 0x00}), UINT64_C(0x67582647CEB3FE00));
    check_u64_to_le(((uint8_t[8]){0x00, 0xFE, 0xB3, 0xCE, 0x47, 0x26, 0x58, 0x67}), UINT64_C(0x67582647CEB3FE00));
    check_u64_to_be(((uint8_t[8]){0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF1, 0xB3, 0x18}), UINT64_C(0xFFFFFFFFFFF1B318));
    check_u64_to_le(((uint8_t[8]){0x18, 0xB3, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}), UINT64_C(0xFFFFFFFFFFF1B318));
    u64_iteration(UINT64_C(0));
    u64_iteration(UINT64_C(1));
    u64_iteration(UINT64_C(512));
    u64_iteration(UINT64_C(7446744073709551104));
    u64_iteration(UINT64_C(18446744073708614424));
    i64_iteration(INT64_C(0));
    i64_iteration(INT64_C(512));
    i64_iteration(INT64_C(7446744073709551104));
    i64_iteration(INT64_C(-1));
    i64_iteration(INT64_C(-512));
    i64_iteration(INT64_C(-90000));
}
