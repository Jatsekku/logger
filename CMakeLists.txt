cmake_minimum_required(VERSION 3.15)
project(logger)

option(BUILD_STATIC_LIBS "Build static libraries" ON)
option(BUILD_EXAMPLES "Build examples" ON)

# Include GNUInstallDirs to use standard directory variables
include(GNUInstallDirs)
# Include CMakePackageConfigHelpers to use config files generator 
include(CMakePackageConfigHelpers)

if(NOT CMAKE_INSTALL_CMAKEDIR)
    set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/logger)
endif()

add_subdirectory(include)
add_subdirectory(src)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
