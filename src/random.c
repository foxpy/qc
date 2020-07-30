#include "qc.h"
#include <stdint.h>
#include <string.h>

#define DOUBLE_ONE_EXPONENT UINT64_C(0x3ff0000000000000)
#define DOUBLE_FRACTION_MASK UINT64_C(0x000fffffffffffff)
#define FLOAT_ONE_EXPONENT UINT32_C(0x3f800000)
#define FLOAT_FRACTION_MASK UINT32_C(0x007fffff)

static void xorshift64(uint64_t *s) {
    *s ^= *s << 21;
    *s ^= *s >> 15;
    *s ^= *s << 29;
}

uint8_t rnd8(qc_rnd *state) {
    xorshift64(&state->s64);
    return state->s8[7];
}

uint16_t rnd16(qc_rnd *state) {
    xorshift64(&state->s64);
    return state->s16[3];
}

uint32_t rnd32(qc_rnd *state) {
    xorshift64(&state->s64);
    return state->s32[1];
}

uint64_t rnd64(qc_rnd *state) {
    xorshift64(&state->s64);
    return state->s64;
}

double rnd_fp64(qc_rnd *state) {
    xorshift64(&state->s64);
    qc_rnd tmp;
    memcpy(&tmp, state, sizeof(qc_rnd));
    tmp.s64 &= DOUBLE_FRACTION_MASK;
    tmp.s64 |= DOUBLE_ONE_EXPONENT;
    tmp.fp64 -= 1.0;
    return tmp.fp64;
}

float rnd_fp32(qc_rnd *state) {
    xorshift64(&state->s64);
    qc_rnd tmp;
    memcpy(&tmp, state, sizeof(qc_rnd));
    tmp.s32[1] &= FLOAT_FRACTION_MASK;
    tmp.s32[1] |= FLOAT_ONE_EXPONENT;
    tmp.fp32[1] -= 1.0f;
    return tmp.fp32[1];
}
