#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "qc.h"

int main(int argc, char* argv[]) {
    qc_err* err = qc_err_new();
    qc_args* args = qc_args_new();
    size_t iterations;
    double mu, sigma;
    qc_args_unsigned_default(args, "n", 10, &iterations, "number of generated values");
    qc_args_double_default(args, "mu", 0.0, &mu, "expected value");
    qc_args_double_default(args, "sigma", 1.0, &sigma, "standard deviation");
    if (qc_args_parse(args, argc, argv, err) == QC_FAILURE) {
        fprintf(stderr, "Failed to parse arguments: %s", qc_err_to_owned_c_str(err));
        return EXIT_FAILURE;
    }
    {
        qc_distr_normal* distr;
        if ((distr = qc_distr_normal_init(mu, sigma, err)) == NULL) {
            fprintf(stderr, "Failed to initialize random generator: %s", qc_err_to_owned_c_str(err));
            return EXIT_FAILURE;
        }
        for (size_t i = 0; i < iterations; ++i) {
            printf("%f\n", qc_distr_normal_gen(distr));
        }
        qc_distr_normal_free(distr);
    }
    qc_args_free(args);
    qc_err_free(err);
}
