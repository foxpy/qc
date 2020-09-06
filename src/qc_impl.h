#pragma once
#include <stddef.h>

#define DEFAULT_ALLOC_SIZE 4
void array_push_back(void** array, size_t* count, size_t* capacity, size_t size);
