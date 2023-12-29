cmake_minimum_required(VERSION 3.5.0)
project(sdl_ffmpeg VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(test_sdl test_sdl.cpp)
add_executable(test_ffmpeg test_ffmpeg.cpp)
add_executable(player SDL_ffmpeg_player.cpp)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(test_sdl PRIVATE SDL2::SDL2)
target_link_libraries(player PRIVATE SDL2::SDL2)

find_package(FFMPEG REQUIRED)
target_include_directories(test_ffmpeg PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(test_ffmpeg PRIVATE ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(test_ffmpeg PRIVATE ${FFMPEG_LIBRARIES})
target_include_directories(player PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(player PRIVATE ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(player PRIVATE ${FFMPEG_LIBRARIES})