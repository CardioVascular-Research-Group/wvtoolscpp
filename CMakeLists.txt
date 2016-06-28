cmake_minimum_required(VERSION 3.5)
project(wvtools)

add_definitions(-std=gnu++11 -Wall -Wextra -pedantic -O3)

set(SOURCE_FILES wvtools.cpp)

add_executable(wvtools ${SOURCE_FILES})

add_subdirectory(test)
add_subdirectory(src)
include_directories(src)

target_link_libraries(wvtools wvtools_lib boost_program_options)
