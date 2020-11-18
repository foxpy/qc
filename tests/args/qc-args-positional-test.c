#include <string.h>
#include "qc.h"

int main() {
    qc_args* args = qc_args_new();
    qc_err* err = qc_err_new();
    qc_result result = qc_args_parse(args, 3, (char*[]){
        "/path/to/exe", "test1", "test 2", NULL
    }, err);
    qc_assert(result == QC_SUCCESS, sprintf_alloc("qc_args_parse has failed: %s", err));
    qc_assert(qc_args_positionals_index(args) == 1, "qc_args_positionals_index() returns wrong value");
    qc_assert(qc_args_positionals_count(args) == 2, "qc_args_positionals_count() returns wrong value");
    qc_err_free(err);
    qc_args_free(args);
}
