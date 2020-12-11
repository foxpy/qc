#pragma once

// these functions act like [v]asprintf from GNU C standard library,
// they allocate memory automatically
// qc_[v]asnprintf functions accept a maximum allocation size limit
ptrdiff_t qc_asprintf(char** dst, char const* format, ...);
ptrdiff_t qc_asnprintf(char** dst, size_t mlimit, char const* format, ...);
ptrdiff_t qc_vasprintf(char** dst, char const* format, va_list ap);
ptrdiff_t qc_vasnprintf(char** dst, size_t mlimit, char const* format, va_list ap);
