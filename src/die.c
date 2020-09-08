#include <stdlib.h>
#include <stdio.h>
#include "qc.h"

noreturn void die(char const* msg) {
    fprintf(stderr, "%s\n", msg);
    abort();
}
