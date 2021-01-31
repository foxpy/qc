#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "qc/string.h"
#include "qc/tests.h"

static void check_empty(void) {
    uint8_t* output;
    qc_assert(qc_hexstr_to_bytes("", &output) == 0, "qc_hexstr_to_bytes fails on empty input");
    qc_assert(output == NULL, "qc_hexstr_to_bytes is expected to zero output on empty input");
}

static void check_valid(char const* input, size_t len, uint8_t expectation[static len]) {
    uint8_t* output;
    qc_assert(qc_hexstr_to_bytes(input, &output) == (ptrdiff_t) len,
              "qc_hexstr_to_bytes has failed on valid input: \"%s\"", input);
    qc_assert(memcmp(output, expectation, len) == 0, "qc_hexstr_to_bytes has parsed \"%s\" input incorrectly", input);
    free(output);
}

static void reject_garbage(char const* input) {
    uint8_t* output;
    qc_assert(qc_hexstr_to_bytes(input, &output) == -1, "qc_hexstr_to_bytes has somehow accepted invalid input: \"%s\"",
              input);
    qc_assert(output == NULL, "qc_hexstr_to_bytes is expected to zero output on garbage input");
}

int main(void) {
    check_empty();
    check_valid("0xa", 1, (uint8_t[]){0x0a});
    check_valid("0x0a", 1, (uint8_t[]){0x0a});
    check_valid("0x20a", 2, (uint8_t[]){0x02, 0x0a});
    check_valid("0x020a", 2, (uint8_t[]){0x02, 0x0a});
    check_valid("0x120a", 2, (uint8_t[]){0x12, 0x0a});
    check_valid("a", 1, (uint8_t[]){0x0a});
    check_valid("0a", 1, (uint8_t[]){0x0a});
    check_valid("20a", 2, (uint8_t[]){0x02, 0x0a});
    check_valid("020a", 2, (uint8_t[]){0x02, 0x0a});
    check_valid("120a", 2, (uint8_t[]){0x12, 0x0a});
    check_valid("0xA", 1, (uint8_t[]){0x0a});
    check_valid("0x0A", 1, (uint8_t[]){0x0a});
    check_valid("0x20A", 2, (uint8_t[]){0x02, 0x0a});
    check_valid("0x020A", 2, (uint8_t[]){0x02, 0x0a});
    check_valid("0x120A", 2, (uint8_t[]){0x12, 0x0a});
    check_valid("A", 1, (uint8_t[]){0x0a});
    check_valid("0A", 1, (uint8_t[]){0x0a});
    check_valid("20A", 2, (uint8_t[]){0x02, 0x0a});
    check_valid("020A", 2, (uint8_t[]){0x02, 0x0a});
    check_valid("120A", 2, (uint8_t[]){0x12, 0x0a});
    reject_garbage("0xabcdefg");
    reject_garbage("abcdefg");
    reject_garbage("0xABCDEFG");
    reject_garbage("ABCDEFG");
    reject_garbage("50_12");
    reject_garbage("@&%$(]");
}
