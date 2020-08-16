#include <stdlib.h>
#include <stdio.h>
#include "qc.h"

__QC_NORETURN void die(char const *msg) {
    fprintf(stderr, "%s\n", msg);
    abort();
}
