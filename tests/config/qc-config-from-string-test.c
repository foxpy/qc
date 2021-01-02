#include "qc/tests.h"
#include "qc/error.h"
#include "qc/config.h"

static char const* config_string = "";

int main() {
    qc_err* err = qc_err_new();
    qc_cfg* cfg;
    qc_assert(qc_cfg_open_string(config_string, &cfg, err) == QC_SUCCESS,
              "qc_cfg_open_string() rejects valid string: %s", qc_err_get(err));
    qc_cfg_close(cfg);
    qc_err_free(err);
}
