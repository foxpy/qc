#include <stdint.h>
#include <string.h>
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

static FILE* open_input_file(char* path) {
    errno = 0;
    FILE* ret = (strcmp(path, "-") == 0) ? stdin : fopen(path, "rb");
    if (ret == NULL) {
        fprintf(stderr, "Failed to open file \"%s\": %s", path, strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        return ret;
    }
}

static FILE* open_output_file(char* path) {
    errno = 0;
    FILE* ret = (strcmp(path, "-") == 0) ? stdout : fopen(path, "wb");
    if (ret == NULL) {
        fprintf(stderr, "Failed to open file \"%s\": %s", path, strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        return ret;
    }
}

int main(int argc, char* argv[]) {
    reopen_stdin_stdout_binary();
    char* input_str = NULL;
    char* output_str = NULL;
    FILE* input_file;
    FILE* output_file;
    char* err;
    qc_args* args = qc_args_new();
    qc_args_set_help(args, help, argv[0]);
    qc_args_positional(args, &input_str);
    qc_args_positional(args, &output_str);
    if (qc_args_parse(args, argc, argv, &err) == -1) {
        fprintf(stderr, "Failed to parse command line: %s", err);
        free(err);
        exit(EXIT_FAILURE);
    }
    if (qc_args_num_positionals(args) == 0) {
        input_file = stdin;
        output_file = stdout;
    } else if (qc_args_num_positionals(args) == 1) {
        input_file = open_input_file(input_str);
        output_file = stdout;
    } else {
        input_file = open_input_file(input_str);
        output_file = open_output_file(output_str);
    }
    encryption_loop(input_file, output_file);
    if (input_str != NULL) {
        free(input_str);
    }
    if (output_str != NULL) {
        free(output_str);
    }
    if (input_file != stdin) {
        fclose(input_file);
    }
    if (output_file != stdout) {
        fclose(output_file);
    }
    qc_args_free(args);
}
