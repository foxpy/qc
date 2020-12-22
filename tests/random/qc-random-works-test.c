#include <stdint.h>
#include <string.h>
#include "qc/error.h"
#include "qc/random.h"
#include "qc/tests.h"

struct test_random_data {
    uint64_t u64;
    double f64;
};

static void populate(struct test_random_data *t) {
    qc_err* err = qc_err_new();
    qc_rnd s;
    qc_assert(qc_rnd_init(&s, err) == QC_SUCCESS, "Failed to initialize random: %s", qc_err_get(err));
    t->u64 = qc_rnd64(&s);
    t->f64 = qc_rnd_fp64(&s);
    qc_err_free(err);
}

static size_t compare(struct test_random_data *t1, struct test_random_data *t2) {
    return memcmp(&t1->u64, &t2->u64, sizeof(uint64_t)) != 0 &&
           memcmp(&t1->f64, &t2->f64, sizeof(double)) != 0;
}

int main(void) {
    struct test_random_data t1, t2, t3;
    populate(&t1);
    populate(&t2);
    populate(&t3);
    qc_assert(compare(&t1, &t2), "random is not seeded well");
    qc_assert(compare(&t1, &t3), "random is not seeded well");
    qc_assert(compare(&t2, &t3), "random is not seeded well");
}
