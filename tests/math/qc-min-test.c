#include <stdint.h>
#include "qc/math.h"
#include "qc/tests.h"

int main(void) {
    qc_assert(qc_min(4, 8) == 4, "expected: qc_min(4, 8) == 4");
    qc_assert(qc_min(4u, 16u) == 4u, "expected: qc_min(4u, 16u) == 4u");
    qc_assert(qc_min(0u, 16u) == 0u, "expected: qc_min(0u, 16u) == 0u");
    qc_assert(qc_min(-8, 16) == -8, "expected: qc_min(-8, 16) == -8");
    qc_assert(qc_min(UINT64_C(0x20000000000), UINT64_C(0x40000000000)) == UINT64_C(0x20000000000),
              "expected: qc_min(0x20000000000, 0x40000000000) == 0x20000000000");
    qc_assert(qc_min(4.3, 4.2) == 4.2, "expected: qc_min(4.3, 4.2) == 4.2");
    qc_assert(qc_min(4.3f, 4.2f) == 4.2f, "expected: qc_min(4.3f, 4.2f) == 4.2f");
    qc_assert(qc_min(-4.3f, 4.2f) == -4.3f, "expected: qc_min(-4.3f, 4.2f) == -4.3f");
    qc_assert(qc_min(4.3, 4.2) == 4.2, "expected: qc_min(4.3, 4.2) == 4.2");
    qc_assert(qc_min(-4.3, 4.2) == -4.3, "expected: qc_min(-4.3, 4.2) == -4.3");
}
