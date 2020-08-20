#include "qc.h"
#include <string.h>

int main() {
    char* first;
    char* second;
    qc_args* args = qc_args_new();
    qc_args_positional(args, &first);
    qc_args_positional(args, &second);

    char* err;
    int rc = qc_args_parse(args, 3, (char*[]){
        "/path/to/exe", "test1", "test 2", NULL
    }, &err);
    qc_assert(rc == 0, sprintf_alloc("qc_args_parse has failed: %s", err));
    qc_assert(strcmp(first, "test1") == 0 && strcmp(second, "test 2") == 0,
              "expected values don't match");
    free(first);
    free(second);
    qc_args_free(args);
}
