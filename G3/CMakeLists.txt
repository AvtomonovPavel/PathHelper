cmake_minimum_required(VERSION 3.10)

add_library(G3 G3.cpp)



target_link_libraries(G3 PUBLIC XPSHelper)
target_include_directories(G3 PUBLIC XPSHelper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

