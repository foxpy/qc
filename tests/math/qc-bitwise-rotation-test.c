#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include "qc/math.h"
#include "qc/tests.h"

static void check_rotr8(uint8_t value, uint8_t expected, size_t shift) {
    uint8_t actual = qc_rotr8(value, shift);
    qc_assert(actual == expected,
              "Expected: rotr8(0x%" PRIx8 ", %zu) == 0x%" PRIx8 ", got: rotr8(0x%" PRIx8 ", %zu) == 0x%" PRIx8, value,
              shift, expected, value, shift, actual);
}

static void check_rotr16(uint16_t value, uint16_t expected, size_t shift) {
    uint16_t actual = qc_rotr16(value, shift);
    qc_assert(actual == expected,
              "Expected: rotr16(0x%" PRIx16 ", %zu) == 0x%" PRIx16 ", got: rotr16(0x%" PRIx16 ", %zu) == 0x%" PRIx16,
              value, shift, expected, value, shift, actual);
}

static void check_rotr32(uint32_t value, uint32_t expected, size_t shift) {
    uint32_t actual = qc_rotr32(value, shift);
    qc_assert(actual == expected,
              "Expected: rotr32(0x%" PRIx32 ", %zu) == 0x%" PRIx32 ", got: rotr32(0x%" PRIx32 ", %zu) == 0x%" PRIx32,
              value, shift, expected, value, shift, actual);
}

static void check_rotr64(uint64_t value, uint64_t expected, size_t shift) {
    uint64_t actual = qc_rotr64(value, shift);
    qc_assert(actual == expected,
              "Expected: rotr64(0x%" PRIx64 ", %zu) == 0x%" PRIx64 ", got: rotr64(0x%" PRIx64 ", %zu) == 0x%" PRIx64,
              value, shift, expected, value, shift, actual);
}

static void check_rotr_usize(size_t value, size_t expected, size_t shift) {
    size_t actual = qc_rotr_usize(value, shift);
    qc_assert(actual == expected, "Expected: rotr_usize(0x%zx, %zu) == 0x%zx, got: rotr_usize(0x%zx, %zu) == 0x%zx",
              value, shift, expected, value, shift, actual);
}

static void check_rotl8(uint8_t value, uint8_t expected, size_t shift) {
    uint8_t actual = qc_rotl8(value, shift);
    qc_assert(actual == expected,
              "Expected: rotl8(0x%" PRIx8 ", %zu) == 0x%" PRIx8 ", got: rotl8(0x%" PRIx8 ", %zu) == 0x%" PRIx8, value,
              shift, expected, value, shift, actual);
}

static void check_rotl16(uint16_t value, uint16_t expected, size_t shift) {
    uint16_t actual = qc_rotl16(value, shift);
    qc_assert(actual == expected,
              "Expected: rotl16(0x%" PRIx16 ", %zu) == 0x%" PRIx16 ", got: rotl16(0x%" PRIx16 ", %zu) == 0x%" PRIx16,
              value, shift, expected, value, shift, actual);
}

static void check_rotl32(uint32_t value, uint32_t expected, size_t shift) {
    uint32_t actual = qc_rotl32(value, shift);
    qc_assert(actual == expected,
              "Expected: rotl32(0x%" PRIx32 ", %zu) == 0x%" PRIx32 ", got: rotl32(0x%" PRIx32 ", %zu) == 0x%" PRIx32,
              value, shift, expected, value, shift, actual);
}

static void check_rotl64(uint64_t value, uint64_t expected, size_t shift) {
    uint64_t actual = qc_rotl64(value, shift);
    qc_assert(actual == expected,
              "Expected: rotl64(0x%" PRIx64 ", %zu) == 0x%" PRIx64 ", got: rotl64(0x%" PRIx64 ", %zu) == 0x%" PRIx64,
              value, shift, expected, value, shift, actual);
}

static void check_rotl_usize(size_t value, size_t expected, size_t shift) {
    size_t actual = qc_rotl_usize(value, shift);
    qc_assert(actual == expected, "Expected: rotl_usize(0x%zx, %zu) == 0x%zx, got: rotl_usize(0x%zx, %zu) == 0x%zx",
              value, shift, expected, value, shift, actual);
}

static void check_zeroes(void) {
    for (size_t i = 0; i < 8; ++i) {
        check_rotr8(0, 0, i);
        check_rotl8(0, 0, i);
    }
    for (size_t i = 0; i < 16; ++i) {
        check_rotr16(0, 0, i);
        check_rotl16(0, 0, i);
    }
    for (size_t i = 0; i < 32; ++i) {
        check_rotr32(0, 0, i);
        check_rotl32(0, 0, i);
    }
    for (size_t i = 0; i < 64; ++i) {
        check_rotr64(0, 0, i);
        check_rotl64(0, 0, i);
    }
    for (size_t i = 0; i < sizeof(size_t) * 8; ++i) {
        check_rotr_usize(0, 0, i);
        check_rotl_usize(0, 0, i);
    }
}

static void check_8(void) {
    check_rotr8(0x04, 0x02, 1);
    check_rotr8(0x04, 0x01, 2);
    check_rotr8(0x04, 0x80, 3);
    check_rotl8(0x40, 0x80, 1);
    check_rotl8(0x40, 0x01, 2);
    check_rotl8(0x40, 0x02, 3);
}

static void check_16(void) {
    check_rotr16(0x0004, 0x0002, 1);
    check_rotr16(0x0004, 0x0001, 2);
    check_rotr16(0x0004, 0x8000, 3);
    check_rotl16(0x4000, 0x8000, 1);
    check_rotl16(0x4000, 0x0001, 2);
    check_rotl16(0x4000, 0x0002, 3);
}

static void check_32(void) {
    check_rotr32(0x00000004, 0x00000002, 1);
    check_rotr32(0x00000004, 0x00000001, 2);
    check_rotr32(0x00000004, 0x80000000, 3);
    check_rotl32(0x40000000, 0x80000000, 1);
    check_rotl32(0x40000000, 0x00000001, 2);
    check_rotl32(0x40000000, 0x00000002, 3);
}

static void check_64(void) {
    check_rotr64(0x0000000000000004, 0x0000000000000002, 1);
    check_rotr64(0x0000000000000004, 0x0000000000000001, 2);
    check_rotr64(0x0000000000000004, 0x8000000000000000, 3);
    check_rotl64(0x4000000000000000, 0x8000000000000000, 1);
    check_rotl64(0x4000000000000000, 0x0000000000000001, 2);
    check_rotl64(0x4000000000000000, 0x0000000000000002, 3);
}

int main(void) {
    check_zeroes();
    check_8();
    check_16();
    check_32();
    check_64();
    check_rotr_usize(0x04, 0x02, 1);
    check_rotl_usize(0x04, 0x08, 1);
}
