add_executable(
    example_hello_bn
    example_hello_bn.cpp
)

target_link_libraries(
    example_hello_bn
    ${LIB_BN}
)
