#pragma once
#include <stdint.h>
#include <stddef.h>
#include "qc/error.h"

typedef union qc_rnd_state_t {
    uint64_t s64;
    double fp64;
} qc_rnd;

// Use rnd_init to seed random generator, then get
// random using qc_rnd64 and qc_rnd_fp64 functions.
// qc_rnd_init returns true on success and zero on failure
qc_result qc_rnd_init(qc_rnd* state, qc_err* err);
void qc_rnd_seed(qc_rnd* state, uint64_t seed);
uint64_t qc_rnd64(qc_rnd* state);
uint64_t qc_rnd64_uniform(qc_rnd* state, uint64_t upper);
double qc_rnd_fp64(qc_rnd* state);
void qc_rnd_buf(qc_rnd* state, size_t len, uint8_t buf[static len]);

// these functions return random in specified range if you need so
int64_t qc_rnd_range64(qc_rnd* state, int64_t low, int64_t high);
double qc_rnd_range_fp64(qc_rnd* state, double low, double high);

// Normal distribution
typedef struct qc_distr_normal qc_distr_normal;
qc_distr_normal* qc_distr_normal_init(double mu, double sigma, qc_err* err);
void qc_distr_normal_settings(qc_distr_normal* state, double mu, double sigma);
double qc_distr_normal_gen(qc_distr_normal* state);
void qc_distr_normal_free(qc_distr_normal* state);

// Crypto quality random
qc_result qc_rnd_os_buf(size_t len, uint8_t buf[static len], qc_err* err);
