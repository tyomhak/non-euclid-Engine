include(ExternalProject)


set(SOURCE_DIR "src")

set(SOURCES
    src/utils/stb_image.h
    src/utils/stb_image.cpp
    
    src/physics/BoundaryBox.h
    src/physics/CollisionHandler.h
    src/physics/Ray.h


    src/Camera.h

    src/Engine.h
    src/Engine.cpp
    
    src/EventHandler.h
    src/EventHandler.cpp

    src/Level.h

    src/Mesh.h

    src/Model.h
    src/Model.cpp
    
    src/Move.h

    src/ObjHandler.h
    src/ObjectHandler.cpp

    src/Object.h
    src/Object.cpp

    src/Player.h

    src/Portal.h
    src/Portal.cpp

    src/Shader.h
    src/Shader.cpp

    src/UI.h
    
    src/Window.h
    src/Window.cpp
    
    src/main.cpp

    
    )

set(SHADERS_SOURCES 
    data/shaders/object.vert
    data/shaders/object.frag
)

add_executable(nonEuclid ${IMGUI_SOURCES} ${SOURCES} )
target_include_directories(nonEuclid PRIVATE src/physics)
target_link_libraries(nonEuclid PRIVATE glfw)
target_link_libraries(nonEuclid PRIVATE glad)
target_link_libraries(nonEuclid PRIVATE glm)
target_link_libraries(nonEuclid PRIVATE imgui_lib)
target_link_libraries(nonEuclid PRIVATE assimp)
 

set(RESOURCE_FILES
  resourcefile.txt
  appresourcedir/appres.txt)

set_target_properties(nonEuclid PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:nonEuclid>"
                                               VS_DEBUGGER_COMMAND           "$<TARGET_FILE:nonEuclid>"
                                               VS_DEBUGGER_ENVIRONMENT       "PATH=%PATH%;${CMAKE_PREFIX_PATH}/bin"
                                               RESOURCE "${RESOURCE_FILES}"
)


# Copy Shaders/Compute.glsl to the same directory as the executable
add_custom_command(
    TARGET nonEuclid POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/nonEuclid/data
        $<TARGET_FILE_DIR:nonEuclid>/data
)