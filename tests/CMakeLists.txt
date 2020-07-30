set(RUNTIME_OUTPUT_DIRECTORY tests)

function(qc_add_test target)
    add_executable(${target} ${target}.c)
    target_link_libraries(${target} PUBLIC qc)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

qc_add_test(qc-die-fails)
set_tests_properties(qc-die-fails PROPERTIES WILL_FAIL ON)
qc_add_test(qc-emalloc-usable)
