include(ExternalProject)


set(SOURCE_DIR "src")

set(INCLUDE_DIRS 
    src
    src/events
    src/platform
    src/platform/OpenGL
)

set(SOURCES
    src/main.cpp

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

add_executable(njin ${SOURCES})
target_include_directories(njin PRIVATE ${INCLUDE_DIRS})
target_link_libraries(njin PRIVATE glad)
target_link_libraries(njin PRIVATE glfw)

# add_executable(nonEuclid ${IMGUI_SOURCES} ${SOURCES} )
# target_include_directories(nonEuclid PRIVATE ${INCLUDE_DIRS})
# target_link_libraries(nonEuclid PRIVATE glfw)
# target_link_libraries(nonEuclid PRIVATE glad)
# target_link_libraries(nonEuclid PRIVATE glm)
# target_link_libraries(nonEuclid PRIVATE imgui_lib)
# target_link_libraries(nonEuclid PRIVATE assimp)
 

set(RESOURCE_FILES
  resourcefile.txt
  appresourcedir/appres.txt)

set_target_properties(njin PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:njin>"
                                               VS_DEBUGGER_COMMAND           "$<TARGET_FILE:njin>"
                                               VS_DEBUGGER_ENVIRONMENT       "PATH=%PATH%;${CMAKE_PREFIX_PATH}/bin"
                                               RESOURCE "${RESOURCE_FILES}"
)



# # Copy Shaders/Compute.glsl to the same directory as the executable
# add_custom_command(
#     TARGET nonEuclid POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_SOURCE_DIR}/nonEuclid/data
#         $<TARGET_FILE_DIR:nonEuclid>/data
# )