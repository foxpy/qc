#include <stdlib.h>
#include <stdio.h>
#include "qc.h"

#define BUFFER_SIZE 8096

int main(void) {
    qc_reopen_stdin_stdout_binary();
    qc_err* err = qc_err_new();
    uint64_t buf[BUFFER_SIZE];
    qc_rnd rnd;
    if (qc_rnd_init(&rnd, err) == QC_FAILURE) {
        fprintf(stderr, "Failed to seed random generator: %s", qc_err_get(err));
        exit(EXIT_FAILURE);
    }
    while (true) {
        for (size_t i = 0; i < BUFFER_SIZE; ++i) {
            buf[i] = qc_rnd64(&rnd);
        }
        if (fwrite(buf, sizeof(uint64_t), BUFFER_SIZE, stdout) != BUFFER_SIZE) {
            break;
        }
    }
    qc_err_free(err);
}
