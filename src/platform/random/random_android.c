#include <sys/random.h>
#include <stdint.h>
#include "qc/error.h"
#include "qc/random.h"

qc_result qc_rnd_init(qc_rnd* state, qc_err* err) {
    if (getrandom(&state->s64, sizeof(uint64_t), 0) != sizeof(uint64_t)) {
        qc_err_set(err, "Failed to acquire entropy from kernel");
        state->s64 = 0;
        return QC_FAILURE;
    } else {
        return QC_SUCCESS;
    }
}
