#include "qc.h"
#include <string.h>
#include <stdlib.h>

void test1() {
    char const* target_str = "The quick brown fox jumps over the lazy dog";
    char* str = sprintf_alloc("The quick brown %s jumps over the lazy %s", "fox", "dog");
    qc_assert(strcmp(target_str, str) == 0, "sprintf_alloc does not allocate new buffer well");
    free(str);
}

void test2() {
    char const* target_str = "10 + 20 = 30";
    char* str = sprintf_alloc("%d + %d = %d", 10, 20, 30);
    qc_assert(strcmp(target_str, str) == 0, "sprintf_alloc does not allocate new buffer well");
    free(str);
}

int main() {
    test1();
    test2();
}
