#include <stddef.h>
#include <stdint.h>
#include <assert.h>

uint16_t qc_rotr8(uint8_t a, size_t n) {
    assert(n < 8);
    return a << (8 - n) | a >> n;
}

uint16_t qc_rotr16(uint16_t a, size_t n) {
    assert(n < 16);
    return a << (16 - n) | a >> n;
}

uint32_t qc_rotr32(uint32_t a, size_t n) {
    assert(n < 32);
    return a << (32 - n) | a >> n;
}

uint64_t qc_rotr64(uint64_t a, size_t n) {
    assert(n < 64);
    return a << (64 - n) | a >> n;
}

size_t qc_rotr_usize(size_t a, size_t n) {
    assert(n < sizeof(size_t) * 8);
    return a << (sizeof(size_t) * 8 - n) | a >> n;
}

uint16_t qc_rotl8(uint8_t a, size_t n) {
    assert(n < 8);
    return a << n | a >> (8 - n);
}

uint16_t qc_rotl16(uint16_t a, size_t n) {
    assert(n < 16);
    return a << n | a >> (16 - n);
}

uint32_t qc_rotl32(uint32_t a, size_t n) {
    assert(n < 32);
    return a << n | a >> (32 - n);
}

uint64_t qc_rotl64(uint64_t a, size_t n) {
    assert(n < 64);
    return a << n | a >> (64 - n);
}

size_t qc_rotl_usize(size_t a, size_t n) {
    assert(n < sizeof(size_t) * 8);
    return a << n | a >> (sizeof(size_t) * 8 - n);
}
