include(ExternalProject)


set(SOURCE_DIR "src")

set(SOURCES
    src/stb_image.h
    src/stb_image.cpp
    
    src/BoundaryBox.h
    src/Camera.h
    src/CollisionHandler.h
    src/Engine.h
    src/EventHandler.h
    src/IncludeHeaders.h
    src/Level.h
    src/Mesh.h
    src/Model.h
    src/Move.h
    src/ObjHandler.h
    src/Object.h
    src/Player.h
    src/Portal.h
    src/PositionUi.h
    src/Ray.h
    src/Shader.h
    src/UI.h
    src/UiWindow.h
    src/Window.h
    src/main.cpp
    )

add_executable(nonEuclid ${IMGUI_SOURCES} ${SOURCES} )
target_link_libraries(nonEuclid glfw)
target_link_libraries(nonEuclid glad)
target_link_libraries(nonEuclid glm)
target_link_libraries(nonEuclid imgui_lib)
target_link_libraries(nonEuclid assimp)


# Copy Shaders/Compute.glsl to the same directory as the executable
add_custom_command(
    TARGET nonEuclid POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/nonEuclid/data
        $<TARGET_FILE_DIR:nonEuclid>/data
)
