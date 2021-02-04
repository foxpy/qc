#ifdef _WIN32
#    include "reopen-binary/reopen-binary_windows.c"
#else
#    include "reopen-binary/reopen-binary_posix.c"
#endif
