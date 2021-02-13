#pragma once
#include "macro_impl/tests-impl.h"

// If condition is false, terminates program and prints
// current filename and line. Has several advantages over
// std assert: prints custom error message and does not depend
// on NDEBUG macro definition
#define qc_assert(cond, ...) QC_ASSERT_IMPL(cond, __VA_ARGS__, '\n')
