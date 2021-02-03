#include <stddef.h>
#include <stdbool.h>
#include "qc/args.h"
#include "qc/error.h"
#include "qc/tests.h"

int main(void) {
    bool a;
    char const* b;
    char const* c;
    char const* d;
    qc_args* args = qc_args_new();
    qc_err* err = qc_err_new();
    qc_args_flag(args, 'd', "decrypt", &a, "a hint");
    qc_args_string_default(args, "input", "-", &b, "some hint");
    qc_args_string_default(args, "output", "-", &c, "another hint");
    qc_args_string(args, "key", &d, "yet another hint");
    qc_result result = qc_args_parse(args, 1, (char*[]){"/path/to/exe", NULL}, err);
    qc_assert(result == QC_FAILURE, "qc_args_parse is expected to fail");
    qc_err_free(err);
    qc_args_free(args);
}
