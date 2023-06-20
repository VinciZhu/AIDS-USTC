cmake_minimum_required(VERSION 3.0.0)
project(algo-hw VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CTEST_ARGUMENTS --verbose)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(CTest)
enable_testing()

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_SHARED_LIBRARY_PREFIX )

include_directories(${SOURCE_DIR})
set(LIB_FILES 
    knapsack/divide_and_conquer.cpp 
    knapsack/dynamic_programming.cpp
    knapsack/greedy.cpp
    knapsack/backtracking.cpp
    knapsack/branch_and_bound.cpp
    knapsack/monte_carlo.cpp
)
set(SOURCE_FILES 
)
set(TEST_FILES 
)

foreach(LIB_FILE ${LIB_FILES})
    get_filename_component(LIB_NAME ${LIB_FILE} NAME_WE)
    add_library(${LIB_NAME} SHARED ${SOURCE_DIR}/${LIB_FILE})
endforeach()

foreach(SOURCE_FILE ${SOURCE_FILES})
    get_filename_component(SOURCE_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${SOURCE_NAME} ${SOURCE_DIR}/${SOURCE_FILE})
endforeach()

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${SOURCE_DIR}/${TEST_FILE})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 99999)
endforeach()
