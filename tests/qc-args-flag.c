#include "qc.h"

void test_flag_short() {
    bool verbose;
    char* err;
    qc_args* args = qc_args_new();
    qc_args_flag(args, 'v', "verbose", &verbose, NULL);
    int ret = qc_args_parse(args, 2, (char*[]){"/path/to/exe", "-v", NULL}, &err);
    qc_assert(ret == 0, "qc_args_parse has failed");
    qc_assert(verbose == true, "expected: true");
    qc_args_free(args);
}

void test_flag_short_multiple() {
    bool a, b, c;
    char* err;
    qc_args* args = qc_args_new();
    qc_args_flag(args, 'a', "flag-a", &a, NULL);
    qc_args_flag(args, 'b', "flag-b", &b, NULL);
    qc_args_flag(args, 'c', "flag-c", &c, NULL);
    int ret = qc_args_parse(args, 3, (char*[]){"/path/to/exe", "-ab", "-c", NULL}, &err);
    qc_assert(ret == 0, "qc_args_parse has failed");
    qc_assert(a && b && c, "expected: all true");
    qc_args_free(args);
}

void test_flag_long() {
    bool verbose;
    char* err;
    qc_args* args = qc_args_new();
    qc_args_flag(args, 'v', "verbose", &verbose, NULL);
    int ret = qc_args_parse(args, 2, (char*[]){"/path/to/exe", "--verbose", NULL}, &err);
    qc_assert(ret == 0, "qc_args_parse has failed");
    qc_assert(verbose == true, "expected: true");
    qc_args_free(args);
}

void test_flag_none() {
    bool verbose;
    char* err;
    qc_args* args = qc_args_new();
    qc_args_flag(args, 'v', "verbose", &verbose, NULL);
    int ret = qc_args_parse(args, 1, (char*[]){"/path/to/exe", NULL}, &err);
    qc_assert(ret == 0, "qc_args_parse has failed");
    qc_assert(verbose == false, "expected: false");
    qc_args_free(args);
}

int main() {
    test_flag_short();
    test_flag_short_multiple();
    test_flag_long();
    test_flag_none();
}
