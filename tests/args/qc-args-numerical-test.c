#include <math.h>
#include "qc.h"

#define EPS 10e-9

void test_unsigned(qc_err* err) {
    size_t length = 0, width = 0, depth = 0;
    qc_args* args = qc_args_new();
    qc_args_unsigned(args, "length", &length, NULL);
    qc_args_unsigned(args, "width", &width, NULL);
    qc_args_unsigned(args, "depth", &depth, NULL);

    qc_result result = qc_args_parse(args, 4, (char*[]){
        "/path/to/exe", "--length=15", "--depth=15", "--width=30", NULL
    }, err);
    qc_assert(result == QC_SUCCESS, qc_sprintf_alloc("qc_args_parse has failed: %s", err));
    qc_assert(length == 15 && width == 30 && depth == 15,
              "Expected values don't match");
    qc_args_free(args);
}

void test_signed(qc_err* err) {
    ptrdiff_t latitude = 0, longitude = 0, altitude = 0;
    qc_args* args = qc_args_new();
    qc_args_signed(args, "latitude", &latitude, NULL);
    qc_args_signed(args, "longitude", &longitude, NULL);
    qc_args_signed(args, "altitude", &altitude, NULL);

    qc_result result = qc_args_parse(args, 4, (char*[]){
        "/path/to/exe", "--altitude=0", "--longitude=250", "--latitude=-115", NULL
    }, err);
    qc_assert(result == QC_SUCCESS, qc_sprintf_alloc("qc_args_parse has failed: %s", err));
    qc_assert(latitude == -115 && longitude == 250 && altitude == 0,
              "Expected values don't match");
    qc_args_free(args);
}

void test_double(qc_err* err) {
    double x = 0.0, y = 0.0, z = 0.0;
    qc_args* args = qc_args_new();
    qc_args_double(args, "x", &x, NULL);
    qc_args_double(args, "y", &y, NULL);
    qc_args_double(args, "z", &z, NULL);

    qc_result result = qc_args_parse(args, 4, (char*[]){
        "/path/to/exe", "--x=12.4", "--z=-13.557", "--y=0.00006", NULL
    }, err);
    qc_assert(result == QC_SUCCESS, qc_sprintf_alloc("qc_args_parse has failed: %s", err));
    qc_assert(fabs(x - 12.4) < EPS && fabs(y - 0.00006) < EPS && fabs(z + 13.557) < EPS,
              "Expected values don't match");
    qc_args_free(args);
}

int main() {
    qc_err* err = qc_err_new();
    test_unsigned(err);
    test_signed(err);
    test_double(err);
    qc_err_free(err);
}
