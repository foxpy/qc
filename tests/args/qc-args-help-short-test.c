#include "qc.h"
#include <stdio.h>

int main() {
    qc_args* args = qc_args_new();
    qc_err* err = qc_err_new();
    if (qc_args_parse(args, 5, (char*[]) {
            "/path/to/exe", "--suspicious-flag", "-vhcn", "--", "--qwerty", NULL
    }, err) == QC_FAILURE) {
        fprintf(stderr, "qc_args: %s\n", qc_err_get(err));
    }
    qc_err_free(err);
    qc_args_free(args);

    // qc_args_parse is expected to print help and exit with zero
    // if not, the test has failed
    return EXIT_FAILURE;
}
