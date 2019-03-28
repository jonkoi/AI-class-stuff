cmake_minimum_required(VERSION 2.8)

project( Assignment07 )

set(CMAKE_BUILD_TYPE Debug)

add_definitions(-std=c++11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include_directories (
    include
    include/matplotlib-cpp
)

add_executable( assignment07
    src/world.cpp
    src/main.cpp
    src/agent.cpp
    )

#to use matplotlib
target_link_libraries(assignment07 -lpython2.7)
