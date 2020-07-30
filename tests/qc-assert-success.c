#include "qc.h"

int main() {
    qc_assert(2 == 2, "constant does not equal constant");
    qc_assert(1, "1 is not truth");
    qc_assert(5, "5 is not truth");
    qc_assert(!0, "negation of lie is not truth");
    qc_assert("cake", "cake is a lie");
}
