#include "qc.h"

int main() {
    qc_assert(gcd(0, 0) == 0, "expected: gcd(0, 0) == 0");
    qc_assert(gcd(0, 2) == 2, "expected: gcd(0, 2) == 2");
    qc_assert(gcd(4, 6) == 2, "expected: gcd(4, 6) == 2");
    qc_assert(gcd(8, 7) == 1, "expected: gcd(8, 7) == 1");
    qc_assert(gcd(8, 12) == 4, "expected: gcd(8, 12) == 4");
    qc_assert(gcd(1, 1) == 1, "expected: gcd(1, 1) == 1");
    qc_assert(gcd(SIZE_MAX, SIZE_MAX) == SIZE_MAX, "expected: gcd(SIZE_MAX, SIZE_MAX) == SIZE_MAX");
    qc_assert(gcd(128, 2147483648) == 128, "expected: gcd(128, 2147483648) == 128");
}
