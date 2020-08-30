#include <stdint.h>
#include "qc.h"

// it is hard to make a reliable test of random, but we will try our best
#define ITERATIONS 1000

void test_8(int8_t low, int8_t high) {
    qc_rnd s;
    qc_assert(qc_rnd_init(&s) == true, "Failed to initialize random");
    for (size_t i = 0; i < ITERATIONS; ++i) {
        int8_t val = qc_rnd_range8(&s, low, high);
        qc_assert(((val >= low) || (val <= high)),
                  "qc_rnd_range8 falls out of specified range");
    }
}

void test_16(int16_t low, int16_t high) {
    qc_rnd s;
    qc_assert(qc_rnd_init(&s) == true, "Failed to initialize random");
    for (size_t i = 0; i < ITERATIONS; ++i) {
        int16_t val = qc_rnd_range16(&s, low, high);
        qc_assert(((val >= low) || (val <= high)),
                  "qc_rnd_range16 falls out of specified range");
    }
}

void test_32(int32_t low, int32_t high) {
    qc_rnd s;
    qc_assert(qc_rnd_init(&s) == true, "Failed to initialize random");
    for (size_t i = 0; i < ITERATIONS; ++i) {
        int32_t val = qc_rnd_range32(&s, low, high);
        qc_assert(((val >= low) || (val <= high)),
                  "qc_rnd_range32 falls out of specified range");
    }
}

void test_64(int64_t low, int64_t high) {
    qc_rnd s;
    qc_assert(qc_rnd_init(&s) == true, "Failed to initialize random");
    for (size_t i = 0; i < ITERATIONS; ++i) {
        int64_t val = qc_rnd_range64(&s, low, high);
        qc_assert(((val >= low) || (val <= high)),
                  "qc_rnd_range64 falls out of specified range");
    }
}

void test_fp32(float low, float high) {
    qc_rnd s;
    qc_assert(qc_rnd_init(&s) == true, "Failed to initialize random");
    for (size_t i = 0; i < ITERATIONS; ++i) {
        float val = qc_rnd_range_fp32(&s, low, high);
        qc_assert(((val >= low) || (val <= high)),
                  "qc_rnd_range_fp32 falls out of specified range");
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
    test_8(2, 8);
    test_8(-2, 4);
    test_8(-10, -2);
    test_16(550, 2500);
    test_16(-513, 254);
    test_16(-25700, -12010);
    test_32(2147473648, 2147483647);
    test_32(-200, 150);
    test_32(-2147473640, -2147472640);
    test_64(9223372036854774808, 9223372036854775800);
    test_64(-200, 150);
    test_64(-9223372036854774808, -9223372036854775800);
    test_fp32(0.4f, 2.5f);
    test_fp32(-1.2f, 2.6f);
    test_fp32(-16.4f, -3.1f);
    test_fp32(3.1e+38f, 3.2e+38f);
    test_fp32(1.2e-37f, 1.3e-37f);
    test_fp64(0.4, 2.5);
    test_fp64(-1.2, 2.6);
    test_fp64(-16.4, -3.1);
    test_fp64(1.6e+308, 1.7e+308);
    test_fp64(2.1e-308, 2.2e-308);
}
