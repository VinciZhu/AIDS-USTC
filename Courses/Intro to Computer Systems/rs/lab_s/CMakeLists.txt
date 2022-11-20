set(Boost_NO_WARN_NEW_VERSIONS ON)
find_package(Boost REQUIRED COMPONENTS program_options)

include_directories(include)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB CXX_SOURCES src/*.cpp)
add_executable(lab_s ${CXX_SOURCES})

target_link_libraries(lab_s ${Boost_LIBRARIES})
