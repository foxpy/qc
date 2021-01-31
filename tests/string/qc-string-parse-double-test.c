#include <string.h>
#include "qc/string.h"
#include "qc/tests.h"

static void parse_double_positive(void) {
    char const* input = "567.45";
    double parsed;
    char const* tail;
    qc_assert(qc_str_to_double(input, &parsed, &tail) == QC_SUCCESS, "qc_str_to_double has failed");
    double expected = 567.45;
    qc_assert(parsed == expected, "Expected: %f, got: %f", expected, parsed);
    qc_assert(tail == &input[strlen(input)], "Tail does not point to the end of input string");
}

static void parse_double_negative(void) {
    char const* input = "-567.45";
    double parsed;
    char const* tail;
    qc_assert(qc_str_to_double(input, &parsed, &tail) == QC_SUCCESS, "qc_str_to_double has failed");
    double expected = -567.45;
    qc_assert(parsed == expected, "Expected: %f, got: %f", expected, parsed);
    qc_assert(tail == &input[strlen(input)], "Tail does not point to the end of input string");
}

static void parse_double_integral(void) {
    char const* input = "567";
    double parsed;
    char const* tail;
    qc_assert(qc_str_to_double(input, &parsed, &tail) == QC_SUCCESS, "qc_str_to_double has failed");
    double expected = 567.0;
    qc_assert(parsed == expected, "Expected: %f, got: %f", expected, parsed);
    qc_assert(tail == &input[strlen(input)], "Tail does not point to the end of input string");
}

static void parse_double_zero(void) {
    char const* input = "0";
    double parsed;
    char const* tail;
    qc_assert(qc_str_to_double(input, &parsed, &tail) == QC_SUCCESS, "qc_str_to_double has failed");
    double expected = 0.0;
    qc_assert(parsed == expected, "Expected: %f, got: %f", expected, parsed);
    qc_assert(tail == &input[strlen(input)], "Tail does not point to the end of input string");
}

static void parse_double_correct_with_garbage(void) {
    char const* input = "15.4qqw";
    double parsed;
    char const* tail;
    qc_assert(qc_str_to_double(input, &parsed, &tail) == QC_SUCCESS, "qc_str_to_double has failed");
    double expected = 15.4;
    qc_assert(parsed == expected, "Expected: %f, got: %f", expected, parsed);
    qc_assert(tail == &input[4], "Tail does not point to the end of input string");
}

static void parse_double_null_tail(void) {
    char const* input = "567.45";
    double parsed;
    qc_assert(qc_str_to_double(input, &parsed, NULL) == QC_SUCCESS, "qc_str_to_double has failed");
    double expected = 567.45;
    qc_assert(parsed == expected, "Expected: %f, got: %f", expected, parsed);
}

static void parse_double_garbage(void) {
    char const* input = "h5jd.ffe4+2";
    double parsed;
    qc_assert(qc_str_to_double(input, &parsed, NULL) == QC_FAILURE, "qc_str_to_double is expected to fail");
}

int main(void) {
    parse_double_positive();
    parse_double_negative();
    parse_double_integral();
    parse_double_zero();
    parse_double_correct_with_garbage();
    parse_double_null_tail();
    parse_double_garbage();
}
