#include "qc.h"

int main() {
    qc_err* err = qc_err_new();
    qc_err_fatal(err, "Ooopsie!");
}
