#include <stdint.h>
#include <stddef.h>
#include "qc/random.h"
#include "qc/tests.h"

// it is hard to make a reliable test of random, but we will try our best
#define ITERATIONS 1000

static void test_64_uniform(qc_rnd* rnd, uint64_t upper) {
    for (size_t i = 0; i < ITERATIONS; ++i) {
        uint64_t val = qc_rnd64_uniform(rnd, upper);
        qc_assert(val < upper, "qc_rnd64_uniform falls out of specified range");
    }
}

static void test_64(qc_rnd* rnd, int64_t low, int64_t high) {
    for (size_t i = 0; i < ITERATIONS; ++i) {
        int64_t val = qc_rnd_range64(rnd, low, high);
        qc_assert(((val >= low) && (val < high)), "qc_rnd_range64 falls out of specified range");
    }
}

static void test_fp64(qc_rnd* rnd, double low, double high) {
    for (size_t i = 0; i < ITERATIONS; ++i) {
        double val = qc_rnd_range_fp64(rnd, low, high);
        qc_assert(((val >= low) && (val < high)), "qc_rnd_range_fp64 falls out of specified range");
    }
}

int main(void) {
    qc_err* err = qc_err_new();
    qc_rnd rnd;
    qc_assert(qc_rnd_init(&rnd, err) == QC_SUCCESS, "Failed to initialize random generator: %s", qc_err_get(err));
    qc_err_free(err);
    test_64_uniform(&rnd, 2);
    test_64_uniform(&rnd, 3);
    test_64_uniform(&rnd, 7);
    test_64_uniform(&rnd, 8191);
    test_64_uniform(&rnd, 4294967295);
    test_64(&rnd, 2, 8);
    test_64(&rnd, -2, 4);
    test_64(&rnd, -10, -2);
    test_64(&rnd, 550, 2500);
    test_64(&rnd, -513, 254);
    test_64(&rnd, -25700, -12010);
    test_64(&rnd, 2147473648, 2147483647);
    test_64(&rnd, -200, 150);
    test_64(&rnd, -2147473640, -2147472640);
    test_64(&rnd, 9223372036854774808, 9223372036854775800);
    test_64(&rnd, -200, 150);
    test_64(&rnd, -9223372036854775800, -9223372036854774808);
    test_fp64(&rnd, 0.4f, 2.5f);
    test_fp64(&rnd, -1.2f, 2.6f);
    test_fp64(&rnd, -16.4f, -3.1f);
    test_fp64(&rnd, 3.1e+38f, 3.2e+38f);
    test_fp64(&rnd, 1.2e-37f, 1.3e-37f);
    test_fp64(&rnd, 0.4, 2.5);
    test_fp64(&rnd, -1.2, 2.6);
    test_fp64(&rnd, -16.4, -3.1);
    test_fp64(&rnd, 1.6e+308, 1.7e+308);
    test_fp64(&rnd, 2.1e-308, 2.2e-308);
}
