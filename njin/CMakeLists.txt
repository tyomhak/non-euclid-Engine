cmake_minimum_required(VERSION 3.28)

project(NJIN)

set(NJIN_SOURCE_DIR "src")

set(NJIN_INCLUDE_DIRS 
    src
    # src/ui
    src/events
    src/platform
    src/platform/OpenGL
)

set(NJIN_SOURCES
    src/application.hpp
    src/application.cpp  
    src/core.hpp
    src/window.hpp
    src/layer.hpp
    src/layer.cpp
    src/layer_stack.hpp
    src/layer_stack.cpp

    src/ui/ui_layer.hpp
    src/ui/ui_layer.cpp
    src/ui/ImGuiConverter.hpp
    
    src/events/event.hpp
    src/events/key_event.hpp
    src/events/key_codes.hpp
    src/events/mouse_event.hpp
    src/events/window_event.hpp

    src/platform/OpenGL/GLWindow.cpp
    src/platform/OpenGL/GLWindow.hpp
    src/platform/OpenGL/GLKeyConverter.hpp
)

# set(SHADERS_SOURCES 
#     data/shaders/object.vert
#     data/shaders/object.frag
# )

add_subdirectory(libs)

# add_executable(njin ${NJIN_SOURCES})
add_library(NJIN ${NJIN_SOURCES})
target_include_directories(NJIN PUBLIC ${NJIN_INCLUDE_DIRS})
set_target_properties(NJIN PROPERTIES FOLDER "NJIN")

target_link_libraries(NJIN PRIVATE glad)
target_link_libraries(NJIN PRIVATE glfw)
target_link_libraries(NJIN PRIVATE imgui_lib)


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