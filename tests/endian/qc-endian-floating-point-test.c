#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "qc/endian.h"
#include "qc/tests.h"
#include "qc/math.h"

static void check_double(double x) {
    uint8_t be[8];
    uint8_t le[8];
    qc_fp64_to_be(be, x);
    qc_fp64_to_le(le, x);
    {
        uint8_t tmp[8];
        for (size_t i = 0; i < 8; ++i) {
            tmp[i] = le[8 - 1 - i];
        }
        qc_assert(memcmp(be, tmp, sizeof(be)) == 0, "qc_fp64 endianness functions damage data");
    }
    {
        double from_be = qc_fp64_from_be(be);
        double from_le = qc_fp64_from_le(le);
        qc_assert(from_be == x, "qc_fp64_from_be misbehaves");
        qc_assert(from_le == x, "qc_fp64_from_le misbehaves");
    }
}

static void check_float(float x) {
    uint8_t be[4];
    uint8_t le[4];
    qc_fp32_to_be(be, x);
    qc_fp32_to_le(le, x);
    {
        uint8_t tmp[4];
        for (size_t i = 0; i < 4; ++i) {
            tmp[i] = le[4 - 1 - i];
        }
        qc_assert(memcmp(be, tmp, sizeof(be)) == 0, "qc_fp32 endianness functions damage data");
    }
    {
        float from_be = qc_fp32_from_be(be);
        float from_le = qc_fp32_from_le(le);
        qc_assert(from_be == x, "qc_fp32_from_be misbehaves");
        qc_assert(from_le == x, "qc_fp32_from_le misbehaves");
    }
}

int main(void) {
    check_double(0.0);
    check_double(1.0);
    check_double(257.974);
    check_double(-257.974);
    check_double(QC_PI);
    check_float(0.0f);
    check_float(1.0f);
    check_float(257.974f);
    check_float(-257.974f);
    check_float((float) QC_PI);
}
