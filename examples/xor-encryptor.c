#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include "qc.h"

#define KEY UINT64_C(0x087a7454e964756d)
#define BUFFER_SIZE 1024

static void help(void* help_data) {
    char* program_name = help_data;
    fprintf(stderr, "Usage: %s [INPUT [OUTPUT]]\n", program_name);
}

static void encryption_loop(FILE* input, FILE* output) {
    qc_rnd rnd;
    qc_rnd_seed(&rnd, KEY);
    uint8_t buf[sizeof(uint64_t) * BUFFER_SIZE];
    size_t nread;
    while ((nread = fread(buf, sizeof(uint8_t), sizeof(buf), input)) > 0) {
        uint64_t* enc = (uint64_t*) buf;
        for (size_t i = 0; i < BUFFER_SIZE; ++i) {
            enc[i] ^= qc_rnd64(&rnd);
        }
        if (fwrite(buf, sizeof(uint8_t), nread, output) < nread) {
            break;
        }
    }
}

static FILE* open_file(char const* path, char const* mode, FILE* fallback) {
    errno = 0;
    FILE* ret = (strcmp(path, "-") == 0) ? fallback : fopen(path, mode);
    if (ret == NULL) {
        fprintf(stderr, "Failed to open file \"%s\": %s", path, strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        return ret;
    }
}

int main(int argc, char* argv[]) {
    qc_reopen_stdin_stdout_binary();
    FILE* input;
    FILE* output;
    qc_args* args = qc_args_new();
    qc_err* err = qc_err_new();
    qc_args_set_help(args, help, argv[0]);
    if (qc_args_parse(args, argc, argv, err) == QC_FAILURE) {
        fprintf(stderr, "Failed to parse arguments: %s\n", qc_err_get(err));
        fputc('\n', stderr);
        help(argv[0]);
        exit(EXIT_FAILURE);
    }
    if (qc_args_positionals_count(args) == 0) {
        input = stdin;
        output = stdout;
    } else if (qc_args_positionals_count(args) == 1) {
        input = open_file(argv[qc_args_positionals_index(args) + 0], "rb", stdin);
        output = stdout;
    } else {
        input = open_file(argv[qc_args_positionals_index(args) + 0], "rb", stdin);
        output = open_file(argv[qc_args_positionals_index(args) + 1], "wb", stdout);
    }
    encryption_loop(input, output);
    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }
    qc_err_free(err);
    qc_args_free(args);
}
