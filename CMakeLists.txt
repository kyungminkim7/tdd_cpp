cmake_minimum_required(VERSION 3.14)
project(tdd_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/module")

enable_testing()

add_subdirectory(src bin)