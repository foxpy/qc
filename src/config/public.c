#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include "qc/config.h"
#include "qc/error.h"
#include "qc/utils.h"
#include "config_impl.h"

qc_result qc_cfg_open_file(FILE* file, qc_cfg** dst, qc_err* err) {
    long initial_file_position = ftell(file);
    errno = 0;
    if (fseek(file, 0, SEEK_END) != 0) {
        qc_err_set(err, "Failed to get config file size: %s", strerror(errno));
        return QC_FAILURE;
    }
    long file_len = ftell(file);
    if (file_len <= 0) {
        qc_err_set(err, "Failed to read config from file: file is empty");
        return QC_FAILURE;
    }
    rewind(file);
    char* file_str = qc_malloc(file_len + 1);
    if (fread(file_str, sizeof(char), file_len, file) != (size_t) file_len) {
        free(file_str);
        qc_err_set(err, "Failed to read config from file: unknown error (really)");
        return QC_FAILURE;
    } else {
        file_str[file_len] = '\0';
    }
    fseek(file, initial_file_position, SEEK_SET);
    qc_result ret = qc_cfg_open_string(file_str, dst, err);
    free(file_str);
    return ret;
}

qc_result qc_cfg_open_string(char const* str, qc_cfg** dst, qc_err* err) {
    QC_UNUSED(err);
    qc_cfg* cfg = qc_cfg_new();
    cfg->len = strlen(str);
    cfg->data = qc_malloc(cfg->len);
    memcpy(cfg->data, str, cfg->len);
    *dst = cfg;
    return QC_SUCCESS;
}

void qc_cfg_close(qc_cfg* cfg) {
    assert(cfg != NULL);
    free(cfg->data);
    free(cfg);
}
