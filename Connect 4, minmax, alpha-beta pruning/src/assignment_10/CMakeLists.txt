cmake_minimum_required(VERSION 2.8)

project( Assignment10 )

set(CMAKE_BUILD_TYPE Debug)

add_definitions(-std=c++11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include_directories (
    include
)

add_executable( assignment10
        	src/main.cpp
            src/Players.cpp
            src/GameBoard.cpp)
