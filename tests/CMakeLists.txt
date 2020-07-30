set(RUNTIME_OUTPUT_DIRECTORY tests)

add_executable(qc-die-fails qc-die-fails.c)
target_link_libraries(qc-die-fails PUBLIC qc)
add_test(NAME qc-die-fails COMMAND qc-die-fails WILL_FAIL)
set_tests_properties(qc-die-fails PROPERTIES WILL_FAIL ON)
