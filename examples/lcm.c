#include <stdio.h>
#include "qc.h"

int main(int argc, char* argv[]) {
    size_t a , b;
    qc_args* args = qc_args_new();
    qc_err* err = qc_err_new();
    qc_args_set_brief(args, "Computes Least Common Multiple of two integers");
    qc_args_unsigned(args, "left", &a, NULL);
    qc_args_unsigned(args, "right", &b, NULL);
    if (qc_args_parse(args, argc, argv, err) == QC_FAILURE) {
        fprintf(stderr, "Failed to parse arguments: %s\n", qc_err_get(err));
        fputc('\n', stderr);
        qc_args_call_help(args);
        exit(EXIT_FAILURE);
    } else if (a == 0 && b == 0) {
        fputs("Both arguments should not be 0 at the same time\n", stderr);
        exit(EXIT_FAILURE);
    } else {
        printf("%zu\n", lcm(a, b));
    }
    qc_err_free(err);
    qc_args_free(args);
}
