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
    char* k;
    char* l;
} cfg = {0};

int main() {
    qc_args* args = qc_args_new();
    qc_args_unsigned(args, "a", &cfg.a);
    qc_args_unsigned(args, "b", &cfg.b);
    qc_args_signed(args, "c", &cfg.c);
    qc_args_signed(args, "d", &cfg.d);
    qc_args_double(args, "e", &cfg.e);
    qc_args_double(args, "f", &cfg.f);
    qc_args_string(args, "g", &cfg.g);
    qc_args_string(args, "h", &cfg.h);
    qc_args_flag(args, 'i', "i", &cfg.i);
    qc_args_flag(args, 'j', "j", &cfg.j);
    qc_args_positional(args, &cfg.k);
    qc_args_positional(args, &cfg.l);

    char* err;
    int rc = qc_args_parse(args, 1 + 12 + 3, (char*[]){
        "/path/to/exe",
        "--a=25", "--b=65500", "--c=-200", "--d=12500",
        "--e=156.75", "--f=-213.666", "--g=sample", "--h=\"sample text\"",
        "-i", "--j", "another sample text", "yet another sample text",
        "--", "--some-unrelated-arg", "--help", NULL
    }, &err);
    qc_assert(rc == 0, sprintf_alloc("qc_args_parse has failed: %s", err));
    qc_assert(cfg.a == 25 &&
              cfg.b == 65500 &&
              cfg.c == -200 &&
              cfg.d == 12500 &&
              fabs(cfg.e - 156.75) < EPS &&
              fabs(cfg.f + 213.666) < EPS &&
              strcmp(cfg.g, "sample") == 0 &&
              strcmp(cfg.h, "sample text") == 0 &&
              cfg.i == true &&
              cfg.j == true &&
              strcmp(cfg.k, "another sample text") == 0 &&
              strcmp(cfg.l, "yet another sample text") == 0,
                     "expected values don't match");
    free(cfg.g);
    free(cfg.h);
    free(cfg.k);
    free(cfg.l);
    qc_args_free(args);
}
