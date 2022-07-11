cmake_minimum_required(VERSION 3.10)

project(PathfinderRE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

add_executable(Pathfinder Pathfinder.cpp)
add_dependencies(Pathfinder XPSTest true_field)

add_subdirectory(XPSHelper)
target_link_libraries(Pathfinder PUBLIC XPSHelper)
target_include_directories(Pathfinder PUBLIC XPSHelper)

add_subdirectory(TimeChecker)
target_link_libraries(Pathfinder PUBLIC TimeChecker)
target_include_directories(Pathfinder PUBLIC TimeChecker)

add_subdirectory(G3)
target_link_libraries(Pathfinder PUBLIC G3)
target_include_directories(Pathfinder PUBLIC G3)

add_subdirectory(PathHelper)
target_link_libraries(Pathfinder PUBLIC PathHelper)
target_include_directories(Pathfinder PUBLIC PathHelper)



add_custom_target(XPSTest
	${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/XPSTest ${CMAKE_CURRENT_BINARY_DIR}/XPSTest 
)

add_custom_target(true_field
	${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/true_field.txt ${CMAKE_CURRENT_BINARY_DIR}/true_field.txt
)
