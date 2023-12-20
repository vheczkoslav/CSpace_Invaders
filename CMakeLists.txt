cmake_minimum_required(VERSION 3.18)
project(project C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
#set(MY_COMPIL_FLAGS ${MY_COMPIL_FLAGS} /fsanitize=address)
#set(CMAKE_EXE_LINKER_FLAGS "/fsanitize=address")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable( main main.c aliens.c main.h aliens.h )
target_link_libraries( main SDL2 SDL2_image SDL2_ttf )