#include <stdio.h>
#include "qc/utils.h"

#ifdef _WIN32
#    include "reopen-binary/reopen-binary_windows.c"
#else
#    include "reopen-binary/reopen-binary_posix.c"
#endif

void qc_reopen_stdin_stdout_binary(void) {
    qc_reopen_binary_read(stdin);
    qc_reopen_binary_write(stdout);
}
