#ifdef __ANDROID__
#    include <android/api-level.h>
#endif

#if defined _WIN32
#    include "random/random_windows.c"
#elif defined __ANDROID__
#    if __ANDROID_API__ < 28
#        include "random/random_bsd.c"
#    else
#        include "random/random_android.c"
#    endif
#elif defined __linux__
#    include "random/random_linux.c"
#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__APPLE_CC__) || \
        defined(__OSX__) || defined(__MACH__)
#    include "random/random_bsd.c"
#else
#    include "random/random_unknown.c"
#endif
