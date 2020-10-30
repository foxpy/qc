add_library(qc
    random.c
    platform_random.c
    math.c
    reopen-binary.c
    args.c
    util.c
    qc_impl.c
    error.c
)
target_include_directories(qc PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
