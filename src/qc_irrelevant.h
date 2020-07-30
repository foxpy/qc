#ifndef __QC_IRRELEVANT_H
#define __QC_IRRELEVANT_H

/*
 * Irrelevant: makes very little sense
 * to pollute main header
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __GNUC__
#   define __QC_NORETURN __attribute__((noreturn))
#else
#   define __QC_NORETURN
#endif

typedef union qc_rnd_state_t {
    uint64_t s64;
    uint32_t s32[2];
    uint16_t s16[4];
    uint8_t s8[8];
    double fp64;
    float fp32[2];
} qc_rnd;

#endif
