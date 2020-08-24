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

void qc_rnd_init(qc_rnd *state) {
#   if defined _WIN32
        HCRYPTPROV   hCryptProv;
        CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0);
        CryptGenRandom(hCryptProv, sizeof(uint64_t), (PBYTE) &state->s64);
#   elif defined __ANDROID_API__
#       if __ANDROID_API__ < 28
            arc4random_buf(&state->s64, sizeof(uint64_t));
#       else
            getrandom(&state->s64, sizeof(uint64_t), 0);
#       endif
#   elif defined __linux__
        syscall(SYS_getrandom, &state->s64, sizeof(uint64_t), 0);
#   elif defined(unix) || defined(__unix__) || defined(__unix)
        arc4random_buf(&state->s64, sizeof(uint64_t));
#   else
        state->s64 = 0;
#   endif
}
