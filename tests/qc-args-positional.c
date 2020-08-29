#include "qc.h"
#include <string.h>

int main() {
    qc_args* args = qc_args_new();
    char* err;
    int rc = qc_args_parse(args, 3, (char*[]){
        "/path/to/exe", "test1", "test 2", NULL
    }, &err);
    qc_assert(rc == 0, sprintf_alloc("qc_args_parse has failed: %s", err));
    qc_assert(qc_args_positionals_index(args) == 1, "qc_args_positionals_index() returns wrong value");
    qc_assert(qc_args_positionals_count(args) == 2, "qc_args_positionals_count() returns wrong value");
    qc_args_free(args);
}
