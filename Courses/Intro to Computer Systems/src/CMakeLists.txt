add_subdirectory(backend)
add_subdirectory(common)

include_directories(backend)
include_directories(common)

if(BUILD_LAB_TEST)
    file(GLOB TEST_SOURCES *.cpp)
    foreach(TEST_SOURCE ${TEST_SOURCES})
        get_filename_component(TEST_SOURCE_NAME ${TEST_SOURCE} NAME_WE)
        add_executable(${TEST_SOURCE_NAME} ${TEST_SOURCE} $<TARGET_OBJECTS:common>)
        target_link_libraries(${TEST_SOURCE_NAME} lc3core)
    endforeach()
endif()