#pragma once
#include "qc/noreturn.h"

qc_noreturn void qc_die_impl(char const* fmt, ...);
#define QC_DIE_IMPL(fmt, ...) qc_die_impl("Fatal error:\n  %s:%d\n  " fmt "%c", __FILE__, __LINE__, __VA_ARGS__)
