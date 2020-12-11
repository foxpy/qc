#include <string.h>
#include <stddef.h>
#include "qc.h"

static void asprintf_basic() {
    char const* expected = "quick brown fox has jumped over dog";
    char* formatted = NULL;
    size_t len = qc_asprintf(&formatted, "quick brown %s has jumped over %s", "fox", "dog");
    qc_assert_format(len == strlen(expected), "Expected length = %zu, got %zu", (size_t) strlen(expected), len);
    qc_assert_format(strcmp(formatted, expected) == 0, "Expected: \"%s\", got: \"%s\"", expected, formatted);
    free(formatted);
}

static void asnprintf_enough() {
    char const* expected = "test: 55";
    char* formatted = NULL;
    size_t len = qc_asnprintf(&formatted, 1024, "test: %s", "55");
    qc_assert_format(len == strlen(expected), "Expected length = %zu, got %zu", (size_t) strlen(expected), len);
    qc_assert_format(strcmp(formatted, expected) == 0, "Expected: \"%s\", got: \"%s\"", expected, formatted);
    free(formatted);
}

static void asnprintf_on_the_edge() {
    char const* expected = "test: 55";
    char* formatted = NULL;
    size_t len = qc_asnprintf(&formatted, strlen(expected) + 1, "test: %s", "55");
    qc_assert_format(len == strlen(expected), "Expected length = %zu, got %zu", (size_t) strlen(expected), len);
    qc_assert_format(strcmp(formatted, expected) == 0, "Expected: \"%s\", got: \"%s\"", expected, formatted);
    free(formatted);
}

static void asnprintf_overflow() {
    char const* expected = "test: 5";
    char* formatted = NULL;
    size_t constraint = strlen(expected) + 1;
    size_t len = qc_asnprintf(&formatted, constraint, "test: %s", "55");
    qc_assert_format(len == constraint - 1, "Expected length = %zu, got %zu", constraint - 1, len);
    qc_assert_format(strcmp(formatted, expected) == 0, "Expected: \"%s\", got: \"%s\"", expected, formatted);
    free(formatted);
}

int main() {
    asprintf_basic();
    asnprintf_enough();
    asnprintf_on_the_edge();
    asnprintf_overflow();
}