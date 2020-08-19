#include "qc.h"
#include <stdio.h>

int main() {
    qc_args* args = qc_args_new();
    char *err;
    qc_args_parse(args, 2, (char*[]) {"/path/to/exe", "--help", NULL}, &err);

    // this test is expected to fail gracefully
    // if qc_args_parse does not exist with non-zero code,
    // we exit with zero code to catch a bug
    return EXIT_SUCCESS;
}
