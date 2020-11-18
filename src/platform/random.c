#ifdef __ANDROID__
#   include <android/api-level.h>
#endif

#if defined _WIN32
#   include <windows.h>
#   include <wincrypt.h>
#elif defined __linux__ || defined __ANDROID_API__
#   include <sys/syscall.h>
#   include <unistd.h>
#endif

#include "qc.h"
#include <stdint.h>
#include <stdlib.h>

qc_result qc_rnd_init(qc_rnd* state, qc_err* err) {
    qc_result ret = QC_SUCCESS;
#   if defined _WIN32
        HCRYPTPROV hCryptProv;
        if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0) == 0) {
            qc_err_set(err, "Failed to acquire WIN32 cryptographic context");
            ret = QC_FAILURE;
            goto exit;
        }
        if (CryptGenRandom(hCryptProv, sizeof(uint64_t), (PBYTE) &state->s64) == 0) {
            qc_err_set(err, "Failed to acquire entropy from WIN32 cryptographic context");
            ret = QC_FAILURE;
            // should release context anyway so we don't jump to exit yet
        }
        if (CryptReleaseContext(hCryptProv, 0) == 0) {
            qc_err_set(err, "Failed to release WIN32 cryptographic context "
                            "(this should never happen, report bug immediately!)");
            ret = QC_FAILURE;
            goto exit;
        }
#   elif defined __ANDROID__
#       if __ANDROID_API__ < 28
            UNUSED(err);
            arc4random_buf(&state->s64, sizeof(uint64_t)); // always successful
            goto exit;
#       else
            if (getrandom(&state->s64, sizeof(uint64_t), 0) != sizeof(uint64_t)) {
                qc_err_set(err, "Failed to acquire entropy from kernel");
                ret = QC_FAILURE;
                goto exit;
            }
#       endif
#   elif defined __linux__
        if (syscall(SYS_getrandom, &state->s64, sizeof(uint64_t), 0) != sizeof(uint64_t)) {
            qc_err_set(err, "Failed to acquire entropy from kernel");
            ret = QC_FAILURE;
            goto exit;
        }
#   elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__APPLE_CC__) || defined(__OSX__) || defined(__MACH__)
        UNUSED(err);
        arc4random_buf(&state->s64, sizeof(uint64_t)); // always successful
        goto exit;
#   else
        // no way to success on unsupported platform :v
        qc_err_set(err, "Your platform is unsupported. "
                        "Please consider opening an issue, or, even better, sending a pull request");
        ret = QC_FAILURE;
        goto exit;
#   endif
exit:
    if (ret == QC_FAILURE) {
        state->s64 = 0;
    }
    return ret;
}
