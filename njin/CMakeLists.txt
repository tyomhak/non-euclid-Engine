project(NJIN)

add_library(NJIN)

target_sources(NJIN PRIVATE
    src/application.cpp
    src/window.cpp
    src/input.cpp
    src/layer.cpp
    src/layer_stack.cpp
    src/ui/ui_layer.cpp
    src/platform/OpenGL/GLKeyConverter.cpp
    src/platform/OpenGL/GLWindow.cpp
    src/platform/OpenGL/GLInput.cpp
    src/render/GL/GLRenderContext.cpp
    src/render/GL/GLShader.cpp
)

target_include_directories(NJIN PUBLIC
    src
    src/ui
    src/events
    src/platform
    src/platform/OpenGL
    src/render
    src/utils
)

target_link_libraries(NJIN
    PUBLIC glad
    PRIVATE glfw
    PUBLIC imgui_lib
    PUBLIC glm::glm
)

# set_target_properties(NJIN PROPERTIES FOLDER "NJIN_TEST_DIRECTORY")

add_library(NJIN::NJIN ALIAS NJIN)


# set(NJIN_SOURCE_DIR "src")

# set(NJIN_INCLUDE_DIRS 
#     src
#     src/ui
#     src/events
#     src/platform
#     src/platform/OpenGL
#     src/render
#     src/utils
# )

# set(NJIN_SOURCES
#     src/application.hpp
#     src/application.cpp  
#     src/core.hpp
#     src/window.hpp
#     src/window.cpp
#     src/input.hpp
#     src/input.cpp
#     src/layer.hpp
#     src/layer.cpp
#     src/layer_stack.hpp
#     src/layer_stack.cpp

#     src/ui/ui_layer.hpp
#     src/ui/ui_layer.cpp
#     src/ui/ImGuiConverter.hpp
    
#     src/events/event.hpp
#     src/events/key_event.hpp
#     src/events/key_codes.hpp
#     src/events/mouse_event.hpp
#     src/events/window_event.hpp

    
#     # src/render/render_context.hpp

#     src/platform/OpenGL/GLKeyConverter.hpp
#     src/platform/OpenGL/GLKeyConverter.cpp
#     src/platform/OpenGL/GLWindow.cpp
#     src/platform/OpenGL/GLWindow.hpp
#     src/platform/OpenGL/GLInput.hpp
#     src/platform/OpenGL/GLInput.cpp

    
#     src/render/renderer.hpp
#     src/render/GL/GLRenderContext.hpp
#     src/render/GL/GLRenderContext.cpp
#     src/render/GL/GLShader.hpp
#     src/render/GL/GLShader.cpp
    
#     src/utils/logging.hpp
#     src/utils/duration.hpp
# )

# add_library(NJIN ${NJIN_SOURCES})
# target_include_directories(NJIN PUBLIC ${NJIN_INCLUDE_DIRS})
# set_target_properties(NJIN PROPERTIES FOLDER "NJIN")

# target_link_libraries(NJIN PUBLIC glad)
# target_link_libraries(NJIN PRIVATE glfw)
# target_link_libraries(NJIN PUBLIC imgui_lib)
# target_link_libraries(NJIN PUBLIC glm)

# add_library(NJIN::NJIN ALIAS NJIN)