#include "qc.h"
#include <stdio.h>

static void help(char* program_name) {
    fprintf(stderr, "%s <useful halp message>\n", program_name);
}

int main() {
    qc_args* args = qc_args_new();
    qc_args_set_help(args, (void (*)(void*)) help, "/path/to/exe");
    char *err;
    if (qc_args_parse(args, 4, (char*[]) {
        "/path/to/exe", "--suspicious-flag", "-vvv", "--help", NULL
    }, &err) != 0) {
        fprintf(stderr, "qc_args: %s\n", err);
        free(err);
    }
    qc_args_free(args);

    // qc_args_parse is expected to print help and exit with zero
    // if not, the test has failed
    return EXIT_FAILURE;
}
