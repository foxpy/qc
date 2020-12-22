#include <stdint.h>
#include "qc/math.h"
#include "qc/tests.h"

int main(void) {
    qc_assert(QC_MIN(4, 8) == 4, "expected: MIN(4, 8) == 4");
    qc_assert(QC_MIN(4, 16) == 4, "expected: MIN(4, 16) == 4");
    qc_assert(QC_MIN(0, 16) == 0, "expected: MIN(0, 16) == 0");
    qc_assert(QC_MIN(-8, 16) == -8, "expected: MIN(-8, 16) == -8");
    qc_assert(QC_MIN(UINT64_C(0x20000000000), UINT64_C(0x40000000000))
              == UINT64_C(0x20000000000),
              "expected: MIN(0x20000000000, 0x40000000000) == 0x20000000000");
    qc_assert(QC_MIN(4.3f, 4.2f) == 4.2f, "expected: MIN(4.3f, 4.2f) == 4.2f");
    qc_assert(QC_MIN(-4.3f, 4.2f) == -4.3f, "expected: MIN(-4.3f, 4.2f) == -4.3f");
    qc_assert(QC_MIN(4.3, 4.2) == 4.2, "expected: MIN(4.3, 4.2) == 4.2");
    qc_assert(QC_MIN(-4.3, 4.2) == -4.3, "expected: MIN(-4.3, 4.2) == -4.3");
}
