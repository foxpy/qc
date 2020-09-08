#include <stdint.h>
#include "qc.h"

// it is hard to make a reliable test of random, but we will try our best
#define ITERATIONS 1000

void test_64(int64_t low, int64_t high) {
    qc_rnd s;
    qc_assert(qc_rnd_init(&s) == true, "Failed to initialize random");
    for (size_t i = 0; i < ITERATIONS; ++i) {
        int64_t val = qc_rnd_range64(&s, low, high);
        qc_assert(((val >= low) || (val <= high)),
                  "qc_rnd_range64 falls out of specified range");
    }
}

void test_fp64(double low, double high) {
    qc_rnd s;
    qc_assert(qc_rnd_init(&s) == true, "Failed to initialize random");
    for (size_t i = 0; i < ITERATIONS; ++i) {
        double val = qc_rnd_range_fp64(&s, low, high);
        qc_assert(((val >= low) || (val <= high)),
                  "qc_rnd_range_fp64 falls out of specified range");
    }
}

int main() {
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
    test_64(-9223372036854774808, -9223372036854775800);
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
