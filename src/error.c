#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "qc.h"

// classic terminal line + null terminator
#define DEFAULT_ALLOC_SIZE 81

struct qc_error {
    char* buf;
    size_t size;
    size_t start;
};

qc_err* qc_err_new() {
    qc_err* ret = emalloc(sizeof(qc_err));
    ret->buf = emalloc(DEFAULT_ALLOC_SIZE);
    ret->size = DEFAULT_ALLOC_SIZE;
    ret->buf[ret->size - 1] = '\0';
    ret->start = ret->size - 1;
    return ret;
}

void qc_err_free(qc_err* err) {
    free(err->buf);
    err->buf = NULL;
    free(err);
}

char const* qc_err_get_error(qc_err const* err) {
    return &err->buf[err->start];
}

void qc_err_set_error(qc_err* err, char const* str) {
    size_t error_size = strlen(str);
    if (error_size > err->size) {
        err->buf = erealloc(err->buf, error_size);
        err->size = error_size;
    }
    err->start = err->size - error_size - 1;
    strcpy(&err->buf[err->start], str);
}

void qc_err_append_error_front(qc_err* err, char const* str) {
    size_t error_size = strlen(str) + 2; // place for ": "
    if (error_size > err->start) {
        size_t size_difference = error_size - err->start;
        err->size += size_difference;
        char* new_err = emalloc(err->size);
        strcpy(&new_err[err->start+size_difference], &err->buf[err->start]);
        free(err->buf);
        err->buf = new_err;
        err->start += size_difference;
    }
    memcpy(&err->buf[err->start - error_size], str, error_size - 2);
    memcpy(&err->buf[err->start - 2], ": ", 2);
    err->start -= error_size;
}
