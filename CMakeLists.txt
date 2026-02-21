cmake_minimum_required(VERSION 3.28)
include(FetchContent)

project(nonEuclid 
	VERSION 1.1 
	LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

option(USE_NJIN "Build NJIN engine" ON)
option(PLAYGROUND "Build Playground examples" ON)

add_subdirectory(external)
add_subdirectory(njin)

if (PLAYGROUND)
	add_subdirectory(examples/Playground)
endif()
