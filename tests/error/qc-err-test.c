#include <string.h>
#include <stdlib.h>
#include "qc.h"

void basic_test() {
    char const* sample_error = "UwU I made a fucky wucky";
    char const* chain = "Some function";
    char const* chain_error = "Some function: UwU I made a fucky wucky";
    char const* big_chain = "Some extremely verbose errrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrror messsage";
    char const* big_chain_error = "Some extremely verbose errrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrror messsage: Some function: UwU I made a fucky wucky";
    {
        qc_err *err = qc_err_new();
        qc_assert(strcmp(qc_err_get(err), "") == 0, "Expected empty error string");
        {
            qc_err_set(err, sample_error);
            char const *ret_error = qc_err_get(err);
            qc_assert_format(strcmp(ret_error, sample_error) == 0, "Expected \"%s\", got \"%s\"", sample_error,
                             ret_error);
        }
        {
            qc_err_append_front(err, chain);
            char const *ret_error = qc_err_get(err);
            qc_assert_format(strcmp(ret_error, chain_error) == 0, "Expected \"%s\", got \"%s\"", chain_error,
                             ret_error);
        }
        {
            qc_err_append_front(err, big_chain);
            char const *ret_error = qc_err_get(err);
            qc_assert_format(strcmp(ret_error, big_chain_error) == 0, "Expected \"%s\", got \"%s\"", big_chain_error,
                             ret_error);
        }
        qc_err_free(err);
    }
    {
        qc_err* err = qc_err_new();
        qc_err_set(err, sample_error);
        char* str_err = qc_err_to_owned_c_str(err);
        qc_assert_format(strcmp(str_err, sample_error) == 0, "Expected: \"%s\", got: \"%s\"", sample_error, str_err);
        free(str_err);
    }
}

void formatting_test() {
    qc_err* err = qc_err_new();
    {
        char const* expected_error = "Failed to open file: /path/to/file";
        qc_err_set(err, "Failed to open file: %s", "/path/to/file");
        qc_assert_format(strcmp(expected_error, qc_err_get(err)) == 0,
                         "Expected: \"%s\", got: \"%s\"", expected_error, qc_err_get(err));
    }
    {
        char const* expected_error = "Module 12: Failed to open file: /path/to/file";
        qc_err_append_front(err, "Module %d", 12);
        qc_assert_format(strcmp(expected_error, qc_err_get(err)) == 0,
                         "Expected: \"%s\", got: \"%s\"", expected_error, qc_err_get(err));
    }
    qc_err_free(err);
}

int main() {
    basic_test();
    formatting_test();
}
