#include <stdint.h>
#include "qc.h"

#define SEED UINT64_C(0x83401d53c3745176)
#define ITERATIONS 1000

int main() {
    qc_rnd rnd1, rnd2;
    qc_rnd_seed(&rnd1, SEED);
    qc_rnd_seed(&rnd2, SEED);
    for (size_t i = 0; i < ITERATIONS; ++i) {
        qc_assert(qc_rnd64(&rnd1) == qc_rnd64(&rnd2), "qc_rnd64 random is not deterministic");
        qc_assert(qc_rnd32(&rnd1) == qc_rnd32(&rnd2), "qc_rnd32 random is not deterministic");
        qc_assert(qc_rnd16(&rnd1) == qc_rnd16(&rnd2), "qc_rnd16 random is not deterministic");
        qc_assert(qc_rnd8(&rnd1) == qc_rnd8(&rnd2), "qc_rnd8 random is not deterministic");
        qc_assert(qc_rnd_fp64(&rnd1) == qc_rnd_fp64(&rnd2), "qc_rnd_fp64 random is not deterministic");
        qc_assert(qc_rnd_fp32(&rnd1) == qc_rnd_fp32(&rnd2), "qc_rnd_fp32 random is not deterministic");
    }
}
