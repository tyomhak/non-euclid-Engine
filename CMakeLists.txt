cmake_minimum_required(VERSION 3.28)
include(FetchContent)

project(nonEuclid)

set(CMAKE_CXX_STANDARD 20)



set(NEW false)
if (NEW)
	add_subdirectory(engine)
	add_subdirectory(game)

else()
	#
	# Dependencies
	#

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


	# GLM
	find_package(glm 1.0.1 QUIET)
	if (NOT glm_FOUND)
		FetchContent_Declare(
				glm
				DOWNLOAD_EXTRACT_TIMESTAMP OFF
				URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip
		)
		FetchContent_GetProperties(glm)
		if (NOT glm_POPULATED)
			set(FETCHCONTENT_QUIET NO)
			FetchContent_MakeAvailable(glm)
			# FetchContent_Populate(glm)
			# add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
		endif()
	endif()
	set_target_properties(glm PROPERTIES FOLDER "Dependencies")


	# ASSIMP
	find_package(assimp 5.4.3 QUIET)
	if (NOT assimp_FOUND)
		FetchContent_Declare(
			assimp
			DOWNLOAD_EXTRACT_TIMESTAMP OFF
			URL https://github.com/assimp/assimp/archive/refs/tags/v5.4.3.zip
		)
		FetchContent_GetProperties(assimp)
		if (NOT assimp_POPULATED)
			set(FETCHCONTENT_QUET NO)
			set(ASSIMP_BUILD_TESTS NO)
			FetchContent_MakeAvailable(assimp)

			# FetchContent_Populate(assimp)
			# add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
			# add_subdirectory("${assimp_SOURCE_DIR}/cmake" assimp_cmake)
			# assimp_add_library(assimp REPRODUCIBLE EXCLUDE_FROM_ALL)
		endif()
	endif()
	set_target_properties(assimp PROPERTIES FOLDER "Dependencies")

	#
	# Projects
	#
	SET (NJIN FALSE)
	if (NJIN)
		add_subdirectory(engine)
	else()
		add_subdirectory(external)
		add_subdirectory(nonEuclid)
	endif()

endif()