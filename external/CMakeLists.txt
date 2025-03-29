
set(IMGUI_SOURCES
    imgui/imconfig.h
    imgui/imgui.h
    imgui/imgui_internal.h
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h

    imgui/imgui.cpp
    # imgui/imgui_demo.cpp
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