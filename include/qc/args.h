#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "error.h"

// Argument parsing library, inspired by Golang's `flag` package
typedef struct qc_args qc_args;
qc_args* qc_args_new(void);
void qc_args_free(qc_args* args);

void qc_args_set_help(qc_args* args, void (*help) (void* help_data), void* help_data);
void qc_args_set_brief(qc_args* args, char const* brief);
void qc_args_call_help(qc_args* args);
qc_result qc_args_parse(qc_args* args, int argc, char* const* argv, qc_err* err);
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
void qc_args_string(qc_args* args, char const* longname, char const** dst, char const* hint);
void qc_args_string_default(qc_args* args, char const* longname, char* default_value, char const** dst, char const* hint);
