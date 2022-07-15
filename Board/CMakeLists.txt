cmake_minimum_required(VERSION 3.10)

add_library(Board Board.cpp)
target_link_libraries(Board PUBLIC Bound)
target_include_directories(Board PUBLIC Bound)
target_link_libraries(Board PUBLIC Block)
target_include_directories(Board PUBLIC Block)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

cmake_policy(SET CMP0074 NEW)
