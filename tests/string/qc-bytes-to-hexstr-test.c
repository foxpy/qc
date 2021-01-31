#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "qc/string.h"
#include "qc/tests.h"

static void check(size_t len, uint8_t input[static len], char const* uppercase_expectation,
                  char const* lowercase_expectation) {
    char* output;
    qc_bytes_to_hexstr(true, len, input, &output);
    qc_assert(strcmp(output, uppercase_expectation) == 0, "Expected: \"%s\", got: \"%s\"", uppercase_expectation,
              output);
    free(output);
    qc_bytes_to_hexstr(false, len, input, &output);
    qc_assert(strcmp(output, lowercase_expectation) == 0, "Expected: \"%s\", got: \"%s\"", lowercase_expectation,
              output);
    free(output);
}

int main(void) {
    check(1, (uint8_t[]){0x00}, "0x00", "0x00");
    check(1, (uint8_t[]){0x1F}, "0x1F", "0x1f");
    check(2, (uint8_t[]){0xA2, 0x4C}, "0xA24C", "0xa24c");
}
