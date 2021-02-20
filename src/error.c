#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "qc/error.h"
#include "qc/utils.h"
#include "qc/string.h"

static char const* delimiter = ": ";

struct qc_err {
    char* buf;
};

static void qc_err_append_front_valist(qc_err* err, char const* format, va_list ap) {
    assert(format != NULL);
    va_list args;
    va_copy(args, ap);
    char* msg;
    qc_vasprintf(&msg, format, args);
    va_end(args);
    size_t new_size = 0;
    if (err->buf != NULL) {
        new_size += strlen(err->buf);
        new_size += strlen(delimiter);
    }
    new_size += strlen(msg);
    new_size += 1;
    char* new_err_msg = qc_malloc(new_size);
    strcpy(new_err_msg, msg);
    if (err->buf != NULL) {
        strcat(new_err_msg, delimiter);
        strcat(new_err_msg, err->buf);
    }
    free(err->buf);
    free(msg);
    err->buf = new_err_msg;
}

qc_err* qc_err_new(void) {
    qc_err* ret = qc_malloc(sizeof(qc_err));
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
    if (err == NULL || err->buf == NULL) {
        return "";
    } else {
        return err->buf;
    }
}

char* qc_err_to_owned_c_str(qc_err* err) {
    if (err == NULL) {
        return "";
    } else {
        char* ret = err->buf;
        free(err);
        return ret;
    }
}

void qc_err_set(qc_err* err, char const* format, ...) {
    assert(format != NULL);
    if (err != NULL) {
        assert(format != NULL);
        va_list args;
        va_start(args, format);
        char* msg;
        qc_vasprintf(&msg, format, args);
        va_end(args);
        if (err->buf != NULL) {
            free(err->buf);
        }
        err->buf = msg;
    }
}

void qc_err_append_front(qc_err* err, char const* format, ...) {
    assert(format != NULL);
    if (err != NULL) {
        assert(format != NULL);
        va_list args;
        va_start(args, format);
        qc_err_append_front_valist(err, format, args);
        va_end(args);
    }
}

qc_noreturn void qc_err_fatal(qc_err* err, char const* format, ...) {
    assert(format != NULL);
    va_list args;
    va_start(args, format);
    qc_err_append_front_valist(err, format, args);
    va_end(args);
    fprintf(stderr, "Fatal error: %s\n", qc_err_get(err));
    exit(EXIT_FAILURE);
}
