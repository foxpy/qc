#include "qc/math.h"
#include "qc/tests.h"

int main(void) {
    qc_assert(qc_lcm(0, 2) == 0, "expected: qc_lcm(0, 2) == 0");
    qc_assert(qc_lcm(4, 6) == 12, "expected: qc_lcm(4, 6) == 12");
    qc_assert(qc_lcm(2, 3) == 6, "expected: qc_lcm(2, 3) == 6");
    qc_assert(qc_lcm(13, 17) == 221, "expected: qc_lcm(13, 17) == 221");
    qc_assert(qc_lcm(127, 8191) == 1040257, "expected: qc_lcm(127, 8191) == 1040257");
}
