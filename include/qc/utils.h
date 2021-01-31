#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "qc/noreturn.h"

// print error message and exit with non-zero code
qc_noreturn void qc_die_impl(char const* fmt, ...);
#define QC_DIE_IMPL(fmt, ...) qc_die_impl("Fatal error:\n  %s:%d\n  " fmt "%c", __FILE__, __LINE__, __VA_ARGS__)
#define qc_die(...) QC_DIE_IMPL(__VA_ARGS__, '\n')

// use this whenever you are 100% sure about unreachable code branch
// and you have to silence compiler warning
#define QC_UNREACHABLE_CODE() qc_die("Execution has reached unreachable code")
// use this as a placeholder for API functions, it is
// cleaner than just returning 0 or NULL
#define QC_UNIMPLEMENTED() qc_die("Call to unimplemented function")
#define QC_UNUSED(x) ((void) (x))

// works just like malloc, but terminates program on OOM condition
void* qc_malloc(size_t size);
// works just like realloc, but terminates program on OOM condition
void* qc_realloc(void* ptr, size_t size);

// platform independent stream reopen in binary mode
// these functions would not be needed without Microsoft <3
void qc_reopen_binary_read(FILE* stream);
void qc_reopen_binary_write(FILE* stream);
// shortcut for the most useful case of functions above
void qc_reopen_stdin_stdout_binary(void);
