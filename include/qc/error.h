#pragma once
#include "qc/noreturn.h"

// Error handling abstraction
// Makes error handling much easier
typedef enum qc_result
{
    QC_SUCCESS = 1,
    QC_FAILURE = 0,
} qc_result;
typedef struct qc_err qc_err;

qc_err* qc_err_new(void);
void qc_err_free(qc_err* err);
char const* qc_err_get(qc_err const* err);
char* qc_err_to_owned_c_str(qc_err* err);
void qc_err_set(qc_err* err, char const* format, ...);
void qc_err_append_front(qc_err* err, char const* format, ...);
qc_noreturn void qc_err_fatal(qc_err* err, char const* format, ...);
