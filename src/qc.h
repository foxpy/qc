#ifndef __QC_H
#define __QC_H
#include "qc_irrelevant.h"

// print error message and exit with non-zero code
__QC_NORETURN void die(char const *msg);

// works just like malloc, but terminates program on OOM condition
void* emalloc(size_t size);

// works just like realloc, but terminates program on OOM condition
void* erealloc(void *ptr, size_t size);

// If condition is false, terminates program and prints
// current filename and line. Has several advantages over
// std assert: prints custom error message and does not depend
// on NDEBUG macro definition
void qc_assert(bool cond, char *err_msg);

// Use rnd_init to seed random generator, then get
// random using qc_rndNN and qc_rnd_fpNN functions.
void qc_rnd_init(qc_rnd *state);
uint8_t qc_rnd8(qc_rnd *state);
uint16_t qc_rnd16(qc_rnd *state);
uint32_t qc_rnd32(qc_rnd *state);
uint64_t qc_rnd64(qc_rnd *state);
double qc_rnd_fp64(qc_rnd *state);
float qc_rnd_fp32(qc_rnd *state);

#endif
