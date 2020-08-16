#include "qc.h"

size_t gcd(size_t a, size_t b) {
    assert(a > 0 && b > 0);
    if (a == b) {
        return a;
    } else if (a > b) {
        return gcd(a - b, b);
    } else {
        return gcd(a, b - a);
    }
}

size_t lcm(size_t a, size_t b) {
    assert(a > 0 && b > 0);
    return a * b / gcd(a, b);
}
