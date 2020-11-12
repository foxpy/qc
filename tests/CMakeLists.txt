set(RUNTIME_OUTPUT_DIRECTORY tests)

function(qc_add_test target)
    add_executable(${target} ${target}.c)
    target_link_libraries(${target} PUBLIC qc)
    add_test(NAME ${target} COMMAND ${target})
endfunction()

function(qc_add_failing_test target)
    qc_add_test(${target})
    set_tests_properties(${target} PROPERTIES WILL_FAIL ON)
endfunction()

qc_add_test(qc-emalloc-usable-test)
qc_add_test(qc-erealloc-usable-test)
qc_add_test(qc-assert-success-test)
qc_add_test(qc-sprintf-alloc-works-test)
qc_add_test(qc-err-test)

add_subdirectory(args)
add_subdirectory(random)
add_subdirectory(math)
