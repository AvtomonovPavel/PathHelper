cmake_minimum_required(VERSION 3.10)

add_library(XPSHelper XPSHelper.cpp)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

cmake_policy(SET CMP0074 NEW)
