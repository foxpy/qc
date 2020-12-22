#include "qc/error.h"

int main(void) {
    qc_err* err = qc_err_new();
    qc_err_fatal(err, "Ooopsie!");
}
