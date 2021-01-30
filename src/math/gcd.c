#include <stdint.h>
#include "qc/math.h"

uintmax_t qc_gcd(uintmax_t a, uintmax_t b) {
    if (a == 0 && b == 0) {
        return 0;
    } else if (a == b || b == 0) {
        return a;
    } else if (a == 0) {
        return b;
    } else if (a % 2 == 0 && b % 2 == 0) {
        return 2 * qc_gcd(a >> 1u, b >> 1u);
    } else if (a % 2 == 0 && b % 2 == 1) {
        return qc_gcd(a >> 1u, b);
    } else if (a % 2 == 1 && b % 2 == 0) {
        return qc_gcd(a, b >> 1u);
    } else {
        if (a > b) {
            return qc_gcd(a - b, b);
        } else {
            return qc_gcd(b - a, a);
        }
    }
}
