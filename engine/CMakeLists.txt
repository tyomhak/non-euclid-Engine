cmake_minimum_required(VERSION 3.28)

project(NJIN)

set(NJIN_SOURCE_DIR "src")

set(NJIN_INCLUDE_DIRS 
    src
    src/events
    src/platform
    src/platform/OpenGL
)

set(NJIN_SOURCES
    src/application.cpp
    src/application.hpp 
    src/core.hpp
    src/window.hpp
    src/layer.hpp
    src/layer.cpp
    src/layer_stack.hpp
    src/layer_stack.cpp

    src/events/event.hpp
    src/events/key_event.hpp
    src/events/mouse_event.hpp
    src/events/window_event.hpp

    
    src/platform/OpenGL/GLWindow.cpp
    src/platform/OpenGL/GLWindow.hpp
    
    )

# set(SHADERS_SOURCES 
#     data/shaders/object.vert
#     data/shaders/object.frag
# )


# GLFW
find_package(glfw3 3.4 QUIET)
if (NOT glfw3_FOUND)
	FetchContent_Declare(
		glfw3
		# DOWNLOAD_EXTRACT_TIMESTAMP OFF
		URL https://github.com/glfw/glfw/archive/refs/tags/3.4.tar.gz
	)
	FetchContent_GetProperties(glfw3)
	if (NOT glfw3_POPULATED)
		set(FETCHCONTENT_QUIET NO)
		FetchContent_MakeAvailable(glfw3)
		# FetchContent_Populate(glfw3)
		# add_subdirectory(${glfw3_SOURCE_DIR} ${glfw3_BINARY_DIR})
	endif()
endif()

# OpenGL
find_package(OpenGL REQUIRED)

# GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad
    GIT_TAG        v2.0.6
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    message("Fetching glad")
    FetchContent_MakeAvailable(glad)

    add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
    glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6 EXTENSIONS GL_ARB_bindless_texture GL_EXT_texture_compression_s3tc)
endif()



# add_executable(njin ${NJIN_SOURCES})
add_library(NJIN ${NJIN_SOURCES})
target_include_directories(NJIN PUBLIC ${NJIN_INCLUDE_DIRS})
set_target_properties(NJIN PROPERTIES FOLDER "NJIN")

target_link_libraries(NJIN PRIVATE glad)
target_link_libraries(NJIN PRIVATE glfw)

add_library(NJIN::NJIN ALIAS NJIN)


# add_executable(nonEuclid ${IMGUI_SOURCES} ${SOURCES} )
# target_include_directories(nonEuclid PRIVATE ${INCLUDE_DIRS})
# target_link_libraries(nonEuclid PRIVATE glfw)
# target_link_libraries(nonEuclid PRIVATE glad)
# target_link_libraries(nonEuclid PRIVATE glm)
# target_link_libraries(nonEuclid PRIVATE imgui_lib)
# target_link_libraries(nonEuclid PRIVATE assimp)



# # Copy Shaders/Compute.glsl to the same directory as the executable
# add_custom_command(
#     TARGET nonEuclid POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_SOURCE_DIR}/nonEuclid/data
#         $<TARGET_FILE_DIR:nonEuclid>/data
# )