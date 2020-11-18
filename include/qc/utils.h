#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>

// print error message and exit with non-zero code
#define die(err_msg)                                                      \
do {                                                                      \
    fprintf(stderr, "Fatal error: %s:%d, ", __FILE__, __LINE__);          \
    fprintf(stderr, "%s\n", err_msg);                                     \
    abort();                                                              \
} while (0)

// use this whenever you are 100% sure about unreachable code branch
// and you have to silence compiler warning
#define UNREACHABLE_CODE() die("Fatal error: execution has reached unreachable code")
// use this as a placeholder for API functions, it is
// cleaner than just returning 0 or NULL
#define UNIMPLEMENTED() die("Fatal error: call to unimplemented function")

#define UNUSED(x) ((void)(x))

// works just like malloc, but terminates program on OOM condition
void* emalloc(size_t size);
// works just like realloc, but terminates program on OOM condition
void* erealloc(void* ptr, size_t size);

// works just like sprintf, but allocates memory on one's own
char* sprintf_alloc(char const* format, ...);
char* vsprintf_alloc(char const* format, va_list ap);

// platform independent stream reopen in binary mode
// these functions would not be needed without Microsoft <3
void reopen_binary_read(FILE *stream);
void reopen_binary_write(FILE *stream);

// shortcut for the most useful case of functions above
void reopen_stdin_stdout_binary();
