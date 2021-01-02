#pragma once

struct qc_cfg {
    size_t len;
    char* data;
};

qc_cfg* qc_cfg_new();
void qc_cfg_free(qc_cfg* cfg);
