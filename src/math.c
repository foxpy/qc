#include "qc.h"

size_t gcd(size_t a, size_t b) {
    assert(!(a == 0 && b == 0));
    if (a == b || b == 0) {
        return a;
    } else if (a == 0) {
        return b;
    } else if (a % 2 == 0 && b % 2 == 0) {
        return 2 * gcd(a / 2, b / 2);
    } else if (a % 2 == 0 && b % 2 == 1) {
        return gcd(a / 2, b);
    } else if (a % 2 == 1 && b % 2 == 0) {
        return gcd(a, b / 2);
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
