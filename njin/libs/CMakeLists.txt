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
		glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6 EXTENSIONS GL_ARB_bindless_texture GL_EXT_texture_compression_s3tc)
	endif()
endif()


find_package(glm 1.0.1 QUIET)
if (NOT glm_FOUND)
	FetchContent_Declare(
		glm
		GIT_REPOSITORY 	https://github.com/g-truc/glm
		GIT_TAG			1.0.1
		GIT_SHALLOW		TRUE
		GIT_PROGRESS	TRUE
	)
	FetchContent_GetProperties(glm)
	if (NOT glm_POPULATED)
		message("Fetching glm")
		FetchContent_MakeAvailable(glm)

		# add_subdirectory("${glm_SOURCE_DIR}" TEMP_TEST_DIRECTORY_GLAD)
	endif()
endif()