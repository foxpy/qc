#include <stdlib.h>
#include <stdio.h>
#include "qc.h"

#define BUFFER_SIZE 8096

int main() {
    reopen_stdin_stdout_binary();
    uint64_t buf[BUFFER_SIZE];
    qc_rnd rnd;
    if (!qc_rnd_init(&rnd)) {
        fputs("Failed to seed random generator", stderr);
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
}
