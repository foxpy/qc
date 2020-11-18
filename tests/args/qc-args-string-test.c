#include <string.h>
#include "qc.h"

int main() {
    char* first_name = NULL;
    char* last_name = NULL;
    qc_args* args = qc_args_new();
    qc_err* err = qc_err_new();
    qc_args_string(args, "first-name", &first_name, NULL);
    qc_args_string(args, "last-name", &last_name, NULL);

    qc_result result = qc_args_parse(args, 3, (char*[]){
        "/path/to/exe", "--first-name=Nicholas",
        "--last-name=\"Unless-Jesus-Christ-Had-Died\"", NULL
    }, err);
    qc_assert(result == QC_SUCCESS, sprintf_alloc("qc_args_parse has failed: %s", err));
    qc_assert(strcmp(first_name, "Nicholas") == 0, "--key=value syntax does not work");
    qc_assert(strcmp(last_name, "Unless-Jesus-Christ-Had-Died") == 0,
              "--key=\"v a l u e\" syntax does not work");
    free(first_name);
    free(last_name);
    qc_err_free(err);
    qc_args_free(args);
}
