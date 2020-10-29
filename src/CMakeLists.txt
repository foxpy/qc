add_library(qc
    die.c
    emalloc.c
    erealloc.c
    random.c
    platform_random.c
    math.c
    reopen-binary.c
    sprintf_alloc.c
    args.c
    qc_impl.c
)
target_include_directories(qc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
