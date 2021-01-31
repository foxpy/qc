#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include "qc/utils.h"

void qc_reopen_binary_read(FILE* stream) {
    _setmode(_fileno(stream), _O_BINARY);
}

void qc_reopen_binary_write(FILE* stream) {
    _setmode(_fileno(stream), _O_BINARY);
}
