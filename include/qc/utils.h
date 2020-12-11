#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>

// print error message and exit with non-zero code
#define qc_die(err_msg)                                                   \
do {                                                                      \
    fprintf(stderr, "Fatal error: %s:%d, ", __FILE__, __LINE__);          \
    fprintf(stderr, "%s\n", err_msg);                                     \
    abort();                                                              \
} while (0)

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

// these functions act like [v]asprintf from GNU C standard library,
// they allocate memory automatically
// qc_[v]asnprintf functions accept a maximum allocation size limit
ptrdiff_t qc_asprintf(char** dst, char const* format, ...);
ptrdiff_t qc_asnprintf(char** dst, size_t mlimit, char const* format, ...);
ptrdiff_t qc_vasprintf(char** dst, char const* format, va_list ap);
ptrdiff_t qc_vasnprintf(char** dst, size_t mlimit, char const* format, va_list ap);

// platform independent stream reopen in binary mode
// these functions would not be needed without Microsoft <3
void qc_reopen_binary_read(FILE *stream);
void qc_reopen_binary_write(FILE *stream);
// shortcut for the most useful case of functions above
void qc_reopen_stdin_stdout_binary();
