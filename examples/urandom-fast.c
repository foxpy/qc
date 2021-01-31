#include <stdio.h>
#include "qc.h"

#define BUFFER_SIZE 65536

int main(void) {
    qc_reopen_stdin_stdout_binary();
    qc_err* err = qc_err_new();
    qc_rnd rnd;
    if (qc_rnd_init(&rnd, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to seed random generator");
    }
    qc_err_free(err);

    uint8_t buf[BUFFER_SIZE];
    for (;;) {
        qc_rnd_buf(&rnd, BUFFER_SIZE, buf);
        if (fwrite(buf, sizeof(uint8_t), BUFFER_SIZE, stdout) != BUFFER_SIZE) {
            break;
        }
    }
}
