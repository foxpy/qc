#include <stdlib.h>
#include "qc/utils.h"
#include "qc/config.h"
#include "config_impl.h"

qc_cfg* qc_cfg_new() {
    qc_cfg* ret = qc_malloc(sizeof(qc_cfg));
    return ret;
}
