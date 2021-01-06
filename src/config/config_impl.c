#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "qc/utils.h"
#include "qc/config.h"
#include "config_impl.h"

qc_cfg* qc_cfg_new() {
    qc_cfg* ret = qc_malloc(sizeof(qc_cfg));
    ret->data = NULL;
    return ret;
}

char* eat_comments(char const input[static 1]) {
    size_t input_len = strlen(input);
    char* ret = qc_malloc(input_len + 1);
    size_t ret_fill = 0;
    bool in_comment = false;
    for (size_t i = 0; i < input_len; ++i) {
        if (in_comment) {
            if (input[i] == '\n') {
                in_comment = false;
            }
        } else {
            if (input[i] == '#') {
                in_comment = true;
            } else {
                ret[ret_fill] = input[i];
                ++ret_fill;
            }
        }
    }
    ret[ret_fill] = '\0';
    ret = qc_realloc(ret, ret_fill + 1);
    return ret;
}
