#include <stddef.h>
#include <string.h>
#include "qc/error.h"
#include "qc/tests.h"

int main() {
    qc_assert(strcmp(qc_err_get(NULL), "") == 0,
              "qc_err_get(NULL) is expected to return a pointer to empty string");
    qc_assert(strcmp(qc_err_to_owned_c_str(NULL), "") == 0,
              "qc_err_to_owned_c_str(NULL) is expected to return a pointer to empty string");

    // we can't really test anything here
    // we are just calling these functions to ensure
    // that program will not crash
    qc_err_set(NULL, "a");
    qc_err_set(NULL, "%d", 20);
    qc_err_append_front(NULL, "b");
    qc_err_append_front(NULL, "%f", 5.4);
}
