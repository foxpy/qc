#include <stdint.h>
#include "qc/math.h"
#include "qc/tests.h"

int main(void) {
    qc_assert(qc_gcd(0, 0) == 0, "expected: qc_gcd(0, 0) == 0");
    qc_assert(qc_gcd(0, 2) == 2, "expected: qc_gcd(0, 2) == 2");
    qc_assert(qc_gcd(4, 6) == 2, "expected: qc_gcd(4, 6) == 2");
    qc_assert(qc_gcd(8, 7) == 1, "expected: qc_gcd(8, 7) == 1");
    qc_assert(qc_gcd(8, 12) == 4, "expected: qc_gcd(8, 12) == 4");
    qc_assert(qc_gcd(1, 1) == 1, "expected: qc_gcd(1, 1) == 1");
    qc_assert(qc_gcd(SIZE_MAX, SIZE_MAX) == SIZE_MAX, "expected: qc_gcd(SIZE_MAX, SIZE_MAX) == SIZE_MAX");
    qc_assert(qc_gcd(128, 2147483648) == 128, "expected: qc_gcd(128, 2147483648) == 128");
}
