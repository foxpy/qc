#include "qc.h"

size_t gcd(size_t a, size_t b) {
    if (a == 0 && b == 0) {
        return 0;
    } else if (a == b || b == 0) {
        return a;
    } else if (a == 0) {
        return b;
    } else if (a % 2 == 0 && b % 2 == 0) {
        return 2 * gcd(a >> 1u, b >> 1u);
    } else if (a % 2 == 0 && b % 2 == 1) {
        return gcd(a >> 1u, b);
    } else if (a % 2 == 1 && b % 2 == 0) {
        return gcd(a, b >> 1u);
    } else {
        if (a > b) {
            return gcd(a - b, b);
        } else {
            return gcd(b - a, a);
        }
    }
}

size_t lcm(size_t a, size_t b) {
    return a * b / gcd(a, b);
}
