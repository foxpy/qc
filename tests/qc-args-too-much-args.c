#include "qc.h"

int main() {
    char* a;
    qc_args* args = qc_args_new();
    qc_args_positional(args, &a);

    char* err;
    int rc = qc_args_parse(args, 3, (char*[]){
        "/path/to/exe", "1", "2", NULL
    }, &err);
    qc_assert(rc != 0, "here, qc_args is expected to fail");
    qc_args_free(args);
}
