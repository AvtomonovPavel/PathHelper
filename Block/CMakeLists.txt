cmake_minimum_required(VERSION 3.10)

add_library(Block Block.cpp)
target_link_libraries(Block PUBLIC XPSHelper)
target_include_directories(Block PUBLIC XPSHelper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

cmake_policy(SET CMP0074 NEW)
