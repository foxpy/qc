#include <stdio.h>
#include "qc.h"

void qc_assert(bool cond, char *err_msg) {
    if (!cond) {
        fprintf(stderr, "%s:%d", __FILE__, __LINE__);
        die(err_msg);
    }
}
