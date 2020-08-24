#include <stdio.h>
#include "qc.h"

void help(char* program_name) {
    fputs("Computes Least Common Multiple of two operands\n", stderr);
    fprintf(stderr, "Usage: %s --left=INTEGER --right=INTEGER\n", program_name);
}

int main(int argc, char* argv[]) {
    size_t a = 0, b = 0;
    char* err;
    qc_args* args = qc_args_new();
    qc_args_set_help(args, (void (*)(void*)) help, argv[0]);
    qc_args_unsigned(args, "left", &a);
    qc_args_unsigned(args, "right", &b);
    if (qc_args_parse(args, argc, argv, &err) == -1) {
        fprintf(stderr, "%s\n", err);
        free(err);
        return EXIT_FAILURE;
    } else if (a == 0) {
        fputs("Left value is required but not set\n", stderr);
    } else if (b == 0) {
        fputs("Right value is required but not set\n", stderr);
    } else {
        printf("%llu\n", (unsigned long long) (lcm(a, b)));
    }
    qc_args_free(args);
}
