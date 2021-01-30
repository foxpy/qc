#include <stdint.h>
#include "qc/math.h"

uintmax_t qc_max_u(uintmax_t a, uintmax_t b) {
    return a > b ? a : b;
}

intmax_t qc_max_s(intmax_t a, intmax_t b) {
    return a > b ? a : b;
}

double qc_max_d(double a, double b) {
    return a > b ? a : b;
}
