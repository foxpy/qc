#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include "qc/random.h"
#include "qc/math.h"
#include "qc/utils.h"

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

struct qc_distr_normal {
    qc_rnd rnd;
    double mu;
    double sigma;
    double z0;
    double z1;
    bool has_to_be_populated;
};

static void qc_distr_normal_populate(qc_distr_normal* state) {
    double u1, u2;
    do {
        u1 = qc_rnd_fp64(&state->rnd);
        u2 = qc_rnd_fp64(&state->rnd);
    } while (u1 <= DBL_EPSILON);
    double mag = state->sigma * sqrt(-2.0 * log(u1));
    state->z0 = mag * cos(2.0 * QC_PI * u2) + state->mu;
    state->z1 = mag * sin(2.0 * QC_PI * u2) + state->mu;
    state->has_to_be_populated = false;
}

qc_distr_normal* qc_distr_normal_init(double mu, double sigma, qc_err* err) {
    qc_distr_normal* ret = qc_malloc(sizeof(qc_distr_normal));
    if (qc_rnd_init(&ret->rnd, err) == QC_FAILURE) {
        qc_err_append_front(err, "Failed to obtain entropy for normal distribution generator");
        free(ret);
        return NULL;
    } else {
        qc_distr_normal_settings(ret, mu, sigma);
        return ret;
    }
}

void qc_distr_normal_settings(qc_distr_normal* state, double mu, double sigma) {
    state->mu = mu;
    state->sigma = sigma;
    state->z0 = 0.0;
    state->z1 = 0.0;
    qc_distr_normal_populate(state);
}

double qc_distr_normal_gen(qc_distr_normal* state) {
    double tmp;
    if (state->has_to_be_populated) {
        tmp = state->z1;
        qc_distr_normal_populate(state);
    } else {
        tmp = state->z0;
        state->has_to_be_populated = true;
    }
    return tmp;
}

void qc_distr_normal_free(qc_distr_normal* state) {
    free(state);
}
