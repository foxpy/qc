#include <stdint.h>
#include <stddef.h>
#include "qc/random.h"
#include "qc/tests.h"

// it is hard to make a reliable test of random, but we will try our best
#define ITERATIONS 1000

static void test_64_uniform(uint64_t upper) {
    qc_err* err = qc_err_new();
    qc_rnd s;
    qc_assert(qc_rnd_init(&s, err) == QC_SUCCESS, "Failed to initialize random");
    for (size_t i = 0; i < ITERATIONS; ++i) {
        uint64_t val = qc_rnd64_uniform(&s, upper);
        qc_assert(val < upper,
                  "qc_rnd64_uniform falls out of specified range");
    }
    qc_err_free(err);
}

static void test_64(int64_t low, int64_t high) {
    qc_err* err = qc_err_new();
    qc_rnd s;
    qc_assert(qc_rnd_init(&s, err) == QC_SUCCESS, "Failed to initialize random");
    for (size_t i = 0; i < ITERATIONS; ++i) {
        int64_t val = qc_rnd_range64(&s, low, high);
        qc_assert(((val >= low) && (val < high)),
                  "qc_rnd_range64 falls out of specified range");
    }
    qc_err_free(err);
}

static void test_fp64(double low, double high) {
    qc_err* err = qc_err_new();
    qc_rnd s;
    qc_assert(qc_rnd_init(&s, err) == QC_SUCCESS, "Failed to initialize random: %s", qc_err_get(err));
    for (size_t i = 0; i < ITERATIONS; ++i) {
        double val = qc_rnd_range_fp64(&s, low, high);
        qc_assert(((val >= low) && (val < high)),
                  "qc_rnd_range_fp64 falls out of specified range");
    }
    qc_err_free(err);
}

int main(void) {
    test_64_uniform(2);
    test_64_uniform(3);
    test_64_uniform(7);
    test_64_uniform(8191);
    test_64_uniform(4294967295);
    test_64(2, 8);
    test_64(-2, 4);
    test_64(-10, -2);
    test_64(550, 2500);
    test_64(-513, 254);
    test_64(-25700, -12010);
    test_64(2147473648, 2147483647);
    test_64(-200, 150);
    test_64(-2147473640, -2147472640);
    test_64(9223372036854774808, 9223372036854775800);
    test_64(-200, 150);
    test_64(-9223372036854775800, -9223372036854774808);
    test_fp64(0.4f, 2.5f);
    test_fp64(-1.2f, 2.6f);
    test_fp64(-16.4f, -3.1f);
    test_fp64(3.1e+38f, 3.2e+38f);
    test_fp64(1.2e-37f, 1.3e-37f);
    test_fp64(0.4, 2.5);
    test_fp64(-1.2, 2.6);
    test_fp64(-16.4, -3.1);
    test_fp64(1.6e+308, 1.7e+308);
    test_fp64(2.1e-308, 2.2e-308);
}
