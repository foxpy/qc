qc_add_test(qc-config-from-string-test)

add_executable(qc-config-from-file-test qc-config-from-file-test.c)
target_link_libraries(qc-config-from-file-test PUBLIC qc)
add_test(NAME qc-config-from-file-test COMMAND qc-config-from-file-test ${CMAKE_CURRENT_SOURCE_DIR}/sample.conf)
