#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "qc/noreturn.h"

// print error message and exit with non-zero code
qc_noreturn void qc_die_impl(char const* file, size_t line, char const* err_msg);
#define qc_die(err_msg) qc_die_impl(__FILE__, __LINE__, err_msg)

// use this whenever you are 100% sure about unreachable code branch
// and you have to silence compiler warning
#define QC_UNREACHABLE_CODE() qc_die("Fatal error: execution has reached unreachable code")
// use this as a placeholder for API functions, it is
// cleaner than just returning 0 or NULL
#define QC_UNIMPLEMENTED() qc_die("Fatal error: call to unimplemented function")
#define QC_UNUSED(x) ((void)(x))

// works just like malloc, but terminates program on OOM condition
void* qc_malloc(size_t size);
// works just like realloc, but terminates program on OOM condition
void* qc_realloc(void* ptr, size_t size);

// platform independent stream reopen in binary mode
// these functions would not be needed without Microsoft <3
void qc_reopen_binary_read(FILE *stream);
void qc_reopen_binary_write(FILE *stream);
// shortcut for the most useful case of functions above
void qc_reopen_stdin_stdout_binary(void);
