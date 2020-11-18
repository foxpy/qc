#pragma once
#include <stdint.h>
#include <stdbool.h>
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

// these functions return random in specified range if you need so
int64_t qc_rnd_range64(qc_rnd* state, int64_t low, int64_t high);
double qc_rnd_range_fp64(qc_rnd* state, double low, double high);
