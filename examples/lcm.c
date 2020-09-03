#include <stdio.h>
#include "qc.h"

int main(int argc, char* argv[]) {
    size_t a , b;
    char* err;
    qc_args* args = qc_args_new();
    qc_args_brief(args, "Computes Least Common Multiple of two integers");
    qc_args_unsigned(args, "left", &a, NULL);
    qc_args_unsigned(args, "right", &b, NULL);
    if (qc_args_parse(args, argc, argv, &err) == -1) {
        fprintf(stderr, "Error: %s\n", err);
        fputc('\n', stderr);
        qc_args_call_help(args);
        free(err);
        exit(EXIT_FAILURE);
    } else if (a == 0 && b == 0) {
        fputs("Both arguments should not be 0 at the same time\n", stderr);
        exit(EXIT_FAILURE);
    } else {
        printf("%zu\n", lcm(a, b));
    }
    qc_args_free(args);
}
