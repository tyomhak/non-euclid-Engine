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
    src/input.hpp
    src/input.cpp
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

    src/platform/OpenGL/GLKeyConverter.hpp
    src/platform/OpenGL/GLKeyConverter.cpp
    src/platform/OpenGL/GLWindow.cpp
    src/platform/OpenGL/GLWindow.hpp
    src/platform/OpenGL/GLInput.hpp
    src/platform/OpenGL/GLInput.cpp
)

add_subdirectory(libs)

add_library(NJIN ${NJIN_SOURCES})
target_include_directories(NJIN PUBLIC ${NJIN_INCLUDE_DIRS})
set_target_properties(NJIN PROPERTIES FOLDER "NJIN")

target_link_libraries(NJIN PRIVATE glad)
target_link_libraries(NJIN PRIVATE glfw)
target_link_libraries(NJIN PRIVATE imgui_lib)
target_link_libraries(NJIN PUBLIC glm)


add_library(NJIN::NJIN ALIAS NJIN)