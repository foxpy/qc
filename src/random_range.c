#include "qc.h"

int64_t qc_rnd_range64(qc_rnd* state, int64_t low, int64_t high) {
    return (qc_rnd64(state) % (high - low + 1)) + low;
}

double qc_rnd_range_fp64(qc_rnd* state, double low, double high) {
    return low + qc_rnd_fp64(state) * (high - low);
}
