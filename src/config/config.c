#include "qc/config.h"
#include "qc/error.h"
#include "qc/utils.h"
#include "config_impl.h"

qc_result qc_cfg_open_string(char const* str, qc_cfg** dst, qc_err* err) {
    QC_UNUSED(str);
    QC_UNUSED(dst);
    QC_UNUSED(err);
    QC_UNIMPLEMENTED();
}

void qc_cfg_close(qc_cfg* cfg) {
    QC_UNUSED(cfg);
    QC_UNIMPLEMENTED();
}
