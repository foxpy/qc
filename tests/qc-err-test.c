#include <string.h>
#include <stdlib.h>
#include "qc.h"

static char const* sample_error = "UwU I made a fucky wucky";
static char const* chain = "Some function";
static char const* chain_error = "Some function: UwU I made a fucky wucky";
static char const* big_chain = "Some extremely verbose errrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrror messsage";
static char const* big_chain_error = "Some extremely verbose errrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrror messsage: Some function: UwU I made a fucky wucky";

int main() {
    {
        qc_err *err = qc_err_new();
        qc_assert(strcmp(qc_err_get_error(err), "") == 0, "Expected empty error string");
        {
            qc_err_set_error(err, sample_error);
            char const *ret_error = qc_err_get_error(err);
            qc_assert_format(strcmp(ret_error, sample_error) == 0, "Expected \"%s\", got \"%s\"", sample_error,
                             ret_error);
        }
        {
            qc_err_append_error_front(err, chain);
            char const *ret_error = qc_err_get_error(err);
            qc_assert_format(strcmp(ret_error, chain_error) == 0, "Expected \"%s\", got \"%s\"", chain_error,
                             ret_error);
        }
        {
            qc_err_append_error_front(err, big_chain);
            char const *ret_error = qc_err_get_error(err);
            qc_assert_format(strcmp(ret_error, big_chain_error) == 0, "Expected \"%s\", got \"%s\"", big_chain_error,
                             ret_error);
        }
        qc_err_free(err);
    }
    {
        qc_err* err = qc_err_new();
        qc_err_set_error(err, sample_error);
        char* str_err = qc_err_to_owned_c_str(err);
        qc_assert_format(strcmp(str_err, sample_error) == 0, "Expected: \"%s\", got: \"%s\"", sample_error, str_err);
        free(str_err);
    }
}
