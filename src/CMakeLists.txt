add_library(qc
    random.c
    platform_random.c
    math.c
    reopen-binary.c
    args.c
    util.c
    qc_impl.c
)
target_include_directories(qc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
