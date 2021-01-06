#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "qc/args.h"
#include "qc/error.h"

#define DEFAULT_ALLOC_SIZE 4

enum {
    OPT_FLAG,
    OPT_UNSIGNED,
    OPT_SIGNED,
    OPT_DOUBLE,
    OPT_STRING,
};

struct short_flag {
    char name;
    char* hint;
    bool* dst;
};

struct long_opt {
    char* name;
    char* hint;
    int type;
    bool mandatory;
    bool provided;
    union {
        size_t unsigned_default;
        ptrdiff_t signed_default;
        double double_default;
        char* string_default;
    } default_value;
    union {
        bool* flag_ptr;
        size_t* unsigned_ptr;
        ptrdiff_t* signed_ptr;
        double* double_ptr;
        char** string_ptr;
    } dst;
};

struct qc_args {
    struct short_flag* flags;
    size_t flags_count;
    size_t flags_capacity;
    struct long_opt* opts;
    size_t opts_count;
    size_t opts_capacity;
    char* program_name;
    char* brief;
    void (*help) (void*);
    void* help_data;
    int positionals_index;
    int positionals_count;
    int extras_index;
    int extras_count;
    bool parsed;
};

void auto_help(qc_args* args);
void add_long_opt(qc_args* args, int type, char const* longname, void* default_value, void* dst, char const* hint);
bool asked_for_help(int argc, char* const* argv);
bool is_short_opt(char const* str);
bool is_long_opt(char const* str);
int match_short_opt(qc_args* args, int argn, char* const* argv, qc_err* err);
int match_long_opt(qc_args* args, int argn, char* const* argv, qc_err* err);
int parse_unsigned(char* str, size_t* dst);
int parse_signed(char* str, ptrdiff_t* dst);
int parse_double(char* str, double* dst);
int parse_string(char* str, char** dst);
void array_push_back(void** array, size_t* count, size_t* capacity, size_t size);
