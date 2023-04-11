cmake_minimum_required(VERSION 3.26.3)
project(VTE)
set(CMAKE_CXX_STANDARD 17)

set(LIB_TARGETS)
set(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_subdirectory(libs)
add_subdirectory(vendors)
add_subdirectory(code)