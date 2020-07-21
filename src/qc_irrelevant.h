#ifndef __QC_IRRELEVANT_H
#define __QC_IRRELEVANT_H

/*
 * Irrelevant: makes very little sense
 * to pollute main header
 */

#include <stddef.h>

#ifdef __GNUC__
#define __QC_NORETURN __attribute__((noreturn))
#else
#define __QC_NORETURN
#endif

#endif
