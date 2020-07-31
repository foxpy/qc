#include "qc.h"

#define ABS(x) ((x >= 0) ? x :-x)

int8_t qc_rnd_range8(qc_rnd *state, int8_t low, int8_t high) {
    int8_t u = qc_rnd8(state);
    u %= ABS(low) + ABS(high);
    return (low >=0 ) ? u - low : u + low;
}

int16_t qc_rnd_range16(qc_rnd *state, int16_t low, int16_t high) {
    int16_t u = qc_rnd16(state);
    u %= ABS(low) + ABS(high);
    return (low >=0 ) ? u - low : u + low;
}

int32_t qc_rnd_range32(qc_rnd *state, int32_t low, int32_t high) {
    int32_t u = qc_rnd32(state);
    u %= ABS(low) + ABS(high);
    return (low >=0 ) ? u - low : u + low;
}

int64_t qc_rnd_range64(qc_rnd *state, int64_t low, int64_t high) {
    int64_t u = qc_rnd64(state);
    u %= ABS(low) + ABS(high);
    return (low >=0 ) ? u - low : u + low;
}

float qc_rnd_range_fp32(qc_rnd *state, float low, float high) {
    return low + qc_rnd_fp32(state) * (high - low);
}

double qc_rnd_range_fp64(qc_rnd *state, double low, double high) {
    return low + qc_rnd_fp64(state) * (high - low);
}
