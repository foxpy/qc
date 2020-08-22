#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "qc.h"

#define KEY UINT64_C(0x087a7454e964756d)
#define BUFFER_SIZE 1024

static void help() {
    fputs("Usage: xor-encryptor INPUT OUTPUT", stderr);
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

int main(int argc, char* argv[]) {
    reopen_stdin_stdout_binary();
    char* input = NULL;
    char* output = NULL;
    char* err;
    qc_args* args = qc_args_new();
    qc_args_set_help(args, help);
    qc_args_positional(args, &input);
    qc_args_positional(args, &output);
    if (qc_args_parse(args, argc, argv, &err) == -1) {
        fprintf(stderr, "Failed to parse command line: %s", err);
        free(err);
        exit(EXIT_FAILURE);
    }
    if (input == NULL || output == NULL) {
        help();
        exit(EXIT_FAILURE);
    } else {
        errno = 0;
        FILE* in = (strcmp(input, "-") == 0) ? stdin : fopen(input, "rb");
        if (in == NULL) {
            fprintf(stderr, "Failed to open file \"%s\": %s", input, strerror(errno));
            exit(EXIT_FAILURE);
        }
        errno = 0;
        FILE* out = (strcmp(output, "-") == 0) ? stdout : fopen(output, "wb");
        if (out == NULL) {
            fprintf(stderr, "Failed to open file \"%s\": %s", output, strerror(errno));
            exit(EXIT_FAILURE);
        }
        encryption_loop(in, out);
        if (in != stdin) {
            fclose(in);
        }
        if (out != stdout) {
            fclose(stdout);
        }
    }
    qc_args_free(args);
}
