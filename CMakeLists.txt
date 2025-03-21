cmake_minimum_required(VERSION 3.28)
include(FetchContent)

project(nonEuclid)

set(CMAKE_CXX_STANDARD 20)

#
# Dependencies
#

# GLFW
find_package(glfw3 3.4 QUIET)
if (NOT glfw3_FOUND)
	FetchContent_Declare(
		glfw3
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
		URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
	)
	FetchCOntent_GetProperties(glfw3)
	if (NOT glfw3_POPULATED)
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(glfw3)
		add_subdirectory(${glfw3_SOURCE_DIR} ${glfw3_BINARY_DIR})
	endif()
endif()



# OpenGL
find_package(OpenGL REQUIRED)

# GLAD
FetchContent_Declare(
    glad
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/Dav1dde/glad/archive/refs/tags/v2.0.8.zip
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(glad)

    add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
    glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6)
endif()
set_target_properties(glad PROPERTIES FOLDER "Dependencies")



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
        FetchContent_Populate(glm)
        add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
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
		FetchContent_Populate(assimp)
		add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
	endif()
endif()
set_target_properties(assimp PROPERTIES FOLDER "Dependencies")


# file(GLOB IMGUI_SRC external/imgui/*.cpp  include/imgui/*.h )
# add_library(imgui SHARED ${IMGUI_SRC})
# target_include_directories(imgui PUBLIC include/imgui)

# IMGUI




# find_package(imgui 1.91.9b QUIET)
# if (NOT imgui_FOUND)
#     FetchContent_Declare(
#             imgui
#             DOWNLOAD_EXTRACT_TIMESTAMP OFF
#             URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.9b.zip
#     )
#     FetchContent_GetProperties(imgui)
#     if (NOT imgui_POPULATED)
#         set(FETCHCONTENT_QUIET NO)
#         FetchContent_Populate(imgui)
#         add_subdirectory(${imgui_SOURCE_DIR} ${imgui_BINARY_DIR})
#     endif()
# endif()
# set_target_properties(imgui PROPERTIES FOLDER "Dependencies")


#
# Projects
#
add_subdirectory(external)
add_subdirectory(nonEuclid)









# SET(sampleName nonEuclid)

# project(NonEuclid VERSION 0.1.0 LANGUAGES C CXX)

# SET(DEBUG_MODE "-g")
# SET(CMAKE_CXX_FLAGS "${DEBUG_MODE}")

# if(UNIX AND NOT APPLE)
# 	set(LINUX TRUE)
# endif()

# include_directories(${CMAKE_SOURCE_DIR}/include)

# # libraries #
# #############
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/tools/cmake/)

# add_library(glad external/glad/glad.c include/glad/glad.h include/KHR/khrplatform.h)
# target_include_directories(glad PUBLIC include/glad/)

# add_library(stb_image external/stb_image/stb_image.cpp include/stb_image/stb_image.h)
# target_include_directories(stb_image PUBLIC include/stb_image)

# #file(GLOB IMGUI_SRC external/imgui/*.cpp  include/imgui/*.h )
# #add_library(imgui SHARED ${IMGUI_SRC})
# #target_include_directories(imgui PUBLIC include/imgui)

# add_library(imgui external/imgui/imgui.cpp external/imgui/imgui_demo.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_impl_glfw.cpp external/imgui/imgui_impl_opengl3.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp include/imgui/imgui.h include/imgui/imconfig.h include/imgui/imgui_impl_glfw.h include/imgui/imgui_impl_opengl3.h include/imgui/imgui_internal.h include/imgui/imstb_rectpack.h include/imgui/imstb_textedit.h include/imgui/imstb_truetype.h)
# target_include_directories(imgui PUBLIC include/imgui)

# find_package(OpenGL REQUIRED)

# find_package(GLM REQUIRED)
# message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# find_package(GLFW3 REQUIRED)
# message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# find_package(ASSIMP REQUIRED)
# message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")


# if(LINUX)
# 	set(OPEN_GL GL dl pthread X11)
# elseif(WIN32)
# 	set(OPEN_GL opengl32)
# endif()

# set(LIBS glfw3 ${OPEN_GL} assimp stb_image glad imgui)


# ###########



# file(GLOB_RECURSE sources src/*.cpp src/*.c src/*.h src/*.hpp)
# file(GLOB_RECURSE data	data/models/*/* data/shaders/*)


# link_directories(${CMAKE_SOURCE_DIR}/libs)

# add_executable(${PROJECT_NAME} ${sources})

# target_link_libraries(${PROJECT_NAME} ${LIBS})

# add_custom_command(
# 	TARGET ${PROJECT_NAME} PRE_BUILD
# 	COMMAND ${CMAKE_COMMAND} -E copy_directory
# 	   ${CMAKE_SOURCE_DIR}/data/ ${CMAKE_BINARY_DIR}/data)

# # Copy dlls
# if(WIN32)
# 	add_custom_command(
# 		TARGET ${PROJECT_NAME} POST_BUILD
# 		COMMAND ${CMAKE_COMMAND} -E copy_directory
# 			"${PROJECT_SOURCE_DIR}/libs/dlls"
# 			$<TARGET_FILE_DIR:${PROJECT_NAME}>)
		
# 	add_custom_command(
# 		TARGET ${PROJECT_NAME} POST_BUILD
# 		COMMAND ${CMAKE_COMMAND} -E copy_directory
# 			"${PROJECT_SOURCE_DIR}/data"
# 			$<TARGET_FILE_DIR:${PROJECT_NAME}>/data)
			

# endif()

# #target_link_libraries(${PROJECT_NAME} PRIVATE glad)
# #target_link_libraries(${PROJECT_NAME} PRIVATE stb_image)
