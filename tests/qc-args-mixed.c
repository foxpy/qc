#include "qc.h"
#include <string.h>
#include <math.h>

#define EPS 10e-9

struct config {
    size_t a;
    size_t b;
    ptrdiff_t c;
    ptrdiff_t d;
    double e;
    double f;
    char* g;
    char* h;
    bool i;
    bool j;
} cfg = {0};

int main() {
    qc_args* args = qc_args_new();
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

    char* err;
    int rc = qc_args_parse(args, 1 + 10 + 3, (char*[]){
        "/path/to/exe",
        "--a=25", "--c=-200", "--d=12500",
        "--e=156.75", "--f=-213.666", "--h=\"sample text\"",
        "-i", "--j", "another sample text", "yet another sample text",
        "--", "--some-unrelated-arg", "--help", NULL
    }, &err);
    qc_assert(rc == 0, sprintf_alloc("qc_args_parse has failed: %s", err));
    qc_assert(cfg.a == 25 &&
              cfg.b == 2 &&
              cfg.c == -200 &&
              cfg.d == 12500 &&
              fabs(cfg.e - 156.75) < EPS &&
              fabs(cfg.f + 213.666) < EPS &&
              strcmp(cfg.g, "sample") == 0 &&
              strcmp(cfg.h, "sample text") == 0 &&
              cfg.i == true &&
              cfg.j == true,
                     "expected values don't match");
    qc_assert(qc_args_positionals_index(args) == 9, "qc_args_positionals_index() returns wrong value");
    qc_assert(qc_args_positionals_count(args) == 2, "qc_args_positionals_count() returns wrong value");
    qc_assert(qc_args_extras_index(args) == 12, "qc_args_extras_index returns wrong value");
    qc_assert(qc_args_extras_count(args) == 2, "qc_args_extras_count returns wrong value");
    free(cfg.g);
    free(cfg.h);
    qc_args_free(args);
}
