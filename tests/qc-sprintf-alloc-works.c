#include "qc.h"
#include <string.h>
#include <stdlib.h>

int main() {
    char const* target_str = "The quick brown fox jumps over the lazy dog";
    char* str;
    str = sprintf_alloc(10, "The quick brown %s jumps over the lazy %s", "fox", "dog");
    qc_assert(strcmp(target_str, str) == 0, "sprintf_alloc does not allocate new buffer well");
    free(str);
    str = sprintf_alloc(30, "The quick brown %s jumps over the lazy %s", "fox", "dog");
    qc_assert(strcmp(target_str, str) == 0, "sprintf_alloc does not allocate new buffer well");
    free(str);
    str = sprintf_alloc(256, "The quick brown %s jumps over the lazy %s", "fox", "dog");
    qc_assert(strcmp(target_str, str) == 0, "sprintf_alloc does not allocate new buffer well");
    free(str);
}
