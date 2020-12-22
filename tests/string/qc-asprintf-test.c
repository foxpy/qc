#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "qc/string.h"
#include "qc/tests.h"

static void asprintf_basic(void) {
    char const* expected = "quick brown fox has jumped over dog";
    char* formatted = NULL;
    size_t len = qc_asprintf(&formatted, "quick brown %s has jumped over %s", "fox", "dog");
    qc_assert(len == strlen(expected), "Expected length = %zu, got %zu", (size_t) strlen(expected), len);
    qc_assert(strcmp(formatted, expected) == 0, "Expected: \"%s\", got: \"%s\"", expected, formatted);
    free(formatted);
}

static void asnprintf_enough(void) {
    char const* expected = "test: 55";
    char* formatted = NULL;
    size_t len = qc_asnprintf(&formatted, 1024, "test: %s", "55");
    qc_assert(len == strlen(expected), "Expected length = %zu, got %zu", (size_t) strlen(expected), len);
    qc_assert(strcmp(formatted, expected) == 0, "Expected: \"%s\", got: \"%s\"", expected, formatted);
    free(formatted);
}

static void asnprintf_on_the_edge(void) {
    char const* expected = "test: 55";
    char* formatted = NULL;
    size_t len = qc_asnprintf(&formatted, strlen(expected) + 1, "test: %s", "55");
    qc_assert(len == strlen(expected), "Expected length = %zu, got %zu", (size_t) strlen(expected), len);
    qc_assert(strcmp(formatted, expected) == 0, "Expected: \"%s\", got: \"%s\"", expected, formatted);
    free(formatted);
}

static void asnprintf_overflow(void) {
    char const* expected = "test: 5";
    char* formatted = NULL;
    size_t constraint = strlen(expected) + 1;
    size_t len = qc_asnprintf(&formatted, constraint, "test: %s", "55");
    qc_assert(len == constraint - 1, "Expected length = %zu, got %zu", constraint - 1, len);
    qc_assert(strcmp(formatted, expected) == 0, "Expected: \"%s\", got: \"%s\"", expected, formatted);
    free(formatted);
}

int main(void) {
    asprintf_basic();
    asnprintf_enough();
    asnprintf_on_the_edge();
    asnprintf_overflow();
}
