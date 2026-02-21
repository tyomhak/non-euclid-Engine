include(FetchContent)

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
	endif()
endif()

find_package(OpenGL REQUIRED)

find_package(glad QUIET)
if (NOT glad_FOUND)
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
		glad_add_library(glad 
			REPRODUCIBLE 
			EXCLUDE_FROM_ALL 
			LOADER 
			API gl:core=4.6 
			EXTENSIONS 
				GL_ARB_bindless_texture 
				GL_EXT_texture_compression_s3tc
		)
	endif()
endif()


find_package(glm 1.0.3 QUIET)
if (NOT glm_FOUND)
	FetchContent_Declare(
		glm
		GIT_REPOSITORY 	https://github.com/g-truc/glm
		GIT_TAG			1.0.3
		GIT_SHALLOW		TRUE
		GIT_PROGRESS	TRUE
	)
	FetchContent_GetProperties(glm)
	if (NOT glm_POPULATED)
		message("Fetching glm")
		FetchContent_MakeAvailable(glm)
	endif()
endif()


set(IMGUI_SOURCES
    imgui/imconfig.h
    imgui/imgui.h
    imgui/imgui_internal.h
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h

    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp

    imgui/backends/imgui_impl_glfw.h
    imgui/backends/imgui_impl_opengl3.h

    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui_lib ${IMGUI_SOURCES})
target_include_directories(imgui_lib PUBLIC imgui/ imgui/backends/)
target_link_libraries(imgui_lib glfw)

set_target_properties(imgui_lib PROPERTIES FOLDER "Dependencies")
set_target_properties(glfw PROPERTIES FOLDER "Dependencies")
set_target_properties(glad PROPERTIES FOLDER "Dependencies")
set_target_properties(glm PROPERTIES FOLDER "Dependencies")
