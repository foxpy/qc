#include <stdio.h>
#ifdef _WIN32
#	include <io.h>
#	include <fcntl.h>
#endif
#include "qc.h"

void reopen_binary_read(FILE *stream) {
#	ifdef _WIN32
        _setmode(_fileno(stream), _O_BINARY);
#	elif defined __ANDROID_API__
        (void)stream; // suppress warning
#	else
        freopen(NULL, "rb", stream);
#	endif
}

void reopen_binary_write(FILE *stream) {
#	ifdef _WIN32
        _setmode(_fileno(stream), _O_BINARY);
#	elif defined __ANDROID_API__
        (void)stream; // suppress warning
#	else
        freopen(NULL, "wb", stream);
#	endif
}

void reopen_stdin_stdout_binary() {
    reopen_binary_read(stdin);
    reopen_binary_write(stdout);
}
