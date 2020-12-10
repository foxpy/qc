function(qc_add_example target)
    add_executable(${target} ${target}.c)
    target_link_libraries(${target} PUBLIC qc)
endfunction()

qc_add_example(lcm)
qc_add_example(xor-encryptor)
qc_add_example(urandom-fast)
qc_add_example(normal-distribution)
