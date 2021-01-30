#include <stdint.h>
#include "qc/math.h"
#include "qc/tests.h"

int main(void) {
    qc_assert(qc_max(4, 8) == 8, "expected: qc_max(4, 8) == 8");
    qc_assert(qc_max(4u, 16u) == 16u, "expected: qc_max(4u, 16u) == 16u");
    qc_assert(qc_max(0u, 16u) == 16u, "expected: qc_max(0u, 16u) == 16u");
    qc_assert(qc_max(-8, 16) == 16, "expected: qc_max(-8, 16) == 16");
    qc_assert(qc_max(UINT64_C(0x20000000000), UINT64_C(0x40000000000)) == UINT64_C(0x40000000000),
              "expected: qc_max(0x20000000000, 0x40000000000) == 0x40000000000");
    qc_assert(qc_max(4.3, 4.2) == 4.3, "expected: qc_max(4.3, 4.2) == 4.3");
    qc_assert(qc_max(4.3f, 4.2f) == 4.3f, "expected: qc_max(4.3f, 4.2f) == 4.3f");
    qc_assert(qc_max(-4.3f, 4.2f) == 4.2f, "expected: qc_max(-4.3f, 4.2f) == 4.2f");
    qc_assert(qc_max(4.3, 4.2) == 4.3, "expected: qc_max(4.3, 4.2) == 4.3");
    qc_assert(qc_max(-4.3, 4.2) == 4.2, "expected: qc_max(-4.3, 4.2) == 4.2");
}
