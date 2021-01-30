#include <stdint.h>
#include "qc/math.h"

uintmax_t qc_lcm(uintmax_t a, uintmax_t b) {
    return a * b / qc_gcd(a, b);
}
