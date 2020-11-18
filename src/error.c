#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "qc.h"

static char const* delimiter = ": ";

struct qc_err {
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

char const* qc_err_get(qc_err const* err) {
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

void qc_err_set(qc_err* err, char const* str, ...) {
    assert(err != NULL);
    assert(str != NULL);
    va_list args;
    va_start(args, str);
    char* msg = vsprintf_alloc(str, args);
    va_end(args);
    if (err->buf != NULL) {
        free(err->buf);
    }
    err->buf = msg;
}

void qc_err_append_front(qc_err* err, char const* str, ...) {
    assert(err != NULL);
    assert(str != NULL);
    va_list args;
    va_start(args, str);
    char* msg = vsprintf_alloc(str, args);
    va_end(args);
    size_t new_size = 0;
    if (err->buf != NULL) {
        new_size += strlen(err->buf);
        new_size += strlen(delimiter);
    }
    new_size += strlen(msg);
    new_size += 1;
    char* new_err_msg = emalloc(new_size);
    strcpy(new_err_msg, msg);
    if (err->buf != NULL) {
        strcat(new_err_msg, delimiter);
        strcat(new_err_msg, err->buf);
    }
    free(err->buf);
    free(msg);
    err->buf = new_err_msg;
}
