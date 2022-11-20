file(GLOB CXX_SOURCES *.cpp)
file(GLOB CXX_HEADERS *.h)

add_library(lc3core ${CXX_SOURCES} ${CXX_HEADERS})