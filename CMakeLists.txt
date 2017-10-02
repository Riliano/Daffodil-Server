cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)
add_definitions("-Wall -Wpedantic")

find_package(PkgConfig)

pkg_check_modules(SDL sdl2 SDL2_net)

link_directories(${SDL_LIBRARY_DIRS})
include_directories(${SDL_INCLUDE_DIRS})
add_definitions(${SDL_CFLAGS_OTHER})

file(GLOB SOURCES "src/*.cpp")

add_executable(daffodil-server ${SOURCES})
target_link_libraries(daffodil-server ${SDL_LIBRARIES})

find_package (Threads)
target_link_libraries (daffodil-server ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS daffodil-server DESTINATION bin)
