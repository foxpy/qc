#include <stdio.h>
#include <stdlib.h>
#include "qc/args.h"
#include "qc/tests.h"

static void help(void* help_data) {
    char* program_name = help_data;
    fprintf(stderr, "Usage: %s The quick brown fox... just kidding, this program is useless\n", program_name);
}

int main(void) {
    qc_args* args = qc_args_new();
    qc_err* err = qc_err_new();
    qc_args_set_help(args, help, "/path/to/exe");
    qc_result result = qc_args_parse(args, 3, (char*[]){
        "/path/to/exe", "hello", "--help", NULL
    }, err);
    qc_assert(result == QC_SUCCESS, "qc_args_parse has failed: %s", qc_err_get(err));
    qc_err_free(err);
    qc_args_free(args);

    // this test should call help and exit
    // if it did not: the test has failed
    exit(EXIT_FAILURE);
}
