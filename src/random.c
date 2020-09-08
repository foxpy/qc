#include "qc.h"
#include <stdint.h>
#include <string.h>

#define DOUBLE_ONE_EXPONENT UINT64_C(0x3ff0000000000000)
#define DOUBLE_FRACTION_MASK UINT64_C(0x000fffffffffffff)

static void xorshift64(uint64_t* s) {
    *s ^= *s << 21u;
    *s ^= *s >> 15u;
    *s ^= *s << 29u;
}

void qc_rnd_seed(qc_rnd* state, uint64_t seed) {
    state->s64 = seed;
}

uint64_t qc_rnd64(qc_rnd* state) {
    xorshift64(&state->s64);
    return state->s64;
}

double qc_rnd_fp64(qc_rnd* state) {
    xorshift64(&state->s64);
    qc_rnd tmp;
    memcpy(&tmp, state, sizeof(qc_rnd));
    tmp.s64 &= DOUBLE_FRACTION_MASK;
    tmp.s64 |= DOUBLE_ONE_EXPONENT;
    tmp.fp64 -= 1.0;
    return tmp.fp64;
}
