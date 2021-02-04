#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include "qc/utils.h"

void qc_reopen_stdin_stdout_binary(void) {
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
}
