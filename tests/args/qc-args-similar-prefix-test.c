#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "qc/args.h"
#include "qc/error.h"
#include "qc/tests.h"

int main(void) {
    qc_err* err = qc_err_new();
    qc_args* args = qc_args_new();
    size_t x, xx, y, z, w;
    qc_args_unsigned(args, "dim-x", &x, NULL);
    qc_args_unsigned(args, "dim-xx", &xx, NULL);
    qc_args_unsigned(args, "dim-y", &y, "some hint for no reason");
    qc_args_unsigned(args, "dim-z", &z, NULL);
    qc_args_unsigned_default(args, "dim-w", 3, &w, NULL);
    if (qc_args_parse(args, 5, (char*[]){
        "/path/to/exe", "--dim-y=4", "--dim-x=5", "--dim-xx=20", "--dim-z=7"
    }, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse arguments");
    }
    qc_assert(x == 5, "Wrong value for x, expected %zu, got %zu", (size_t) 5, x);
    qc_assert(xx == 20, "Wrong value for xx, expected %zu, got %zu", (size_t) 20, xx);
    qc_assert(y == 4, "Wrong value for y, expected %zu, got %zu", (size_t) 4, y);
    qc_assert(z == 7, "Wrong value for z, expected %zu, got %zu", (size_t) 7, z);
    qc_assert(w == 3, "Wrong value for w, expected %zu, got %zu", (size_t) 3, w);
    qc_args_free(args);
    qc_err_free(err);
}
