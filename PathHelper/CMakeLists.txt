cmake_minimum_required(VERSION 3.10)

add_library(PathHelper PathHelper.cpp)
target_link_libraries(PathHelper PUBLIC Board)
target_include_directories(PathHelper PUBLIC Board)
target_link_libraries(PathHelper PUBLIC Snake)
target_include_directories(PathHelper PUBLIC Snake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

cmake_policy(SET CMP0074 NEW)
