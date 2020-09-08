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
        qc_assert(qc_rnd_fp64(&rnd1) == qc_rnd_fp64(&rnd2), "qc_rnd_fp64 random is not deterministic");
    }
}
