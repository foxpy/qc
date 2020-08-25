#include "qc.h"

int main() {
    qc_assert(lcm(0, 2) == 0, "expected: lcm(0, 2) == 0");
    qc_assert(lcm(4, 6) == 12, "expected: lcm(4, 6) == 12");
    qc_assert(lcm(2, 3) == 6, "expected: lcm(2, 3) == 6");
    qc_assert(lcm(13, 17) == 221, "expected: lcm(13, 17) == 221");
    qc_assert(lcm(127, 8191) == 1040257, "expected: lcm(127, 8191) == 1040257");
}
