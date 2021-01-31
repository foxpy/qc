#include <stdlib.h>
#include <stdint.h>
#include "qc/error.h"
#include "qc/utils.h"
#include "qc/random.h"

qc_result qc_rnd_init(qc_rnd* state, qc_err* err) {
    QC_UNUSED(err);
    arc4random_buf(&state->s64, sizeof(uint64_t));
    return QC_SUCCESS;
}
