#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include "qc/error.h"
#include "qc/config.h"
#include "qc/tests.h"

int main(int argc, char* argv[]) {
    qc_assert(argc == 2, "This test expects exactly one argument: path to config file");
    errno = 0;
    FILE* file = fopen(argv[1], "r");
    qc_assert(file != NULL, "Failed to open file %s: %s", argv[1], strerror(errno));
    qc_err* err = qc_err_new();
    qc_cfg* cfg;
    qc_assert(qc_cfg_open_file(file, &cfg, err) == QC_SUCCESS,
              "qc_cfg_open_file has failed: %s", qc_err_get(err));
    qc_cfg_close(cfg);
    qc_err_free(err);
    fclose(file);
}
