cmake_minimum_required(VERSION 3.19)
project(cimnet)

set(CMAKE_CXX_STANDARD 11)

include_directories(..)

set(CMAKE_CXX_FLAGS -o3)

add_executable(test_base test_base.cc)
add_executable(test_network test_network.cc)
add_executable(test_algorithms test_algorithms.cc)
add_executable(test_io test_io.cc)
