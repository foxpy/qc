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

int qc_rnd_init(qc_rnd* state) {
    bool ret = true;
#   if defined _WIN32
        HCRYPTPROV hCryptProv;
        if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0) == 0) {
            ret = false;
            goto exit;
        }
        if (CryptGenRandom(hCryptProv, sizeof(uint64_t), (PBYTE) &state->s64) == 0) {
            ret = false;
            // should release context anyway
        }
        if (CryptReleaseContext(hCryptProv, 0) == 0) {
            ret = false;
            goto exit;
        }
#   elif defined __ANDROID_API__
#       if __ANDROID_API__ < 28
            arc4random_buf(&state->s64, sizeof(uint64_t)); // always successful
            goto exit;
#       else
            if (getrandom(&state->s64, sizeof(uint64_t), 0) != sizeof(uint64_t)) {
                ret = false;
                goto exit;
            }
#       endif
#   elif defined __linux__
        if (syscall(SYS_getrandom, &state->s64, sizeof(uint64_t), 0) != sizeof(uint64_t)) {
                ret = false;
                goto exit;
            }
#   elif defined(unix) || defined(__unix__) || defined(__unix)
        arc4random_buf(&state->s64, sizeof(uint64_t)); // always successful
        goto exit;
#   else
        // no way to success on unsupported platform :v
        ret = false;
        goto exit;
#   endif
exit:
    if (ret == false) {
        state->s64 = 0;
    }
    return ret;
}
