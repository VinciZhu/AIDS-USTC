cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

project(ics2021)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

option(BUILD_SHARED_LIBS "Build shared libs." OFF)
option(BUILD_LAB_TEST "Build testing program for labs." ON)

add_subdirectory(src)
add_subdirectory(rs/lab_s)
