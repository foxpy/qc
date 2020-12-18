#pragma once

// using C11 noreturn in Windows is impossible
// (only if using Windows itself was possible by any margin)
// henceforth this header exists

#define qc_noreturn _Noreturn
