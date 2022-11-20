include_directories(../backend)

file(GLOB CXX_SOURCES *.cpp)
file(GLOB CXX_HEADERS *.h)

add_library(common OBJECT ${CXX_SOURCES} ${CXX_HEADERS})
