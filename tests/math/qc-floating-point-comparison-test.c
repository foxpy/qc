#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <float.h>
#include "qc/math.h"
#include "qc/tests.h"

int main(void) {
    {
        double d1 = 0.2;
        double d2 = 1.0 / sqrt(5.0) / sqrt(5.0);
        qc_assert(qc_almost_equal_fp64(d1, d2, 2), "d1 is not almost equal to d2");
    }
    {
        float f1 = 0.2f;
        float f2 = 1.0f / sqrtf(5.0f) / sqrtf(5.0f);
        qc_assert(qc_almost_equal_fp32(f1, f2, 2), "f1 is not almost equal to f2");
    }
    {
        double x = 5.0;
        double y = x;
        for (size_t i = 0; i < 200; ++i) {
            y -= DBL_EPSILON;
        }
        qc_assert(qc_almost_equal_fp64(x, y, 200), "x is not almost equal to y");
    }
    {
        double x = 4.1;
        double y = 4.2;
        qc_assert(qc_almost_equal_fp64(x, y, 1000) == false, "x is almost equal to y");
    }
}
