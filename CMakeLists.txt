cmake_minimum_required(VERSION 3.14)

SET(sampleName nonEuclid)

project(NonEuclid VERSION 0.1.0 LANGUAGES C CXX)

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

# libraries #
#############
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/tools/cmake/)

add_library(glad external/glad/glad.c include/glad/glad.h include/KHR/khrplatform.h)
target_include_directories(glad PUBLIC include/glad/)

add_library(stb_image external/stb_image/stb_image.cpp include/stb_image/stb_image.h)
target_include_directories(stb_image PUBLIC include/stb_image)


find_package(OpenGL REQUIRED)

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")


if(LINUX)
	set(OPEN_GL GL dl pthread X11)
elseif(WIN32)
	set(OPEN_GL opengl32)
endif()

set(LIBS glfw3 ${OPEN_GL} assimp stb_image glad)


###########



file(GLOB_RECURSE sources src/*.cpp src/*.c src/*.h src/*.hpp)
file(GLOB_RECURSE data	data/models/*/* data/shaders/*)


link_directories(${CMAKE_SOURCE_DIR}/libs)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} ${LIBS})

add_custom_command(
	TARGET ${PROJECT_NAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	   ${CMAKE_SOURCE_DIR}/data/ ${CMAKE_BINARY_DIR}/data)

# Copy dlls
if(WIN32)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${PROJECT_SOURCE_DIR}/libs/dlls"
			$<TARGET_FILE_DIR:${PROJECT_NAME}>)
		
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${PROJECT_SOURCE_DIR}/data"
			$<TARGET_FILE_DIR:${PROJECT_NAME}>/data)
			

endif()

#target_link_libraries(${PROJECT_NAME} PRIVATE glad)
#target_link_libraries(${PROJECT_NAME} PRIVATE stb_image)
