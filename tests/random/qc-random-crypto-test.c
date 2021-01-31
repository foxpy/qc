#include <stdint.h>
#include <string.h>
#include "qc/error.h"
#include "qc/random.h"
#include "qc/tests.h"

int main(void) {
    qc_err* err = qc_err_new();
    uint8_t buf[16] = {0};
    qc_assert(qc_rnd_os_buf(8, &buf[4], err) == QC_SUCCESS, "qc_rnd_os_buf() has failed: %s", qc_err_get(err));
    qc_err_free(err);
    qc_assert(memcmp(&buf[4], (uint8_t[8]){0}, 8) != 0, "qc_rnd_os_buf() does not write random");
    qc_assert(memcmp(&buf[0], (uint8_t[4]){0}, 4) == 0 && memcmp(&buf[12], (uint8_t[4]){0}, 4) == 0,
              "qc_rnd_os_buf() writes out of bounds");
}
