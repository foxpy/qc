add_library(qc
    random.c
    math.c
    utils.c
    error.c
    string.c
    endian/integer64.c
    endian/integer32.c
    endian/integer16.c
    endian/floating-point.c
    platform/random.c
    platform/reopen-binary.c
    args/args_public_api.c
    args/args_impl.c
)
target_include_directories(qc PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
