#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "qc/args.h"
#include "qc/error.h"
#include "qc/tests.h"
#include "qc/math.h"

struct config {
    size_t a;
    size_t b;
    ptrdiff_t c;
    ptrdiff_t d;
    double e;
    double f;
    char const* g;
    char const* h;
    bool i;
    bool j;
} cfg = {0};

int main(void) {
    qc_args* args = qc_args_new();
    qc_err* err = qc_err_new();
    qc_args_unsigned(args, "a", &cfg.a, NULL);
    qc_args_unsigned_default(args, "b", 2, &cfg.b, NULL);
    qc_args_signed_default(args, "c", -56, &cfg.c, NULL);
    qc_args_signed(args, "d", &cfg.d, NULL);
    qc_args_double(args, "e", &cfg.e, NULL);
    qc_args_double_default(args, "f", 126.513, &cfg.f, NULL);
    qc_args_string_default(args, "g", "sample", &cfg.g, NULL);
    qc_args_string(args, "h", &cfg.h, NULL);
    qc_args_flag(args, 'i', "i", &cfg.i, NULL);
    qc_args_flag(args, 'j', "j", &cfg.j, NULL);

    qc_result result = qc_args_parse(args, 1 + 10 + 3, (char*[]){
        "/path/to/exe",
        "--a=25", "--c=-200", "--d=12500",
        "--e=156.75", "--f=-213.666", "--h=\"sample text\"",
        "-i", "--j", "another sample text", "yet another sample text",
        "--", "--some-unrelated-arg", "--help", NULL
    }, err);
    qc_assert(result == QC_SUCCESS, "qc_args_parse has failed: %s", qc_err_get(err));
    qc_assert(cfg.a == 25 &&
              cfg.b == 2 &&
              cfg.c == -200 &&
              cfg.d == 12500 &&
              qc_almost_equal_fp64(cfg.e, 156.75, 100) &&
              qc_almost_equal_fp64(cfg.f, -213.666, 100) &&
              strcmp(cfg.g, "sample") == 0 &&
              strcmp(cfg.h, "sample text") == 0 &&
              cfg.i == true &&
              cfg.j == true,
                     "expected values don't match");
    qc_assert(qc_args_positionals_index(args) == 9, "qc_args_positionals_index() returns wrong value");
    qc_assert(qc_args_positionals_count(args) == 2, "qc_args_positionals_count() returns wrong value");
    qc_assert(qc_args_extras_index(args) == 12, "qc_args_extras_index returns wrong value");
    qc_assert(qc_args_extras_count(args) == 2, "qc_args_extras_count returns wrong value");
    qc_err_free(err);
    qc_args_free(args);
}
