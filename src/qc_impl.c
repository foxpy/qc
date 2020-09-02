#include "qc.h"
#include "qc_impl.h"

void array_push_back(void** array, size_t* count, size_t* capacity, size_t size) {
    *count += 1;
    if (*count == *capacity) {
        *capacity *= 2;
        *array = erealloc(*array, *capacity * size);
    }
}
