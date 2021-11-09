cmake_minimum_required(VERSION 3.0)

project("Bayesian Networks")

set(BASE_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH ${BASE_DIR}/cmake)

find_package(Doxygen)
find_package(Graphviz)
find_package(Eigen3 REQUIRED)


# Prefix to be used for all library names
set(LIB_PREFIX "bn_")

enable_testing()

include_directories(
    ${BASE_DIR}/include
    ${EIGEN3_INCLUDE_DIR}
    ${GRAPHVIZ_INCLUDE_DIRS}
)

# Macro to generate library name with prefix
macro(LIBNAME _origname _newname)
    set(${_newname} "${LIB_PREFIX}${_origname}")
endmacro()

# Library Names
LIBNAME("bn" LIB_BN)
LIBNAME("utils" LIB_UTILS)

add_subdirectory(src/bn/bn)
add_subdirectory(src/bn/utils)
add_subdirectory(src/bn/examples)
