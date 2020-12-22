#include <stdio.h>
#ifdef _WIN32
#   include <io.h>
#   include <fcntl.h>
#endif
#include "qc/utils.h"

void qc_reopen_binary_read(FILE *stream) {
#   ifdef _WIN32
        _setmode(_fileno(stream), _O_BINARY);
#   elif defined __ANDROID__
        QC_UNUSED(stream);
#   else
        freopen(NULL, "rb", stream);
#   endif
}

void qc_reopen_binary_write(FILE *stream) {
#   ifdef _WIN32
        _setmode(_fileno(stream), _O_BINARY);
#   elif defined __ANDROID__
        QC_UNUSED(stream);
#   else
        freopen(NULL, "wb", stream);
#   endif
}

void qc_reopen_stdin_stdout_binary(void) {
    qc_reopen_binary_read(stdin);
    qc_reopen_binary_write(stdout);
}
