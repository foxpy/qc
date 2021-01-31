#include <stdint.h>
#include <string.h>
#include "qc/error.h"
#include "qc/random.h"
#include "qc/tests.h"

int main(void) {
    qc_rnd rnd;
    qc_err* err = qc_err_new();
    qc_assert(qc_rnd_init(&rnd, err) == QC_SUCCESS, "qc_rnd_init has failed: %s", qc_err_get(err));
    qc_err_free(err);
    uint8_t buf[32] = {0};
    qc_rnd_buf(&rnd, 20, &buf[2]);
    qc_assert(memcmp(&buf[2], (uint8_t[20]){0}, 20) != 0, "qc_rnd_buf() does not write random");
    qc_assert(memcmp(&buf[0], (uint8_t[2]){0}, 2) == 0 && memcmp(&buf[22], (uint8_t[10]){0}, 10) == 0,
              "qc_rnd_buf() writes out of bounds");
}
