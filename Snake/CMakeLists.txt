cmake_minimum_required(VERSION 3.10)

add_library(Snake Snake.cpp)
target_link_libraries(Snake PUBLIC Block)
target_include_directories(Snake PUBLIC Block)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

cmake_policy(SET CMP0074 NEW)
