add_library(qc
    random.c
    math.c
    args.c
    utils.c
    qc_impl.c
    error.c
    platform/random.c
    platform/reopen-binary.c
)
target_include_directories(qc PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
