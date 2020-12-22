#include <stdbool.h>
#include "qc/args.h"
#include "qc/error.h"
#include "qc/tests.h"

void test_flag_short(qc_err* err) {
    bool verbose;
    qc_args* args = qc_args_new();
    qc_args_flag(args, 'v', "verbose", &verbose, NULL);
    qc_result result = qc_args_parse(args, 2, (char*[]){"/path/to/exe", "-v", NULL}, err);
    qc_assert(result == QC_SUCCESS, "qc_args_parse has failed: %s", qc_err_to_owned_c_str(err));
    qc_assert(verbose == true, "expected: true");
    qc_args_free(args);
}

void test_flag_short_multiple(qc_err* err) {
    bool a, b, c;
    qc_args* args = qc_args_new();
    qc_args_flag(args, 'a', "flag-a", &a, NULL);
    qc_args_flag(args, 'b', "flag-b", &b, NULL);
    qc_args_flag(args, 'c', "flag-c", &c, NULL);
    qc_result result = qc_args_parse(args, 3, (char*[]){"/path/to/exe", "-ab", "-c", NULL}, err);
    qc_assert(result == QC_SUCCESS, "qc_args_parse has failed: %s", qc_err_to_owned_c_str(err));
    qc_assert(a && b && c, "expected: all true");
    qc_args_free(args);
}

void test_flag_long(qc_err* err) {
    bool verbose;
    qc_args* args = qc_args_new();
    qc_args_flag(args, 'v', "verbose", &verbose, NULL);
    qc_result result = qc_args_parse(args, 2, (char*[]){"/path/to/exe", "--verbose", NULL}, err);
    qc_assert(result == QC_SUCCESS, "qc_args_parse has failed: %s", qc_err_to_owned_c_str(err));
    qc_assert(verbose == true, "expected: true");
    qc_args_free(args);
}

void test_flag_none(qc_err* err) {
    bool verbose;
    qc_args* args = qc_args_new();
    qc_args_flag(args, 'v', "verbose", &verbose, NULL);
    qc_result result = qc_args_parse(args, 1, (char*[]){"/path/to/exe", NULL}, err);
    qc_assert(result == QC_SUCCESS, "qc_args_parse has failed: %s", qc_err_to_owned_c_str(err));
    qc_assert(verbose == false, "expected: false");
    qc_args_free(args);
}

int main(void) {
    qc_err* err = qc_err_new();
    test_flag_short(err);
    test_flag_short_multiple(err);
    test_flag_long(err);
    test_flag_none(err);
    qc_err_free(err);
}
