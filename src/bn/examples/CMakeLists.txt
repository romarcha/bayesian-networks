add_executable(
    example_hello_bn
    example_hello_bn.cpp
)

target_link_libraries(
    example_hello_bn
    ${LIB_BN}
)

add_executable(
    example_bn_from_csv
    example_bn_from_csv.cpp
)

target_link_libraries(
    example_bn_from_csv
    ${LIB_BN}
)
