#ifdef _WIN32
#   define _CRT_RAND_S
#endif

#if defined __linux__ || defined __ANDROID_API__
#   include <sys/syscall.h>
#   include <unistd.h>
#endif

#include <stdint.h>
#include <stdlib.h>
#include "qc.h"

void rnd_init(qc_rnd *state) {
#   ifdef _WIN32
        rand_s(&state->s32[0]);
        rand_s(&state->s32[1]);
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
