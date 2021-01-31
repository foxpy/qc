#include "qc/random.h"
#include "qc/error.h"

qc_result qc_rnd_init(qc_rnd* state, qc_err* err) {
    qc_err_set(err,
               "Your platform is unsupported. "
               "Please consider opening an issue, or, even better, sending a pull request");
    state->s64 = 0;
    return QC_FAILURE;
}
