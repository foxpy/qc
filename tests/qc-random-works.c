#include <stdint.h>
#include <string.h>
#include "qc.h"

struct test_random_data {
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    float f32;
    double f64;
};

static void populate(struct test_random_data *t) {
    qc_rnd s;
    qc_assert(qc_rnd_init(&s) == true, "Failed to initialize random");
    t->u8 = qc_rnd8(&s);
    t->u16 = qc_rnd16(&s);
    t->u32 = qc_rnd32(&s);
    t->u64 = qc_rnd64(&s);
    t->f32 = qc_rnd_fp32(&s);
    t->f64 = qc_rnd_fp64(&s);
}

static size_t compare(struct test_random_data *t1, struct test_random_data *t2) {
    return memcmp(&t1->u8, &t2->u8, sizeof(uint8_t)) |
           memcmp(&t1->u16, &t2->u16, sizeof(uint16_t)) |
           memcmp(&t1->u32, &t2->u32, sizeof(uint32_t)) |
           memcmp(&t1->u64, &t2->u64, sizeof(uint64_t)) |
           memcmp(&t1->f32, &t2->f32, sizeof(float)) |
           memcmp(&t1->f64, &t2->f64, sizeof(double));
}

int main() {
    struct test_random_data t1, t2, t3;
    populate(&t1);
    populate(&t2);
    populate(&t3);
    qc_assert(compare(&t1, &t2), "random is not seeded well");
    qc_assert(compare(&t1, &t3), "random is not seeded well");
    qc_assert(compare(&t2, &t3), "random is not seeded well");
}
