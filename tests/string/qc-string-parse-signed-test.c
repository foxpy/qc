#include <stddef.h>
#include <string.h>
#include "qc/string.h"
#include "qc/tests.h"

static void parse_unsigned_correct(void) {
    char const* input = "567";
    ptrdiff_t parsed;
    char const* tail;
    qc_assert(qc_str_to_signed(input, &parsed, &tail) == QC_SUCCESS,
              "qc_str_to_signed has failed");
    ptrdiff_t expected = 567;
    qc_assert(parsed == expected, "Expected: %td, got: %td", expected, parsed);
    qc_assert(tail == &input[strlen(input)], "Tail does not point to the end of input string");
}

static void parse_signed_correct(void) {
    char const* input = "-567";
    ptrdiff_t parsed;
    char const* tail;
    qc_assert(qc_str_to_signed(input, &parsed, &tail) == QC_SUCCESS,
              "qc_str_to_signed has failed");
    ptrdiff_t expected = -567;
    qc_assert(parsed == expected, "Expected: %td, got: %td", expected, parsed);
    qc_assert(tail == &input[strlen(input)], "Tail does not point to the end of input string");
}

static void parse_signed_zero(void) {
    char const* input = "000";
    ptrdiff_t parsed;
    char const* tail;
    qc_assert(qc_str_to_signed(input, &parsed, &tail) == QC_SUCCESS,
              "qc_str_to_signed has failed");
    ptrdiff_t expected = 0;
    qc_assert(parsed == expected, "Expected: %td, got: %td", expected, parsed);
    qc_assert(tail == &input[strlen(input)], "Tail does not point to the end of input string");
}

static void parse_signed_ignore_null_tail(void) {
    char const* input = "567";
    ptrdiff_t parsed;
    qc_assert(qc_str_to_signed(input, &parsed, NULL) == QC_SUCCESS,
              "qc_str_to_signed has failed");
    ptrdiff_t expected = 567;
    qc_assert(parsed == expected, "Expected: %td, got: %td", expected, parsed);
}

static void parse_signed_garbage(void) {
    char const* input = "abc-56dddf";
    ptrdiff_t parsed;
    qc_assert(qc_str_to_signed(input, &parsed, NULL) == QC_FAILURE,
              "qc_str_to_signed is expected to fail");
}

int main(void) {
    parse_unsigned_correct();
    parse_signed_correct();
    parse_signed_zero();
    parse_signed_ignore_null_tail();
    parse_signed_garbage();
}
