#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "qc.h"

static char const* delimiter = ": ";

struct qc_error {
    char* buf;
};

qc_err* qc_err_new() {
    qc_err* ret = emalloc(sizeof(qc_err));
    ret->buf = NULL;
    return ret;
}

void qc_err_free(qc_err* err) {
    assert(err != NULL);
    if (err->buf != NULL) {
        free(err->buf);
    }
    free(err);
}

char const* qc_err_get_error(qc_err const* err) {
    assert(err != NULL);
    if (err->buf == NULL) {
        return "";
    } else {
        return err->buf;
    }
}

char* qc_err_to_owned_c_str(qc_err* err) {
    assert(err != NULL);
    char* ret = err->buf;
    free(err);
    return ret;
}

void qc_err_set_error(qc_err* err, char const* str) {
    assert(err != NULL);
    assert(str != NULL);
    if (err->buf != NULL) {
        free(err->buf);
    }
    size_t error_size = strlen(str);
    err->buf = emalloc(error_size + 1);
    strcpy(err->buf, str);
}

void qc_err_append_error_front(qc_err* err, char const* str) {
    assert(err != NULL);
    assert(str != NULL);
    size_t new_size = 0;
    if (err->buf != NULL) {
        new_size += strlen(err->buf);
        new_size += strlen(delimiter);
    }
    new_size += strlen(str);
    new_size += 1;
    char* new_err_msg = emalloc(new_size);
    strcpy(new_err_msg, str);
    if (err->buf != NULL) {
        strcat(new_err_msg, delimiter);
        strcat(new_err_msg, err->buf);
    }
    free(err->buf);
    err->buf = new_err_msg;
}
