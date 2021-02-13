#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "qc/error.h"

// these functions act like [v]asprintf from GNU C standard library,
// they allocate memory automatically
// qc_[v]asnprintf functions accept a maximum allocation size limit
ptrdiff_t qc_asprintf(char** dst, char const* format, ...);
ptrdiff_t qc_asnprintf(char** dst, size_t mlimit, char const* format, ...);
ptrdiff_t qc_vasprintf(char** dst, char const* format, va_list ap);
ptrdiff_t qc_vasnprintf(char** dst, size_t mlimit, char const* format, va_list ap);

// these functions are easier to use properly than stdlib strtoXX ones
qc_result qc_str_to_unsigned(char const* str, size_t* dst, char const** tail);
qc_result qc_str_to_signed(char const* str, ptrdiff_t* dst, char const** tail);
qc_result qc_str_to_double(char const* str, double* dst, char const** tail);

// hexadecimal string <-> raw bytes conversion utilities
ptrdiff_t qc_hexstr_to_bytes(char const* str, uint8_t** dst);
void qc_bytes_to_hexstr(bool uppercase, size_t len, uint8_t const src[static len], char** dst);
