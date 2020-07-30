add_library(qc
    die.c
    emalloc.c
    erealloc.c
    assert.c
    random.c
    platform_random.c
)
target_include_directories(qc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
