cmake_minimum_required(VERSION 3.15)
project(logger)

option(BUILD_STATIC_LIBS "Build static libraries" ON)
option(BUILD_EXAMPLES "Build examples" ON)

add_subdirectory(include)
add_subdirectory(src)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
