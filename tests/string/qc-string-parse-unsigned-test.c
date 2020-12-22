#include <stddef.h>
#include <string.h>
#include "qc/string.h"
#include "qc/tests.h"

static void parse_unsigned_correct(void) {
    char const* input = "567";
    size_t parsed;
    char const* tail;
    qc_assert(qc_str_to_unsigned(input, &parsed, &tail) == QC_SUCCESS,
              "qc_str_to_unsigned has failed");
    size_t expected = 567;
    qc_assert(parsed == expected, "Expected: %zu, got: %zu", expected, parsed);
    qc_assert(tail == &input[strlen(input)], "Tail does not point to the end of input string");
}

static void parse_unsigned_correct_with_garbage(void) {
    char const* input = "567af";
    size_t parsed;
    char const* tail;
    qc_assert(qc_str_to_unsigned(input, &parsed, &tail) == QC_SUCCESS,
              "qc_str_to_unsigned has failed");
    size_t expected = 567;
    qc_assert(parsed == expected, "Expected: %zu, got: %zu", expected, parsed);
    qc_assert(tail == &input[3], "Tail does not point to the end of input string");
}

static void parse_unsigned_zero(void) {
    char const* input = "000";
    size_t parsed;
    char const* tail;
    qc_assert(qc_str_to_unsigned(input, &parsed, &tail) == QC_SUCCESS,
              "qc_str_to_unsigned has failed");
    size_t expected = 0;
    qc_assert(parsed == expected, "Expected: %zu, got: %zu", expected, parsed);
    qc_assert(tail == &input[strlen(input)], "Tail does not point to the end of input string");
}

static void parse_unsigned_ignore_null_tail(void) {
    char const* input = "567";
    size_t parsed;
    qc_assert(qc_str_to_unsigned(input, &parsed, NULL) == QC_SUCCESS,
              "qc_str_to_unsigned has failed");
    size_t expected = 567;
    qc_assert(parsed == expected, "Expected: %zu, got: %zu", expected, parsed);
}

static void parse_unsigned_negative_sign(void) {
    char const* input = "-512";
    size_t parsed;
    qc_assert(qc_str_to_unsigned(input, &parsed, NULL) == QC_FAILURE,
              "qc_str_to_unsigned is expected to fail");
}

static void parse_unsigned_garbage(void) {
    char const* input = "abc56dddf";
    size_t parsed;
    qc_assert(qc_str_to_unsigned(input, &parsed, NULL) == QC_FAILURE,
              "qc_str_to_unsigned is expected to fail");
}

int main(void) {
    parse_unsigned_correct();
    parse_unsigned_correct_with_garbage();
    parse_unsigned_zero();
    parse_unsigned_ignore_null_tail();
    parse_unsigned_negative_sign();
    parse_unsigned_garbage();
}
