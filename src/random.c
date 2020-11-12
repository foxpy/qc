#include "qc.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>

#define DOUBLE_ONE_EXPONENT (UINT64_C(0x3ff) << 52u)
#define DOUBLE_FRACTION_SHIFT_LENGTH 12u

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

uint64_t qc_rnd64_uniform(qc_rnd* state, uint64_t upper) {
    uint64_t rand_excess = (UINT64_MAX % upper) + 1;
    uint64_t rand_limit = UINT64_MAX - rand_excess;
    uint64_t x;
    while ((x = qc_rnd64(state)) > rand_limit);
    return x % upper;
}

int64_t qc_rnd_range64(qc_rnd* state, int64_t low, int64_t high) {
    assert(high > low);
    return (qc_rnd64_uniform(state, high - low)) + low;
}

double qc_rnd_fp64(qc_rnd* state) {
    xorshift64(&state->s64);
    qc_rnd tmp;
    memcpy(&tmp, state, sizeof(qc_rnd));
    tmp.s64 >>= DOUBLE_FRACTION_SHIFT_LENGTH;
    tmp.s64 |= DOUBLE_ONE_EXPONENT;
    tmp.fp64 -= 1.0;
    return tmp.fp64;
}

double qc_rnd_range_fp64(qc_rnd* state, double low, double high) {
    assert(high > low);
    return low + qc_rnd_fp64(state) * (high - low);
}
