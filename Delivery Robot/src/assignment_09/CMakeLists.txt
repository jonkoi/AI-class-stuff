cmake_minimum_required(VERSION 2.8)

project( Assignment09 )

set(CMAKE_BUILD_TYPE Debug)

add_definitions(-std=c++11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include_directories (
    include
)

add_executable( assignment09
		src/agent.cpp
        	src/environment.cpp
        	src/main.cpp)

#to use matplot
target_link_libraries(assignment09 )
