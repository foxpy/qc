#ifndef __QC_H
#define __QC_H
#include "qc_irrelevant.h"

__QC_NORETURN void die(char const *msg);
void* emalloc(size_t size);
void* erealloc(void *ptr, size_t size);

#endif
