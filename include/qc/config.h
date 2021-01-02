#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "qc/error.h"

typedef struct qc_cfg qc_cfg;
qc_result qc_cfg_open_file(FILE* file, qc_cfg** dst, qc_err* err);
qc_result qc_cfg_open_string(char const* str, qc_cfg** dst, qc_err* err);
void qc_cfg_close(qc_cfg* cfg);

typedef struct qc_cfg_section qc_cfg_section;
qc_result qc_cfg_get_section(qc_cfg* cfg, char const* name, qc_cfg_section** dst, qc_err* err);
void qc_cfg_close_section(qc_cfg_section* section);

qc_result qc_cfg_boolean(qc_cfg_section* section, char const* name, bool* dst, qc_err* err);
qc_result qc_cfg_unsigned(qc_cfg_section* section, char const* name, size_t* dst, qc_err* err);
qc_result qc_cfg_signed(qc_cfg_section* section, char const* name, ptrdiff_t* dst, qc_err* err);
qc_result qc_cfg_double(qc_cfg_section* section, char const* name, double* dst, qc_err* err);
qc_result qc_cfg_string(qc_cfg_section* section, char const* name, char** dst, qc_err* err);

typedef struct qc_cfg_array qc_cfg_array;
qc_result qc_cfg_get_array(qc_cfg_section* section, char const* name, qc_cfg_array** dst, qc_err* err);
void qc_cfg_close_array(qc_cfg_array* array);

size_t qc_cfg_array_length(qc_cfg_array* array);
qc_result qc_cfg_array_boolean(qc_cfg_array* array, size_t index, bool* dst, qc_err* err);
qc_result qc_cfg_array_unsigned(qc_cfg_array* array, size_t index, size_t* dst, qc_err* err);
qc_result qc_cfg_array_signed(qc_cfg_array* array, size_t index, ptrdiff_t* dst, qc_err* err);
qc_result qc_cfg_array_double(qc_cfg_array* array, size_t index, double* dst, qc_err* err);
qc_result qc_cfg_array_string(qc_cfg_array* array, size_t index, char** dst, qc_err* err);
