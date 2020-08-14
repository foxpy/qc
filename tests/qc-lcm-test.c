#include "qc.h"

int main() {
    qc_assert(lcm(4, 6) == 12, "expected: gcd(4, 6) == 12");
    qc_assert(lcm(2, 3) == 6, "expected: gcd(2, 3) == 6");
    qc_assert(lcm(13, 17) == 221, "expected: gcd(13, 17) == 221");
}
