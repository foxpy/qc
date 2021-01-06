#pragma once

struct qc_cfg {
    char* data;
};

qc_cfg* qc_cfg_new();
char* eat_comments(char const input[static 1]);
