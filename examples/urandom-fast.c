#include <stdio.h>
#include "qc.h"

#define BUFFER_SIZE 8096

int main(void) {
    qc_reopen_stdin_stdout_binary();
    qc_err* err = qc_err_new();
    qc_rnd rnd;
    if (qc_rnd_init(&rnd, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to seed random generator");
    }
    qc_err_free(err);

    uint64_t buf[BUFFER_SIZE];
    for (;;) {
        for (size_t i = 0; i < BUFFER_SIZE; ++i) {
            buf[i] = qc_rnd64(&rnd);
        }
        if (fwrite(buf, sizeof(uint64_t), BUFFER_SIZE, stdout) != BUFFER_SIZE) {
            break;
        }
    }
}
