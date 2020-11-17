#pragma once

// Error handling abstraction
// Makes error handling much easier
typedef struct qc_error qc_err;
qc_err* qc_err_new();
void qc_err_free(qc_err* err);
char const* qc_err_get_error(qc_err const* err);
char* qc_err_to_owned_c_str(qc_err* err);
void qc_err_set_error(qc_err* err, char const* str);
void qc_err_append_error_front(qc_err* err, char const* str);
