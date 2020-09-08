#pragma once
#include "qc_irrelevant.h"

// print error message and exit with non-zero code
noreturn void die(char const* msg);
// use this whenever you are 100% sure about unreachable code branch
// and you have to silence compiler warning
#define UNREACHABLE_CODE() die("Fatal error: execution has reached unreachable code")

// works just like malloc, but terminates program on OOM condition
void* emalloc(size_t size);
// works just like realloc, but terminates program on OOM condition
void* erealloc(void* ptr, size_t size);

// works just like sprintf, but allocates memory on one's own,
// and if size_hint is not enough, allocates more memory to fit output string in
char* sprintf_alloc(char const* format, ...);

// If condition is false, terminates program and prints
// current filename and line. Has several advantages over
// std assert: prints custom error message and does not depend
// on NDEBUG macro definition
#define qc_assert(cond, err_msg) __qc_assert(cond, err_msg)

// Use rnd_init to seed random generator, then get
// random using qc_rnd64 and qc_rnd_fp64 functions.
// qc_rnd_init returns nonzero (true) on success and zero (false) on failure
int qc_rnd_init(qc_rnd* state);
void qc_rnd_seed(qc_rnd* state, uint64_t seed);
uint64_t qc_rnd64(qc_rnd* state);
double qc_rnd_fp64(qc_rnd* state);

// these functions return random in specified range if you need so
int64_t qc_rnd_range64(qc_rnd* state, int64_t low, int64_t high);
double qc_rnd_range_fp64(qc_rnd* state, double low, double high);

// Argument parsing library, inspired by Golang's `flag` package
typedef struct qc_args qc_args;
qc_args* qc_args_new();
void qc_args_free(qc_args* args);
void qc_args_set_help(qc_args* args, void (*help) (void* help_data), void* help_data);
void qc_args_brief(qc_args* args, char const* brief);
noreturn void qc_args_call_help(qc_args* args);
int qc_args_parse(qc_args* args, int argc, char* const* argv, char** err);
int qc_args_positionals_index(qc_args* args);
int qc_args_positionals_count(qc_args* args);
int qc_args_extras_index(qc_args* args);
int qc_args_extras_count(qc_args* args);

void qc_args_flag(qc_args* args, char shortname, char const* longname, bool* dst, char const* hint);
void qc_args_unsigned(qc_args* args, char const* longname, size_t* dst, char const* hint);
void qc_args_unsigned_default(qc_args* args, char const* longname, size_t default_value, size_t* dst, char const* hint);
void qc_args_signed(qc_args* args, char const* longname, ptrdiff_t* dst, char const* hint);
void qc_args_signed_default(qc_args* args, char const* longname, ptrdiff_t default_value, ptrdiff_t* dst, char const* hint);
void qc_args_double(qc_args* args, char const* longname, double* dst, char const* hint);
void qc_args_double_default(qc_args* args, char const* longname, double default_value, double* dst, char const* hint);
// dst string should be freed to prevent memory leaks
void qc_args_string(qc_args* args, char const* longname, char** dst, char const* hint);
void qc_args_string_default(qc_args* args, char const* longname, char* default_value, char** dst, char const* hint);

// Classic macros, type generic
#define MIN(a, b) __qc_min(a, b)
#define MAX(a, b) __qc_max(a, b)
// Greatest Common Divisor, a and b should be different from zero
size_t gcd(size_t a, size_t b);
// Least Common Multiple, a and b should be different from zero
size_t lcm(size_t a, size_t b);

// platform independent stream reopen in binary mode
// these functions would not be needed without Microsoft <3
void reopen_binary_read(FILE *stream);
void reopen_binary_write(FILE *stream);

// shortcut for the most useful case of functions above
void reopen_stdin_stdout_binary();
