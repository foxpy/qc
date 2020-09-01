#include <stdio.h>
#include "qc.h"

int main(int argc, char* argv[]) {
    size_t a = 0, b = 0;
    char* err;
    qc_args* args = qc_args_new();
    qc_args_unsigned(args, "left", &a, NULL);
    qc_args_unsigned(args, "right", &b, NULL);
    if (qc_args_parse(args, argc, argv, &err) == -1) {
        fprintf(stderr, "Error: %s\n", err);
        fputc('\n', stderr);
        qc_args_call_help(args);
        free(err);
        exit(EXIT_FAILURE);
    } else if (a == 0) {
        fputs("Left value is required but not set\n", stderr);
    } else if (b == 0) {
        fputs("Right value is required but not set\n", stderr);
    } else {
        printf("%lu\n", (unsigned long) (lcm(a, b)));
    }
    qc_args_free(args);
}
