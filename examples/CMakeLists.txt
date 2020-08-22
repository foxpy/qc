add_executable(lcm lcm.c)
target_link_libraries(lcm PUBLIC qc)

add_executable(xor-encryptor xor-encryptor.c)
target_link_libraries(xor-encryptor PUBLIC qc)
