add_executable(lcm lcm.c)
target_link_libraries(lcm PUBLIC qc)

add_executable(xor-encryptor xor-encryptor.c)
target_link_libraries(xor-encryptor PUBLIC qc)

add_executable(urandom-fast urandom-fast.c)
target_link_libraries(urandom-fast PUBLIC qc)
