#include "qc.h"
#include <stdint.h>

int main() {
    qc_assert(MAX(4, 8) == 8, "expected: MAX(4, 8) == 8");
    qc_assert(MAX(4, 16) == 16, "expected: MAX(4, 16) == 16");
    qc_assert(MAX(0, 16) == 16, "expected: MAX(0, 16) == 16");
    qc_assert(MAX(-8, 16) == 16, "expected: MAX(-8, 16) == 16");
    qc_assert(MAX(UINT64_C(0x20000000000), UINT64_C(0x40000000000))
              == UINT64_C(0x40000000000),
              "expected: MIN(0x20000000000, 0x40000000000) == 0x40000000000");
    qc_assert(MAX(4.3f, 4.2f) == 4.3f, "expected: MAX(4.3f, 4.2f) == 4.3f");
    qc_assert(MAX(-4.3f, 4.2f) == 4.2f, "expected: MAX(-4.3f, 4.2f) == 4.2f");
    qc_assert(MAX(4.3, 4.2) == 4.3, "expected: MAX(4.3, 4.2) == 4.3");
    qc_assert(MAX(-4.3, 4.2) == 4.2, "expected: MAX(-4.3, 4.2) == 4.2");
}
